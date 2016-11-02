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

/*******************************************************************************
DISCLAIMER:
    This library has been created mostly to test output code for being
	compilable and, in general, working. All other requirements (such as
	performance, for instance, or perfectness of interfaces) have been left
	out of consideration. Therefore -
	Please do not blame us for quality of this library; and
	if you need anything practical, please check our repository or write your
	own perfect library :)
*******************************************************************************/

#ifndef SIMPLE_LIB_H
#define SIMPLE_LIB_H

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <assert.h>
#include <stdio.h>
#include <string>
using namespace std;

// classes below are used for support of discriminated unions

template <class discriminant_type> class DiscriminatedUnionDescriptorEntry
{
public:
	constexpr DiscriminatedUnionDescriptorEntry( discriminant_type dt, std::initializer_list<const char*> l ) {}
};

template <class discriminant_type> class DiscriminatedUnionDescriptor
{
public:
	constexpr DiscriminatedUnionDescriptor( std::initializer_list<DiscriminatedUnionDescriptorEntry<discriminant_type>> dud ) {}
};


// (De)serialization

class OStream
{
protected:
	FILE* outstr;
public:
	OStream( FILE* outStr ) : outstr( outStr ) {}
	// boolean
	void write_bool( bool x )	{uint8_t bx = x ? 1 : 0; fwrite( &bx, 1, 1, outstr );}
	// signed ints
	void write_int8_t( int8_t x )	{fwrite( &x, 1, 1, outstr );}
	void write_int16_t( int16_t x ){fwrite( &x, 2, 1, outstr );}
	void write_int32_t( int32_t x ){fwrite( &x, 4, 1, outstr );}
	void write_int64_t( int64_t x ){fwrite( &x, 8, 1, outstr );}
	// unsigned ints
	void write_uint8_t( uint8_t x ) {fwrite( &x, 1, 1, outstr );}
	void write_uint16_t( uint16_t x ){fwrite( &x, 2, 1, outstr );}
	void write_uint32_t( uint32_t x ){fwrite( &x, 4, 1, outstr );}
	void write_uint64_t( uint64_t x ){fwrite( &x, 8, 1, outstr );}
	// floating
	void write_float( float x ){fwrite( &x, sizeof(float), 1, outstr );}
	void write_double( double x ){fwrite( &x, sizeof(double), 1, outstr );}
	// strings
	void write_string( std::string x )
	{
		uint32_t sz = x.size();
		write_uint32_t( sz );
		fwrite( x.c_str(), sz, 1, outstr );
	}
};

class IStream
{
protected:
	uint8_t* instr;
	size_t buffSz;
	size_t readPos;
	size_t readData( uint8_t* buff, size_t cnt )
	{
		if ( readPos + cnt <= buffSz )
		{
			memcpy( buff, instr +readPos, cnt );
			readPos += cnt;
			return cnt;
		}
		else
		{
			cnt = buffSz - readPos;
			memcpy( buff, instr +readPos, cnt );
			readPos += cnt;
			return cnt;
		}
	}
public:
	IStream( uint8_t* inStr, size_t buffSz_ ) : instr( inStr ), buffSz( buffSz_ ) { readPos = 0; }
	// boolean
	bool read_bool( bool& x ) { uint8_t bx; bool ret = readData( reinterpret_cast<uint8_t*>(&bx), 1 ) == 1; x = bx != 0; return ret;}
	// signed ints
	bool read_int8_t( int8_t& x ) {	return readData( reinterpret_cast<uint8_t*>(&x), 1 ) == 1; }
	bool read_int16_t( int16_t& x ) {	return readData( reinterpret_cast<uint8_t*>(&x), 2 ) == 2; }
	bool read_int32_t( int32_t& x ) {	return readData( reinterpret_cast<uint8_t*>(&x), 4 ) == 4; }
	bool read_int64_t( int64_t& x ) {	return readData( reinterpret_cast<uint8_t*>(&x), 8 ) == 8; }
	// unsigned ints
	bool read_uint8_t( bool& x ) { return read_bool(x); }
	bool read_uint8_t( uint8_t& x )   {return readData( reinterpret_cast<uint8_t*>(&x), 1 ) == 1; }
	bool read_uint16_t( uint16_t& x ) {return readData( reinterpret_cast<uint8_t*>(&x), 2 ) == 2; }
	bool read_uint32_t( uint32_t& x ) {return readData( reinterpret_cast<uint8_t*>(&x), 4 ) == 4; }
	bool read_uint64_t( uint64_t& x ) {return readData( reinterpret_cast<uint8_t*>(&x), 8 ) == 8; }
	// floating
	bool read_float( float& x ) {return readData( reinterpret_cast<uint8_t*>(&x), sizeof(float) ) == sizeof(float); }
	bool read_double( double& x ) {return readData( reinterpret_cast<uint8_t*>(&x), sizeof(double) ) == sizeof(double); }
	// strings
	bool read_string( string& x )
	{
		uint32_t sz;
		bool ret = read_uint32_t( sz );
		if (!ret )
			return false;
/*		x.resize( sz + 1 );
		uint8_t* strBuff = reinterpret_cast<uint8_t*>(const_cast<char*>(x.c_str()));
		strBuff[sz] = 0;*/
		for (uint32_t i=0; i<sz; i++ )
		{
			signed char ch;
			if (!read_int8_t( ch ))
				return false;
			x.push_back( ch );
		}
//		return readData( strBuff, sz ) == sz;
		return true;
	}
};

#endif // SIMPLE_LIB_H

