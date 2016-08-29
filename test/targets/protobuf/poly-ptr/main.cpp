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

TEST(PolyPtr, NullPtr)
{
    TestClass tc;

    protobufSerializeToFile(tc, &serializeTestClass, "file10", {
        0x0a, 0x00
    });
}

TEST(PolyPtr, BasePtr)
{
    TestClass tc;
    tc.ptr.reset(new TestBase);

    protobufSerializeToFile(tc, &serializeTestClass, "file11", {
        0x0a, 0x04,
        0x12, 0x02, 0x08, 0x00 
    });
}

TEST(PolyPtr, DerivedPtr)
{
    TestClass tc;
    tc.ptr.reset(new TestDerived);

    protobufSerializeToFile(tc, &serializeTestClass, "file20", {
        0x0a, 0x06,
        0x1a, 0x04, 0x0a, 0x02, 0x08, 0x00
    });
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

