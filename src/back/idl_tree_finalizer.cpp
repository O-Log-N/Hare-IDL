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

struct STRUCTURE_DATA_SOURCES
{
	BackStructure* idl;
	BackStructure* mapping;
	BackStructure* encoding;
	bool idlExists;
	bool mappingExists;
	bool encodingExists;
};

void fillDefaultDataWhereApplicable( STRUCTURE_DATA_SOURCES& sources ) // preliminary interface
{
}

void finalizeTree( BackRoot& root )
{
	STRUCTURE_DATA_SOURCES sources;
	// 1. go through all structures; invalidate cross-ref ptrs
	for ( auto& it:root.structures )
	{
		it->idlStruct = nullptr;
		it->mappingStruct = nullptr;
		it->encodingStruct = nullptr;
	}

	// 2. go through all structures; process IDL structures
	for ( size_t i=0; i<root.structures.size(); ++i )
	{
		if ( root.structures[i]->declType != Structure::DECLTYPE::IDL )
			continue;
		assert( root.structures[i]->mappingStruct == nullptr );
		assert( root.structures[i]->encodingStruct == nullptr );

		memset( &sources, 0, sizeof(sources) );
		sources.idlExists = true;
		sources.idl = &(*(root.structures[i]));

		// find proper mapping
		bool mapFound = false;
		for ( auto& itMap:root.structures )
			if ( itMap->declType == Structure::DECLTYPE::MAPPING && itMap->type == root.structures[i]->type && itMap->name == root.structures[i]->name ) // TODO: check whether this condition makes sense
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
				itMap->mappingStruct = &(*itMap); // self
				sources.mappingExists = true;
				sources.mapping = &(*itMap);
			}
		if ( !mapFound )
		{ 
			BackStructure* newMap = new BackStructure;
			newMap->declType = Structure::DECLTYPE::MAPPING;
			root.structures.push_back( unique_ptr<BackStructure>(newMap) );
			root.structures[i]->mappingStruct = &(*(root.structures.back()));
			(root.structures.back())->idlStruct = &(*(root.structures[i]));
			(root.structures.back())->mappingStruct = &(*(root.structures.back())); // self
			sources.mapping = &(*(root.structures.back()));
		}

		// find proper encoding
		bool encodingFound = false;
		for ( auto& itEnc:root.structures )
			if ( itEnc->declType == Structure::DECLTYPE::ENCODING && itEnc->type == root.structures[i]->type && itEnc->name == root.structures[i]->name ) // TODO: check whether this condition makes sense
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
				sources.encodingExists = true;
				sources.encoding = &(*itEnc);
			}
		if ( !encodingFound )
		{ 
			BackStructure* newEnc = new BackStructure;
			newEnc->declType = Structure::DECLTYPE::ENCODING;
			root.structures.push_back( unique_ptr<BackStructure>(newEnc) ); // TODO: think about very defaults
			root.structures[i]->encodingStruct = &(*(root.structures.back()));
			root.structures.back()->idlStruct = &(*(root.structures[i]));
			(root.structures.back())->encodingStruct = &(*(root.structures.back())); // self
			sources.encoding = &(*(root.structures.back()));
		}

		// fill cross-ref ptrs between mapping and encoding structs
		root.structures[i]->mappingStruct->encodingStruct = root.structures[i]->encodingStruct;
		root.structures[i]->encodingStruct->mappingStruct = root.structures[i]->mappingStruct;
		root.structures[i]->idlStruct = &(*(root.structures[i])); // self

		// fill defaults
		fillDefaultDataWhereApplicable( sources );
	}

	// 3. go through all structures; process MAPPING structures (note that some of them are already processed)
	for ( size_t i=0; i<root.structures.size(); ++i )
	{
		if ( root.structures[i]->declType != Structure::DECLTYPE::MAPPING )
			continue;
		if( root.structures[i]->idlStruct != nullptr || root.structures[i]->mappingStruct != nullptr || root.structures[i]->encodingStruct != nullptr )
		{
			assert( root.structures[i]->idlStruct != nullptr && root.structures[i]->mappingStruct != nullptr && root.structures[i]->encodingStruct != nullptr );
			continue;
		}

		memset( &sources, 0, sizeof(sources) );
		sources.mapping = &(*(root.structures[i]));
		sources.mappingExists = true;

		// find proper idl (indeed, just check that there is none)
		for ( auto& itIdl:root.structures )
			if ( itIdl->declType == Structure::DECLTYPE::IDL && itIdl->type == root.structures[i]->type && itIdl->name == root.structures[i]->name ) // TODO: check whether this condition makes sense
			{
				// TODO: report error (potential source of this error: more than a single IDL description
				assert( 0 );
			}
		BackStructure* newIdl = new BackStructure;
		newIdl->declType = Structure::DECLTYPE::IDL;
		root.structures.push_back( unique_ptr<BackStructure>(newIdl) );
		root.structures[i]->idlStruct = &(*(root.structures.back()));
		(root.structures.back())->mappingStruct = &(*(root.structures[i]));
		(root.structures.back())->idlStruct = &(*(root.structures.back())); // self
		sources.idl = &(*(root.structures.back()));

		// find proper encoding
		for ( auto& itEnc:root.structures )
			if ( itEnc->declType == Structure::DECLTYPE::ENCODING && itEnc->type == root.structures[i]->type && itEnc->name == root.structures[i]->name ) // TODO: check whether this condition makes sense
			{
				// TODO: report error (potential source of this error: more than a single ENCODING description
				assert( 0 );
			}
		BackStructure* newEnc = new BackStructure;
		newEnc->declType = Structure::DECLTYPE::ENCODING;
		root.structures.push_back( unique_ptr<BackStructure>(newEnc) ); // TODO: think about very defaults
		root.structures[i]->encodingStruct = &(*(root.structures.back()));
		root.structures.back()->mappingStruct = &(*(root.structures[i]));
		(root.structures.back())->encodingStruct = &(*(root.structures.back())); // self
		sources.encoding = &(*(root.structures.back()));

		// fill cross-ref ptrs between mapping and encoding structs
		root.structures[i]->idlStruct->encodingStruct = root.structures[i]->encodingStruct;
		root.structures[i]->encodingStruct->idlStruct = root.structures[i]->idlStruct;
		root.structures[i]->mappingStruct = &(*(root.structures[i])); // self

		// fill defaults
		fillDefaultDataWhereApplicable( sources );
	}

	// 4. go through all structures; process ENCODING structures (note that some of them are already processed)
	for ( size_t i=0; i<root.structures.size(); ++i )
	{
		if ( root.structures[i]->declType != Structure::DECLTYPE::ENCODING )
			continue;
		if( root.structures[i]->idlStruct != nullptr || root.structures[i]->mappingStruct != nullptr || root.structures[i]->encodingStruct != nullptr )
		{
			assert( root.structures[i]->idlStruct != nullptr && root.structures[i]->mappingStruct != nullptr && root.structures[i]->encodingStruct != nullptr );
			continue;
		}

		memset( &sources, 0, sizeof(sources) );
		sources.encoding = &(*(root.structures[i]));
		sources.encodingExists = true;

		// find proper idl (indeed, just check that there is none)
		for ( auto& itIdl:root.structures )
			if ( itIdl->declType == Structure::DECLTYPE::IDL && itIdl->type == root.structures[i]->type && itIdl->name == root.structures[i]->name ) // TODO: check whether this condition makes sense
			{
				// TODO: report error (potential source of this error: more than a single IDL description
				assert( 0 );
			}
		BackStructure* newIdl = new BackStructure;
		newIdl->declType = Structure::DECLTYPE::IDL;
		root.structures.push_back( unique_ptr<BackStructure>(newIdl) );
		root.structures[i]->idlStruct = &(*(root.structures.back()));
		(root.structures.back())->encodingStruct = &(*(root.structures[i]));
		(root.structures.back())->idlStruct = &(*(root.structures.back())); // self
		sources.idl = &(*(root.structures.back()));

		// find proper mapping
		for ( auto& itEnc:root.structures )
			if ( itEnc->declType == Structure::DECLTYPE::MAPPING && itEnc->type == root.structures[i]->type && itEnc->name == root.structures[i]->name ) // TODO: check whether this condition makes sense
			{
				// TODO: report error (potential source of this error: more than a single ENCODING description
				assert( 0 );
			}
		BackStructure* newMap = new BackStructure;
		newMap->declType = Structure::DECLTYPE::MAPPING;
		root.structures.push_back( unique_ptr<BackStructure>(newMap) );
		root.structures[i]->mappingStruct = &(*(root.structures.back()));
		root.structures.back()->encodingStruct = &(*(root.structures[i]));
		(root.structures.back())->mappingStruct = &(*(root.structures.back())); // self
		sources.mapping = &(*(root.structures.back()));

		// fill cross-ref ptrs between mapping and encoding structs
		root.structures[i]->idlStruct->mappingStruct = root.structures[i]->mappingStruct;
		root.structures[i]->mappingStruct->idlStruct = root.structures[i]->idlStruct;
		root.structures[i]->encodingStruct = &(*(root.structures[i])); // self

		// fill defaults
		fillDefaultDataWhereApplicable( sources );
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
