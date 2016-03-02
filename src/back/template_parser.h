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
	FULL_TEMPLATE,
	CONTENT,
	IF,
	INCLUDE,
	ASSERT,
	IF_TRUE_BRANCH,
	IF_FALSE_BRANCH,

	FOR_EACH_OF_MEMBERS, // used ONLY within STRUCT
	OPEN_OUTPUT_FILE,
	FOR_EACH_PUBLISHABLE_STRUCT,
	CLOSE_OUTPUT_FILE,
};

enum PLACEHOLDER {
	VERBATIM,
	STRUCT_NAME, // used ONLY within STRUCT or down the tree
	MEMBER_TYPE, // used ONLY within STRUCT-MEMBER
	MEMBER_NAME, // used ONLY within STRUCT-MEMBER
};

struct LinePart
{
	int type;
	string verbatim;
};

struct ExpressionElement
{
	enum OPERATION { PUSH, EQ, NEQ };
    enum ARGTYPE {NONE, PLACEHOLDER, NUMBER, STRING};
	OPERATION oper;
    ARGTYPE argtype = NONE; // for operation PUSH: any but NONE
	// values below are used in case of PUSH operation
    double numberValue = 0; // argtype: NUMBER
    string stringValue; // argtype: STRING
	::PLACEHOLDER placeholder; // argtype: PLACEHOLDER
};

struct TemplateNode
{
	int type;
	int srcLineNum;
	vector<TemplateNode> childNodes;

	// node-type-specific values
	vector<LinePart> lineParts; // used only for NODE_TYPE::CONTENT
	vector<ExpressionElement> expression; // used only for NODE_TYPE::IF and NODE_TYPE::ASSERT
	string templateName; // used only for NODE_TYPE::BEGIN_TEMPLATE
	string templateType; // used only for NODE_TYPE::BEGIN_TEMPLATE
	string outputFileName; // used only for NODE_TYPE::OPEN_OUTPUT_FILE
};

typedef vector<TemplateNode> TEMPLATE_NODES;

bool loadTemplate( istream& tf, TemplateNode& rootNode, int& currentLineNum );
void dbgPrintTree( TemplateNode& rootNode );


#endif // TEMPLATE_PARSER_H
