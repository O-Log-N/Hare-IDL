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
#include <protobuf/baselib.h>

void sint64ToUint64( int64_t src, uint64_t& target )
{
	target = (src << 1) ^ (src >> 63);
}
void uint64ToSint64( uint64_t src, int64_t& target )
{
	target = ( (src << 63) ^ (src >> 1) );
}

uint8_t* serializeToStringVariantUint64( uint64_t value, uint8_t* buff )
{
	while( value >= 0x80 )
	{
		*buff = value & 0x7f;
		*(buff++) |= 0x80;
		value >>= 7;
	}
	*buff = value & 0x7f;
	++buff;
	return buff;
}

uint8_t* deserializeFromStringVariantUint64( uint64_t& value, uint8_t* buff )
{
	value = 0;
	uint64_t tmp;
	int ctr = 0;
	do
	{
		tmp = *buff & 0x7f;
		tmp <<= ctr;
		ctr += 7;
		value |= tmp;
	}
	while( *(buff++) & 0x80 );

	return buff;
}

uint8_t* deserializeHeaderFromString( int& fieldNumber, int& type, uint8_t* buff )
{
	uint64_t key;
	buff = deserializeFromStringVariantUint64( key, buff );
	type = key & 7;
	fieldNumber = key >> 3;
	return buff;
}


///////////////////////////   WIRE_TYPE::VARINT      ////////////////////////////////////

uint8_t* serializeUnsignedVariantToString( int fieldNumber, uint64_t value, uint8_t* buff )
{
	uint32_t key = (fieldNumber << 3) | WIRE_TYPE::VARINT;
	buff = serializeToStringVariantUint64( key, buff );
	return serializeToStringVariantUint64( value, buff );
}

uint8_t* serializeSignedVariantToString( int fieldNumber, int64_t value, uint8_t* buff )
{
	uint32_t key = (fieldNumber << 3) | WIRE_TYPE::VARINT;
	uint64_t target;
	sint64ToUint64( value, target );
	buff = serializeToStringVariantUint64( key, buff );
	return serializeToStringVariantUint64( target, buff );
}

uint8_t* deserializeSignedVariantFromString( int64_t& value, uint8_t* buff )
{
	uint64_t preValue;
	buff = deserializeFromStringVariantUint64( preValue, buff );
	uint64ToSint64( preValue, value );
	return buff;
}

uint8_t* deserializeUnsignedVariantFromString( uint64_t& value, uint8_t* buff )
{
	return deserializeFromStringVariantUint64( value, buff );
}


///////////////////////////   WIRE_TYPE::FIXED_64_BIT      ////////////////////////////////////

uint8_t* serializeToStringFixedUint64( uint64_t value, uint8_t* buff )
{
	// TODO: version favouring little endian platforms
	for ( int ctr = 0; ctr < 8; ++ctr )
	{
		*(buff++) = value & 0xff;
		value >>= 8;
	}
	return buff;
}

uint8_t* deserializeFromStringFixedUint64( uint64_t& value, uint8_t* buff )
{
	// TODO: version favouring little endian platforms
	uint64_t tmp;
	
	for ( int ctr = 0; ctr < 64; ctr += 8 )
	{
		tmp = *(buff++);
		tmp <<= ctr;
		value |= tmp;
	}

	return buff;
}

uint8_t* serializeUnsignedFixed64ToString( int fieldNumber, uint64_t value, uint8_t* buff )
{
	uint32_t key = (fieldNumber << 3) | WIRE_TYPE::FIXED_64_BIT;
	buff = serializeToStringVariantUint64( key, buff );
	return serializeToStringFixedUint64( value, buff );
}

uint8_t* serializeSignedFixed64ToString( int fieldNumber, int64_t value, uint8_t* buff )
{
	uint32_t key = (fieldNumber << 3) | WIRE_TYPE::FIXED_64_BIT;
	buff = serializeToStringVariantUint64( key, buff );
	return serializeToStringFixedUint64( *(uint64_t*)(&value), buff );
}

uint8_t* serializeDoubleToString( int fieldNumber, double value, uint8_t* buff )
{
	uint32_t key = (fieldNumber << 3) | WIRE_TYPE::FIXED_64_BIT;
	buff = serializeToStringVariantUint64( key, buff );
	return serializeToStringFixedUint64( *(uint64_t*)(&value), buff );
}

uint8_t* deserializeUnsignedFixed64FromString( int fieldNumber, uint64_t& value, uint8_t* buff )
{
	return deserializeFromStringFixedUint64( value, buff );
}

uint8_t* deserializeSignedFixed64FromString( int fieldNumber, int64_t& value, uint8_t* buff )
{
	uint64_t tmp;
	buff = deserializeFromStringFixedUint64( tmp, buff );
	value = *(int64_t*)(&tmp);
	return buff;
}

