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

#include "idlc_include.h"
#include "front-back/idl_tree.h"
#include "back/idlc_back.h"

#include "front/idl/parser.h"
#include "front-back/idl_tree_serializer.h"


Root* deserializeFile(const char* fileName) {
    unique_ptr<Root> root(new Root());
    uint8_t baseBuff[0x10000];
    FILE* in = fopen(fileName, "rb");
    size_t sz = fread(baseBuff, 1, 0x10000, in);
    fclose(in);
    IStream i(baseBuff, sz);
    deserializeRoot(*root, i);

    return root.release();
}

int main(int argc, char* argv[])
{
	try
	{


        Root* root = parseSourceFile("../../Hare-IDL/dbg/protobuf/sample.idl", false);
        //Root* root = deserializeFile("../../Hare-IDL/dbg/protobuf/sample.h.idlbin");
        //Root* root = deserializeFile("idl_tree.h.idlbin");
//		loadFakeSample( root );
        HAREASSERT(root);

        // Roughly: back end
        //idlcBackEnd(*root, "../../Hare-IDL/src/targets/cpp/codegen/protobuf/", 
        //    {"main.txt", "mapping.txt", "encoding.txt", "proto.txt" , "dbg_assert_equal.txt"}, false);
        idlcBackEnd(*root, "../../src/targets/cpp/codegen/protobuf/",
        { "main.txt", "mapping.txt", "encoding.txt", "proto.txt", "dbg_assert_equal.txt", "dbg_print.txt" }, false);
    }
	catch ( std::exception& x )
	{
		fmt::print( "Exception happened: {}\n", x.what() );
	}
 

    return 0;
}

