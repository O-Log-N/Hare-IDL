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

#include "idlc_back.h"
#include "back_idl_tree.h"
#include "template_parser.h"
#include "template_instantiator.h"

void idlcBackEnd( Root& root )
{
	BackRoot backRoot;
	convertToBackTree( root, backRoot );

	ANY_TEMPLATE_ROOTS template_roots;
	AnyTemplateRoot template_root;

	FILE* ft = fopen( "template.txt", "rb" );
	int line = 0;
	if ( loadTemplate( ft, template_root, &line ) != 0 )
		return;
	printf( "\n\n" );
	dbgPrintTree( template_root );
	printf( "\n\n" );
	apply( *(backRoot.structures[0]), template_root );
}