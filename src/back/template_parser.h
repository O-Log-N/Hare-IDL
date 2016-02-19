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

#if !defined __TEMPLATE_PARSER_H__
#define __TEMPLATE_PARSER_H__

#include <stdio.h>
#include <vector>
using namespace std;


#define NODE_TYPE_CONTENT 0
#define NODE_TYPE_BEGIN_TEMPLATE 1
#define NODE_TYPE_END_TEMPLATE 2
#define NODE_TYPE_IF 3
#define NODE_TYPE_ELSE 4
#define NODE_TYPE_ELIF 5
#define NODE_TYPE_ENDIF 6
#define NODE_TYPE_FOR_EACH_OF_MEMBERS 7
#define NODE_TYPE_INCLUDE 8
#define NODE_TYPE_ASSERT 9
// derived types
//#define NODE_TYPE_UNDEFINED 20 // placeholedr
#define NODE_TYPE_IF_TRUE_BRANCHE 21
#define NODE_TYPE_IF_FALSE_BRANCHE 22
#define NODE_TYPE_TEMPLATE_ROOT 23

#define PARAM_BEGIN_TEMPLATE 101
#define PARAM_END_TEMPLATE 102
#define KEYWORD_FOR_EACH_OF_MEMBERS 103
#define KEYWORD_IF 104
#define KEYWORD_ELSE 105
#define KEYWORD_ELIF 106
#define PARAM_ENDIF 107
#define PARAM_ASSERT 108

// PARAMETERS (following main keywords)
#define PARAM_NONE 120
#define PARAM_TYPE 121
#define PARAM_BEGIN 122
#define PARAM_END 123

// plaseholders (single-words between '@')
#define LINE_PART_VERBATIM 200
#define PLACEHOLDER_STRUCTNAME 201
#define PLACEHOLDER_MEMBER_TYPE 202
#define PLACEHOLDER_MEMBER_NAME 203

// expression parts ( ==, !=, etc)
#define EXPRESSION_PART_EQ 301
#define EXPRESSION_PART_NEQ 302

typedef struct _LINE_PART
{
	int type;
	std:: string verbatim;
} LINE_PART;

typedef vector<LINE_PART> LINE_PARTS;

typedef struct _TEMPLATE_NODE
{
	int type;
	int src_line_num;
	LINE_PARTS line_parts;
	vector<_TEMPLATE_NODE> child_nodes;
} TEMPLATE_NODE;

typedef vector<TEMPLATE_NODE> TEMPLATE_NODES;
typedef vector<TEMPLATE_NODE>::iterator TEMPLATE_NODES_ITERATOR;

typedef struct _ANY_TEMPLATE_ROOT
{
	std::string name;
	std::string type;
	int src_line_num;
	TEMPLATE_NODE root;
} ANY_TEMPLATE_ROOT;

typedef vector<ANY_TEMPLATE_ROOT> ANY_TEMPLATE_ROOTS;
typedef vector<ANY_TEMPLATE_ROOT>::iterator ANY_TEMPLATE_ROOTS_ITERATOR;


bool load_template( FILE* ft, ANY_TEMPLATE_ROOT& _root_node, int* current_line_num );
void print_tree( ANY_TEMPLATE_ROOT& _root_node );


#endif // __TEMPLATE_PARSER_H__
