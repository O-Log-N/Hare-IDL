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

#include <iostream>
#include <memory>
#include <vector>
#include <deque>
#include <list>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <cstring>

using namespace std;

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

namespace bl2
{

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
    return (src >> 1) ^ -(src & 1);
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

    So, the general idea of the encoder is to verify we have 20 bytes left at the current buffer,
    if we don't, begging with a new one.
    The decoder will also check we have at least 20 bytes left in the current buffer,
    if we don't, we copy the bytes left on the current buffer 'before' the first byte of the next buffer.
    To do so, decoder buffers need to have a 'gap' at the front for this.
    Strings are handled in special case, and always copy the content to as many buffers as needed.

    This will allow to handle arbitrary size messages using one or more fixed size buffers,
    and encoding / decoding on the buffer, without extra copy.

    General working concept:
    On the encoding side, encoding is made on the main loop thread over a set of empty buffers,
    when encoding is done, the set of buffers is pased to the io thread for sending.
    On the receive side, io thread receives a message on a set of empty buffers and passes them
    to the main loop thread for decoding.
    In this concept, the buffers are the main object shared between io and main loop threads,
    and the main syncronization point. It should allow a very simple, robust and performing interface.

    However all this buffer managment adds extra work and performance should be checked
*/

const size_t MIN_BUFFER_LEFT = 20;
const size_t BUFFER_SIZE = 1024;

/*
    Every buffer must has MIN_BUFFER_LEFT unused bytes at the begging and
    1 byte at the end.
*/

struct BufferData {
public:
    uint8_t* buffer;
    size_t bufferSize;
    uint8_t* beginPtr;
    uint8_t* endPtr;
    bool isLast;

    BufferData(uint8_t* buffer, size_t bufferSize) :
        buffer(buffer), bufferSize(bufferSize),
        beginPtr(buffer + MIN_BUFFER_LEFT),
        endPtr(buffer + bufferSize - 1),
        isLast(false) {}

    //    BufferData& operator=(const BufferData& other) = default;
    BufferData() : BufferData(0, 0) {}

    bool isValid() const {
        return buffer != 0;
    }
    void reset() {
        beginPtr = buffer + MIN_BUFFER_LEFT;
        endPtr = buffer + bufferSize - 1;
        isLast = false;
    }

    bool needReplace(const uint8_t* dataPtr) const {
        assert(dataPtr != 0);
        size_t left = endPtr - dataPtr;
        return !isLast && left < MIN_BUFFER_LEFT;
    }

    void copyLastFragment(const BufferData& other, const uint8_t* dataPtr) {
        size_t left = other.endPtr - dataPtr;
        assert(left < MIN_BUFFER_LEFT);

        beginPtr -= left;

        memcpy(beginPtr, dataPtr, left);
    }

    void setEnd(size_t dataSize, bool last) {
        isLast = last;
        endPtr = beginPtr + dataSize;
        *endPtr = 0; //null terminate to avoid varint overrun
    }

};

class FakeBufferManager {
    list<BufferData> buffersInUse;
    list<BufferData> buffersFree;
public:
    BufferData getFreeBuffer() {
        if (buffersFree.empty()) {
            uint8_t* ptr = static_cast<uint8_t*>(malloc(BUFFER_SIZE));

            BufferData b(ptr, BUFFER_SIZE);

            buffersInUse.push_back(b);

            return b;
        }
        else {
            BufferData b = buffersFree.front();
            buffersFree.pop_front();
            buffersInUse.push_back(b);
            return b;
        }
    }

    void releaseBuffers(const deque<BufferData>& toRelease) {
        for (auto each : toRelease) {
            buffersInUse.remove(each);
            each.reset();
            buffersFree.push_back(each);
        }
    }

    ~FakeBufferManager() {
        for (auto each : buffersInUse)
            free(each.buffer);
        for (auto each : buffersFree)
            free(each.buffer);
    }
};


class OProtobufStream
{
protected:
    FakeBufferManager& manager;
    deque<BufferData> bufferSet;
    BufferData current;
    uint8_t* dataPtr = nullptr;


    void writeData(const uint8_t* data, size_t size)
    {
        size_t left = size;
        const uint8_t* ptr = data;

        while (left > current.endPtr - dataPtr) {
            size_t sz = current.endPtr - dataPtr;
            memcpy(dataPtr, ptr, sz);
            left -= sz;
            ptr += sz;
            preWrite();
            assert(left > 0);
        }

        assert(left <= current.endPtr - dataPtr);
        memcpy(dataPtr, ptr, left);
        assert(data + size == ptr + left);
    }


