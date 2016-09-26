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

#ifndef BASELIB_FUNC_BENCHMARK_H
#define BASELIB_FUNC_BENCHMARK_H

#include <iostream>
#include <memory>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <cstring>

using namespace std;

#
namespace bnchmrk
{


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


} //namespace bnchmrk

#endif // BASELIB_FUNC_BENCHMARK_H

