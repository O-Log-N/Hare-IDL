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

TEST(BasicTypes, UnsignedVarIntZero)
{
    TestUnsigned tc;

    protobufSerializeToFile(tc, &serializeTestUnsigned, "test10", {
        0x08, 0x00,
        0x10, 0x00
    });
}

TEST(BasicTypes, UnsignedVarIntMax)
{
    TestUnsigned tc;

    tc.max_u32 = UINT32_MAX;
    tc.max_u64 = UINT64_MAX;

    protobufSerializeToFile(tc, &serializeTestUnsigned, "test11", {
        0x08, 0xff, 0xff, 0xff, 0xff, 0x0f,
        0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01
    });
}

TEST(BasicTypes, SignedVarIntZero)
{
    TestSigned tc;

    protobufSerializeToFile(tc, &serializeTestSigned, "test20", {
        0x08, 0x00,
        0x10, 0x00
    });
}

TEST(BasicTypes, SignedVarIntMin)
{
    TestSigned tc;

    tc.max_s32 = INT32_MIN;
    tc.max_s64 = INT64_MIN;

    protobufSerializeToFile(tc, &serializeTestSigned, "tes21", {
        0x08, 0xff, 0xff, 0xff, 0xff, 0x0f,
        0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01
    });
}


TEST(BasicTypes, SignedVarIntMax)
{
    TestSigned tc;

    tc.max_s32 = INT32_MAX;
    tc.max_s64 = INT64_MAX;

    protobufSerializeToFile(tc, &serializeTestSigned, "test22", {
        0x08, 0xfe, 0xff, 0xff, 0xff, 0x0f,
        0x10, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01
    });
}

TEST(BasicTypes, FixedFpZero)
{
    TestFixed tc;

    protobufSerializeToFile(tc, &serializeTestFixed, "test30", {
        0x0d, 0x00, 0x00, 0x00, 0x00,
        0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    });
}

TEST(BasicTypes, FixedFpNonZero)
{
    TestFixed tc;

    tc.aFloat = -128;
    tc.aDouble = 128;

    protobufSerializeToFile(tc, &serializeTestFixed, "test31", {
        0x0d, 0x00, 0x00, 0x00, 0xc3,
        0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x40
    });
}

TEST(BasicTypes, StringEmpty)
{
    TestString tc;

    protobufSerializeToFile(tc, &serializeTestString, "test40", {
        0x0a, 0x00 
    });
}

TEST(BasicTypes, StringText)
{
    TestString tc;

    tc.description = "Hello world!";

    protobufSerializeToFile(tc, &serializeTestString, "test41", {
        0x0a, 0x0c, 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'
    });
}

TEST(BasicTypes, EnumBool0)
{
    TestMisc tc;

    protobufSerializeToFile(tc, &serializeTestMisc, "test50", {
        0x08, 0x01,
        0x10, 0x00
    });
}

TEST(BasicTypes, EnumBool1)
{
    TestMisc tc;

    tc.aValue = TestMisc::Second;
    tc.flag = true;

    protobufSerializeToFile(tc, &serializeTestMisc, "test51", {
          0x08, 0x02,
          0x10, 0x01 
    });
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

