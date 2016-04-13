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

#include "idl_tree_finalizer.h"

void finalizeTree( BackRoot& root )
{
	// 1. go through all structures; invalidate cross-ref ptrs
	for ( auto& it:root.structures )
	{
		it->idlStruct = nullptr;
		it->mappingStruct = nullptr;
		it->encodingStruct = nullptr;
	}

	// 2. go through all structures; process IDL structures
//	for ( auto& itIDL:root.structures )
	for ( size_t i=0; i<root.structures.size(); ++i )
	{
		if ( root.structures[i]->declType != Structure::DECLTYPE::IDL )
			continue;
		assert( root.structures[i]->mappingStruct == nullptr );
		assert( root.structures[i]->encodingStruct == nullptr );

		// find proper mapping
		bool mapFound = false;
		for ( auto& itMap:root.structures )
			if ( itMap->declType == Structure::DECLTYPE::MAPPING && itMap->type == root.structures[i]->type && itMap->name == root.structures[i]->name ) // TODO: check whether this condition is sufficient
			{
				assert( itMap->idlStruct == nullptr );
				if ( mapFound )
				{
					// TODO: report error
					assert( 0 );
				}
				mapFound = true;
				root.structures[i]->mappingStruct = &(*itMap);
				itMap->idlStruct = &(*(root.structures[i]));
				itMap->mappingStruct = &(*itMap);
				// TODO: fill mutual defaults where applicable
			}
		if ( !mapFound )
		{ 
			BackStructure* newMap = new BackStructure;
			newMap->declType = Structure::DECLTYPE::MAPPING;
			root.structures.push_back( unique_ptr<BackStructure>(newMap) ); // TODO: think about very defaults
			root.structures[i]->mappingStruct = &(*(root.structures.back()));
			(root.structures.back())->idlStruct = &(*(root.structures[i]));
			(root.structures.back())->mappingStruct = &(*(root.structures.back()));
			// TODO: fill it with defaults based on root.structures[i]
		}

		// find proper encoding
		bool encodingFound = false;
		for ( auto& itEnc:root.structures )
			if ( itEnc->declType == Structure::DECLTYPE::ENCODING && itEnc->type == root.structures[i]->type && itEnc->name == root.structures[i]->name ) // TODO: check whether this condition is sufficient
			{
				assert( itEnc->idlStruct == nullptr );
				if ( encodingFound )
				{
					// TODO: report error
					assert( 0 );
				}
				encodingFound = true;
				root.structures[i]->encodingStruct = &(*itEnc);
				itEnc->idlStruct = &(*(root.structures[i]));
				itEnc->encodingStruct = &(*itEnc);
				// TODO: fill cross-ref ptrs; fill mutual defaults where applicable
			}
		if ( !encodingFound )
		{ 
			BackStructure* newEnc = new BackStructure;
			newEnc->declType = Structure::DECLTYPE::ENCODING;
			root.structures.push_back( unique_ptr<BackStructure>(newEnc) ); // TODO: think about very defaults
			root.structures[i]->encodingStruct = &(*(root.structures.back()));
			root.structures.back()->idlStruct = &(*(root.structures[i]));
			(root.structures.back())->encodingStruct = &(*(root.structures.back()));
			// TODO: fill it with defaults based on root.structures[i]
		}

		// fill cross-ref ptrs between mapping and encoding structs
		root.structures[i]->mappingStruct->encodingStruct = root.structures[i]->encodingStruct;
		root.structures[i]->encodingStruct->mappingStruct = root.structures[i]->mappingStruct;
		root.structures[i]->idlStruct = &(*(root.structures[i]));
	}
}

void prevalidateTree( BackRoot& root )
{
	for ( auto& it:root.structures )
	{
		// no orphan check
		assert( it->idlStruct != nullptr );
		assert( it->mappingStruct != nullptr );
		assert( it->encodingStruct != nullptr );
		if ( it->declType == Structure::DECLTYPE::MAPPING )
		{
			assert( it->idlStruct->mappingStruct == &(*it) );
			continue; // will be processed in context of a respective IDL type
		}
		if ( it->declType == Structure::DECLTYPE::ENCODING )
		{
			assert( it->idlStruct->encodingStruct == &(*it) );
			continue; // will be processed in context of a respective IDL type
		}
		assert(  it->declType == Structure::DECLTYPE::IDL );
		assert( it->mappingStruct->idlStruct == &(*it) );
		assert( it->encodingStruct->idlStruct == &(*it) );
		// TODO: any further validation
	}
}
