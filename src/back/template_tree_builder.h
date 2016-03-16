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

#ifndef TEMPLATE_TREE_BUILDER_H
#define TEMPLATE_TREE_BUILDER_H

#include "../idlc_include.h"
#include "template_line_tokenizer.h"

using namespace std;

struct TemplateNode
{
	NODE_TYPE type;
	int srcLineNum;
	vector<TemplateNode> childNodes;

	map<AttributeName, vector<ExpressionElement>> attributes;
	vector<ExpressionElement> expression; // used only for NODE_TYPE::IF(ELIF) and NODE_TYPE::ASSERT
};

bool buildTemplateTree( TemplateNode& root, vector<TemplateLine>& lines, size_t& flidx );
void dbgPrintNode_( TemplateNode& node, int depth );


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
			auto attrT = node.attributes.find( {ATTRIBUTE::NAME, ""} );
			assert( attrT != node.attributes.end() );
			assert( attrT->second.size() == 1 );
			assert( attrT->second[0].oper == ExpressionElement::OPERATION::PUSH );
			assert( attrT->second[0].argtype == ExpressionElement::ARGTYPE::STRING );
			assert( attrT->second[0].lineParts.size() == 1 );
			assert( attrT->second[0].lineParts[0].type == PLACEHOLDER::VERBATIM );

			auto typeT = node.attributes.find( {ATTRIBUTE::TYPE, ""} );
			assert( typeT != node.attributes.end() );
			assert( typeT->second.size() == 1 );
			assert( typeT->second[0].oper == ExpressionElement::OPERATION::PUSH );
			assert( typeT->second[0].argtype == ExpressionElement::ARGTYPE::STRING );
			assert( typeT->second[0].lineParts.size() == 1 );
			assert( typeT->second[0].lineParts.size() == 1 );
			assert( typeT->second[0].lineParts[0].type == PLACEHOLDER::VERBATIM );

			if ( attrT->second[0].lineParts[0].verbatim == name && typeT->second[0].lineParts[0].verbatim == expectedType )
				return &node;
		}
		return nullptr;
	}
};

bool loadTemplates( istream& tf, TemplateNodeSpace& nodeSpace, int& currentLineNum );
void dbgPrintTemplateTrees( TemplateNodeSpace& nodeSpace );

#endif // TEMPLATE_TREE_BUILDER_H
