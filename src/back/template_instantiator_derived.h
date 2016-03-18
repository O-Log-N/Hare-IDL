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
	virtual void applyNode( TemplateNode& node );
	virtual string placeholder( Placeholder ph );
	virtual string context() override {return "ROOT"; }

public:
	RootTemplateInstantiator( BackRoot& structRoot, TemplateNodeSpace& templateSpace_, ostream* outStr ) : TemplateInstantiator( templateSpace_, outStr ), root( &structRoot ) {}

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
	virtual void applyNode( TemplateNode& node );
	virtual string placeholder( Placeholder ph );
	virtual string context() override {return "STRUCT"; }

public:
	StructTemplateInstantiator( BackStructure& currentStruct, TemplateNodeSpace& templateSpace_, ostream* outStr ) : TemplateInstantiator( templateSpace_, outStr ), structure( &currentStruct ) {}

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
	virtual void applyNode( TemplateNode& node );
	virtual string placeholder( Placeholder ph );
	virtual string context() override {return "STRUCT-MEMBER"; }

public:
	StructMemberTemplateInstantiator( BackDataMember& currentMember, TemplateNodeSpace& templateSpace_, ostream* outStr ) : TemplateInstantiator( templateSpace_, outStr ), member( &currentMember ) {}

	void apply( TemplateNode& node )
	{
		applyNode( node );
	}
};


void apply( BackRoot& structure, TemplateNodeSpace& templateSpace );


#endif // TEMPLATE_INSTANTIATOR_DERIVED_H
