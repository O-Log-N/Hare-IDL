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
	// TODO: copy Type
	return ret;
}

BackEncodedOrMember* copy_encoded( const EncodedOrMember* src )
{
	if ( src->isMember() )
//	if ( dynamic_cast<const DataMember*>(src) != NULL )
	{
		BackDataMember* current_member = copy_member( reinterpret_cast<const DataMember*>(src) );
	}
	else
	{
		const EncodedMembers* encsrc = reinterpret_cast<const EncodedMembers*>(src);
		unsigned int i;
		BackEncodedMembers* current_encoded = new BackEncodedMembers;
		for ( i=0; i<encsrc->members.size(); i++ )
		{ 
			BackEncodedOrMember* ret = copy_encoded( &(*(encsrc->members[i])) );
			current_encoded->members.push_back( unique_ptr<BackEncodedOrMember>(ret) );
		}
	}
	BackEncodedOrMember* ret = new BackEncodedOrMember;
	return ret;
}

BackStructure* copy_structure( const Structure* src )
{
	BackStructure* ret = new BackStructure;
	ret->declType = src->declType;
	ret->structureType = src->structureType;
	ret->name = src->name;
	// TODO: copy attributes
	unsigned int i;
	for ( i=0; i<src->members.size(); i++ )
	{
		BackEncodedOrMember* ret_child = copy_encoded( &(*(src->members[i])) );
		ret->members.push_back( unique_ptr<BackEncodedOrMember>(ret_child) );
	}
	return ret;
}

#if 0
BackEncodedOrMember* make_a_copy( const EncodedOrMember* src )
{
	BackEncodedOrMember* ret;
/*	if ( src->isMember() )
	{
	}
	else
	{
	}
	BackEncodedOrMember* ret = new BackEncodedOrMember;
	ret->*/
	switch ( src->myType() )
	{
		case EncodedOrMember::MEMBER:
		{
			BackDataMember* current_member = new BackDataMember;
			ret = current_member;
		}
		case EncodedOrMember::ENCODED:
		{
			BackEncodedMembers* current_encoded = new BackEncodedMembers;
			ret = current_encoded;
		}
		case EncodedOrMember::STRUCTURE:
		{
			BackStructure* current_structure = new BackStructure;
			ret = current_structure;
		}
	}
}
#endif

void convert_to_back_tree( const VectorOfStructures& interface_tree, VectorOfBackStructures& back_tree )
{
	unsigned int i;
	for ( i=0; i<interface_tree.size(); i++ )
	{
		BackStructure* ret = copy_structure( &(*(interface_tree[i])) );
		back_tree.push_back( unique_ptr<BackStructure>(ret) );
	}
}