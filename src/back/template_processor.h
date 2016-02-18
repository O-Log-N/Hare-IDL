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

#if !defined __TEMPLATE_PROCESSOR_H__
#define __TEMPLATE_PROCESSOR_H__

#include <stdio.h>
#include <idl.h>
#include <literal_node.h>

#define CONTEXT_STRUCT 1
#define CONTEXT_STRUCT_MEMBER 2

using namespace kpm;

bool load_template( FILE* ft, int* current_line_num );
void print_template_basics();
void print_tree();
void apply( void* idlmap, int context );


#endif // __TEMPLATE_PROCESSOR_H__
