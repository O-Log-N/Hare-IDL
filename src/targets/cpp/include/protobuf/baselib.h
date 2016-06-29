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

#ifndef BASELIB_H
#define BASELIB_H

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

enum WIRE_TYPE
{
	VARINT = 0,
	FIXED_64_BIT = 1,
	LENGTH_DELIMITED = 2,
	START_GROUP = 3,
	END_GROUP = 4,
	FIXED_32_BIT = 5,
};


inline int64_t toSigned64(uint64_t value)
{
    union {
        uint64_t u;
        int64_t s;
    } temp = { (value << 63) | (value >> 1) };

    return temp.s;
}

inline uint64_t toUnsigned64(int64_t value)
{
    union {
        int64_t s;
        uint64_t u;
    } temp = { (value >> 63) & (value << 1) };

    return temp.u;
}

pair<bool, uint64_t> readVarInt(istream& is);
pair<bool, uint64_t> readFixed64(istream& is);
pair<bool, uint32_t> readFixed32(istream& is);
pair<bool, string> readLengthDelimitedString(istream& is);

void writeVarInt(ostream& os, uint64_t value);
void writeFixed64(ostream& os, uint64_t value);
void writeFixed32(ostream& os, uint32_t value);
void writeLengthDelimitedString(ostream& os, const string& value);

class OStream
{
protected:
    ostream& os;
public:
    OStream(ostream& os) : os(os) {}

private:
    void writeTagAndType(uint64_t tag, WIRE_TYPE wt)
    {
        uint64_t value = (tag << 3) | wt;
        writeVarInt(os, value);
    }

public:
    template<class T>
    void writeUnsignedVarInt(uint64_t tag, T value)
    {
        writeTagAndType(tag, WIRE_TYPE::VARINT);
        writeVarInt(os, value);
    }

    template<class T>
    void writeSignedVarInt(uint64_t tag, T x)
    {
        writeTagAndType(tag, WIRE_TYPE::VARINT);
        uint64_t value = toUnsigned64(x);
        writeVarInt(os, value);
    }

    void writeBool(uint64_t tag, bool x)
    {
        writeTagAndType(tag, WIRE_TYPE::VARINT);
        writeVarInt(os, static_cast<uint64_t>(x));
    }

    template<class T>
    void writeEnum(uint64_t tag, T x)
    {
        writeTagAndType(tag, WIRE_TYPE::VARINT);
        writeVarInt(os, static_cast<uint64_t>(x));
    }

    void writeFloatingPoint(uint64_t tag, float x)
    {
        union {
            float asFloat;
            uint32_t asUnsigned32;
        } value = { x };

        writeTagAndType(tag, WIRE_TYPE::FIXED_32_BIT);
        writeFixed32(os, value.asUnsigned32);
    }

    void writeFloatingPoint(uint64_t tag, double x)
    {
        union {
            double asDouble;
            uint64_t asUnsigned64;
        } value = {x};

        writeTagAndType(tag, WIRE_TYPE::FIXED_64_BIT);
        writeFixed64(os, value.asUnsigned64);
    }

    void writeString(uint64_t tag, const string& value)
    {
        writeTagAndType(tag, WIRE_TYPE::LENGTH_DELIMITED);
        writeLengthDelimitedString(os, value);
    }
};

class IStream
{
private:
    istream& is;
public:
    IStream(istream& is) : is(is) {}
    bool readFieldTypeAndID(int& type, int& fieldNumber)
    {
        pair<bool, uint64_t> temp = readVarInt(is);
        if (temp.first) {

            // TODO add check
            type = temp.second & 0x07;
            fieldNumber = temp.second >> 3;
            return true;
        }
        return false;
    }
public:
    template<class T>
    bool readUnsignedVarInt(T& x)
    {
        pair<bool, uint64_t> temp = readVarInt(is);
        if (temp.first && temp.second <= numeric_limits<T>::max()) {
            x = static_cast<T>(temp.second);
            return true;
        }
        else
            return false;
    }

    template<class T>
    bool readSignedVarInt(T& x)
    {
        pair<bool, uint64_t> temp = readVarInt(is);
        if (temp.first) {
            int64_t temp2 = toSigned64(temp.second);
            if (temp2 >= numeric_limits<T>::min() && temp2 <= numeric_limits<T>::max()) {
                x = static_cast<T>(temp2);
                return true;
            }
        }
        return false;
    }

    bool readBool(bool& x)
    {
        pair<bool, uint64_t> temp = readVarInt(is);
        x = temp.second != 0;
        return temp.first;
    }

    template<class T>
    bool readEnum(T& x)
    {
        pair<bool, uint64_t> temp = readVarInt(is);
        x = static_cast<T>(temp.second);
        return temp.first;
    }

    bool readFloatingPoint(float& x)
    {
        pair<bool, uint32_t> temp = readFixed32(is);

        union {
            uint32_t asUnsigned32;
            float asFloat;
        } temp2 = { temp.second };

        x = temp2.asFloat;
        return temp.first;
    }

    bool readFloatingPoint(double& x)
    {
        pair<bool, uint64_t> temp = readFixed64(is);

        union {
            uint64_t asUnsigned64;
            double asDouble;
        } temp2 = {temp.second};

        x = temp2.asDouble;
        return temp.first;
    }


    bool readString(string& x)
    {
        pair<bool, string> temp = readLengthDelimitedString(is);
        x = temp.second;
        return temp.first;
    }
};


#endif // BASELIB_H

