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

#include <iostream>

#include "idl_node.h"
#include "literal_node.h"
#include "debug.h"
#include "parser.h"

using namespace hare;
using namespace std;

AttributeDeclNode* make_named_att(const string& type_name, const string& att_name) {
	AttributeDeclNode* att = new AttributeDeclNode();
	att->name = att_name;
	NameTypeNode* t1 = new NameTypeNode();
	t1->name = type_name;
	att->type.set(t1);

	return att;
}

AttributeDeclNode* make_number_att(const string& type_name, int low, int high, const string& att_name) {
	AttributeDeclNode* att = new AttributeDeclNode();
	att->name = att_name;
	NumericTypeNode* t1 = new NumericTypeNode();

	IntegerLiteralExprNode* e1 = new IntegerLiteralExprNode();
	e1->setIntegerLiteral(low);

	IntegerLiteralExprNode* e2 = new IntegerLiteralExprNode();
	e2->setIntegerLiteral(high);

	t1->arguments.push_back(e1);
	t1->arguments.push_back(e2);

	att->type.set(t1);

	return att;
}

AttributeDeclNode* make_inline_enum_att(const string& type_name, const string& att_name) {
	AttributeDeclNode* att = new AttributeDeclNode();
	att->name = att_name;
	InlineEnumTypeNode* t1 = new InlineEnumTypeNode();
	t1->name = type_name;


	att->type.set(t1);

	return att;
}


AttributeDeclNode* make_sequence_of_att(const string& elem_name, const string& att_name) {
	AttributeDeclNode* att = new AttributeDeclNode();
	att->name = att_name;
	SequenceOfTypeNode* t1 = new SequenceOfTypeNode();

	NameTypeNode* t2 = new NameTypeNode();
	t2->name = elem_name;
	t1->type.set(t2);

	att->type.set(t1);

	return att;
}

int main()
{

	RootNode* root = new RootNode();

	FileNode* file2 = parseSourceFile("sample.idl", true, false);
	if (file2) {
		root->files.push_back(file2);
	}


	FileNode* file = new FileNode("input.idl");
	//file->fileName = "input.idl";
	root->files.push_back(file);

	PublishableStructDeclNode* ps = new PublishableStructDeclNode();
	ps->name = "Character";
	file->items.push_back(ps);

	ps->attributes.push_back(make_named_att("UINT16", "character_id"));
	ps->attributes.push_back(make_number_att("NUMERIC", -10000, 10000, "x"));
	ps->attributes.push_back(make_number_att("NUMERIC", -10000, 10000, "y"));
	ps->attributes.push_back(make_number_att("NUMERIC", -100, 100, "z"));
	ps->attributes.push_back(make_number_att("NUMERIC", -10, 10, "vx"));
	ps->attributes.push_back(make_number_att("NUMERIC", -10, 10, "vy"));
	ps->attributes.push_back(make_number_att("NUMERIC", -10, 10, "vz"));

	ps->attributes.push_back(make_number_att("NUMERIC", 0, 360, "angle"));
	ps->attributes.push_back(make_inline_enum_att("Animation", /* TODO Standing, Walking, Running */ "anim"));
	ps->attributes.push_back(make_number_att("INT", 0, 120, "animation_frame"));
	ps->attributes.push_back(make_sequence_of_att("Item", "inventory"));


	MappingDeclNode* map1 = new MappingDeclNode();
	map1->name = "Character";
	map1->tags.push_back("CPP");
	map1->tags.push_back("Client");
	file->items.push_back(map1);

	map1->attributes.push_back(make_named_att("UINT16", "character_id"));
	map1->attributes.push_back(make_named_att("double", "x"));
	map1->attributes.push_back(make_named_att("double", "y"));
	map1->attributes.push_back(make_named_att("double", "z"));
	map1->attributes.push_back(make_named_att("double", "vx"));
	map1->attributes.push_back(make_named_att("double", "vy"));
	map1->attributes.push_back(make_named_att("double", "vz"));

	map1->attributes.push_back(make_named_att("float", "angle"));
	map1->attributes.push_back(make_inline_enum_att("Animation", /* TODO Standing, Walking, Running */ "anim"));
	map1->attributes.push_back(make_named_att("UINT8", "animation_frame"));
//	map1->attributes.push_back(make_sequence_of_att("vector", "Item", "inventory"));

	MappingDeclNode* map2 = new MappingDeclNode();
	map2->name = "Character";
	map2->tags.push_back("CPP");
	map2->tags.push_back("Server");
	file->items.push_back(map2);

	map2->attributes.push_back(make_named_att("UINT16", "character_id"));
	map2->attributes.push_back(make_named_att("double", "x"));
	map2->attributes.push_back(make_named_att("double", "y"));
	map2->attributes.push_back(make_named_att("double", "z"));
	map2->attributes.push_back(make_named_att("double", "vx"));
	map2->attributes.push_back(make_named_att("double", "vy"));
	map2->attributes.push_back(make_named_att("double", "vz"));

	map2->attributes.push_back(make_named_att("float", "angle"));
	map2->attributes.push_back(make_inline_enum_att("Animation", /* TODO Standing, Walking, Running */ "anim"));
	map2->attributes.push_back(make_named_att("UINT8", "animation_frame"));
	map2->attributes.push_back(make_named_att("MyInventory", "inventory"));

	dumpDown(std::cout, root);

	return 0;
}

