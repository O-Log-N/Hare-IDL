// sample.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "back_idl_tree.h"
#include "template_parser.h"
#include "template_instantiator.h"


DataMember* makeMember(const string& type_name, const string& name)
{
	DataMember* dm = new DataMember;
	dm->type.name = type_name;
	dm->name = name;
	return dm;
}

void loadFakeSample( Root& root )
{
	Structure* stre;

	stre = new Structure;
	stre->name = "Character";
	stre->declType = Structure::MAPPING;
	stre->type = Structure::STRUCT;

	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("UINT16", "character_id") ) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("double", "x")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("double", "y")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("double", "z")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("double", "vx")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("double", "vy")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("double", "vz")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("float", "angle")) );
//	map2->addAttribute(make_inline_enum_att("Animation", /* TODO Standing, Walking, Running */ "anim")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("UINT8", "animation_frame")) );
	stre->members.push_back( unique_ptr<EncodedOrMember>( makeMember("MyInventory", "inventory")) );

	root.structures.push_back( unique_ptr<Structure>(stre) );
}

int main()
{
	Root root;
	BackRoot backRoot;

	// Roughly: front end
	loadFakeSample( root );

	// interfacing
	convertToBackTree( root, backRoot );

	// back end
	ANY_TEMPLATE_ROOTS template_roots;
	AnyTemplateRoot template_root;

	FILE* ft = fopen( "template.txt", "rb" );
	int line = 0;
	if ( loadTemplate( ft, template_root, &line ) != 0 )
		return 0;
	printf( "\n\n" );
	dbgPrintTree( template_root );
	printf( "\n\n" );
	apply( *(backRoot.structures[0]), template_root );

    return 0;
}

