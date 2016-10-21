/*******************************************************************************
Copyright (C) 2016  OLogN Technologies AG
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*******************************************************************************/

#ifndef BASELIB2_H
#define BASELIB2_H

//#include <iostream>
//#include <memory>
#include <deque>
#include <list>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>

#include "hare/hare.h"

using namespace std;

#define BASELIB_MB

#ifdef _MSC_VER
#define LIKELY_BRANCH_( X ) (X)
#else
#define LIKELY_BRANCH_( X ) __builtin_expect( (X), 1 )
#endif


#if _MSC_VER
#define ALIGN(n)      __declspec(align(n))
#define NOINLINE      __declspec(noinline)
#define FORCE_INLINE	__forceinline
#elif __GNUC__
#define NOINLINE      __attribute__ ((noinline))
#define	FORCE_INLINE inline __attribute__((always_inline))
#define ALIGN(n)      __attribute__ ((aligned(n))) 
#else
#define	FORCE_INLINE inline
#define NOINLINE
#define ALIGN(n)
#warning ALIGN, FORCE_INLINE and NOINLINE may not be properly defined
#endif

enum WIRE_TYPE
{
    VARINT = 0,
    FIXED_64_BIT = 1,
    LENGTH_DELIMITED = 2,
    START_GROUP = 3,
    END_GROUP = 4,
    FIXED_32_BIT = 5,
};

constexpr
uint64_t sint64ToUint64(int64_t src)
{
    return (src << 1) ^ (src >> 63);
}

constexpr
int64_t uint64ToSint64(uint64_t src)
{
    return (src >> 1) ^ -static_cast<int64_t>(src & 1);
}


uint8_t* deserializeHeaderFromString(int& fieldNumber, int& type, uint8_t* buff);


///////////////////////////   WIRE_TYPE::VARINT      ////////////////////////////////////

/*
    mb: serializeToStringVariantUint64 will read at most 10 bytes from buffer
    However, if there is risk of buffer being overread, a null byte must be
    set after the last buffer position, to force stop the algorithm.
*/

uint8_t* serializeToStringVariantUint64(uint64_t value, uint8_t* buff);
uint8_t* deserializeFromStringVariantUint64(uint64_t& value, uint8_t* buff);


///////////////////////////   WIRE_TYPE::FIXED_64_BIT      ////////////////////////////////////

