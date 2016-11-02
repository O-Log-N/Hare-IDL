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

#include "front-back/idl_tree.h"
#include "output.h"
#include "output.pb.h"

#include "gtest/gtest.h"
#include "dbg_helpers.h"
#include "dbg_proto_helpers.h"
#include "protobuf/baselib.h"

#include "front-back/idl_tree_serializer.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void protobufTestLoop(const Root& toSend, const char* fileName)
{
    string fullName(fileName);
    fullName += ".protobuf.bin";

    FILE* out = fopen(fullName.c_str(), "w+b");
    ASSERT_NE(out, nullptr);
    OProtobufStream o(out);

    harepb::serializeRoot(toSend, o);
    fclose(out);

    fstream is(fullName, ios::in | ios::binary);

    pb::Root gpb;
    ASSERT_TRUE(gpb.ParseFromIstream(&is));

    harepb::assertEqualRoot(toSend, gpb);

    stringstream os;
    ASSERT_TRUE(gpb.SerializeToOstream(&os));

    string buff = os.str();
    IProtobufStream ipbs(reinterpret_cast<const uint8_t*>(buff.c_str()), buff.size());

    unique_ptr<Root> recv(new Root);
    ASSERT_TRUE(harepb::deserializeRoot(*recv, ipbs));

    harepb::assertEqualRoot(toSend, *recv);
}


TEST(GpbLoop, Test10)
{
    Root tc;

    protobufTestLoop(tc, "file10");
}

TEST(GpbLoop, Test11)
{
    uint8_t baseBuff[0x10000];
    FILE* in = fopen( "idl_tree.h.idlbin", "rb" );
    ASSERT_TRUE(in != nullptr);

    size_t sz = fread( baseBuff, 1, 0x10000, in );
    fclose( in );
    IStream i( baseBuff, sz );


    Root tc;
    ASSERT_TRUE(deserializeRoot( tc, i ));
    protobufTestLoop(tc, "file11");

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

