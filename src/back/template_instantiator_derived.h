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


class StructTemplateInstantiator : public TemplateInstantiator
{
protected:
	BackStructure* structure;

	virtual string placeholder( int placeholderId );
	virtual void applyToEach( TemplateNode& node );
	void applyNode( TemplateNode& node );


public:
	StructTemplateInstantiator( BackStructure& currentStruct ) { structure = &currentStruct; }

	void apply( AnyTemplateRoot& node )
	{
		applyNode( node.root );
	}
};


class StructMemberTemplateInstantiator : public TemplateInstantiator
{
protected:
	BackDataMember* member;

	virtual string placeholder( int placeholderId );
//	virtual void applyToEach( TemplateNode& node );
	void applyNode( TemplateNode& node );

public:
	StructMemberTemplateInstantiator( BackDataMember& currentMember ) { member = &currentMember; }

	void apply( TemplateNode& node )
	{
		applyNode( node );
	}
};


void apply( BackStructure& structure, AnyTemplateRoot& rootNode );


#endif // TEMPLATE_INSTANTIATOR_DERIVED_H
