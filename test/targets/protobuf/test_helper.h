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
void testHelper(const T& root, size_t(*serialize)(const T&, OProtobufStream& os), bool(*deserialize)(T&, IProtobufStream& os, size_t),
    void(*assertEqual)(const T&, const T&), const char* fileName, const vector<uint8_t>& result)
{
    FakeBufferManager manager(4096);

    OProtobufStream o(manager);

    size_t sz = serialize(root, o);

    const BufferGroup& buff = o.getBufferSet();

    if(!result.empty()) {
        ASSERT_TRUE(areEqual(buff, result.begin(), result.end()));
    }
    else {
        string fullName(fileName);
        fullName += ".protobuf.bin";

        FILE* f = fopen(fullName.c_str(), "w+b");
        ASSERT_NE(f, nullptr);

        writeFile(f, buff);
    }

    IProtobufStream i(buff);
    T deserialized;

    ASSERT_TRUE(deserialize(deserialized, i, SIZE_MAX));
    assertEqual(root, deserialized);
}

template<class T>
void testHelper(const T& root, size_t(*serialize)(const T&, OProtobufStream& os), const char* fileName, const vector<uint8_t>& result)
{
    FakeBufferManager manager(4096);

    OProtobufStream o(manager);

    size_t sz = serialize(root, o);

    const BufferGroup& buff = o.getBufferSet();

    if(!result.empty()) {
        ASSERT_TRUE(buff, result.begin(), result.end());
    }
    else {
        string fullName(fileName);
        fullName += ".protobuf.bin";

        FILE* f = fopen(fullName.c_str(), "w+b");
        ASSERT_NE(f, nullptr);

        writeFile(f, buff);
    }
}
