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
	const BackRoot* root;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "ROOT"; }

public:
	RootTemplateInstantiator( const BackRoot& structRoot, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiator( templateSpace_, outStr ), root( &structRoot ) {}

	void apply()
	{
		TemplateNode* mainT = templateSpace.getTemplate( "MAIN", "ROOT" );
		if ( mainT != nullptr )
			applyNode( *mainT );
	}
};

class RootTemplateInstantiatorFactory : public TemplateInstantiatorFactory
{
protected:
	const BackRoot* root;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "ROOT"; }
public:
	RootTemplateInstantiatorFactory( const RootTemplateInstantiatorFactory& other ) = default;
	RootTemplateInstantiatorFactory( const BackRoot& structRoot, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiatorFactory( templateSpace_, outStr ), root( &structRoot ) {}
//	virtual TemplateInstantiator* create() const 	{return new RootTemplateInstantiator( *root, templateSpace, outstr );}
	virtual TemplateInstantiator* create() const 	{return new TemplateInstantiator( templateSpace, outstr );}
	virtual RootTemplateInstantiatorFactory* clone() const {return new RootTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


class StructTemplateInstantiator : public TemplateInstantiator
{
protected:
	const BackStructure* structure;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "STRUCT"; }

public:
	StructTemplateInstantiator( const BackStructure& currentStruct, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiator( templateSpace_, outStr ), structure( &currentStruct ) {}
};

class  StructTemplateInstantiatorFactory : public TemplateInstantiatorFactory
{
protected:
	const BackStructure* structure;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "STRUCT"; }
public:
	StructTemplateInstantiatorFactory( const StructTemplateInstantiatorFactory& other ) = default;
	StructTemplateInstantiatorFactory( BackStructure& currentStruct, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiatorFactory( templateSpace_, outStr ), structure( &currentStruct ) {}
//	virtual TemplateInstantiator* create() const 	{return new  StructTemplateInstantiator( *structure, templateSpace, outstr );}
	virtual TemplateInstantiator* create() const 	{return new TemplateInstantiator( templateSpace, outstr );}
	virtual StructTemplateInstantiatorFactory* clone() const {return new StructTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


class StructMemberTemplateInstantiator : public TemplateInstantiator
{
protected:
	const BackDataMember* member;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "STRUCT-MEMBER"; }

public:
	StructMemberTemplateInstantiator( const BackDataMember& currentMember, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiator( templateSpace_, outStr ), member( &currentMember ) {}
};

class  StructMemberTemplateInstantiatorFactory : public TemplateInstantiatorFactory
{
protected:
	const BackDataMember* member;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "STRUCT-MEMBER"; }
public:
	StructMemberTemplateInstantiatorFactory( const StructMemberTemplateInstantiatorFactory& other ) = default;
	StructMemberTemplateInstantiatorFactory( const BackDataMember& currentMember, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiatorFactory( templateSpace_, outStr ), member( &currentMember ) {}
//	virtual TemplateInstantiator* create() const 	{return new  StructMemberTemplateInstantiator( *member, templateSpace, outstr );}
	virtual TemplateInstantiator* create() const 	{return new TemplateInstantiator( templateSpace, outstr );}
	virtual StructMemberTemplateInstantiatorFactory* clone() const {return new StructMemberTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


class MemberTypeTemplateInstantiator : public TemplateInstantiator
{
protected:
	const DataType* dataType;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "DATATYPE"; }

public:
	MemberTypeTemplateInstantiator( const DataType& currentDataType, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiator( templateSpace_, outStr ), dataType( &currentDataType ) {}
};

class  MemberTypeTemplateInstantiatorFactory : public TemplateInstantiatorFactory
{
protected:
	const DataType* dataType;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "DATATYPE"; }
public:
	MemberTypeTemplateInstantiatorFactory( const MemberTypeTemplateInstantiatorFactory& other ) = default;
	MemberTypeTemplateInstantiatorFactory( DataType& currentDataType, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiatorFactory( templateSpace_, outStr ), dataType( &currentDataType ) {}
//	virtual TemplateInstantiator* create() const 	{return new  MemberTypeTemplateInstantiator( *dataType, templateSpace, outstr );}
	virtual TemplateInstantiator* create() const 	{return new TemplateInstantiator( templateSpace, outstr );}
	virtual MemberTypeTemplateInstantiatorFactory* clone() const {return new MemberTypeTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


class EnumValueTemplateInstantiator : public TemplateInstantiator
{
protected:
	string name;
	uint32_t idlValue;
	uint32_t mappingValue;
	uint32_t encodingValue;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "ENUMVALUE"; }

public:
	EnumValueTemplateInstantiator( const string& currentName, uint32_t currentIdlValue, uint32_t currentMappingValue, uint32_t currentEncodingValue, TemplateNodeSpace& templateSpace_, FILE* outStr ) : 
		TemplateInstantiator( templateSpace_, outStr ), name( currentName ), idlValue( currentIdlValue ), mappingValue( currentMappingValue ), encodingValue( currentEncodingValue ) {}
};

class  EnumValueTemplateInstantiatorFactory : public TemplateInstantiatorFactory
{
protected:
	string name;
	uint32_t idlValue;
	uint32_t mappingValue;
	uint32_t encodingValue;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "ENUMVALUE"; }
public:
	EnumValueTemplateInstantiatorFactory( const EnumValueTemplateInstantiatorFactory& other ) = default;
	EnumValueTemplateInstantiatorFactory( const string& currentName, uint32_t currentIdlValue, uint32_t currentMappingValue, uint32_t currentEncodingValue, TemplateNodeSpace& templateSpace_, FILE* outStr ) : 
		TemplateInstantiatorFactory( templateSpace_, outStr ), name( currentName ), idlValue( currentIdlValue ), mappingValue( currentMappingValue ), encodingValue( currentEncodingValue ) {}
//	virtual TemplateInstantiator* create() const 	{return new  EnumValueTemplateInstantiator( name, idlValue, mappingValue, encodingValue, templateSpace, outstr );}
	virtual TemplateInstantiator* create() const 	{return new TemplateInstantiator( templateSpace, outstr );}
	virtual EnumValueTemplateInstantiatorFactory* clone() const {return new EnumValueTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


class DiscriminatedUnionTemplateInstantiator : public TemplateInstantiator
{
protected:
	const BackStructure* structure;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "DISCRIMINATED-UNION"; }

public:
	DiscriminatedUnionTemplateInstantiator( const BackStructure& currentStruct, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiator( templateSpace_, outStr ), structure( &currentStruct ) {}
};

class  DiscriminatedUnionTemplateInstantiatorFactory : public TemplateInstantiatorFactory
{
protected:
	BackStructure* structure;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "DISCRIMINATED-UNION"; }
public:
	DiscriminatedUnionTemplateInstantiatorFactory( const DiscriminatedUnionTemplateInstantiatorFactory& other ) = default;
	DiscriminatedUnionTemplateInstantiatorFactory( BackStructure& currentStruct, TemplateNodeSpace& templateSpace_, FILE* outStr ) : TemplateInstantiatorFactory( templateSpace_, outStr ), structure( &currentStruct ) {}
//	virtual TemplateInstantiator* create() const 	{return new  DiscriminatedUnionTemplateInstantiator( *structure, templateSpace, outstr );}
	virtual TemplateInstantiator* create() const 	{return new TemplateInstantiator( templateSpace, outstr );}
	virtual DiscriminatedUnionTemplateInstantiatorFactory* clone() const {return new DiscriminatedUnionTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


class DiscriminatedUnionOptionTemplateInstantiator : public TemplateInstantiator
{
protected:
	vector<const BackDataMember*> usedMembers;
	const BackDataMember* baseEnum;
	string enumValueName;
	uint32_t idlValue;
	uint32_t mappingValue;
	uint32_t encodingValue;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "DISCRIMINATED-UNION-OPTION"; }

public:
	DiscriminatedUnionOptionTemplateInstantiator( const BackDataMember& currentBaseEnum, const vector<const BackDataMember*>& currentUsedMembers, const string& currentEnumValueName, uint32_t currentIdlValue, uint32_t currentMappingValue, uint32_t currentEncodingValue, TemplateNodeSpace& templateSpace_, FILE* outStr ) : 
		TemplateInstantiator( templateSpace_, outStr ), usedMembers( currentUsedMembers ), baseEnum( &currentBaseEnum ), enumValueName( currentEnumValueName ), idlValue( currentIdlValue ), mappingValue( currentMappingValue ), encodingValue( currentEncodingValue ) {}
};

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
	virtual StackElement placeholder( Placeholder ph );
	virtual string context() override {return "DISCRIMINATED-UNION-OPTION"; }
public:
	DiscriminatedUnionOptionTemplateInstantiatorFactory( const DiscriminatedUnionOptionTemplateInstantiatorFactory& other ) = default;
	DiscriminatedUnionOptionTemplateInstantiatorFactory( const BackDataMember& currentBaseEnum, vector<const BackDataMember*>& currentUsedMembers, const string& currentEnumValueName, uint32_t currentIdlValue, uint32_t currentMappingValue, uint32_t currentEncodingValue, TemplateNodeSpace& templateSpace_, FILE* outStr ) : 
		TemplateInstantiatorFactory( templateSpace_, outStr ),usedMembers( currentUsedMembers ), baseEnum( &currentBaseEnum ), enumValueName( currentEnumValueName ), idlValue( currentIdlValue ), mappingValue( currentMappingValue ), encodingValue( currentEncodingValue ) {}
//	virtual TemplateInstantiator* create() const 	{return new  DiscriminatedUnionOptionTemplateInstantiator( *baseEnum, usedMembers, enumValueName, idlValue, mappingValue, encodingValue, templateSpace, outstr );}
	virtual TemplateInstantiator* create() const 	{return new TemplateInstantiator( templateSpace, outstr );}
	virtual DiscriminatedUnionOptionTemplateInstantiatorFactory* clone() const {return new DiscriminatedUnionOptionTemplateInstantiatorFactory( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


void apply( BackRoot& structure, TemplateNodeSpace& templateSpace );


#endif // TEMPLATE_INSTANTIATOR_DERIVED_H
