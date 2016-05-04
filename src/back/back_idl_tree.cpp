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
	ret->extendTo = src->extendTo;
	ret->defaultValue = src->defaultValue;
	for ( auto& it:src->whenDiscriminant )
		ret->whenDiscriminant.push_back( it );
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
		size_t i;
		BackEncodedMembers* currentEncoded = new BackEncodedMembers;
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
	ret->discriminant = src->discriminant;
	size_t i;
	for ( i=0; i<src->members.size(); i++ )
	{
		BackEncodedOrMember* retChild = copyEncoded( &(*(src->members[i])) );
		ret->addChild( retChild );
	}
	return ret;
}

void convertToBackTree( const Root& root, BackRoot& backRoot )
{
	size_t i;
	for ( i=0; i<root.structures.size(); i++ )
	{
		BackStructure* ret = copyStructure( &(*(root.structures[i])) );
		switch ( ret->declType )
		{
			case Structure::DECLTYPE::IDL: backRoot.structuresIdl.push_back( unique_ptr<BackStructure>(ret) ); break;
			case Structure::DECLTYPE::MAPPING: backRoot.structuresMapping.push_back( unique_ptr<BackStructure>(ret) ); break;
			case Structure::DECLTYPE::ENCODING: backRoot.structuresEncoding.push_back( unique_ptr<BackStructure>(ret) ); break;
			default:
			{
				// TODO: report error
				assert( 0 );
			}
		}
		
	}
}