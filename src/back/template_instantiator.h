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

#if !defined __TEMPLATE_INSTANTIATOR_H__
#define __TEMPLATE_INSTANTIATOR_H__

#include "template_parser.h"
#include <stdio.h>
#include <idl.h>
#include <literal_node.h>

#define CONTEXT_STRUCT 1
#define CONTEXT_STRUCT_MEMBER 2

using namespace kpm;

class template_instantiator
{
protected:
	bool calc_condition_of_if_node( TEMPLATE_NODE& if_node );
	void apply_node( TEMPLATE_NODE& node );

public:
	template_instantiator() {}

	virtual std::string placeholder( int placeholder_id );
	virtual void apply_to_each( TEMPLATE_NODE& node );
};

class struct_template_instantiator : public template_instantiator
{
protected:
	MappingDeclNode* idlmap; // TODO: use actual type!

	virtual std::string placeholder( int placeholder_id );
	virtual void apply_to_each( TEMPLATE_NODE& node );


public:
	struct_template_instantiator( MappingDeclNode* _idlmap ) { idlmap = _idlmap; }

	void apply( ANY_TEMPLATE_ROOT& node )
	{
		apply_node( node.root );
	}
};

class struct_member_template_instantiator : public template_instantiator
{
protected:
	AttributeDeclNode* attr; // TODO: use actual type!

	virtual std::string placeholder( int placeholder_id );
//	virtual void apply_to_each( TEMPLATE_NODE& node );

public:
	struct_member_template_instantiator( AttributeDeclNode* _attr ) { attr = _attr; }

	void apply( TEMPLATE_NODE& node )
	{
		apply_node( node );
	}
};


void apply( MappingDeclNode* idlmap, ANY_TEMPLATE_ROOT& _root_node );


#endif // __TEMPLATE_INSTANTIATOR_H__
