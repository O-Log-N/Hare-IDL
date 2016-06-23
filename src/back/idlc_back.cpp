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

#include "idlc_back.h"
#include "back_idl_tree.h"
#include "template_tree_builder.h"
#include "template_instantiator_derived.h"
#include "idl_tree_finalizer.h"

#include "../front-back/idl_tree_serializer.h"

using namespace std;

void addTestData( Root& root )
{
	for ( auto& it:root.structures )
	{
		if ( it->name == "Structure" )
			it->inheritedFrom = "EncodedMembers";
		else if ( it->name == "EncodedMembers" )
			it->inheritedFrom = "EncodedOrMember";
		else if ( it->name == "DataMember" )
			it->inheritedFrom = "EncodedOrMember";
//		else if ( it->name == "CharacterSet" )
//			it->inheritedFrom = "CharacterRange";
	}
}

void idlcBackEnd( Root& root2 )
{
#if 1
	// serialize tree
	FILE* out = fopen( "idl_tree.bin", "wb" );
	OStream o(out);
	serializeRoot( root2, o );
	fclose( out );


	// deserialize tree
	Root root1;
	uint8_t baseBuff[0x10000];
	FILE* in = fopen( "idl_tree.bin", "rb" );
	size_t sz = fread( baseBuff, 1, 0x10000, in );
	fclose( in );
	IStream i( baseBuff, sz );
	deserializeRoot( root1, i );

	Root& root = root1;
#else
	Root& root = root2;
#endif

	addTestData( root );

	// further usage
	BackRoot backRoot;
	convertToBackTree( root, backRoot );
	TREE_DATA_COMPLETION_SCENARIO scenario = TREE_DATA_COMPLETION_SCENARIO::MAP_ONLY; // TODO: must be precalculated from user input
//	TREE_DATA_COMPLETION_SCENARIO scenario = TREE_DATA_COMPLETION_SCENARIO::IDL_ONLY; // TODO: must be precalculated from user input
	finalizeTree( backRoot, scenario );

	TemplateNodeSpace nodeSpace;

//	FILE* tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/cpp/codegen/protobuf/protobuff_gen.txt", "rb" );
//	FILE* tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template5.txt", "rb" );

	// NOTE: our target goal is a possibility to specify multiple files; for a while we imitate it manually
	//       exact details are to be developed
	// TODO: implement

	int line = 0; // TODO: switch to File/Line addressing for error reporting
	FILE* tf;

//	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template6/main.txt", "rb" );
//	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template7/main.txt", "rb" );
//	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template8/main.txt", "rb" );
//	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template9/main.txt", "rb" );
	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/cpp/codegen/protobuf/main.txt", "rb" );
	if ( tf == NULL )
	{
		fmt::print( "failed to open template file\n" );
		return;
	}
	line = 0;
	fmt::print( "Processing {}...", "main.txt" );
	if ( !loadTemplates( tf, nodeSpace, line ) )
		return;
	fmt::print( "  done\n" );
//	fmt::print( "\n\n" );
//	dbgPrintTemplateTrees( nodeSpace );
//	fmt::print( "\n\n" );

//	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template6/mapping.txt", "rb" );
//	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template7/mapping.txt", "rb" );
//	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template8/mapping.txt", "rb" );
//	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template9/mapping.txt", "rb" );
	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/cpp/codegen/protobuf/mapping.txt", "rb" );
	if ( tf == NULL )
	{
		fmt::print( "failed to open template file\n" );
		return;
	}
	line = 0;
	fmt::print( "Processing {}...", "mapping.txt" );
	if ( !loadTemplates( tf, nodeSpace, line ) )
		return;
	fmt::print( "  done\n" );
//	fmt::print( "\n\n" );
//	dbgPrintTemplateTrees( nodeSpace );
//	fmt::print( "\n\n" );

//	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template6/encoding.txt", "rb" );
//	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template7/encoding.txt", "rb" );
//	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template8/encoding.txt", "rb" );
//	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template9/encoding.txt", "rb" );
	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/cpp/codegen/protobuf/encoding.txt", "rb" );
	if ( tf == NULL )
	{
		fmt::print( "failed to open template file\n" );
		return;
	}
	line = 0;
	fmt::print( "Processing {}...", "encoding.txt" );
	if ( !loadTemplates( tf, nodeSpace, line ) )
		return;
	fmt::print( "  done\n" );
	fmt::print( "\n\n" );
	dbgPrintTemplateTrees( nodeSpace );
	fmt::print( "\n\n" );

//	apply( backRoot, nodeSpace );
	processStructures( backRoot, nodeSpace );
}

void idlcBackEnd(Root& root, const string& path, const vector<string>& files)
{
    // further usage
    BackRoot backRoot;
    convertToBackTree(root, backRoot);
    TREE_DATA_COMPLETION_SCENARIO scenario = TREE_DATA_COMPLETION_SCENARIO::MAP_ONLY; // TODO: must be precalculated from user input
//	TREE_DATA_COMPLETION_SCENARIO scenario = TREE_DATA_COMPLETION_SCENARIO::IDL_ONLY; // TODO: must be precalculated from user input
    finalizeTree(backRoot, scenario);

    TemplateNodeSpace nodeSpace;

    // NOTE: our target goal is a possibility to specify multiple files; for a while we imitate it manually
    //       exact details are to be developed
    // TODO: implement

    for (const string& current : files) {
        string pathName = path + current;
        FILE* tf = fopen(pathName.c_str(), "rb");
        if (tf == NULL)
        {
            fmt::print("failed to open template file {}\n", current);
            return;
        }
        int line = 0; // TODO: switch to File/Line addressing for error reporting
        fmt::print("Processing {}...", current);
        if (!loadTemplates(tf, nodeSpace, line))
            return;
        fmt::print("  done\n");
    }

    fmt::print("\n\n");
    dbgPrintTemplateTrees(nodeSpace);
    fmt::print("\n\n");

    //	apply( backRoot, nodeSpace );
    processStructures(backRoot, nodeSpace);
}