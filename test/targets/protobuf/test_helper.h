/*******************************************************************************
Copyright (C) 2016 OLogN Technologies AG

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

#include <iostream>

#include "protobuf/baselib.h"
#include "gtest/gtest.h"

using namespace std;

template<class T>
void testHelper(const T& root, size_t(*serialize)(const T&, OProtobufStream& os), bool(*deserialize)(T&, IProtobufStream& os),
    void(*assertEqual)(const T&, const T&), const char* fileName, const vector<uint8_t>& result)
{
    string fullName(fileName);
    fullName += ".protobuf.bin";

    FILE* f = fopen(fullName.c_str(), "w+b");
    ASSERT_NE(f, nullptr);
    OProtobufStream o(f);

    size_t sz = serialize(root, o);


    vector<uint8_t> toRead(sz);

    rewind(f);
    size_t readSize = fread(&toRead[0], sizeof(toRead[0]), toRead.size(), f);

    ASSERT_EQ(readSize, sz);
    ASSERT_EQ(fgetc(f), EOF);

    fclose(f);

    if(!result.empty()) {
        ASSERT_EQ(readSize, result.size());
        for(size_t i = 0; i < result.size(); ++i) {
            EXPECT_EQ(result[i], toRead[i]);
        }
    }

    IProtobufStream i(&toRead[0], toRead.size());
    T deserialized;

    ASSERT_TRUE(deserialize(deserialized, i));
    assertEqual(root, deserialized);
}

template<class T>
void testHelper(const T& root, size_t(*serialize)(const T&, OProtobufStream& os), const char* fileName, const vector<uint8_t>& result)
{
    string fullName(fileName);
    fullName += ".protobuf.bin";

    FILE* f = fopen(fullName.c_str(), "w+b");
    ASSERT_NE(f, nullptr);
    OProtobufStream o(f);

    size_t sz = serialize(root, o);


    vector<uint8_t> toRead(sz);

    rewind(f);
    size_t readSize = fread(&toRead[0], sizeof(toRead[0]), toRead.size(), f);

    ASSERT_EQ(readSize, sz);
    ASSERT_EQ(fgetc(f), EOF);

    fclose(f);

    if(!result.empty()) {
        ASSERT_EQ(readSize, result.size());
        for(size_t i = 0; i < result.size(); ++i) {
            EXPECT_EQ(result[i], toRead[i]);
        }
    }
}