    void preWrite()
    {
        if (dataPtr != nullptr) {
            if (current.needReplace(dataPtr)) {
                current.setEnd(dataPtr - current.beginPtr, false);
                bufferSet.push_back(current);
                current = manager.getFreeBuffer();
                dataPtr = current.beginPtr;
            }
        }
        else {
            current = manager.getFreeBuffer();
            dataPtr = current.beginPtr;
        }
    }


public:
    OProtobufStream(FakeBufferManager& manager) :
        manager(manager) {}
    
    void flush()
    {
        if (dataPtr != nullptr) {
            current.setEnd(dataPtr - current.beginPtr, true);
            bufferSet.push_back(current);
            //invalidate buffer
            dataPtr = nullptr;
        }
    }

    void finish()
    {
        flush();
    }

    void writeInt(int fieldNumber, int64_t x)
    {
        dataPtr = serializeHeaderToString(fieldNumber, WIRE_TYPE::VARINT, dataPtr);
        writePackedSignedVarInt(x);
    }
    
    void writeUInt(int fieldNumber, uint64_t x)
    {
        dataPtr = serializeHeaderToString(fieldNumber, WIRE_TYPE::VARINT, dataPtr);
        writePackedUnsignedVarInt(x);
    }

    void writeDouble(int fieldNumber, double x)
    {
        dataPtr = serializeHeaderToString(fieldNumber, WIRE_TYPE::FIXED_64_BIT, dataPtr);
        writePackedDouble(x);
    }

    void writeFloat(int fieldNumber, float x)
    {
        dataPtr = serializeHeaderToString(fieldNumber, WIRE_TYPE::FIXED_32_BIT, dataPtr);
        writePackedFloat(x);
    }

    void writeString(int fieldNumber, const std::string& x)
    {
        dataPtr = serializeLengthDelimitedHeaderToString(fieldNumber, x.size(), dataPtr);
        writeData(reinterpret_cast<const uint8_t*>(x.c_str()), x.size());
    }

    void writeObjectTagAndSize(int fieldNumber, size_t sz)
    {
        preWrite();
        dataPtr = serializeLengthDelimitedHeaderToString(fieldNumber, sz, dataPtr);
    }

    void writePackedSignedVarInt(int64_t x)
    {
        preWrite();
        uint64_t unsig = sint64ToUint64(x);
        dataPtr = serializeToStringVariantUint64(unsig, dataPtr);
    }

    void writePackedUnsignedVarInt(uint64_t x)
    {
        preWrite();
        dataPtr = serializeToStringVariantUint64(x, dataPtr);
    }

    void writePackedDouble(double x)
    {
        preWrite();
        dataPtr = serializeToStringFixedUint64(*(uint64_t*)(&x), dataPtr);
    }

    void writePackedFloat(float x)
    {
        preWrite();
        dataPtr = serializeToStringFixedUint32(*(uint32_t*)(&x), dataPtr);
    }
};

void writeFile(FILE* file, const deque<BufferData>& buffSet)
{
    for (auto each : buffSet) {
        fwrite(each.beginPtr, each.endPtr - each.beginPtr, 1, file);
    }
}


deque<BufferData> readFile(FILE* file, FakeBufferManager& manager)
{
    deque<BufferData> bufferPool;
    bool isLast = false;
    while (!isLast) {
        uint8_t* ptr = static_cast<uint8_t*>(malloc(BUFFER_SIZE));

        BufferData buffer = manager.getFreeBuffer();
        size_t maxRead = buffer.endPtr - buffer.beginPtr;
        size_t sz = fread(buffer.beginPtr, 1, maxRead, file);
        isLast = sz != maxRead;
        buffer.setEnd(sz, isLast);

        bufferPool.push_back(buffer);
    }

    return bufferPool;
}

class IProtobufBuffer
{
public:
    deque<BufferData> bufferPool;
    BufferData current;
    uint8_t* dataPtr;
    size_t alreadyRead = 0;

    IProtobufBuffer(deque<BufferData> bp) :
        bufferPool(bp), current(bp.front()), dataPtr(bp.front().beginPtr)
    {
        bufferPool.pop_front();
    }


    void preRead()
    {
        if (current.needReplace(dataPtr)) {
            alreadyRead += dataPtr - current.beginPtr;
            BufferData next = bufferPool.front();
            next.copyLastFragment(current, dataPtr);
            current = next;
            dataPtr = current.beginPtr;
        }
    }

