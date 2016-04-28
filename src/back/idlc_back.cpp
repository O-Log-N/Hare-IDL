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

using namespace std;

void idlcBackEnd( Root& root )
{
	BackRoot backRoot;
	convertToBackTree( root, backRoot );
//	TREE_DATA_COMPLETION_SCENARIO scenario = TREE_DATA_COMPLETION_SCENARIO::MAP_ONLY; // TODO: must be precalculated from user input
	TREE_DATA_COMPLETION_SCENARIO scenario = TREE_DATA_COMPLETION_SCENARIO::IDL_ONLY; // TODO: must be precalculated from user input
	finalizeTree( backRoot, scenario );

	TemplateNodeSpace nodeSpace;

//	FILE* tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/cpp/codegen/protobuf/protobuff_gen.txt", "rb" );
//	FILE* tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template5.txt", "rb" );

	// NOTE: our target goal is a possibility to specify multiple files; for a while we imitate it manually
	//       exact details are to be developed
	// TODO: implement

	int line = 0; // TODO: switch to File/Line addressing for error reporting
	FILE* tf;

	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template6/main.txt", "rb" );
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

	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template6/mapping.txt", "rb" );
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

	tf = fopen( "../../../GITHUB/Hare-IDL/src/targets/sample/template6/encoding.txt", "rb" );
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

	apply( backRoot, nodeSpace );
}