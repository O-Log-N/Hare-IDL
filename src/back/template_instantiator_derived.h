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

	virtual void applyNode( TemplateNode& node );
	virtual string placeholder( int placeholderId );
	virtual string context() override {return "ROOT"; }

public:
	RootTemplateInstantiator( BackRoot& structRoot, TemplateNodeSpace& templateSpace_, ostream* outStr ) : TemplateInstantiator( templateSpace_, outStr ), root( &structRoot ) {}

	void apply()
	{
		for ( auto t:templateSpace.templates )
		{
			if ( t.templateType == "ROOT" )
			{
				assert( t.childNodes.size() == 1 );
				applyNode( t.childNodes[0] );
			}
		}
		/*TemplateNode& node
		assert( node.childNodes.size() == 1 );
		applyNode( node.childNodes[0] );*/
	}
};


class StructTemplateInstantiator : public TemplateInstantiator
{
protected:
	BackStructure* structure;

	virtual void applyNode( TemplateNode& node );
	virtual string placeholder( int placeholderId );
	virtual string context() override {return "STRUCT"; }

public:
	StructTemplateInstantiator( BackStructure& currentStruct, TemplateNodeSpace& templateSpace_, ostream* outStr ) : TemplateInstantiator( templateSpace_, outStr ), structure( &currentStruct ) {}

	void apply( TemplateNode& node )
	{
		assert( node.childNodes.size() == 1 );
//		applyNode( node.childNodes[0] );
		applyNode( node );
	}
};


class StructMemberTemplateInstantiator : public TemplateInstantiator
{
protected:
	BackDataMember* member;

	virtual void applyNode( TemplateNode& node );
	virtual string placeholder( int placeholderId );
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
