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
#include <array>


pair<bool, uint64_t> readVarInt(istream& is)
{
    uint64_t result = 0;
    char current = 0;
    unsigned offset = 0;

    //Little endian version
    do {
        is.get(current);
        result |= static_cast<uint64_t>(current & 0x7f) << offset;
        offset += 7; //TODO check where don't go away 64 bits
    } while((current & 0x80) != 0);

    return make_pair(is.good(), result);
}

pair<bool, uint64_t> readFixed64(istream& is)
{
    uint64_t result = 0;
    //Little endian version
    is.read(reinterpret_cast<char*>(&result), sizeof(uint64_t));
    return make_pair(is.good(), result);
}

pair<bool, uint32_t> readFixed32(istream& is)
{
    uint32_t result = 0;
    //Little endian version
    is.read(reinterpret_cast<char*>(&result), sizeof(uint32_t));
    return make_pair(is.good(), result);
}

pair<bool, string> readLengthDelimitedString(istream& is)
{
    pair<bool, uint64_t> s = readVarInt(is);
    string result;
    if (s.first && s.second < result.max_size()) {
        result.resize(static_cast<string::size_type>(s.second));
        is.read(const_cast<char*>(result.data()), result.size());
        return make_pair(is.good(), result);
    }
    return make_pair(false, result);
}

void writeVarInt(ostream& os, uint64_t value)
{
    uint64_t result = 0;
    char current = 0;

    //Little endian version


    while ((value & 0xffffffffffffff80) != 0) {
        char current = (value & 0x7f) | 0x80;
        os.put(current);
        value >>= 7;
    }

    os.put(static_cast<char>(value));
}
void writeFixed64(ostream& os, uint64_t value)
{
    os.write(reinterpret_cast<const char*>(&value), 8);
}
void writeFixed32(ostream& os, uint32_t value)
{
    os.write(reinterpret_cast<const char*>(&value), 4);
}
void writeLengthDelimitedString(ostream& os, const string& value)
{
    writeVarInt(os, value.size());
    os.write(value.c_str(), value.size());
}


