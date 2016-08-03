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

inline
void sint64ToUint64(int64_t src, uint64_t& target)
{
    target = (src << 1) ^ (src >> 63);
}

inline
void uint64ToSint64(uint64_t src, int64_t& target)
{
    target = (src >> 1) ^ -(src & 1);
}

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

uint8_t* serializeToStringVariantUint64(uint64_t value, uint8_t* buff);
uint8_t* deserializeFromStringVariantUint64(uint64_t& value, uint8_t* buff);


//uint8_t* serializeLengthDelimitedToString(int fieldNumber, const uint8_t* valueStr, size_t valueSize, uint8_t* buff);
//uint8_t* serializeLengthDelimitedToString(int fieldNumber, std::string& value, uint8_t* buff);
//uint8_t* deserializeLengthDelimitedFromString(uint8_t* valueStr, size_t& valueSize, uint8_t* buff);
//uint8_t* deserializeLengthDelimitedFromString(std::string& value, uint8_t* buff);

///////////////////////////   WIRE_TYPE::VARINT      ////////////////////////////////////

uint8_t* deserializeSignedVariantFromString(int64_t& value, uint8_t* buff);
uint8_t* deserializeUnsignedVariantFromString(uint64_t& value, uint8_t* buff);

///////////////////////////   WIRE_TYPE::FIXED_64_BIT      ////////////////////////////////////