    bool readData(char* target, size_t size)
    {

        size_t left = size;
        while (left > current.endPtr - dataPtr) {
            memcpy(target, dataPtr, current.endPtr - dataPtr);
            dataPtr += current.endPtr - dataPtr;
            left -= current.endPtr - dataPtr;
            
            if (current.isLast)
                return false;

            preRead();
        }

        assert(left <= current.endPtr - dataPtr);
        memcpy(target, dataPtr, left);
        dataPtr += left;

        return true;
    }

    bool isEndOfStream(size_t last) const {
        if (last == SIZE_MAX)
            return (current.isLast && dataPtr == current.endPtr);
        else
            return alreadyRead + (dataPtr - current.beginPtr) == last;
    }

    bool isGood(int value) const {
        return current.endPtr - dataPtr >= value;
    }

    size_t getAlreadyRead() const {
        return alreadyRead + (dataPtr - current.beginPtr);
    }
};


class IProtobufStream
{
private:
    IProtobufBuffer& buffer;
    const size_t last;

public:
    IProtobufStream(IProtobufBuffer& buffer) :
        buffer(buffer), last(SIZE_MAX) {}
private:
    IProtobufStream(IProtobufBuffer& buffer, size_t last) :
        buffer(buffer), last(last) {}
public:
    //mb: need to diferentiate a 'clean' end of stream (at the end of a field),
    // from a stream ending in the middle of a read.
    bool isEndOfStream() const
    {
        return buffer.isEndOfStream(last);
    }

    bool readFieldTypeAndID(int& type, int& fieldNumber)
    {
        buffer.preRead();

        buffer.dataPtr = deserializeHeaderFromString(fieldNumber, type, buffer.dataPtr);
        
        return buffer.isGood(0); //read past the end of buffer
    }

    bool readVariantInt64(int64_t& x)
    {
        buffer.preRead();

        uint64_t preValue;
        buffer.dataPtr = deserializeFromStringVariantUint64(preValue, buffer.dataPtr);
        x = uint64ToSint64(preValue);

        return buffer.isGood(0); //read past the end of buffer
    }


    bool readVariantUInt64(uint64_t& x)
    {
        buffer.preRead();

        buffer.dataPtr = deserializeFromStringVariantUint64(x, buffer.dataPtr);

        return buffer.isGood(0); //read past the end of buffer
    }

    bool readFixed64Bit(double& x)
    {
        buffer.preRead();

        if (buffer.isGood(8)) {
            uint64_t tmp;
            deserializeFromStringFixedUint64(tmp, buffer.dataPtr);
            x = *reinterpret_cast<double*>(&tmp);
            buffer.dataPtr += 8;
            return true;
        }
        else
            return false;
    }

    bool readFixed32Bit(float& x)
    {
        buffer.preRead();

        if (buffer.isGood(4)) {
            uint32_t tmp;
            deserializeFromStringFixedUint32(tmp, buffer.dataPtr);
            x = *reinterpret_cast<float*>(&tmp);
            buffer.dataPtr += 4;
            return true;
        }
        else
            return false;
    }

    bool readString(std::string& x)
    {
        uint64_t size;
        if (readVariantUInt64(size)) {
            x.resize(size);
            return buffer.readData(const_cast<char*>(x.data()), size);
        }
        else
            return false;
    }

    IProtobufStream makeSubStream(bool& ok, size_t subSize)
    {
        size_t current = buffer.getAlreadyRead();
        IProtobufStream sub(buffer, current + subSize);
        ok = current + subSize <= last; 
        return sub;
    }

};

//mb
bool discardUnexpectedField(int fieldType, IProtobufStream& i) {

    // Unexpected field, just read and discard
    switch (fieldType)
    {
    case VARINT:
    {
        uint64_t temp;
        return i.readVariantUInt64(temp);
    }
    break;
    case FIXED_64_BIT:
    {
        double temp;
        return i.readFixed64Bit(temp);
    }
    break;
    case LENGTH_DELIMITED:
    {
        uint64_t sz;
        bool readOk = i.readVariantUInt64(sz);
        if (!readOk)
            return false;
        IProtobufStream is = i.makeSubStream(readOk, sz);
        if (!readOk)
            return false;

        string temp;
        return is.readString(temp);
    }
    break;
    case FIXED_32_BIT:
    {
        float temp;
        return i.readFixed32Bit(temp);
    }
    break;
    default:
        return false;
    }
}

} //namespace bl

#endif // BASELIB_H

