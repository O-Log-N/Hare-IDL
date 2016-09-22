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
#include <assert.h>
#include <stdio.h>
#include <string>
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


//uint8_t* deserializeHeaderFromString(int& fieldNumber, int& type, uint8_t* buff);
uint8_t* deserializeHeaderFromString(int& fieldNumber, int& type, uint8_t* buff);


///////////////////////////   WIRE_TYPE::VARINT      ////////////////////////////////////

uint8_t* serializeToStringVariantUint64_loop(uint64_t value, uint8_t* buff);
uint8_t* deserializeFromStringVariantUint64_loop(uint64_t& value, uint8_t* buff);

/*
    mb: serializeToStringVariantUint64 will read at most 10 bytes from buffer
    However, if there is risk of buffer being overread, a null byte must be
    set after the last buffer position, to force stop the algorithm.
*/

uint8_t* serializeToStringVariantUint64(uint64_t value, uint8_t* buff);
uint8_t* deserializeFromStringVariantUint64(uint64_t& value, uint8_t* buff);


///////////////////////////   WIRE_TYPE::FIXED_64_BIT      ////////////////////////////////////

uint8_t* serializeToStringFixedUint64_little(uint64_t value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint64_little(uint64_t& value, uint8_t* buff);

uint8_t* serializeToStringFixedUint64(uint64_t value, uint8_t* buff);
uint8_t* serializeToStringFixedUint64_2(uint64_t value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint64(uint64_t& value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint64_2(uint64_t& value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint64_3(uint64_t& value, uint8_t* buff);

uint8_t* serializeToStringFixedUint64_loop(uint64_t value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint64_loop(uint64_t& value, uint8_t* buff);
uint8_t* serializeToStringFixedUint64_loop2(uint64_t value, uint8_t* buff);

///////////////////////////     WIRE_TYPE::FIXED_32_BIT    ////////////////////////////////////

uint8_t* serializeToStringFixedUint32_little(uint32_t value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint32_little(uint32_t& value, uint8_t* buff);

uint8_t* serializeToStringFixedUint32(uint32_t value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint32(uint32_t& value, uint8_t* buff);

uint8_t* serializeToStringFixedUint32_2(uint32_t value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint32_2(uint32_t& value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint32_3(uint32_t& value, uint8_t* buff);

uint8_t* serializeToStringFixedUint32_loop(uint32_t value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint32_loop(uint32_t& value, uint8_t* buff);
uint8_t* serializeToStringFixedUint32_loop2(uint32_t value, uint8_t* buff);

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


const size_t MIN_BUFFER_LEFT = 20;
const size_t VAR_INT_MAX_SIZE = 10;

class FileWriter
{
private:
    FILE* file;
public:
    FileWriter(FILE* file) :file(file) {}

    void write(const void* buffer, size_t size)
    {
        fwrite(buffer, size, 1, file);
    }
};
class NullWriter
{
public:
    NullWriter() {}

    void write(const void* buffer, size_t size)
    {
        ;//do-nothing
    }
};

//MB end

template<class WR>
class OProtobufStream
{
protected:
    uint8_t* const buffer;
    const size_t bufferSize;
    uint8_t* dataPtr;
    WR& wr;

    void writeData(const string& data)
    {
        flush();
        wr.write(data.c_str(), data.size());
    }

    void write()
    {
        if(buffer + bufferSize - dataPtr > MIN_BUFFER_LEFT)
            return;

        flush();
    }
public:
    OProtobufStream(uint8_t* buffer, size_t bufferSize, WR& wr) :
        buffer(buffer), bufferSize(bufferSize), dataPtr(buffer), wr(wr) {}

    void flush()
    {
        wr.write(buffer, dataPtr - buffer);
        dataPtr = buffer;
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
        writeData(x);
    }

    void writeObjectTagAndSize(int fieldNumber, size_t sz)
    {
        dataPtr = serializeLengthDelimitedHeaderToString(fieldNumber, sz, dataPtr);
        write();
    }

    void writePackedSignedVarInt(int64_t x)
    {
        uint64_t unsig = sint64ToUint64(x);
        dataPtr = serializeToStringVariantUint64(unsig, dataPtr);
        write();
    }

    void writePackedUnsignedVarInt(uint64_t x)
    {
        dataPtr = serializeToStringVariantUint64(x, dataPtr);
        write();
    }

    void writePackedDouble(double x)
    {
        dataPtr = serializeToStringFixedUint64(*(uint64_t*)(&x), dataPtr);
        write();
    }

    void writePackedFloat(float x)
    {
        dataPtr = serializeToStringFixedUint32(*(uint32_t*)(&x), dataPtr);
        write();
    }
};

class FileReader
{
private:
    FILE* file;
public:
    FileReader(FILE* file) :file(file) {}

    size_t read(const void* buffer, size_t size)
    {
        return fread(const_cast<void*>(buffer), 1, size, file);
    }
};

template<class RD>
class IProtobufBuffer
{
public:
    uint8_t* const buffer;
    const size_t bufferSize;
    uint8_t* dataPtr;
    uint8_t* dataEnd;
    size_t discardedData = 0;
    bool endOfInput = false;
    RD& rd;


    IProtobufBuffer(uint8_t* buffer, size_t bufferSize, RD& rd) :
        buffer(buffer), bufferSize(bufferSize), dataPtr(buffer), dataEnd(buffer), rd(rd) {}

    void preRead()
    {
        assert(dataPtr != 0);
        size_t left = dataEnd - dataPtr;
        if (left > MIN_BUFFER_LEFT || endOfInput)
            return;

        discardedData += dataPtr - buffer;
        memcpy(buffer, dataPtr, left);
        dataPtr = buffer;
        dataEnd = buffer + left;

        size_t toRead = bufferSize - 1 - left;

        size_t sz = rd.read(dataEnd, toRead);

        endOfInput = sz != toRead;
        dataEnd += sz;
        *dataEnd = 0; //to force stop reading VarInt past end of buffer

        return;
    }

    bool readData(std::string& data, size_t size)
    {
        data.resize(size);

        size_t left = dataEnd - dataPtr;
        if (size <= left) {
            memcpy(const_cast<char*>(data.data()), dataPtr, size);
            dataPtr += size;
            return true;
        }
        else {
            memcpy(const_cast<char*>(data.data()), dataPtr, left);
            discardedData += dataEnd - buffer; // dataPtr + left - buffer 
            dataPtr = buffer;
            dataEnd = buffer;

            size_t toRead = size - left;
            size_t sz = rd.read(data.data() + left, toRead);
            discardedData += sz;
            endOfInput = sz != toRead;

            return endOfInput;
        }
    }

    bool isEndOfStream(size_t last) const {
        if (last == SIZE_MAX)
            return (endOfInput && dataPtr == dataEnd);
        else
            return discardedData + (dataPtr - buffer) == last;
    }
};


template<class RD>
class IProtobufStream
{
private:
    IProtobufBuffer<RD>& buffer;
    size_t last = SIZE_MAX;

public:
    IProtobufStream(IProtobufBuffer<RD>& buffer) :
        buffer(buffer) {}

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
        
        return buffer.dataPtr <= buffer.dataEnd; //read past the end of buffer
    }

    bool readVariantInt64(int64_t& x)
    {
        buffer.preRead();

        uint64_t preValue;
        buffer.dataPtr = deserializeFromStringVariantUint64(preValue, buffer.dataPtr);
        x = uint64ToSint64(preValue);

        return buffer.dataPtr <= buffer.dataEnd; //read past the end of buffer
    }


    bool readVariantUInt64(uint64_t& x)
    {
        buffer.preRead();

        buffer.dataPtr = deserializeFromStringVariantUint64(x, buffer.dataPtr);

        return buffer.dataPtr <= buffer.dataEnd; //read past the end of buffer
    }

    bool readFixed64Bit(double& x)
    {
        buffer.preRead();

        if (buffer.dataEnd - buffer.dataPtr >= 8) {
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

        if (buffer.dataEnd - buffer.dataPtr >= 4) {
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
        if (readVariantUInt64(size))
            return buffer.readData(x, size);
        else
            return false;
    }

    bool setAsSubStream(size_t subSize)
    {
        size_t current = buffer.discardedData + (buffer.dataPtr - buffer.buffer);

        if (current + subSize <= last) {
            last = current + subSize;
            return true;
        }
        else
            return false;
    }

    IProtobufStream makeSubStream(bool& ok, size_t subSize)
    {
        IProtobufStream sub(*this);
        ok = sub.setAsSubStream(subSize);
        return sub;
    }

};

//mb
template<class T>
bool discardUnexpectedField(int fieldType, IProtobufStream<T>& i) {

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
        IProtobufStream<T> is = i.makeSubStream(readOk, sz);
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

