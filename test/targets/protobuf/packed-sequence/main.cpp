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

#include "test.h"
#include "output.h"
#include "protobuf/baselib.h"

#include "gtest/gtest.h"

#include <iostream>

using namespace std;

template<class T>
void protobufSerializeToFile(const T& root, void(*func)(const T&, OProtobufStream& os), const char* fileName, const vector<uint8_t>& result)
{
    string fullName(fileName);
    fullName += ".protobuf.bin";

    FILE* out = fopen(fullName.c_str(), "w+b");
    ASSERT_NE(out, nullptr);
    OProtobufStream o(out);

    func(root, o);

    if(!result.empty()) {

        vector<uint8_t> toRead(result.size());

        rewind(out);
        size_t readSize = fread(&toRead[0], sizeof(toRead[0]), toRead.size(), out);

        ASSERT_EQ(readSize, result.size());
        ASSERT_EQ(fgetc(out), EOF);

        for(size_t i = 0; i < result.size(); ++i) {
            EXPECT_EQ(result[i], toRead[i]);
        }
    }
    fclose(out);
}

TEST(PackedSequence, UnpackedStrings)
{
    TestClass tc;

    tc.unpackedStrings.push_back("hello");
    tc.unpackedStrings.push_back("world");

    protobufSerializeToFile(tc, &serializeTestClass, "test1", {
        0x0a, 5, 'h', 'e', 'l', 'l', 'o',
        0x0a, 5, 'w', 'o', 'r', 'l', 'd'
    });
}

TEST(PackedSequence, PackedVarInts)
{
    TestClass tc;

    tc.packedVarInts.push_back(0);
    tc.packedVarInts.push_back(1000);
    tc.packedVarInts.push_back(-1000);
    tc.packedVarInts.push_back(100000);
    tc.packedVarInts.push_back(-100000);

    protobufSerializeToFile(tc, &serializeTestClass, "test2", {
        0x12, 0x0b,
        0x00,
        0xd0, 0x0f,
        0xcf, 0x0f,
        0xbf, 0xe5, 0x03,
        0xc0, 0xe5, 0x03
    });
}

TEST(PackedSequence, packedDoubles)
{
    TestClass tc;

    tc.packedDoubles.push_back(0.);
    tc.packedDoubles.push_back(-1.);
    tc.packedDoubles.push_back(1.);
    tc.packedDoubles.push_back(-10.5e-6);

    protobufSerializeToFile(tc, &serializeTestClass, "test3", {
        0x1a, 0x20,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xbf,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f,
        0xc9, 0xc7, 0xee, 0x02, 0x25, 0x05, 0xe6, 0xbe
    });
}

TEST(PackedSequence, PackedEnum)
{
    TestClass tc;

    tc.packedEnum.push_back(TestClass::Nothing);
    tc.packedEnum.push_back(TestClass::First);
    tc.packedEnum.push_back(TestClass::Second);

    protobufSerializeToFile(tc, &serializeTestClass, "test4", {
        0x22, 0x03, 0x01, 0x00, 0x02
    });
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
