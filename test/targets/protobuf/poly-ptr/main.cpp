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

TEST(PolyPtr, NullPtr)
{
    TestClass tc;

    testHelper(tc, &serializeTestClass, &deserializeTestClass, &assertEqualTestClass, "file10", {
        0x0a, 0x00
    });
}

TEST(PolyPtr, BasePtr)
{
    TestClass tc;
    tc.ptr.reset(new TestBase);

    testHelper(tc, &serializeTestClass, &deserializeTestClass, &assertEqualTestClass, "file11", {
        0x0a, 0x04,
        0x12, 0x02, 0x08, 0x00 
    });
}

TEST(PolyPtr, DerivedPtr)
{
    TestClass tc;
    tc.ptr.reset(new TestDerived);

    testHelper(tc, &serializeTestClass, &deserializeTestClass, &assertEqualTestClass, "file20", {
        0x0a, 0x06,
        0x1a, 0x04, 0x0a, 0x02, 0x08, 0x00
    });
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

