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
    if (!in) {
        fmt::print("Failed to open input file '{}'\n", fileName);
        return nullptr;
    }
    size_t sz = fread(baseBuff, 1, 0x10000, in);
    fclose(in);
    IStream i(baseBuff, sz);
    bool ok = deserializeRoot(*root, i);

    return ok ? root.release() : nullptr;
}

struct CmdOptions {
    vector<string> templs;
    string templPath;
    string inputIdl;
    string inputBinary;
};

CmdOptions getCmdOptionFake()
{
    CmdOptions result;

    result.templPath = "../../Hare-IDL/src/targets/cpp/codegen/protobuf/";
    result.templs = { "main.txt", "mapping.txt", "encoding.txt", "proto.txt",
        "dbg_helpers.txt" };
    //    result.inputBinary = "../../Hare-IDL/test/targets/protobuf/poly-ptr/test.h.idlbin";
    result.inputIdl = "../../Hare-IDL/test/targets/protobuf/idl-primitive/test.idl";

    return result;
}

CmdOptions getCmdOption(char** begin, char** end)
{
    if (begin != end) {
        string current(*begin);
        if (current == "--debug") {
            return getCmdOptionFake();
        }
    }
    
    CmdOptions result;
    for (char** it = begin; it != end; ++it) {
        string current(*it);
        if (current.substr(0, 11) == "--template=")
            result.templs.push_back(current.substr(11));
        else if (current.substr(0, 15) == "--templatePath=")
            result.templPath = current.substr(15);
        else if (current.substr(0, 14) == "--inputBinary=")
            result.inputBinary = current.substr(14);
        else if (current.substr(0, 11) == "--inputIdl=")
            result.inputIdl = current.substr(11);
        else
            fmt::print("Unrecognized command line option: {}\n", current);
    }


    return result;
}

int main(int argc, char* argv[])
{
	try
	{
        HAREASSERT(argc >= 1);
        CmdOptions opts = getCmdOption(argv + 1, argv + argc);

        Root* root = 0;
        if(!opts.inputIdl.empty()) {
            root = parseSourceFile(opts.inputIdl, false);
        }
        else if (!opts.inputBinary.empty()) {
            root = deserializeFile(opts.inputBinary.c_str());
        }
        else {
            fmt::print("Missing input file name\n");
            return 1;
        }

        HAREASSERT(root);

        idlcBackEnd(*root, opts.templPath, opts.templs, false);
    }
	catch ( std::exception& x )
	{
		fmt::print( "Exception happened:\n{}\n", x.what() );
        return 1;
	}
 

    return 0;
}

