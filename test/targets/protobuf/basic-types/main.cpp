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

#define _CRT_SECURE_NO_WARNINGS

#include "test.h"
#include "output.h"
#include "../test_helper.h"
#include "dbg_helpers.h"

TEST(BasicTypes, UnsignedVarIntZero)
{
    TestUnsigned tc;

    testHelper(tc, &serializeTestUnsigned, &deserializeTestUnsigned, &assertEqualTestUnsigned, "file10", {
        0x08, 0x00,
        0x10, 0x00
    });
}

TEST(BasicTypes, UnsignedVarIntMax)
{
    TestUnsigned tc;

    tc.max_u32 = UINT32_MAX;
    tc.max_u64 = UINT64_MAX;

    testHelper(tc, &serializeTestUnsigned, &deserializeTestUnsigned, &assertEqualTestUnsigned, "file11", {
        0x08, 0xff, 0xff, 0xff, 0xff, 0x0f,
        0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01
    });
}

TEST(BasicTypes, SignedVarIntZero)
{
    TestSigned tc;

    testHelper(tc, &serializeTestSigned, &deserializeTestSigned, &assertEqualTestSigned, "file20", {
        0x08, 0x00,
        0x10, 0x00
    });
}

TEST(BasicTypes, SignedVarIntMin)
{
    TestSigned tc;

    tc.max_s32 = INT32_MIN;
    tc.max_s64 = INT64_MIN;

    testHelper(tc, &serializeTestSigned, &deserializeTestSigned, &assertEqualTestSigned, "file21", {
        0x08, 0xff, 0xff, 0xff, 0xff, 0x0f,
        0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01
    });
}


TEST(BasicTypes, SignedVarIntMax)
{
    TestSigned tc;

    tc.max_s32 = INT32_MAX;
    tc.max_s64 = INT64_MAX;

    testHelper(tc, &serializeTestSigned, &deserializeTestSigned, &assertEqualTestSigned, "file22", {
        0x08, 0xfe, 0xff, 0xff, 0xff, 0x0f,
        0x10, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01
    });
}

TEST(BasicTypes, FixedFpZero)
{
    TestFixed tc;

    testHelper(tc, &serializeTestFixed, &deserializeTestFixed, &assertEqualTestFixed, "file30", {
        0x0d, 0x00, 0x00, 0x00, 0x00,
        0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    });
}

TEST(BasicTypes, FixedFpNonZero)
{
    TestFixed tc;

    tc.aFloat = -128;
    tc.aDouble = 128;

    testHelper(tc, &serializeTestFixed, &deserializeTestFixed, &assertEqualTestFixed, "file31", {
        0x0d, 0x00, 0x00, 0x00, 0xc3,
        0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x40
    });
}

TEST(BasicTypes, StringEmpty)
{
    TestString tc;

    testHelper(tc, &serializeTestString, &deserializeTestString, &assertEqualTestString, "file40", {
        0x0a, 0x00 
    });
}

TEST(BasicTypes, StringText)
{
    TestString tc;

    tc.description = "Hello world!";

    testHelper(tc, &serializeTestString, &deserializeTestString, &assertEqualTestString, "file41", {
        0x0a, 0x0c, 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'
    });
}

TEST(BasicTypes, EnumBool0)
{
    TestMisc tc;

    testHelper(tc, &serializeTestMisc, &deserializeTestMisc, &assertEqualTestMisc, "file50", {
        0x08, 0x01,
        0x10, 0x00
    });
}

TEST(BasicTypes, EnumBool1)
{
    TestMisc tc;

    tc.aValue = TestMisc::Second;
    tc.flag = true;

    testHelper(tc, &serializeTestMisc, &deserializeTestMisc, &assertEqualTestMisc, "file51", {
          0x08, 0x02,
          0x10, 0x01 
    });
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

