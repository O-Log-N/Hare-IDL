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

class RootTemplateInstantiatorFactory : public TemplateInstantiatorFactory
{
protected:
	const BackRoot* root;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context() override {return "ROOT"; }
public:
	RootTemplateInstantiatorFactory( const RootTemplateInstantiatorFactory& other ) = default;
	RootTemplateInstantiatorFactory( const BackRoot& structRoot, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiatorFactory( templateSpace_, outStr ), root( &structRoot ) {}
	virtual RootTemplateInstantiatorFactory* clone() const {return new RootTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  StructTemplateInstantiatorFactory : public TemplateInstantiatorFactory
{
protected:
	const BackStructure* structure;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context() override {return "STRUCT"; }
public:
	StructTemplateInstantiatorFactory( const StructTemplateInstantiatorFactory& other ) = default;
	StructTemplateInstantiatorFactory( BackStructure& currentStruct, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiatorFactory( templateSpace_, outStr ), structure( &currentStruct ) {}
	virtual StructTemplateInstantiatorFactory* clone() const {return new StructTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  StructMemberTemplateInstantiatorFactory : public TemplateInstantiatorFactory
{
protected:
	const BackDataMember* member;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context() override {return "STRUCT-MEMBER"; }
public:
	StructMemberTemplateInstantiatorFactory( const StructMemberTemplateInstantiatorFactory& other ) = default;
	StructMemberTemplateInstantiatorFactory( const BackDataMember& currentMember, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiatorFactory( templateSpace_, outStr ), member( &currentMember ) {}
	virtual StructMemberTemplateInstantiatorFactory* clone() const {return new StructMemberTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  MemberTypeTemplateInstantiatorFactory : public TemplateInstantiatorFactory
{
protected:
	const DataType* dataType;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context() override {return "DATATYPE"; }
public:
	MemberTypeTemplateInstantiatorFactory( const MemberTypeTemplateInstantiatorFactory& other ) = default;
	MemberTypeTemplateInstantiatorFactory( DataType& currentDataType, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiatorFactory( templateSpace_, outStr ), dataType( &currentDataType ) {}
	virtual MemberTypeTemplateInstantiatorFactory* clone() const {return new MemberTypeTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  EnumValueTemplateInstantiatorFactory : public TemplateInstantiatorFactory
{
protected:
	string name;
	uint32_t idlValue;
	uint32_t mappingValue;
	uint32_t encodingValue;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context() override {return "ENUMVALUE"; }
public:
	EnumValueTemplateInstantiatorFactory( const EnumValueTemplateInstantiatorFactory& other ) = default;
	EnumValueTemplateInstantiatorFactory( const string& currentName, uint32_t currentIdlValue, uint32_t currentMappingValue, uint32_t currentEncodingValue, TemplateNodeSpace& templateSpace_, FILE* outStr ) : 
		TemplateInstantiatorFactory( templateSpace_, outStr ), name( currentName ), idlValue( currentIdlValue ), mappingValue( currentMappingValue ), encodingValue( currentEncodingValue ) {}
	virtual EnumValueTemplateInstantiatorFactory* clone() const {return new EnumValueTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  DiscriminatedUnionTemplateInstantiatorFactory : public TemplateInstantiatorFactory
{
protected:
	BackStructure* structure;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context() override {return "DISCRIMINATED-UNION"; }
public:
	DiscriminatedUnionTemplateInstantiatorFactory( const DiscriminatedUnionTemplateInstantiatorFactory& other ) = default;
	DiscriminatedUnionTemplateInstantiatorFactory( BackStructure& currentStruct, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiatorFactory( templateSpace_, outStr ), structure( &currentStruct ) {}
	virtual DiscriminatedUnionTemplateInstantiatorFactory* clone() const {return new DiscriminatedUnionTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  DiscriminatedUnionOptionTemplateInstantiatorFactory : public TemplateInstantiatorFactory
{
protected:
	vector<const BackDataMember*> usedMembers;
	const BackDataMember* baseEnum;
	string enumValueName;
	uint32_t idlValue;
	uint32_t mappingValue;
	uint32_t encodingValue;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context() override {return "DISCRIMINATED-UNION-OPTION"; }
public:
	DiscriminatedUnionOptionTemplateInstantiatorFactory( const DiscriminatedUnionOptionTemplateInstantiatorFactory& other ) = default;
	DiscriminatedUnionOptionTemplateInstantiatorFactory( const BackDataMember& currentBaseEnum, vector<const BackDataMember*>& currentUsedMembers, const string& currentEnumValueName, uint32_t currentIdlValue, uint32_t currentMappingValue, uint32_t currentEncodingValue, TemplateNodeSpace& templateSpace_, FILE* outStr ) : 
		TemplateInstantiatorFactory( templateSpace_, outStr ),usedMembers( currentUsedMembers ), baseEnum( &currentBaseEnum ), enumValueName( currentEnumValueName ), idlValue( currentIdlValue ), mappingValue( currentMappingValue ), encodingValue( currentEncodingValue ) {}
	virtual DiscriminatedUnionOptionTemplateInstantiatorFactory* clone() const {return new DiscriminatedUnionOptionTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // TEMPLATE_INSTANTIATOR_DERIVED_H
