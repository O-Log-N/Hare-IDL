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

#if !defined TEMPLATE_INSTANTIATOR_H
#define TEMPLATE_INSTANTIATOR_H

#include "template_parser.h"
#include <stdio.h>
#include "back_idl_tree.h"

#define CONTEXT_STRUCT 1
#define CONTEXT_STRUCT_MEMBER 2

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
	BackStructure* structure;

	virtual std::string placeholder( int placeholder_id );
	virtual void apply_to_each( TEMPLATE_NODE& node );


public:
	struct_template_instantiator( BackStructure& currentStruct ) { structure = &currentStruct; }

	void apply( ANY_TEMPLATE_ROOT& node )
	{
		apply_node( node.root );
	}
};

class struct_member_template_instantiator : public template_instantiator
{
protected:
	BackDataMember* member;

	virtual std::string placeholder( int placeholder_id );
//	virtual void apply_to_each( TEMPLATE_NODE& node );

public:
	struct_member_template_instantiator( BackDataMember& currentMember ) { member = &currentMember; }

	void apply( TEMPLATE_NODE& node )
	{
		apply_node( node );
	}
};


void apply( BackStructure& structure, ANY_TEMPLATE_ROOT& root_node );


#endif // TEMPLATE_INSTANTIATOR_H
