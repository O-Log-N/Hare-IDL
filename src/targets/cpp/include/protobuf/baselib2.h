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


uint8_t* deserializeHeaderFromString(int& fieldNumber, int& type, uint8_t* buff);


///////////////////////////   WIRE_TYPE::VARINT      ////////////////////////////////////

uint8_t* serializeToStringVariantUint64(uint64_t value, uint8_t* buff);
uint8_t* deserializeFromStringVariantUint64(uint64_t& value, uint8_t* buff);

///////////////////////////   WIRE_TYPE::FIXED_64_BIT      ////////////////////////////////////

uint8_t* serializeToStringFixedUint64(uint64_t value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint64(uint64_t& value, uint8_t* buff);

///////////////////////////     WIRE_TYPE::FIXED_32_BIT    ////////////////////////////////////

uint8_t* serializeToStringFixedUint32(uint32_t value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint32(uint32_t& value, uint8_t* buff);

///////////////////////////     WIRE_TYPE::LENGTH_DELIMITED    ////////////////////////////////////

//MB
uint8_t* serializeLengthDelimitedHeaderToString(int fieldNumber, size_t valueSize, uint8_t* buff);



//MB
inline
uint8_t* serializeHeaderToString(int fieldNumber, WIRE_TYPE wire_type, uint8_t* buff)
{
    uint64_t key = (fieldNumber << 3) | wire_type;
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
    
    //MB
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

    //mb
    void writeObjectTagAndSize(int fieldNumber, size_t sz)
    {
        dataPtr = serializeLengthDelimitedHeaderToString(fieldNumber, sz, dataPtr);
        write();
    }

    //mb without fieldNumber, to be used by packed sequence
    void writePackedSignedVarInt(int64_t x)
    {
        uint64_t unsig = sint64ToUint64(x);
        dataPtr = serializeToStringVariantUint64(unsig, dataPtr);
        write();
    }

    //mb without fieldNumber, to be used by packed sequence
    void writePackedUnsignedVarInt(uint64_t x)
    {
        dataPtr = serializeToStringVariantUint64(x, dataPtr);
        write();
    }

    //mb without fieldNumber, to be used by packed sequence
    void writePackedDouble(double x)
    {
        dataPtr = serializeToStringFixedUint64(*(uint64_t*)(&x), dataPtr);
        write();
    }

    //mb without fieldNumber, to be used by packed sequence
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
        const void* dest = data.data();

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

    bool readFieldTypeAndID(WIRE_TYPE& type, int& fieldNumber)
    {
        buffer.preRead();

        uint64_t key;
        buffer.dataPtr = deserializeFromStringVariantUint64(key, buffer.dataPtr);
        type = static_cast<WIRE_TYPE>(key & 7);
        fieldNumber = key >> 3;

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


    //MB copy and paste from readVariantInt64, 
    // but calls deserializeUnsignedVariantFromString
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
            deserializeDoubleFromString(x, buffer.dataPtr);
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
            deserializeFloatFromString(x, buffer.dataPtr);
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

} //namespace bl

#endif // BASELIB_H

