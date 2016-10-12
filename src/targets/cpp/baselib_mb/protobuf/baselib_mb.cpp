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
#include <protobuf/baselib_mb.h>

#define BASELIB_LITTLE_ENDIAN


uint8_t* deserializeHeaderFromString(int& fieldNumber, int& type, uint8_t* buff)
{
    uint64_t key;
    buff = deserializeFromStringVariantUint64(key, buff);
    type = static_cast<int>(key & 7);
    fieldNumber = static_cast<int>(key >> 3);
    return buff;
}

///////////////////////////   WIRE_TYPE::VARINT      ////////////////////////////////////

/*
mb: manual loop unrool seems to be detrimental for this particular case.
*/

uint8_t* serializeToStringVariantUint64(uint64_t value, uint8_t* buff)
{
    if (value > 0x7f) {
        *(buff++) = (value & 0x7f) | 0x80;
        value >>= 7;
        if (value > 0x7f) {
            *(buff++) = (value & 0x7f) | 0x80;
            value >>= 7;
            if (value > 0x7f) {
                *(buff++) = (value & 0x7f) | 0x80;
                value >>= 7;
                if (value > 0x7f) {
                    *(buff++) = (value & 0x7f) | 0x80;
                    value >>= 7;
                    if (value > 0x7f) {
                        *(buff++) = (value & 0x7f) | 0x80;
                        value >>= 7;
                        if (value > 0x7f) {
                            *(buff++) = (value & 0x7f) | 0x80;
                            value >>= 7;
                            if (value > 0x7f) {
                                *(buff++) = (value & 0x7f) | 0x80;
                                value >>= 7;
                                if (value > 0x7f) {
                                    *(buff++) = (value & 0x7f) | 0x80;
                                    value >>= 7;
                                    if (value > 0x7f) {
                                        *(buff++) = (value & 0x7f) | 0x80;
                                        value >>= 7;
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }
    }
    *(buff++) = value & 0x7f;
    return buff;
}

/* mb:  manual loop unroll goes a little slower on Linux 64bits,
        but more importantly is that it will not keep eating from the buffer
        in case of a broken packet. It will always stop after 10 bytes.
        TODO: how to signal such stream error
*/

uint8_t* deserializeFromStringVariantUint64(uint64_t& value, uint8_t* buff)
{
    value = 0;
    {
        value |= uint64_t(*buff & 0x7f);
        if (*buff & 0x80)
        {
            ++buff;
            value |= uint64_t(*buff & 0x7f) << 7;
            if (*buff & 0x80)
            {
                ++buff;
                value |= uint64_t(*buff & 0x7f) << 14;
                if (*buff & 0x80)
                {
                    ++buff;
                    value |= uint64_t(*buff & 0x7f) << 21;
                    if (*buff & 0x80)
                    {
                        ++buff;
                        value |= uint64_t(*buff & 0x7f) << 28;
                        if (*buff & 0x80)
                        {
                            ++buff;
                            value |= uint64_t(*buff & 0x7f) << 35;
                            if (*buff & 0x80)
                            {
                                ++buff;
                                value |= uint64_t(*buff & 0x7f) << 42;
                                if (*buff & 0x80)
                                {
                                    ++buff;
                                    value |= uint64_t(*buff & 0x7f) << 49;
                                    if (*buff & 0x80)
                                    {
                                        ++buff;
                                        value |= uint64_t(*buff & 0x7f) << 56;
                                        if (*buff & 0x80)
                                        {
                                            ++buff;
                                            value |= uint64_t(*buff & 0x7f) << 63;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ++buff;
    return buff;
}



///////////////////////////   WIRE_TYPE::FIXED_64_BIT      ////////////////////////////////////

#ifdef BASELIB_LITTLE_ENDIAN

uint8_t* serializeToStringFixedUint64(uint64_t value, uint8_t* buff)
{
    *reinterpret_cast<uint64_t*>(buff) = value;
    return buff + 8;
}

#else
uint8_t* serializeToStringFixedUint64(uint64_t value, uint8_t* buff)
{
    buff[0] = value & 0xff;
    buff[1] = (value >> 8) & 0xff;
    buff[2] = (value >> 16) & 0xff;
    buff[3] = (value >> 24) & 0xff;
    buff[4] = (value >> 32) & 0xff;
    buff[5] = (value >> 40) & 0xff;
    buff[6] = (value >> 48) & 0xff;
    buff[7] = (value >> 56) & 0xff;

    return buff + 8;
}

#endif

uint8_t* deserializeFromStringFixedUint64(uint64_t& value, uint8_t* buff)
{
    uint64_t value0 = uint64_t(buff[0]);
    uint64_t value1 = uint64_t(buff[1]) << 8;
    uint64_t value2 = uint64_t(buff[2]) << 16;
    uint64_t value3 = uint64_t(buff[3]) << 24;
    uint64_t value4 = uint64_t(buff[4]) << 32;
    uint64_t value5 = uint64_t(buff[5]) << 40;
    uint64_t value6 = uint64_t(buff[6]) << 48;
    uint64_t value7 = uint64_t(buff[7]) << 56;

    value = value0 | value1 | value2 | value3 | value4 | value5 | value6 | value7;

    return buff + 8;
}



///////////////////////////     WIRE_TYPE::FIXED_32_BIT    ////////////////////////////////////

#ifdef BASELIB_LITTLE_ENDIAN

uint8_t* serializeToStringFixedUint32(uint32_t value, uint8_t* buff)
{
    *reinterpret_cast<uint32_t*>(buff) = value;
    return buff + 4;
}

#else

uint8_t* serializeToStringFixedUint32(uint32_t value, uint8_t* buff)
{
    buff[0] = value & 0xff;
    buff[1] = (value >> 8) & 0xff;
    buff[2] = (value >> 16) & 0xff;
    buff[3] = (value >> 24) & 0xff;

    return buff + 4;
}

#endif

uint8_t* deserializeFromStringFixedUint32(uint32_t& value, uint8_t* buff)
{
    uint32_t value0 = uint32_t(buff[0]);
    uint32_t value1 = uint32_t(buff[1]) << 8;
    uint32_t value2 = uint32_t(buff[2]) << 16;
    uint32_t value3 = uint32_t(buff[3]) << 24;

    value = value0 | value1 | value2 | value3;

    return buff + 4;
}


///////////////////////////     WIRE_TYPE::LENGTH_DELIMITED    ////////////////////////////////////

uint8_t* serializeLengthDelimitedHeaderToString(int fieldNumber, size_t valueSize, uint8_t* buff)
{
    buff = serializeHeaderToString(fieldNumber, LENGTH_DELIMITED, buff);
    return serializeToStringVariantUint64(valueSize, buff);
}


//mb
bool discardUnexpectedField(int fieldType, IProtobufStream& i) {

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
        /* TODO test
        uint64_t sz;
        bool readOk = i.readVariantUInt64(sz);
        if (!readOk)
        return false;
        size_t eos = i.makeSubStream(readOk, eos, sz);
        if (!readOk)
        return false;
        */
        string temp;
        return i.readString(temp);
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