uint8_t* serializeToStringFixedUint64(uint64_t value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint64(uint64_t& value, uint8_t* buff);

uint8_t* serializeUnsignedFixed64ToString(int fieldNumber, uint64_t value, uint8_t* buff);
uint8_t* serializeSignedFixed64ToString(int fieldNumber, int64_t value, uint8_t* buff);
uint8_t* serializeDoubleToString(int fieldNumber, double value, uint8_t* buff);
//mb without fieldNumber, to be used by packed sequence
uint8_t* serializeDoubleToString(double value, uint8_t* buff);

uint8_t* deserializeUnsignedFixed64FromString(uint64_t& value, uint8_t* buff);
uint8_t* deserializeSignedFixed64FromString(int64_t& value, uint8_t* buff);
uint8_t* deserializeDoubleFromString(double& value, uint8_t* buff);

///////////////////////////     WIRE_TYPE::FIXED_32_BIT    ////////////////////////////////////

uint8_t* serializeToStringFixedUint32(uint32_t value, uint8_t* buff);
uint8_t* deserializeFromStringFixedUint32(uint32_t& value, uint8_t* buff);

uint8_t* serializeUnsignedFixed32ToString(int fieldNumber, uint32_t value, uint8_t* buff);
uint8_t* serializeSignedFixed64ToString(int fieldNumber, int32_t value, uint8_t* buff);
uint8_t* serializeFloatToString(int fieldNumber, float value, uint8_t* buff);
//mb without fieldNumber, to be used by packed sequence
uint8_t* serializeFloatToString(float value, uint8_t* buff);

uint8_t* deserializeUnsignedFixed32FromString(uint32_t& value, uint8_t* buff);
uint8_t* deserializeSignedFixed32FromString(int32_t& value, uint8_t* buff);
uint8_t* deserializeFloatFromString(float& value, uint8_t* buff);

///////////////////////////     WIRE_TYPE::LENGTH_DELIMITED    ////////////////////////////////////

uint8_t* serializeToStringKnownLength(const uint8_t* valueBytes, size_t valueSize, uint8_t* buff);
uint8_t* deserializeFromStringKnownLength(uint8_t* valueBytes, size_t valueSize, uint8_t* buff);
uint8_t* serializeLengthDelimitedToString(int fieldNumber, const uint8_t* valueStr, size_t valueSize, uint8_t* buff);
uint8_t* serializeLengthDelimitedToString(int fieldNumber, std::string& value, uint8_t* buff);
uint8_t* deserializeLengthDelimitedFromString(uint8_t* valueStr, size_t& valueSize, uint8_t* buff);
uint8_t* deserializeLengthDelimitedFromString(std::string& value, uint8_t* buff);



//MB
inline
uint8_t* serializeHeaderToString(int fieldNumber, WIRE_TYPE wire_type, uint8_t* buff)
{
    uint64_t key = (fieldNumber << 3) | wire_type;
    return serializeToStringVariantUint64(key, buff);
}


//MB
uint8_t* serializeLengthDelimitedHeaderToString(int fieldNumber, size_t valueSize, uint8_t* buff);

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
size_t getSignedVarIntSize(int64_t value);

constexpr size_t getTagSize(uint64_t tag) { return getUnsignedVarIntSize(tag << 3); }
constexpr size_t getFixedSize(float) { return 4; }
constexpr size_t getFixedSize(double) { return 8; }


const size_t MIN_BUFFER_LEFT = 20;

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

template<class WR, size_t SIZE>
class OProtobufStream
{
protected:
    uint8_t buff[SIZE];
    uint8_t* buff_ptr = buff;
    WR& wr;

    void writeData(const string& data)
    {
        flush();
        wr.write(data.c_str(), data.size());
    }

    void write()
    {
        if(buff + SIZE - buff_ptr > MIN_BUFFER_LEFT)
            return;

        flush();
    }
public:
    OProtobufStream(WR& wr) : wr(wr) {}

    void flush()
    {
        wr.write(buff, buff_ptr - buff);
        buff_ptr = buff;
    }

    void writeInt(int fieldNumber, int64_t x)
    {
        buff_ptr = serializeHeaderToString(fieldNumber, WIRE_TYPE::VARINT, buff_ptr);
        uint64_t unsig = sint64ToUint64(x);
        buff_ptr = serializeToStringVariantUint64(unsig, buff_ptr);
        write();
    }
    
    //MB
    void writeUInt(int fieldNumber, uint64_t x)
    {
        buff_ptr = serializeHeaderToString(fieldNumber, WIRE_TYPE::VARINT, buff_ptr);
        buff_ptr = serializeToStringVariantUint64(x, buff_ptr);
        write();
    }

    void writeDouble(int fieldNumber, double x)
    {
        buff_ptr = serializeHeaderToString(fieldNumber, WIRE_TYPE::FIXED_64_BIT, buff_ptr);
        buff_ptr = serializeToStringFixedUint64(*(uint64_t*)(&x), buff_ptr);
        write();
    }

    void writeFloat(int fieldNumber, float x)
    {
        buff_ptr = serializeHeaderToString(fieldNumber, WIRE_TYPE::FIXED_32_BIT, buff_ptr);
        buff_ptr = serializeToStringFixedUint32(*(uint32_t*)(&x), buff_ptr);
        write();
    }

    void writeString(int fieldNumber, const std::string& x)
    {
        buff_ptr = serializeLengthDelimitedHeaderToString(fieldNumber, sz, buff_ptr);
        writeData(x);
    }

    //mb
    void writeObjectTagAndSize(int fieldNumber, size_t sz)
    {
        buff_ptr = serializeLengthDelimitedHeaderToString(fieldNumber, sz, buff_ptr);
        write();
    }

    //mb without fieldNumber, to be used by packed sequence
    void writePackedSignedVarInt(int64_t x)
    {
        uint64_t unsig = sint64ToUint64(x);
        buff_ptr = serializeToStringVariantUint64(unsig, buff_ptr);
        write();
    }

    //mb without fieldNumber, to be used by packed sequence
    void writePackedUnsignedVarInt(uint64_t x)
    {
        buff_ptr = serializeToStringVariantUint64(x, buff_ptr);
        write();
    }

    //mb without fieldNumber, to be used by packed sequence
    void writePackedDouble(double x)
    {
        buff_ptr = serializeToStringFixedUint64(*(uint64_t*)(&x), buff_ptr);
        write();
    }

    //mb without fieldNumber, to be used by packed sequence
    void writePackedFloat(float x)
    {
        buff_ptr = serializeToStringFixedUint32(*(uint32_t*)(&x), buff_ptr);
        write();
    }
};

class FileReader
{
private:
    FILE* file;
public:
    FileReader(FILE* file) :file(file) {}

    size_t read(void* buffer, size_t size)
    {
        return fread(buffer, 1, size, file);
    }
};

class IProtobufBuffer
{
public:
    uint8_t* const buffer;
    const size_t bufferSize;
    uint8_t* dataPtr;
    uint8_t* dataEnd;
    size_t readSize;

    IProtobufBuffer(uint8_t* buffer, size_t bufferSize) :
        buffer(buffer), bufferSize(bufferSize), dataPtr(buffer), dataEnd(buffer) {}


};


template<class RD>
class IProtobufStream
{
private:
    IProtobufBuffer& buffer;

    size_t inputLeft = SIZE_MAX;

    RD& rd;
    

    bool readData(std::string& data, size_t size)
    {
        data.resize(size);

        size_t left = buffer.dataEnd - buffer.dataPtr;
        if (size < left) {
            memcpy(data.data(), buffer.dataPtr, size);
            buffer.dataPtr += size;
            return true;
        }
        else if (left + inputLeft < size) {
            return false;
        }
        else {
            memcpy(data.data(), buffer.dataPtr, left);
            buffer.dataPtr = buffer.buffer;
            buffer.dataEnd = buffer.buffer;

            size_t sz = rd.read(data.data() + left, size - left);

            if (sz != size - left)
                return false;

            // => left + inputLeft >= size == sz + left
            // => inputLeft >= sz
            inputLeft -= sz;

            return true;
        }
    }

    bool read()
    {
        size_t left = buffer.dataEnd - buffer.dataPtr;
        if (left > MIN_BUFFER_LEFT || inputLeft == 0)
            return true;

        memcpy(buffer.buffer, buffer.dataPtr, left);
        buffer.dataPtr = buffer.buffer;
        buffer.dataEnd = buffer.buffer + left;

        size_t toRead = buffer.bufferSize - 1 - left;

        size_t sz = rd.read(buffer.dataEnd, toRead);
            
        buffer.dataEnd += sz;
        *(buffer.dataEnd) = 0; //to force stop reading VarInt past end of buffer

        if (inputLeft != SIZE_MAX) {
            if (sz != toRead && sz < inputLeft) //EOF and not enought read
                return false;

            inputLeft -= sz < inputLeft ? sz : inputLeft;
        }
        else {
            if (sz != toRead) { //EOF
                inputLeft = 0;
            }
        }
        return true;
    }

public:
    IProtobufStream(IProtobufBuffer& buffer, RD& rd) :
        buffer(buffer), rd(rd) {}

    //mb: need to diferentiate a 'clean' end of stream (at the end of a field),
    // from a stream ending in the middle of a read.
    bool isEndOfStream() const {
        return inputLeft == 0 && buffer.dataPtr == buffer.dataEnd;
    }

    bool readFieldTypeAndID(WIRE_TYPE& type, int& fieldNumber)
    {
        if(!read())
            return false;

        uint64_t key;
        buffer.dataPtr = deserializeFromStringVariantUint64(key, buffer.dataPtr);
        type = static_cast<WIRE_TYPE>(key & 7);
        fieldNumber = key >> 3;

        return buffer.dataPtr != buffer.dataEnd + 1; //read past the end of buffer
    }

    bool readVariantInt64(int64_t& x)
    {
        if (!read())
            return false;

        uint64_t preValue;
        buffer.dataPtr = deserializeFromStringVariantUint64(preValue, buffer.dataPtr);
        x = uint64ToSint64(preValue);

        return buffer.dataPtr != buffer.dataEnd + 1; //read past the end of buffer
    }


    //MB copy and paste from readVariantInt64, 
    // but calls deserializeUnsignedVariantFromString
    bool readVariantUInt64(uint64_t& x)
    {
        if (!read())
            return false;

        buffer.dataPtr = deserializeFromStringVariantUint64(x, buffer.dataPtr);

        return buffer.dataPtr != buffer.dataEnd + 1; //read past the end of buffer
    }

    bool readFixed64Bit(double& x)
    {
        if (!read())
            return false;

        if (buffer.dataEnd - buffer.dataPtr < 8)
            return false;

        deserializeDoubleFromString(x, buffer.dataPtr);
        buffer.dataPtr += 8;
        return true;
    }

    bool readFixed32Bit(float& x)
    {
        if (!read())
            return false;

        if (buffer.dataEnd - buffer.dataPtr < 4)
            return false;

        deserializeFloatFromString(x, buffer.dataPtr);
        buffer.dataPtr += 4;
        return true;
    }

    bool readString(std::string& x)
    {
        uint64_t size;
        if (!readVariantUInt64(size))
            return false;


        return readData(x, size);
    }

    //MB check!
    std::pair<bool, IProtobufStream> makeSubStream(size_t subSize)
    {
        IProtobufStream is(*this);

        if (inputLeft >= subSize) {
            inputLeft -= subSize;
            is.inputLeft = subSize;
            return make_pair(true, is);
        }
        else {
            return make_pair(false, is);
        }
    }

};

} //namespace bl

#endif // BASELIB_H

