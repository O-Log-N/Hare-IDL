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

enum NODE_TYPE {
	CONTENT = 0,
	BEGIN_TEMPLATE,
	END_TEMPLATE,
	IF,
	ELSE,
	ELIF,
	ENDIF,
	FOR_EACH_OF_MEMBERS,
	INCLUDE,
	ASSERT,
	// derived types
	IF_TRUE_BRANCHE,
	IF_FALSE_BRANCHE,
	TEMPLATE_ROOT,
};

enum PARAMETER {
	NONE = 100,
	TYPE,
	BEGIN,
	END,
};

enum PLACEHOLDER {
	VERBATIM = 200,
	STRUCTNAME,
	MEMBER_TYPE,
	MEMBER_NAME,
};

enum OPERATOR {
	EQ,
	NEQ,
};

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
