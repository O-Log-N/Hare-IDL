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

#include <iostream>

using namespace std;

template<class T>
void protobufSerializeToFile(const T& root, void(*func)(const T&, OProtobufStream& os), const char* fileName, const vector<uint8_t>& result)
{
    FILE* out = fopen(fileName, "w+b");
    assert(out);
    OProtobufStream o(out);

    func(root, o);

    if(!result.empty()) {

        vector<uint8_t> toRead(result.size());

        rewind(out);
        size_t readSize = fread(&toRead[0], sizeof(toRead[0]), toRead.size(), out);

        assert(readSize == result.size());
        assert(fgetc(out) == EOF);

        for(size_t i = 0; i < result.size(); ++i) {
            assert(result[i] == toRead[i]);
        }
    }
    fclose(out);
}

void test10(const char* tempFile)
{
    TestUnsigned tc;

    protobufSerializeToFile(tc, &serializeTestUnsigned, tempFile, {
        0x08, 0x00,
        0x10, 0x00
    });
}

void test11(const char* tempFile)
{
    TestUnsigned tc;

    tc.max_u32 = UINT32_MAX;
    tc.max_u64 = UINT64_MAX;

    protobufSerializeToFile(tc, &serializeTestUnsigned, tempFile, {
        0x08, 0xff, 0xff, 0xff, 0xff, 0x0f,
        0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01
    });
}

void test20(const char* tempFile)
{
    TestSigned tc;

    protobufSerializeToFile(tc, &serializeTestSigned, tempFile, {
        0x08, 0x00,
        0x10, 0x00
    });
}

void test21(const char* tempFile)
{
    TestSigned tc;

    tc.max_s32 = INT32_MIN;
    tc.max_s64 = INT64_MIN;

    protobufSerializeToFile(tc, &serializeTestSigned, tempFile,
        {}); //TODO not working
}


void test22(const char* tempFile)
{
    TestSigned tc;

    tc.max_s32 = INT32_MAX;
    tc.max_s64 = INT64_MAX;

    protobufSerializeToFile(tc, &serializeTestSigned, tempFile,
        {}); //TODO not working
}

void test30(const char* tempFile)
{
    TestFixed tc;

    protobufSerializeToFile(tc, &serializeTestFixed, tempFile, {
        0x0d, 0x00, 0x00, 0x00, 0x00,
        0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    });
}

void test31(const char* tempFile)
{
    TestFixed tc;

    tc.aFloat = -128;
    tc.aDouble = 128;

    protobufSerializeToFile(tc, &serializeTestFixed, tempFile, {
        0x0d, 0x00, 0x00, 0x00, 0xc3,
        0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x40
    });
}

void test40(const char* tempFile)
{
    TestString tc;

    protobufSerializeToFile(tc, &serializeTestString, tempFile, {
        0x0a, 0x00 
    });
}

void test41(const char* tempFile)
{
    TestString tc;

    tc.description = "Hello world!";

    protobufSerializeToFile(tc, &serializeTestString, tempFile, {
        0x0a, 0x0c, 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'
    });
}
void test50(const char* tempFile)
{
    TestMisc tc;

    protobufSerializeToFile(tc, &serializeTestMisc, tempFile, {
        0x08, 0x01,
        0x10, 0x00
    });
}

void test51(const char* tempFile)
{
    TestMisc tc;

    tc.aValue = TestMisc::Second;
    tc.flag = true;

    protobufSerializeToFile(tc, &serializeTestMisc, tempFile, {
          0x08, 0x02,
          0x10, 0x01 
    });
}


int main()
{
    test10("test10.protobuf.bin");
    test11("test11.protobuf.bin");
    test20("test20.protobuf.bin");
    test21("test21.protobuf.bin");
    test22("test22.protobuf.bin");
    test30("test30.protobuf.bin");
    test31("test31.protobuf.bin");
    test40("test40.protobuf.bin");
    test41("test41.protobuf.bin");
    test50("test50.protobuf.bin");
    test51("test51.protobuf.bin");

    printf("Ok!\n");

    return 0;
}