uint8_t* deserializeDoubleFromString( int fieldNumber, double& value, uint8_t* buff )
{
	uint64_t tmp;
	buff = deserializeFromStringFixedUint64( tmp, buff );
	value = *(double*)(&tmp);
	return buff;
}


///////////////////////////     WIRE_TYPE::FIXED_64_BIT    ////////////////////////////////////

uint8_t* serializeToStringFixedUint32( uint32_t value, uint8_t* buff )
{
	// TODO: version favouring little endian platforms
	*(buff++) = value & 0xff;
	value >>= 8;
	*(buff++) = value & 0xff;
	value >>= 8;
	*(buff++) = value & 0xff;
	value >>= 8;
	*(buff++) = value & 0xff;
	return buff;
}

uint8_t* deserializeFromStringFixedUint32( uint32_t& value, uint8_t* buff )
{
	// TODO: version favouring little endian platforms
	uint32_t tmp;
	
	for ( int ctr = 0; ctr < 32; ctr += 8 )
	{
		tmp = *(buff++);
		tmp <<= ctr;
		value |= tmp;
	}

	return buff;
}

uint8_t* serializeUnsignedFixed32ToString( int fieldNumber, uint32_t value, uint8_t* buff )
{
	uint32_t key = (fieldNumber << 3) | WIRE_TYPE::FIXED_32_BIT;
	buff = serializeToStringVariantUint64( key, buff );
	return serializeToStringFixedUint32( value, buff );
}

uint8_t* serializeSignedFixed64ToString( int fieldNumber, int32_t value, uint8_t* buff )
{
	uint32_t key = (fieldNumber << 3) | WIRE_TYPE::FIXED_32_BIT;
	buff = serializeToStringVariantUint64( key, buff );
	return serializeToStringFixedUint32( *(uint32_t*)(&value), buff );
}

uint8_t* serializeDoubleToString( int fieldNumber, float value, uint8_t* buff )
{
	uint32_t key = (fieldNumber << 3) | WIRE_TYPE::FIXED_32_BIT;
	buff = serializeToStringVariantUint64( key, buff );
	return serializeToStringFixedUint32( *(uint32_t*)(&value), buff );
}

uint8_t* deserializeUnsignedFixed32FromString( int fieldNumber, uint32_t& value, uint8_t* buff )
{
	return deserializeFromStringFixedUint32( value, buff );
}

uint8_t* deserializeSignedFixed32FromString( int fieldNumber, int32_t& value, uint8_t* buff )
{
	uint32_t tmp;
	buff = deserializeFromStringFixedUint32( tmp, buff );
	value = *(int32_t*)(&tmp);
	return buff;
}

uint8_t* deserializeDoubleFromString( int fieldNumber, float& value, uint8_t* buff )
{
	uint32_t tmp;
	buff = deserializeFromStringFixedUint32( tmp, buff );
	value = *(float*)(&tmp);
	return buff;
}


///////////////////////////     WIRE_TYPE::LENGTH_DELIMITED    ////////////////////////////////////

uint8_t* serializeToStringKnownLength( const uint8_t* valueBytes, size_t valueSize, uint8_t* buff )
{
	memcpy( buff, valueBytes, valueSize );
	return buff + valueSize;
}

uint8_t* deserializeFromStringKnownLength( uint8_t* valueBytes, size_t valueSize, uint8_t* buff )
{
	memcpy( valueBytes, buff, valueSize );
	return buff + valueSize;
}

uint8_t* serializeLengthDelimitedToString( int fieldNumber, const uint8_t* valueStr, size_t valueSize, uint8_t* buff )
{
	uint32_t key = (fieldNumber << 3) | WIRE_TYPE::LENGTH_DELIMITED;
	buff = serializeToStringVariantUint64( key, buff );
	buff = serializeToStringVariantUint64( valueSize, buff );
	return serializeToStringKnownLength( valueStr, valueSize, buff );
}

uint8_t* serializeLengthDelimitedToString( int fieldNumber, std::string& value, uint8_t* buff )
{
	uint32_t key = (fieldNumber << 3) | WIRE_TYPE::LENGTH_DELIMITED;
	buff = serializeToStringVariantUint64( key, buff );
	buff = serializeToStringVariantUint64( value.size(), buff );
	return serializeToStringKnownLength( reinterpret_cast<const uint8_t*>(value.c_str()), value.size(), buff );
}

uint8_t* deserializeLengthDelimitedFromString( uint8_t* valueStr, size_t& valueSize, uint8_t* buff )
{
	buff = deserializeFromStringVariantUint64( valueSize, buff );
	return deserializeFromStringKnownLength( valueStr, valueSize, buff );
}

uint8_t* deserializeLengthDelimitedFromString( std::string& value, uint8_t* buff )
{
	size_t valueSize;
	buff = deserializeFromStringVariantUint64( valueSize, buff );
	value = std::string( buff, buff + valueSize );
	return buff + valueSize;
}




