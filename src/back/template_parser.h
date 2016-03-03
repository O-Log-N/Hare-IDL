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
	string templateType; // used only for NODE_TYPE::BEGIN_TEMPLATE  TODO: consider IDs for known types, or predefined type strings (such as ROOT) whereever necessary!!!!
	string outputFileName; // used only for NODE_TYPE::OPEN_OUTPUT_FILE
};

class TemplateNodeSpace
{
public:
	// TODO: internals of this class might be havily revised; its interface should hopefully survive
	vector<TemplateNode> templates;
	void dbgValidateTemplateSpace()
	{
		// TODO (at least):
		// 1. make sure all names distinct (unless map is used for storing, then it's already done)
		// 2. for each @@include there must be a template with a respective name
		// 3. there is at least one template of type ROOT
	}
	TemplateNode* getTemplate( string name, string expectedType )
	{
		for ( auto& node:templates )
		{
			if ( node.templateName == name && node.templateType == expectedType )
				return &node;
		}
		return nullptr;
	}
};

bool loadTemplate( istream& tf, TemplateNode& rootNode, int& currentLineNum );
void dbgPrintTree( TemplateNode& rootNode );

bool loadTemplates( istream& tf, TemplateNodeSpace& nodeSpace, int& currentLineNum );
void dbgPrintTemplateTrees( TemplateNodeSpace& nodeSpace );


#endif // TEMPLATE_PARSER_H
