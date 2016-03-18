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

using namespace std;

void idlcBackEnd( Root& root )
{
	BackRoot backRoot;
	convertToBackTree( root, backRoot );

//	TemplateNode template_root;
	TemplateNodeSpace nodeSpace;

/*	ifstream tf;
//	tf.open ( "template.txt", ios::in | ios::binary );
	tf.open ( "template2.txt", ios::in | ios::binary );
	if ( !tf )
	{
		fmt::print( "failed to open template file\n" );
		return;
	}*/
	FILE* tf = fopen( "template2.txt", "rb" );

	int line = 0;
//	if ( !loadTemplate( tf, template_root, line ) )
	if ( !loadTemplates( tf, nodeSpace, line ) )
		return;
	fmt::print( "\n\n" );
//	dbgPrintTree( template_root );
	dbgPrintTemplateTrees( nodeSpace );
	fmt::print( "\n\n" );

	apply( backRoot, nodeSpace );
}