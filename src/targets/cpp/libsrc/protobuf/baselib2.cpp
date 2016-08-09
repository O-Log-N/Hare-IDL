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
#include <protobuf/baselib2.h>

namespace bl2
{



uint8_t* serializeHeaderToString(int fieldNumber, WIRE_TYPE wire_type, uint8_t* buff)
{
    uint64_t key = (fieldNumber << 3) | wire_type;
    return serializeToStringVariantUint64(key, buff);
}

uint8_t* deserializeHeaderFromString(int& fieldNumber, int& type, uint8_t* buff)
{
    uint64_t key;
    buff = deserializeFromStringVariantUint64(key, buff);
    type = key & 7;
    fieldNumber = key >> 3;
    return buff;
}

///////////////////////////   WIRE_TYPE::VARINT      ////////////////////////////////////

uint8_t* serializeToStringVariantUint64(uint64_t value, uint8_t* buff)
{
    while (value >= 0x80)
    {
        *buff = value & 0x7f;
        *(buff++) |= 0x80;
        value >>= 7;
    }
    *buff = value & 0x7f;
    ++buff;
    return buff;
}

uint8_t* deserializeFromStringVariantUint64(uint64_t& value, uint8_t* buff)
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
    } while (*(buff++) & 0x80);

    return buff;
}




///////////////////////////   WIRE_TYPE::FIXED_64_BIT      ////////////////////////////////////

uint8_t* serializeToStringFixedUint64(uint64_t value, uint8_t* buff)
{
    // TODO: version favouring little endian platforms
    for (int ctr = 0; ctr < 8; ++ctr)
    {
        *(buff++) = value & 0xff;
        value >>= 8;
    }
    return buff;
}

uint8_t* deserializeFromStringFixedUint64(uint64_t& value, uint8_t* buff)
{
    // TODO: version favouring little endian platforms
    value = 0;
    uint64_t tmp;

    for (int ctr = 0; ctr < 64; ctr += 8)
    {
        tmp = *(buff++);
        tmp <<= ctr;
        value |= tmp;
    }

    return buff;
}


///////////////////////////     WIRE_TYPE::FIXED_32_BIT    ////////////////////////////////////

uint8_t* serializeToStringFixedUint32(uint32_t value, uint8_t* buff)
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

uint8_t* deserializeFromStringFixedUint32(uint32_t& value, uint8_t* buff)
{
    // TODO: version favouring little endian platforms
    value = 0;
    uint32_t tmp;

    for (int ctr = 0; ctr < 32; ctr += 8)
    {
        tmp = *(buff++);
        tmp <<= ctr;
        value |= tmp;
    }

    return buff;
}

///////////////////////////     WIRE_TYPE::LENGTH_DELIMITED    ////////////////////////////////////

uint8_t* serializeLengthDelimitedHeaderToString(int fieldNumber, size_t valueSize, uint8_t* buff)
{
    buff = serializeHeaderToString(fieldNumber, LENGTH_DELIMITED, buff);
    return serializeToStringVariantUint64(valueSize, buff);
}


} //namespace bl

