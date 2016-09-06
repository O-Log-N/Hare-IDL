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

#include "output_declare.h"
#include "output.h"
#include "../test_helper.h"
#include "dbg_helpers.h"

TEST(DiscriminatedUnion, OptionAbc)
{
    TestClass tc;
    tc.disc = TestClass::Abc;
    tc.name = "Abc";
    tc.value1 = 1;

    testHelper(tc, &serializeTestClass, &deserializeTestClass, &assertEqualTestClass, "file10", {
        0x10, 0x00, 0x0a, 0x03, 'A', 'b', 'c', 0x18, 0x02
    });
}

TEST(DiscriminatedUnion, OptionDef)
{
    TestClass tc;
    tc.disc = TestClass::Def;
    tc.name = "Def";
    tc.value1 = 1;

    testHelper(tc, &serializeTestClass, &deserializeTestClass, &assertEqualTestClass, "file11", {
        0x10, 0x01, 0x0a, 0x03, 'D', 'e', 'f', 0x18, 0x02
    });
}

TEST(DiscriminatedUnion, OptionGhi)
{
    TestClass tc;
    tc.disc = TestClass::Ghi;
    tc.name = "Ghi";
    tc.value2 = 1;

    testHelper(tc, &serializeTestClass, &deserializeTestClass, &assertEqualTestClass, "file12", {
        0x10, 0x02, 0x0a, 0x03, 'G', 'h', 'i', 0x20, 0x02
    });
}

TEST(DiscriminatedUnion, OptionKlm)
{
    TestClass tc;
    tc.disc = TestClass::Klm;
    tc.name = "Klm";
    tc.value3 = 1;

    testHelper(tc, &serializeTestClass, &deserializeTestClass, &assertEqualTestClass, "file13", {
        0x10, 0x03, 0x0a, 0x03, 'K', 'l', 'm', 0x28, 0x02
    });
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

