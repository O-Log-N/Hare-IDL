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

#ifndef TEMPLATE_INSTANTIATOR_DERIVED_H
#define TEMPLATE_INSTANTIATOR_DERIVED_H

#include "template_instantiator.h"


class RootTemplateInstantiator : public TemplateInstantiator
{
protected:
	BackRoot* root;

	virtual void execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "ROOT"; }

public:
	RootTemplateInstantiator( BackRoot& structRoot, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiator( templateSpace_, outStr ), root( &structRoot ) {}

	void apply()
	{
		TemplateNode* mainT = templateSpace.getTemplate( "MAIN", "ROOT" );
		if ( mainT != nullptr )
			applyNode( *mainT );
	}
};


class StructTemplateInstantiator : public TemplateInstantiator
{
protected:
	BackStructure* structure;

	virtual void execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "STRUCT"; }

public:
	StructTemplateInstantiator( BackStructure& currentStruct, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiator( templateSpace_, outStr ), structure( &currentStruct ) {}

	void apply( TemplateNode& node )
	{
		applyNode( node );
	}
};


class StructMemberTemplateInstantiator : public TemplateInstantiator
{
protected:
	BackDataMember* member;

	virtual void execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "STRUCT-MEMBER"; }

public:
	StructMemberTemplateInstantiator( BackDataMember& currentMember, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiator( templateSpace_, outStr ), member( &currentMember ) {}

	void apply( TemplateNode& node )
	{
		applyNode( node );
	}
};


class MemberTypeTemplateInstantiator : public TemplateInstantiator
{
protected:
	DataType* dataType;

	virtual void execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "DATATYPE"; }

public:
	MemberTypeTemplateInstantiator( DataType& currentDataType, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiator( templateSpace_, outStr ), dataType( &currentDataType ) {}

	void apply( TemplateNode& node )
	{
		applyNode( node );
	}
};


class EnumValueTemplateInstantiator : public TemplateInstantiator
{
protected:
	string name;
	uint32_t idlValue;
	uint32_t mappingValue;
	uint32_t encodingValue;

	virtual void execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "ENUMVALUE"; }

public:
	EnumValueTemplateInstantiator( const string& currentName, uint32_t currentIdlValue, uint32_t currentMappingValue, uint32_t currentEncodingValue, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiator( templateSpace_, outStr ), name( currentName ), idlValue( currentIdlValue ), mappingValue( currentMappingValue ), encodingValue( currentEncodingValue ) {}

	void apply( TemplateNode& node )
	{
		applyNode( node );
	}
};


class DiscriminatedUnionTemplateInstantiator : public TemplateInstantiator
{
protected:
	BackStructure* structure;

	virtual void execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "DISCRIMINATED-UNION"; }

public:
	DiscriminatedUnionTemplateInstantiator( BackStructure& currentStruct, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiator( templateSpace_, outStr ), structure( &currentStruct ) {}

	void apply( TemplateNode& node )
	{
		applyNode( node );
	}
};


class DiscriminatedUnionOptionTemplateInstantiator : public TemplateInstantiator
{
protected:
	vector<BackDataMember*> usedMembers;
	BackDataMember* baseEnum;
	string enumValueName;
	uint32_t idlValue;
	uint32_t mappingValue;
	uint32_t encodingValue;

	virtual void execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "DISCRIMINATED-UNION-OPTION"; }

public:
	DiscriminatedUnionOptionTemplateInstantiator( BackDataMember& currentBaseEnum, vector<BackDataMember*>& currentUsedMembers, const string& currentEnumValueName, uint32_t currentIdlValue, uint32_t currentMappingValue, uint32_t currentEncodingValue, TemplateNodeSpace& templateSpace_, FILE* outStr ) : 
		TemplateInstantiator( templateSpace_, outStr ), usedMembers( currentUsedMembers ), baseEnum( &currentBaseEnum ), enumValueName( currentEnumValueName ), idlValue( currentIdlValue ), mappingValue( currentMappingValue ), encodingValue( currentEncodingValue ) {}

	void apply( TemplateNode& node )
	{
		applyNode( node );
	}
};


void apply( BackRoot& structure, TemplateNodeSpace& templateSpace );


#endif // TEMPLATE_INSTANTIATOR_DERIVED_H
