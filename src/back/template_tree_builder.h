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
	vector<ExpressionElement> expression; // used only for NODE_TYPE::IF(ELIF), NODE_TYPE::NODE_TYPE::FOR_EACH_OF, NODE_TYPE::INCLUDE_WITH, NODE_TYPE::RETURN, and NODE_TYPE::ASSERT
	bool isFunctionNode = false; // set to true if @@RETURN found down the tree
};

struct TemplateRootNode
{
	bool isFunction;
	int srcLineNum;
	string name;
	vector<TemplateNode> childNodes;
	vector<AttributeName> params;
};

void dbgPrintNode_( TemplateNode& node, int depth );


class TemplateNodeSpace
{
public:
	// TODO: internals of this class might be havily revised; its interface should hopefully survive
	vector<TemplateRootNode> templates;
	void dbgValidateTemplateSpace()
	{
		// TODO (at least):
		// 1. make sure all names distinct (unless map is used for storing, then it's already done)
		// 2. for each @@include there must be a template with a respective name
		// 3. there is at least one template of type ROOT
	}
	TemplateRootNode* getTemplate( string name )
	{
		for ( auto& node:templates )
		{
			if ( node.name == name )
				return &node;
		}
		return nullptr;
	}
};

bool loadTemplates( FILE* tf, TemplateNodeSpace& nodeSpace, int& currentLineNum );
void dbgPrintTemplateTrees( TemplateNodeSpace& nodeSpace );

#endif // TEMPLATE_TREE_BUILDER_H
