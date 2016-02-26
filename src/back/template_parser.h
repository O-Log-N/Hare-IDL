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

#ifndef TEMPLATE_PARSER_H
#define TEMPLATE_PARSER_H

#include "../idlc_include.h"

using namespace std;

enum NODE_TYPE {
	CONTENT = 0,
	BEGIN_TEMPLATE,
	END_TEMPLATE,
	IF,
	ELSE,
	ELIF,
	ENDIF,
	INCLUDE,
	ASSERT,
	// derived types
	IF_TRUE_BRANCH,
	IF_FALSE_BRANCH,
	FULL_TEMPLATE,
//	TEMPLATE_ROOT,
	FOR_EACH_OF_MEMBERS, // used ONLY within STRUCT
};

enum PARAMETER {
	NONE = 100,
	TYPE,
	BEGIN,
	END,
};

enum PLACEHOLDER {
	VERBATIM = 200,
	STRUCT_NAME, // used ONLY within STRUCT or down the tree
	MEMBER_TYPE, // used ONLY within STRUCT-MEMBER
	MEMBER_NAME, // used ONLY within STRUCT-MEMBER
};

enum OPERATOR {
	EQ,
	NEQ,
};

struct LinePart
{
	int type;
	string verbatim;
};

struct TemplateNode
{
	int type;
	int srcLineNum;
	vector<LinePart> lineParts;
	vector<TemplateNode> childNodes;
};

typedef vector<TemplateNode> TEMPLATE_NODES;
typedef vector<TemplateNode>::iterator TEMPLATE_NODES_ITERATOR;

struct AnyTemplateRoot
{
	string name;
	string type;
	int srcLineNum;
	TemplateNode root;
};

typedef vector<AnyTemplateRoot> ANY_TEMPLATE_ROOTS;


bool loadTemplate( ifstream& tf, AnyTemplateRoot& rootNode, int& currentLineNum );
void dbgPrintTree( AnyTemplateRoot& rootNode );


#endif // TEMPLATE_PARSER_H
