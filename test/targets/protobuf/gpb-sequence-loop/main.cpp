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
#include "output.pb.h"

#include "gtest/gtest.h"
#include "dbg_assert_equal.h"
#include "protobuf/baselib.h"


#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void protobufTestLoop(const TestClass& toSend, const char* fileName)
{
    string fullName(fileName);
    fullName += ".protobuf.bin";

    FILE* out = fopen(fullName.c_str(), "w+b");
    ASSERT_NE(out, nullptr);
    OProtobufStream o(out);

    serializeTestClass(toSend, o);
    fclose(out);

    fstream is(fullName, ios::in | ios::binary);

    pb::TestClass gpb;
    ASSERT_TRUE(gpb.ParseFromIstream(&is));

    assertEqualTestClass(toSend, gpb);

    stringstream os;
    ASSERT_TRUE(gpb.SerializeToOstream(&os));

    string buff = os.str();
    IProtobufStream ipbs(reinterpret_cast<const uint8_t*>(buff.c_str()), buff.size());

    unique_ptr<TestClass> recv(new TestClass);
    ASSERT_TRUE(deserializeTestClass(*recv, ipbs));

    assertEqualTestClass(toSend, *recv);
}


TEST(GpbLoop, Test10)
{
    TestClass tc;

    protobufTestLoop(tc, "test10");
}

TEST(GpbLoop, Test11)
{
    TestClass tc;

    tc.someUints.push_back(10);
    tc.someUints.push_back(1000);
    tc.someUints.push_back(100000);
    tc.someUints.push_back(10000000);

    tc.someInts.push_back(10);
    tc.someInts.push_back(-1000);
    tc.someInts.push_back(100000);
    tc.someInts.push_back(-10000000);

    tc.someFloats.push_back(1.0);
    tc.someFloats.push_back(2.0);

    tc.someDoubles.push_back(1.0);
    tc.someDoubles.push_back(2.0);
    tc.someDoubles.push_back(3.0);
    tc.someDoubles.push_back(4.0);

    tc.someStrings.push_back("Hello");
    tc.someStrings.push_back("world!");

    //mb: THIS HAS A BUG, FIX

    tc.someValues.push_back(TestClass::Nothing);
    tc.someValues.push_back(TestClass::First);
    tc.someValues.push_back(TestClass::Second);
/*
    tc.someBools.push_back(true);
    tc.someBools.push_back(false);
*/
    protobufTestLoop(tc, "test11");
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

