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


enum WIRE_TYPE
{
	VARINT = 0,
	FIXED_64_BIT = 1,
	LENGTH_DELIMITED = 2,
	START_GROUP = 3,
	END_GROUP = 4,
	FIXED_32_BIT = 5,
};

uint8_t* deserializeHeaderFromString( int& fieldNumber, int& type, uint8_t* buff );

uint8_t* serializeToStringVariantUint64( uint64_t value, uint8_t* buff );
uint8_t* deserializeFromStringVariantUint64( uint64_t& value, uint8_t* buff );

uint8_t* serializeLengthDelimitedToString( int fieldNumber, const uint8_t* valueStr, size_t valueSize, uint8_t* buff );
uint8_t* serializeLengthDelimitedToString( int fieldNumber, std::string& value, uint8_t* buff );
uint8_t* deserializeLengthDelimitedFromString( uint8_t* valueStr, size_t& valueSize, uint8_t* buff );
uint8_t* deserializeLengthDelimitedFromString( std::string& value, uint8_t* buff );

///////////////////////////   WIRE_TYPE::VARINT      ////////////////////////////////////

uint8_t* serializeUnsignedVariantToString( int fieldNumber, uint64_t value, uint8_t* buff );
uint8_t* serializeSignedVariantToString( int fieldNumber, int64_t value, uint8_t* buff );
uint8_t* deserializeSignedVariantFromString( int64_t& value, uint8_t* buff );
uint8_t* deserializeUnsignedVariantFromString( uint64_t& value, uint8_t* buff );

///////////////////////////   WIRE_TYPE::FIXED_64_BIT      ////////////////////////////////////

uint8_t* serializeUnsignedFixed64ToString( int fieldNumber, uint64_t value, uint8_t* buff );
uint8_t* serializeSignedFixed64ToString( int fieldNumber, int64_t value, uint8_t* buff );
uint8_t* serializeDoubleToString( int fieldNumber, double value, uint8_t* buff );
uint8_t* deserializeUnsignedFixed64FromString( uint64_t& value, uint8_t* buff );
uint8_t* deserializeSignedFixed64FromString( int64_t& value, uint8_t* buff );
uint8_t* deserializeDoubleFromString( double& value, uint8_t* buff );

///////////////////////////     WIRE_TYPE::FIXED_32_BIT    ////////////////////////////////////

uint8_t* serializeUnsignedFixed32ToString( int fieldNumber, uint32_t value, uint8_t* buff );
uint8_t* serializeSignedFixed64ToString( int fieldNumber, int32_t value, uint8_t* buff );
uint8_t* serializeDoubleToString( int fieldNumber, float value, uint8_t* buff );
uint8_t* deserializeUnsignedFixed32FromString( uint32_t& value, uint8_t* buff );
uint8_t* deserializeSignedFixed32FromString( int32_t& value, uint8_t* buff );
uint8_t* deserializeDoubleFromString( float& value, uint8_t* buff );

///////////////////////////     WIRE_TYPE::LENGTH_DELIMITED    ////////////////////////////////////

uint8_t* serializeToStringKnownLength( const uint8_t* valueBytes, size_t valueSize, uint8_t* buff );
uint8_t* deserializeFromStringKnownLength( uint8_t* valueBytes, size_t valueSize, uint8_t* buff );
uint8_t* serializeLengthDelimitedToString( int fieldNumber, const uint8_t* valueStr, size_t valueSize, uint8_t* buff );
uint8_t* serializeLengthDelimitedToString( int fieldNumber, std::string& value, uint8_t* buff );
uint8_t* deserializeLengthDelimitedFromString( uint8_t* valueStr, size_t& valueSize, uint8_t* buff );
uint8_t* deserializeLengthDelimitedFromString( std::string& value, uint8_t* buff );




