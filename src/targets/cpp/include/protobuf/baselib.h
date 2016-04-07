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

#include <memory>
#include <vector>
#include <assert.h>
#include <stdio.h>


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
uint8_t* deserializeUnsignedFixed64FromString( int fieldNumber, uint64_t& value, uint8_t* buff );
uint8_t* deserializeSignedFixed64FromString( int fieldNumber, int64_t& value, uint8_t* buff );
uint8_t* deserializeDoubleFromString( int fieldNumber, double& value, uint8_t* buff );

///////////////////////////     WIRE_TYPE::FIXED_64_BIT    ////////////////////////////////////

uint8_t* serializeUnsignedFixed32ToString( int fieldNumber, uint32_t value, uint8_t* buff );
uint8_t* serializeSignedFixed64ToString( int fieldNumber, int32_t value, uint8_t* buff );
uint8_t* serializeDoubleToString( int fieldNumber, float value, uint8_t* buff );
uint8_t* deserializeUnsignedFixed32FromString( int fieldNumber, uint32_t& value, uint8_t* buff );
uint8_t* deserializeSignedFixed32FromString( int fieldNumber, int32_t& value, uint8_t* buff );
uint8_t* deserializeDoubleFromString( int fieldNumber, float& value, uint8_t* buff );

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
		uint8_t* ret = serializeUnsignedVariantToString( fieldNumber, x, buff );
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

#endif // BASELIB_H

