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

class RootExpressionObject : public ExpressionObject
{
protected:
	const BackRoot* root;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context() override {return "ROOT"; }
public:
	RootExpressionObject( const RootExpressionObject& other ) = default;
	RootExpressionObject( const BackRoot& structRoot, TemplateNodeSpace& templateSpace_, FILE* outStr ) : ExpressionObject( templateSpace_, outStr ), root( &structRoot ) {}
	virtual RootExpressionObject* clone() const {return new RootExpressionObject( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  StructExpressionObject : public ExpressionObject
{
protected:
	const BackStructure* structure;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context() override {return "STRUCT"; }
public:
	StructExpressionObject( const StructExpressionObject& other ) = default;
	StructExpressionObject( BackStructure& currentStruct, TemplateNodeSpace& templateSpace_, FILE* outStr ) : ExpressionObject( templateSpace_, outStr ), structure( &currentStruct ) {}
	virtual StructExpressionObject* clone() const {return new StructExpressionObject( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  StructMemberExpressionObject : public ExpressionObject
{
protected:
	const BackDataMember* member;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context() override {return "STRUCT-MEMBER"; }
public:
	StructMemberExpressionObject( const StructMemberExpressionObject& other ) = default;
	StructMemberExpressionObject( const BackDataMember& currentMember, TemplateNodeSpace& templateSpace_, FILE* outStr ) : ExpressionObject( templateSpace_, outStr ), member( &currentMember ) {}
	virtual StructMemberExpressionObject* clone() const {return new StructMemberExpressionObject( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  MemberTypeExpressionObject : public ExpressionObject
{
protected:
	const DataType* dataType;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context() override {return "DATATYPE"; }
public:
	MemberTypeExpressionObject( const MemberTypeExpressionObject& other ) = default;
	MemberTypeExpressionObject( DataType& currentDataType, TemplateNodeSpace& templateSpace_, FILE* outStr ) : ExpressionObject( templateSpace_, outStr ), dataType( &currentDataType ) {}
	virtual MemberTypeExpressionObject* clone() const {return new MemberTypeExpressionObject( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  EnumValueExpressionObject : public ExpressionObject
{
protected:
	string name;
	uint32_t idlValue;
	uint32_t mappingValue;
	uint32_t encodingValue;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context() override {return "ENUMVALUE"; }
public:
	EnumValueExpressionObject( const EnumValueExpressionObject& other ) = default;
	EnumValueExpressionObject( const string& currentName, uint32_t currentIdlValue, uint32_t currentMappingValue, uint32_t currentEncodingValue, TemplateNodeSpace& templateSpace_, FILE* outStr ) : 
		ExpressionObject( templateSpace_, outStr ), name( currentName ), idlValue( currentIdlValue ), mappingValue( currentMappingValue ), encodingValue( currentEncodingValue ) {}
	virtual EnumValueExpressionObject* clone() const {return new EnumValueExpressionObject( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  DiscriminatedUnionExpressionObject : public ExpressionObject
{
protected:
	BackStructure* structure;

	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context() override {return "DISCRIMINATED-UNION"; }
public:
	DiscriminatedUnionExpressionObject( const DiscriminatedUnionExpressionObject& other ) = default;
	DiscriminatedUnionExpressionObject( BackStructure& currentStruct, TemplateNodeSpace& templateSpace_, FILE* outStr ) : ExpressionObject( templateSpace_, outStr ), structure( &currentStruct ) {}
	virtual DiscriminatedUnionExpressionObject* clone() const {return new DiscriminatedUnionExpressionObject( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  DiscriminatedUnionOptionExpressionObject : public ExpressionObject
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
	DiscriminatedUnionOptionExpressionObject( const DiscriminatedUnionOptionExpressionObject& other ) = default;
	DiscriminatedUnionOptionExpressionObject( const BackDataMember& currentBaseEnum, vector<const BackDataMember*>& currentUsedMembers, const string& currentEnumValueName, uint32_t currentIdlValue, uint32_t currentMappingValue, uint32_t currentEncodingValue, TemplateNodeSpace& templateSpace_, FILE* outStr ) : 
		ExpressionObject( templateSpace_, outStr ),usedMembers( currentUsedMembers ), baseEnum( &currentBaseEnum ), enumValueName( currentEnumValueName ), idlValue( currentIdlValue ), mappingValue( currentMappingValue ), encodingValue( currentEncodingValue ) {}
	virtual DiscriminatedUnionOptionExpressionObject* clone() const {return new DiscriminatedUnionOptionExpressionObject( *this );}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // TEMPLATE_INSTANTIATOR_DERIVED_H