uint8_t* serializeToStringFixedUint64(uint64_t value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint64(uint64_t& value, uint8_t* buff);

///////////////////////////     WIRE_TYPE::FIXED_32_BIT    ////////////////////////////////////

uint8_t* serializeToStringFixedUint32(uint32_t value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint32(uint32_t& value, uint8_t* buff);

///////////////////////////     WIRE_TYPE::LENGTH_DELIMITED    ////////////////////////////////////

uint8_t* serializeLengthDelimitedHeaderToString(int fieldNumber, size_t valueSize, uint8_t* buff);


///// inline
inline uint8_t* serializeHeaderToString(int fieldNumber, int wire_type, uint8_t* buff)
{
    int key = (fieldNumber << 3) | wire_type;
    return serializeToStringVariantUint64(key, buff);
}

//MB begin
constexpr size_t getUnsignedVarIntSize(uint64_t value)
{
    return (value < (uint64_t(1) << 7)) ? 1 : (
        (value < (uint64_t(1) << 14)) ? 2 : (
            (value < (uint64_t(1) << 21)) ? 3 : (
                (value < (uint64_t(1) << 28)) ? 4 : (
                    (value < (uint64_t(1) << 35)) ? 5 : (
                        (value < (uint64_t(1) << 42)) ? 6 : (
                            (value < (uint64_t(1) << 49)) ? 7 : (
                                (value < (uint64_t(1) << 56)) ? 8 : (
                                    (value < (uint64_t(1) << 63) ? 9 : 10)))))))));
}

constexpr
size_t getSignedVarIntSize(int64_t value)
{
    return getUnsignedVarIntSize(sint64ToUint64(value));
}

constexpr size_t getTagSize(int tag) { return getUnsignedVarIntSize(tag << 3); }
constexpr size_t getFixedSize(float) { return 4; }
constexpr size_t getFixedSize(double) { return 8; }


/*
    mb: Input / output stream using pool of buffers.
    General idea is to aisolate / syncronize io threads from event queue thread
    using a pool of fixed size buffers.
    A pool of fixed size buffers allow to have them preallocated and reused them, 
    but requires some tricks when a message does not fit in a single buffer and needs
    to be splitted.

    This implementation tries to minimize copy, based on following facts:
    1. The encoding functions for a single value need a max buffer size of 
        8 bytes for fixed64 or 10 bytes for varint.
    2. Each element at protobuf is encoded as a varint tag followed by the value.
        So the max size for encoding a non-string is 20 bytes.
    3. To encoding / decoding strings need to copy to / from buffer the content
        of the string anyway.

    
    To avoid extra checks at encoding, we always verify we have 20 bytes left at the current buffer,
    so we can be sure current element will fit inside current buffer.
    If we don't have 20 bytes, we just beging with a new buffer.

    At decoding we need to handle two situations, one is normal (good working) buffer swap,
    when one element to be read begins in current buffer and ends in the next one.
    Second problem is how to prevent a read after the end of the buffer on a broken packet.

    To do so, at decoding we copy the first 20 bytes from next buffer at the end of the current buffer,
    And keep marks where this buffer data ends (softEndPtr), and where 'extended' data from next buffer
    ends (hardEndPtr).
    After 'hardEndPtr', we write a 'buffer stop' of zeros to stop decoder from overrun.
    If current data pointer is before 'softEndPtr', we can be sure current element can be read from
    current (possible extended) buffer. 
    If current data pointer is between 'softEndPtr' and 'hardEndPtr' we are reading into data copied from
    next buffer, so we can just change our pointer into next buffer and go on.
    If current data pointer is after 'hardEndPtr' the previous data was broken, and decoder stoped
    because of zeros at the end.

    This will allow to handle arbitrary size messages using one or more fixed size buffers,
    and encoding / decoding on the buffer, without extra copy.

*/

const size_t BUFFER_GAP_BEGIN = 20;
const size_t BUFFER_GAP_END = 9;
const size_t BUFFER_SIZE = 1024;
const size_t MAX_STRING_SIZE = std::string().max_size();

/*
    Every buffer must has BUFFER_GAP_BEGIN plus BUFFER_GAP_END unused bytes at the end,
    to allow for required manipulation on the buffers
*/

struct BufferDescriptor {
public:
    uint8_t* buffer;
    size_t bufferSize;
    size_t dataSize = 0;

    BufferDescriptor(uint8_t* buffer, size_t bufferSize) :
        buffer(buffer), bufferSize(bufferSize)
        {
        	HAREASSERT(bufferSize > BUFFER_GAP_BEGIN + BUFFER_GAP_END);
        }

    void setDataSize(size_t dataSize)
    {
        HAREASSERT(dataSize <= getMaxDataSize());
        this->dataSize = dataSize;
    }

    size_t getMaxDataSize() const
    {
        return bufferSize - BUFFER_GAP_BEGIN - BUFFER_GAP_END; 
    }

    size_t copyBufferOverlapAndMakeBufferStop(const BufferDescriptor& other)
    {
        HAREASSERT(dataSize + BUFFER_GAP_BEGIN + BUFFER_GAP_END <= bufferSize);
        size_t gap = min(BUFFER_GAP_BEGIN, other.dataSize);
        memcpy(&buffer[dataSize], other.buffer, gap);
        memset(&buffer[dataSize + gap], 0, BUFFER_GAP_END);
        
        return gap;
    }

    void makeBufferStop()
    {
        HAREASSERT(dataSize + BUFFER_GAP_BEGIN + BUFFER_GAP_END <= bufferSize);
        memset(&buffer[dataSize], 0, BUFFER_GAP_END);
    }
};

typedef deque<BufferDescriptor> BufferGroup;

template<class T>
bool areEqual(const BufferGroup& left, T itBegin, T itEnd)
{
    BufferGroup::const_iterator leftIt = left.begin();
    if (leftIt == left.end())
        return itBegin == itEnd;
    uint8_t* dataPtr = leftIt->buffer;
    uint8_t* endPtr = leftIt->buffer + leftIt->dataSize;
    while (itBegin != itEnd) {
        if (dataPtr == endPtr) {
            ++leftIt;
            if (leftIt == left.end())
                return false;
            dataPtr = leftIt->buffer;
            endPtr = leftIt->buffer + leftIt->dataSize;
        }
        if (*dataPtr != *itBegin)
            return false;

        ++dataPtr;
        ++itBegin;
    }

    return dataPtr == endPtr && ++leftIt == left.end();
}
    

class FakeBufferManager {
    const size_t bufferSize;
    list<void*> buffersInUse;
    list<void*> buffersFree;
public:

    FakeBufferManager(size_t bufferSize) : bufferSize(bufferSize) {}

    BufferDescriptor getFreeBuffer() {
        if (buffersFree.empty()) {
            void* ptr = malloc(BUFFER_SIZE);
            buffersFree.push_back(ptr);
        }

        void* ptr = buffersFree.front();
        buffersFree.pop_front();
        buffersInUse.push_back(ptr);
        return BufferDescriptor(static_cast<uint8_t*>(ptr), BUFFER_SIZE);
    }

    void releaseBuffers(const BufferGroup& toRelease) {
        for (auto each : toRelease) {
            buffersInUse.remove(each.buffer);
            buffersFree.push_back(each.buffer);
        }
    }

    ~FakeBufferManager() {
        for (auto each : buffersInUse)
            free(each);
        for (auto each : buffersFree)
            free(each);
    }
};


class OProtobufStream
{
private:
    FakeBufferManager& manager;
    BufferGroup bufferSet;

    uint8_t* beginPtr = nullptr;
    uint8_t* dataPtr = nullptr;
    uint8_t* endPtr = nullptr;


    void writeData(const uint8_t* data, size_t size)
    {
        size_t left = size;
        const uint8_t* ptr = data;

        while (left > static_cast<size_t>(endPtr - dataPtr)) {
            size_t sz = endPtr - dataPtr;
            memcpy(dataPtr, ptr, sz);
            left -= sz;
            ptr += sz;
            dataPtr += sz;
            changeBuffer();
        }

        //HAREASSERT(left <= static_cast<size_t>(endPtr - dataPtr));
        HAREASSERT(data + size == ptr + left);

        memcpy(dataPtr, ptr, left);
        dataPtr += left;
    }


    void changeBuffer()
    {
        if (endPtr <= dataPtr) {
            if(!bufferSet.empty())
                bufferSet.back().setDataSize(dataPtr - beginPtr);

            BufferDescriptor& current = manager.getFreeBuffer();
            beginPtr = current.buffer;
            dataPtr = beginPtr;
            endPtr = beginPtr + current.getMaxDataSize();

            bufferSet.push_back(current);
        }
    }


public:
    OProtobufStream(FakeBufferManager& manager) :
        manager(manager) {}
    
    void flush()
    {
        if(!bufferSet.empty())
            bufferSet.back().setDataSize(dataPtr - beginPtr);

        beginPtr = nullptr;
        dataPtr = nullptr;
        endPtr = nullptr;
    }

    void finish()
    {
        flush();
    }

    const BufferGroup& getBufferSet() const
    {
        return bufferSet;
    }

    void writeInt(int fieldNumber, int64_t x)
    {
        changeBuffer();
        dataPtr = serializeHeaderToString(fieldNumber, WIRE_TYPE::VARINT, dataPtr);
        uint64_t unsig = sint64ToUint64(x);
        dataPtr = serializeToStringVariantUint64(unsig, dataPtr);
    }
    
    void writeUInt(int fieldNumber, uint64_t x)
    {
        changeBuffer();
        dataPtr = serializeHeaderToString(fieldNumber, WIRE_TYPE::VARINT, dataPtr);
        dataPtr = serializeToStringVariantUint64(x, dataPtr);
    }

    void writeDouble(int fieldNumber, double x)
    {
        changeBuffer();
        dataPtr = serializeHeaderToString(fieldNumber, WIRE_TYPE::FIXED_64_BIT, dataPtr);
        dataPtr = serializeToStringFixedUint64(*(uint64_t*)(&x), dataPtr);
    }

    void writeFloat(int fieldNumber, float x)
    {
        changeBuffer();
        dataPtr = serializeHeaderToString(fieldNumber, WIRE_TYPE::FIXED_32_BIT, dataPtr);
        dataPtr = serializeToStringFixedUint32(*(uint32_t*)(&x), dataPtr);
    }

    void writeString(int fieldNumber, const std::string& x)
    {
        changeBuffer();
        size_t sz = min(x.size(), MAX_STRING_SIZE);
        dataPtr = serializeLengthDelimitedHeaderToString(fieldNumber, sz, dataPtr);
        writeData(reinterpret_cast<const uint8_t*>(x.c_str()), sz);
    }

    void writeObjectTagAndSize(int fieldNumber, size_t sz)
    {
        changeBuffer();
        dataPtr = serializeLengthDelimitedHeaderToString(fieldNumber, sz, dataPtr);
    }

    void writePackedSignedVarInt(int64_t x)
    {
        changeBuffer();
        uint64_t unsig = sint64ToUint64(x);
        dataPtr = serializeToStringVariantUint64(unsig, dataPtr);
    }

    void writePackedUnsignedVarInt(uint64_t x)
    {
        changeBuffer();
        dataPtr = serializeToStringVariantUint64(x, dataPtr);
    }

    void writePackedDouble(double x)
    {
        changeBuffer();
        dataPtr = serializeToStringFixedUint64(*(uint64_t*)(&x), dataPtr);
    }

    void writePackedFloat(float x)
    {
        changeBuffer();
        dataPtr = serializeToStringFixedUint32(*(uint32_t*)(&x), dataPtr);
    }
};

inline
void writeFile(FILE* file, const BufferGroup& buffSet)
{
    for (auto each : buffSet) {
        fwrite(each.buffer, each.dataSize, 1, file);
    }
}


inline
BufferGroup readFile(FILE* file, FakeBufferManager& manager)
{
    BufferGroup bufferPool;
    bool isLast = false;
    while (!isLast) {
        uint8_t* ptr = static_cast<uint8_t*>(malloc(BUFFER_SIZE));

        BufferDescriptor buffer = manager.getFreeBuffer();
        size_t maxRead = buffer.getMaxDataSize();
        size_t sz = fread(buffer.buffer, 1, maxRead, file);
        isLast = sz != maxRead;
        buffer.setDataSize(sz);

        bufferPool.push_back(buffer);
    }

    return bufferPool;
}


/*
    Other options, experimental.
    General idea is to avoid buffer size checks as much as possible,
    To do so, we need to tackle two issues.
    First one is normal (good working) buffer swap, when one element is split,
    with the begging in current buffer and the last part in the next buffer.
    Second problem is how to prevent a read after the end of the buffer (on broken packet).

    This implementation handles both cases using extra free space at the end of the buffers.

    We use two 'gaps' at the end of each buffer.
    The real place where valid data from each buffer ends is called 'SoftEnd',
    After this we copy some bytes from the beggining of next buffer, we call this 'HardEnd',
    So data between 'SoftEnd' and 'HardEnd' is duplicate from next buffer,
    so an element we start decoding in current buffer, will always
    end in this same buffer, without need to swap buffers in the middle.
    After the 'HardEnd' we write a block of zero '0' to prevent decoder from reading after
    the end of the buffer on a broken packet.

    Algorithm is as follow, it is always safe to begin to decode.
    After decoding a value, we check our data pointer.
    If it is before 'SoftEnd', nothing to do. If it is between 'SoftEnd' and 'HardEnd'
    we need to change buffers. If it is after 'HardEnd' the data was broken.
*/


class IProtobufStream
{
private:
    BufferGroup::iterator bpIt;
    const BufferGroup::iterator bpItEnd;

    uint8_t* beginPtr = nullptr;
    uint8_t* dataPtr = nullptr;
    uint8_t* softEndPtr = nullptr;
    uint8_t* hardEndPtr = nullptr;
    size_t alreadyRead = 0;

    bool changeBuffer() {
        HAREASSERT(dataPtr <= hardEndPtr);
        if(bpIt != bpItEnd) {

            alreadyRead += dataPtr - beginPtr;
            size_t extra = dataPtr - softEndPtr;

            beginPtr = bpIt->buffer + extra;
            dataPtr = beginPtr;
            softEndPtr = bpIt->buffer + bpIt->dataSize;
            hardEndPtr = softEndPtr;

            auto currentIt = bpIt;
            ++bpIt;

            if(bpIt != bpItEnd) {
                hardEndPtr += currentIt->copyBufferOverlapAndMakeBufferStop(*bpIt);
            }
            else {
                currentIt->makeBufferStop();
            }

            return true;
        }
        else {
       
            return false;
        }
    }

    bool isGood()
    {
        if (dataPtr <= softEndPtr)
            return true;
        else if(hardEndPtr < dataPtr) {
            // TODO invalidate
            return false;
        }
        else // softEndPtr < dataPtr <= hardEndPtr
            return changeBuffer();
    }

    bool readData(char* target, size_t size)
    {
        size_t left = size;
        char* ptr = target;

        HAREASSERT(dataPtr <= hardEndPtr);
        while (left > static_cast<size_t>(hardEndPtr - dataPtr)) {
            size_t sz = hardEndPtr - dataPtr;
            if(target)
                memcpy(ptr, dataPtr, sz);
            left -= sz;
            dataPtr += sz;
            ptr += sz;

            if (!changeBuffer())
                return false;

        }

        HAREASSERT(left <= static_cast<size_t>(hardEndPtr - dataPtr));
        if(target)
            memcpy(ptr, dataPtr, left);
        //left -= left
        dataPtr += left;

        return isGood();
    }

public:

    IProtobufStream(BufferGroup& bp) :
        bpIt(bp.begin()), bpItEnd(bp.end())
        {
            changeBuffer();       
        }

    bool next()
    {
        return true;
    }

    bool isEndOfStream(size_t last) const
    {
        if (last == SIZE_MAX)
            return bpIt == bpItEnd && dataPtr == softEndPtr;
        else
            return alreadyRead + (dataPtr - beginPtr) == last;
    }

    bool readFieldTypeAndID(int& type, int& fieldNumber)
    {
        dataPtr = deserializeHeaderFromString(fieldNumber, type, dataPtr);

        return isGood(); //read past the end of buffer
    }

    bool readVariantInt64(int64_t& x)
    {
        uint64_t preValue;
        dataPtr = deserializeFromStringVariantUint64(preValue, dataPtr);
        x = uint64ToSint64(preValue);

        return isGood(); //read past the end of buffer
    }


    bool readVariantUInt64(uint64_t& x)
    {
        dataPtr = deserializeFromStringVariantUint64(x, dataPtr);

        return isGood(); //read past the end of buffer
    }

    bool readFixed64Bit(double& x)
    {
        uint64_t tmp;
        dataPtr = deserializeFromStringFixedUint64(tmp, dataPtr);
        x = *reinterpret_cast<double*>(&tmp);

        return isGood();
    }

    bool readFixed32Bit(float& x)
    {
        uint32_t tmp;
        dataPtr = deserializeFromStringFixedUint32(tmp, dataPtr);
        x = *reinterpret_cast<float*>(&tmp);

        return isGood();
    }

    bool readString(std::string& x)
    {
        uint64_t size;
        if (readVariantUInt64(size)) {
            if (size <= MAX_STRING_SIZE) {
                x.resize(static_cast<size_t>(size));
                return readData(const_cast<char*>(x.data()), static_cast<size_t>(size));
            }
        }

        return false;
    }

    bool discardData(size_t sz)
    {
        return readData(nullptr, sz);
    }

    size_t makeSubEos(size_t subSize)
    {
        size_t currentIndex = alreadyRead + (dataPtr - beginPtr);
        return currentIndex + subSize;
    }

};

//mb
bool discardUnexpectedField(int fieldType, IProtobufStream& i);

#endif // BASELIB_H

