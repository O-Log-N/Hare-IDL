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

#include "back_idl_tree.h"

BackDataMember* copy_member( const DataMember* src )
{
	BackDataMember* ret = new BackDataMember;
	ret->name = src->name;
	ret->type = src->type;
	return ret;
}

BackEncodedOrMember* copy_encoded( const EncodedOrMember* src )
{
	if ( dynamic_cast<const DataMember*>(src) != NULL )
	{
		BackDataMember* current_member = copy_member( reinterpret_cast<const DataMember*>(src) );
		return current_member;
	}
	else
	{
		const EncodedMembers* encsrc = reinterpret_cast<const EncodedMembers*>(src);
		unsigned int i;
		BackEncodedMembers* current_encoded = new BackEncodedMembers;
		current_encoded->encodingAttr = encsrc->encodingAttr;
		for ( i=0; i<encsrc->members.size(); i++ )
		{ 
			BackEncodedOrMember* ret = copy_encoded( &(*(encsrc->members[i])) );
			current_encoded->addChild( ret );
		}
		return current_encoded;
	}
}

BackStructure* copy_structure( const Structure* src )
{
	BackStructure* ret = new BackStructure;
	ret->declType = src->declType;
	ret->type = src->type;
	ret->name = src->name;
	ret->encodingAttr = src->encodingAttr;
	unsigned int i;
	for ( i=0; i<src->members.size(); i++ )
	{
		BackEncodedOrMember* ret_child = copy_encoded( &(*(src->members[i])) );
//		ret->members.push_back( unique_ptr<BackEncodedOrMember>(ret_child) );
		ret->addChild( ret_child );
	}
	return ret;
}

void convert_to_back_tree( const Root& root, BackRoot& back_root )
{
	unsigned int i;
	for ( i=0; i<root.structures.size(); i++ )
	{
		BackStructure* ret = copy_structure( &(*(root.structures[i])) );
		back_root.structures.push_back( unique_ptr<BackStructure>(ret) );
	}
}