class OStream
{
protected:
	FILE* outstr;
public:
	OStream( FILE* outStr ) : outstr( outStr ) {}
	void writeInt( int fieldNumber, int x )
	{
		uint8_t buff[1000];
		uint8_t* ret = serializeSignedVariantToString( fieldNumber, x, buff );
		fwrite( buff, ret - buff, 1, outstr );
	}
	void writeDouble( int fieldNumber, double x )
	{
		uint8_t buff[1000];
		uint8_t* ret = serializeDoubleToString( fieldNumber, x, buff );
		fwrite( buff, ret - buff, 1, outstr );
	}
	void writeString( int fieldNumber, std::string x )
	{
		uint8_t buff[1000];
		uint8_t* ret = serializeLengthDelimitedToString( fieldNumber, x, buff );
		fwrite( buff, ret - buff, 1, outstr );
	}
};

class IStream
{
protected:
	FILE* instr;
public:
	IStream( FILE* inStr ) : instr( inStr ) {}
	bool readFieldTypeAndID( int& type, int& fieldNumber )
	{
		uint8_t buff[12];
		memset( buff, 0, 12 );
		int pos = 0;
		size_t readret;
		for (;;)
		{
			readret = fread( buff + pos, 1, 1, instr );
			if ( readret == 0 )
				return false; // nothing to read (anymore); TODO: think about incomplete/broken packet
			if ( ( buff[pos] & 0x80 ) == 0 )
			{
				deserializeHeaderFromString( fieldNumber, type, buff );
				return true;
			}
			++pos;
		}
		return false; // TODO: think about incomplete/broken packet
	}
	bool readInt32( int32_t& x )
	{
		uint8_t buff[4];
		size_t readret = fread( buff, 1, 4, instr );
		if ( readret < 4 )
			return false;
		deserializeSignedFixed32FromString( x, buff );
		return true;
	}
	bool readInt64( int64_t& x )
	{
		uint8_t buff[8];
		size_t readret = fread( buff, 1, 8, instr );
		if ( readret < 8 )
			return false;
		deserializeSignedFixed64FromString( x, buff );
		return true;
	}
#if 0
	bool readVariantInt32( int32_t& x )
	{
		uint8_t buff[4];
		size_t readret = fread( buff, 1, 4, instr );
		if ( readret < 4 )
			return false;
		deserializeSignedVariantFromString( x, buff );
		return true;
	}
#endif // 0
	bool readVariantInt64( int64_t& x )
	{
		uint8_t buff[12];
		memset( buff, 0, 12 );
		int pos = 0;
		size_t readret;
		uint32_t stringSz = 0;
		for (;;)
		{
			readret = fread( buff + pos, 1, 1, instr );
			if ( readret == 0 )
				return false; // nothing to read (anymore); TODO: think about incomplete/broken packet
			if ( ( buff[pos] & 0x80 ) == 0 )
			{
				deserializeSignedVariantFromString( x, buff );
				break;
			}
			++pos;
		}
		return true;
	}
#if 0
	bool readInt64( int64_t& x )
	{
		uint8_t buff[1000];
		uint8_t* ret = serializeUnsignedVariantToString( fieldNumber, x, buff );
		fwrite( buff, ret - buff, 1, outstr );
	}
	bool readDouble( double& x )
	{
		uint8_t buff[1000];
		uint8_t* ret = serializeDoubleToString( fieldNumber, x, buff );
		fwrite( buff, ret - buff, 1, outstr );
	}
#endif
	bool readString( std::string& x )
	{
		uint8_t buff[12];
		memset( buff, 0, 12 );
		int pos = 0;
		size_t readret;
		uint64_t stringSz = 0;
		for (;;)
		{
			readret = fread( buff + pos, 1, 1, instr );
			if ( readret == 0 )
				return false; // nothing to read (anymore); TODO: think about incomplete/broken packet
			if ( ( buff[pos] & 0x80 ) == 0 )
			{
				deserializeUnsignedVariantFromString( stringSz, buff );
				break;
			}
			++pos;
		}

		for ( ; stringSz; --stringSz )
		{
			readret = fread( buff, 1, 1, instr );
			if ( readret == 0 )
				return false; // incmplete or broken record
			x.push_back( buff[0] );
		}

		return true;
	}
};

#endif // BASELIB_H

