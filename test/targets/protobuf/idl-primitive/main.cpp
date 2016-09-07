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
#include "dbg_helpers.h"
#include "../test_helper.h"


using namespace std;


TEST(IdlPrimitive, AllZero)
{
    TestClass tc;

    tc.integer0 = 0;
    tc.integer1 = 0;
    tc.integer2 = 0;
    tc.integer3 = 0;

    tc.floating0 = 0;

    tc.typedef0 = 0;
    tc.typedef1 = 0;
    tc.typedef2 = 0;

    tc.typedef4 = 0;
    tc.typedef5 = 0;
    tc.typedef6 = 0;

    testHelper(tc, &serializeTestClass, &deserializeTestClass, &assertEqualTestClass, "file10", {
//        0x10, 0x01, 0x0a, 0x03, 'A', 'b', 'c', 0x18, 0x02
    });
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

