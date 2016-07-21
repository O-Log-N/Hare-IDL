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

DataMember* makeMember(const string& type_name, const string& name)
{
	DataMember* dm = new DataMember;
	dm->type.name = type_name;
	dm->name = name;
	return dm;
}

void loadFakeSample( Root& root )
{
	// a quite rudimentary sample - just to make sure main things work
	Structure* stre;

	stre = new Structure;
	stre->name = "Character";
	stre->declType = Structure::MAPPING;
	stre->type = Structure::STRUCT;

	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("UINT16", "character_id") ) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("double", "x")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("double", "y")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("double", "z")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("double", "vx")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("double", "vy")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("double", "vz")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("float", "angle")) );
//	map2->addAttribute(make_inline_enum_att("Animation", /* TODO Standing, Walking, Running */ "anim")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("UINT8", "animation_frame")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("MyInventory", "inventory")) );

	root.structures.push_back( unique_ptr<Structure>(stre) );
}

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

void addTestInherit(Root& root)
{
    for (auto& it : root.structures)
    {
        if (it->name == "Structure")
            it->inheritedFrom = "EncodedMembers";
        else if (it->name == "EncodedMembers")
            it->inheritedFrom = "EncodedOrMember";
        else if (it->name == "DataMember")
            it->inheritedFrom = "EncodedOrMember";
        //else if ( it->name == "CharacterSet" )
        //	it->inheritedFrom = "CharacterRange";
    }
}

int main()
{
	try
	{
        //Root* root = parseSourceFile("idl_tree.idl", false);
        //Root* root = deserializeFile("../../Hare-IDL/dbg/protobuf/idl_tree.h.idlbin");
        Root* root = deserializeFile("idl_tree.h.idlbin");
//		loadFakeSample( root );
        HAREASSERT(root);

        // Roughly: back end
        //idlcBackEnd(*root, "../../Hare-IDL/src/targets/cpp/codegen/protobuf/", 
        //    {"main.txt", "mapping.txt", "encoding.txt", "proto.txt" , "dbg_assert_equal.txt"}, false);
        idlcBackEnd(*root, "../../src/targets/cpp/codegen/protobuf/",
        { "main.txt", "mapping.txt", "encoding.txt", "proto.txt", "dbg_assert_equal.txt" }, false);
    }
	catch ( std::exception& x )
	{
		fmt::print( "Exception happened: {}\n", x.what() );
	}
 

    return 0;
}

