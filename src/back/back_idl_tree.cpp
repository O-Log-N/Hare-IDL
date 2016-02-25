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

BackDataMember* copyMember( const DataMember* src )
{
	BackDataMember* ret = new BackDataMember;
	ret->name = src->name;
	ret->type = src->type;
	return ret;
}

BackEncodedOrMember* copyEncoded( const EncodedOrMember* src )
{
	const DataMember* srcMember = dynamic_cast<const DataMember*>(src);
	if ( srcMember != NULL )
	{
		BackDataMember* currentMember = copyMember( srcMember );
		return currentMember;
	}
	else
	{
		const EncodedMembers* encsrc = dynamic_cast<const EncodedMembers*>(src);
		assert( encsrc != NULL ); // currently we do not expect any other type here
		unsigned int i;
		BackEncodedMembers* currentEncoded = new BackEncodedMembers;
		currentEncoded->encodingAttr = encsrc->encodingAttr;
		for ( i=0; i<encsrc->members.size(); i++ )
		{ 
			BackEncodedOrMember* ret = copyEncoded( &(*(encsrc->members[i])) );
			currentEncoded->addChild( ret );
		}
		return currentEncoded;
	}
}

BackStructure* copyStructure( const Structure* src )
{
	BackStructure* ret = new BackStructure;
	ret->declType = src->declType;
	ret->type = src->type;
	ret->name = src->name;
	ret->encodingAttr = src->encodingAttr;
	unsigned int i;
	for ( i=0; i<src->members.size(); i++ )
	{
		BackEncodedOrMember* retChild = copyEncoded( &(*(src->members[i])) );
		ret->addChild( retChild );
	}
	return ret;
}

void convertToBackTree( const Root& root, BackRoot& backRoot )
{
	unsigned int i;
	for ( i=0; i<root.structures.size(); i++ )
	{
		BackStructure* ret = copyStructure( &(*(root.structures[i])) );
		backRoot.structures.push_back( unique_ptr<BackStructure>(ret) );
	}
}