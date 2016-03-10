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
#include "template_parser.h" // for a while...
#include "template_line_tokenizer.h"

using namespace std;

struct TemplateNode_
{
	NODE_TYPE type;
	int srcLineNum;
	vector<TemplateNode_> childNodes;

	map<AttributeName, vector<LinePart>> attributes;
	vector<ExpressionElement> expression; // used only for NODE_TYPE::IF(ELIF) and NODE_TYPE::ASSERT
};

bool buildTemplateTree( TemplateNode_& root, vector<TemplateLine>& lines, size_t& flidx );

#endif // TEMPLATE_TREE_BUILDER_H
