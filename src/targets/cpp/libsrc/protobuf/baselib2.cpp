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

#define IS_LITTLE_ENDIAN 1

namespace bl2
{

uint8_t* deserializeHeaderFromString(int& fieldNumber, int& type, uint8_t* buff)
{
    uint64_t key;
    buff = deserializeFromStringVariantUint64(key, buff);
    type = key & 7;
    fieldNumber = key >> 3;
    return buff;
}

///////////////////////////   WIRE_TYPE::VARINT      ////////////////////////////////////

/*
    mb: manual loop unrool seems to be detrimental for this particular case.
*/


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



/*
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
*/

/* mb:  manual loop unroll goes faster,
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

#if IS_LITTLE_ENDIAN

uint8_t* serializeToStringFixedUint64(uint64_t value, uint8_t* buff)
{
    *reinterpret_cast<uint64_t*>(buff) = value;
    return buff + 8;
}

uint8_t* deserializeFromStringFixedUint64(uint64_t& value, uint8_t* buff)
{
    value = *reinterpret_cast<uint64_t*>(buff);
    return buff + 8;
}

#else

uint8_t* serializeToStringFixedUint64(uint64_t value, uint8_t* buff)
{
    for (int ctr = 0; ctr < 8; ++ctr)
    {
        *(buff++) = value & 0xff;
        value >>= 8;
    }
    return buff;
}

uint8_t* deserializeFromStringFixedUint64(uint64_t& value, uint8_t* buff)
{
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

#endif


///////////////////////////     WIRE_TYPE::FIXED_32_BIT    ////////////////////////////////////

#if IS_LITTLE_ENDIAN

uint8_t* serializeToStringFixedUint32(uint32_t value, uint8_t* buff)
{
    *reinterpret_cast<uint32_t*>(buff) = value;
    return buff + 4;
}

uint8_t* deserializeFromStringFixedUint32(uint32_t& value, uint8_t* buff)
{
    value = *reinterpret_cast<uint32_t*>(buff);
    return buff + 4;
}

#else

uint8_t* serializeToStringFixedUint32(uint32_t value, uint8_t* buff)
{
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

#endif
///////////////////////////     WIRE_TYPE::LENGTH_DELIMITED    ////////////////////////////////////

uint8_t* serializeLengthDelimitedHeaderToString(int fieldNumber, size_t valueSize, uint8_t* buff)
{
    buff = serializeHeaderToString(fieldNumber, LENGTH_DELIMITED, buff);
    return serializeToStringVariantUint64(valueSize, buff);
}



//MB
bool discardUnexpectedField( int fieldType, IProtobufStream& i ) {

  // Unexpected field, just read and discard
  switch(fieldType)
  {
  case VARINT:
    {
      uint64_t temp;
      return i.readVariantUInt64( temp );
    }
    break;
  case FIXED_64_BIT:
    {
      double temp;
      return i.readFixed64Bit( temp );
    }
    break;
  case LENGTH_DELIMITED:
    {
      uint64_t sz;
      bool readOk = i.readVariantUInt64( sz );
      if( !readOk )
        return false;
      IProtobufStream is = i.makeSubStream( readOk, sz );
      if ( !readOk )
        return false;

      string temp;
      return is.readString( temp );
    }
    break;
  case FIXED_32_BIT:
    {
      float temp;
      return i.readFixed32Bit( temp );
    }
    break;
  default:
    return false;
  }
}

} //namespace bl

