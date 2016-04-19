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

#if 0
struct STRUCTURE_DATA_SOURCES
{
	BackEncodedOrMember* idl;
	BackEncodedOrMember* mapping;
	BackEncodedOrMember* encoding;
	bool idlExists;
	bool mappingExists;
	bool encodingExists;
};

void fillMappingUsingIdl( const BackStructure& idl, BackStructure& mapping )
{
	size_t sz = idl.getChildCount();
	for ( size_t i=0; i<sz; ++i )
	{
		const BackEncodedOrMember* member = idl.getConstMember( i );
	};
}

void fillEncodingUsingIdl( const BackStructure& idl, BackStructure& mapping )
{
}

void cleanCrossRefPtrsOfMembers( BackStructure& backstruct )
{
	size_t sz = backstruct.getChildCount();
	for ( size_t i=0; i<sz; ++i )
	{
		BackEncodedOrMember* member = backstruct.getMember( i );
		member->idlRepresentation = nullptr;
		member->mappingRepresentation = nullptr;
		member->encodingRepresentation = nullptr;
	}
}

void fillDefaultDataWhereApplicableMemberLevel( STRUCTURE_DATA_SOURCES& sources ) // preliminary interface
{
}

void findOrAddMatchesAndFillDefaults( BackStructure& structIdl, BackStructure& structMapping, BackStructure& structEncoding )
{
	//BackStructure& backStructBase, BackStructure& backStruct1, BackStructure& backStruct2
	STRUCTURE_DATA_SOURCES sources;

	// go through IDL members
	size_t szIdl = structIdl.getChildCount();
	for ( size_t i=0; i<szIdl; ++i )
	{
		BackDataMember* memberIdl = dynamic_cast<BackDataMember*>( structIdl.getMember( i ) );

		memset( &sources, 0, sizeof(sources) );
		sources.idlExists = true;
		sources.idl = memberIdl;

		// find or add in mapping
		size_t szMap = structMapping.getChildCount();
		bool found = false;
		for ( size_t i=0; i<szMap; ++i )
		{
			BackDataMember* memberMap = dynamic_cast<BackDataMember*>( structMapping.getMember( i ) );
			if ( memberMap->name == memberIdl->name )
			{
				assert( memberMap->idlRepresentation == nullptr );
				if ( found )
				{
					// TODO: report error (repeated entry)
					assert( 0 );
				}
				found = true;
				memberIdl->mappingRepresentation = memberMap;
				memberMap->idlRepresentation = memberIdl;
				memberMap->mappingRepresentation = memberMap; // self
				sources.mappingExists = true;
				sources.mapping = memberMap;
			}
		}
		if ( !found )
		{ 
			BackDataMember* newMap = new BackDataMember;
			structMapping.addChild( newMap );
			memberIdl->mappingRepresentation = newMap;
			newMap->idlRepresentation = memberIdl;
			newMap->mappingRepresentation = newMap; // self
			sources.mapping = newMap;
		}

		// find or add in encoding
		size_t szEnc = structMapping.getChildCount();
		found = false;
		for ( size_t i=0; i<szEnc; ++i )
		{
			BackDataMember* memberEnc = dynamic_cast<BackDataMember*>( structEncoding.getMember( i ) );
			if ( memberEnc->name == memberIdl->name )
			{
				assert( memberEnc->idlRepresentation == nullptr );
				if ( found )
				{
					// TODO: report error (repeated entry)
					assert( 0 );
				}
				found = true;
				memberIdl->mappingRepresentation = memberEnc;
				memberEnc->idlRepresentation = memberIdl;
				memberEnc->mappingRepresentation = memberEnc; // self
				sources.encodingExists = true;
				sources.encoding = memberEnc;
			}
		}
		if ( !found )
		{ 
			BackDataMember* newEnc = new BackDataMember;
			structEncoding.addChild( newEnc );
			memberIdl->encodingRepresentation = newEnc;
			newEnc->idlRepresentation = memberIdl;
			newEnc->encodingRepresentation = newEnc; // self
			sources.encoding = newEnc;
		}

		// fill cross-ref ptrs between mapping and encoding structs
		memberIdl->mappingRepresentation->encodingRepresentation = memberIdl->encodingRepresentation;
		memberIdl->encodingRepresentation->mappingRepresentation = memberIdl->mappingRepresentation;
		memberIdl->idlRepresentation = memberIdl; // self

		// fill defaults
		fillDefaultDataWhereApplicableMemberLevel( sources );
	}

	// go through MAPPING members
	size_t szMapping = structMapping.getChildCount();
	for ( size_t i=0; i<szMapping; ++i )
	{
		BackDataMember* memberIdl = dynamic_cast<BackDataMember*>( structIdl.getMember( i ) );

		memset( &sources, 0, sizeof(sources) );
		sources.idlExists = true;
		sources.idl = memberIdl;

		// find or add in mapping
		size_t szMap = structMapping.getChildCount();
		bool found = false;
		for ( size_t i=0; i<szMap; ++i )
		{
			BackDataMember* memberMap = dynamic_cast<BackDataMember*>( structMapping.getMember( i ) );
			if ( memberMap->name == memberIdl->name )
			{
				assert( memberMap->idlRepresentation == nullptr );
				if ( found )
				{
					// TODO: report error (repeated entry)
					assert( 0 );
				}
				found = true;
				memberIdl->mappingRepresentation = memberMap;
				memberMap->idlRepresentation = memberIdl;
				memberMap->mappingRepresentation = memberMap; // self
				sources.mappingExists = true;
				sources.mapping = memberMap;
			}
		}
		if ( !found )
		{ 
			BackDataMember* newMap = new BackDataMember;
			structMapping.addChild( newMap );
			memberIdl->mappingRepresentation = newMap;
			newMap->idlRepresentation = memberIdl;
			newMap->mappingRepresentation = newMap; // self
			sources.mapping = newMap;
		}

		// find or add in encoding
		size_t szEnc = structMapping.getChildCount();
		found = false;
		for ( size_t i=0; i<szEnc; ++i )
		{
			BackDataMember* memberEnc = dynamic_cast<BackDataMember*>( structEncoding.getMember( i ) );
			if ( memberEnc->name == memberIdl->name )
			{
				assert( memberEnc->idlRepresentation == nullptr );
				if ( found )
				{
					// TODO: report error (repeated entry)
					assert( 0 );
				}
				found = true;
				memberIdl->mappingRepresentation = memberEnc;
				memberEnc->idlRepresentation = memberIdl;
				memberEnc->mappingRepresentation = memberEnc; // self
				sources.encodingExists = true;
				sources.encoding = memberEnc;
			}
		}
		if ( !found )
		{ 
			BackDataMember* newEnc = new BackDataMember;
			structEncoding.addChild( newEnc );
			memberIdl->encodingRepresentation = newEnc;
			newEnc->idlRepresentation = memberIdl;
			newEnc->encodingRepresentation = newEnc; // self
			sources.encoding = newEnc;
		}

		// fill cross-ref ptrs between mapping and encoding structs
		memberIdl->mappingRepresentation->encodingRepresentation = memberIdl->encodingRepresentation;
		memberIdl->encodingRepresentation->mappingRepresentation = memberIdl->mappingRepresentation;
		memberIdl->idlRepresentation = memberIdl; // self

		// fill defaults
		fillDefaultDataWhereApplicableMemberLevel( sources );
	}
}

void fillDefaultDataWhereApplicableStructLevel( STRUCTURE_DATA_SOURCES& sources ) // preliminary interface
{
	assert( sources.idl != nullptr && sources.mapping != nullptr && sources.encoding != nullptr ); // all obj are created
	assert( sources.idlExists || sources.mappingExists || sources.encodingExists ); // at least one is pre-filled

	// Part I: only a single object exists
	if ( (!sources.mappingExists) && (!sources.encodingExists) ) // only IDL
	{
		fillMappingUsingIdl( *(dynamic_cast<BackStructure*>(sources.idl)), *(dynamic_cast<BackStructure*>(sources.idl)) );
		fillEncodingUsingIdl( *(dynamic_cast<BackStructure*>(sources.idl)), *(dynamic_cast<BackStructure*>(sources.idl)) );
		return;
	}
	if ( (!sources.idlExists) && (!sources.encodingExists) ) // only MAPPING
	{
		// TODO: process
		return;
	}
	if ( (!sources.idlExists) && (!sources.mappingExists) ) // only ENCODING
	{
		// TODO: process
		return;
	}
}
#endif // 0

BackDataMember* createMember( const BackDataMember& base, Structure::DECLTYPE baseDeclType, Structure::DECLTYPE retDeclType )
{
	BackDataMember* ret = new BackDataMember;
	// experimental logic
	// TODO: actual implementation
	if ( baseDeclType == Structure::DECLTYPE::MAPPING )
	{
		assert( retDeclType == Structure::DECLTYPE::IDL );
		ret->name = base.name;
		ret->type = base.type;
	}
	return ret;
}

bool matchMembers( const BackDataMember& member1, Structure::DECLTYPE declType1, const BackDataMember& member2, Structure::DECLTYPE declType2 )
{
	bool ret = true;
	return ret;
}

BackDataMember* createFakeMember()
{
	BackDataMember* ret = new BackDataMember;
	//ret->type = FAKE;
	return ret;
}

BackStructure* doStructureDataMatchingOrOverridding( BackStructure& structBase, Structure::DECLTYPE type1, BackStructure* structOverr, Structure::DECLTYPE type2, TREE_DATA_COMPLETION_OPERATION oper )
{
	size_t sz = structBase.getChildCount();
	bool noDefaults = structOverr == nullptr;
	if ( noDefaults )
	{
		structOverr = new BackStructure;
		structOverr->declType = type2;
		structOverr->name = structBase.name;
		if ( oper == TREE_DATA_COMPLETION_OPERATION::MATCH ) // quick jump is possible
		{
			if ( sz != 0 )
			{
				// TODO: issue warnings
			}
			return structOverr;
		}
	}
	else
	{
		assert( structOverr->declType == type2 );
		assert( structOverr->name == structBase.name );
	}

	assert( structOverr != nullptr );

	for ( size_t i=0; i<sz; ++i )
	{
		BackDataMember* member = dynamic_cast<BackDataMember*>( structBase.getMember( i ) );
		size_t sz2 = structOverr->getChildCount();
		BackDataMember* otherMember = nullptr;
		for ( size_t j=0; j<sz2; ++j )
		{
			BackDataMember* member2 = dynamic_cast<BackDataMember*>( structOverr->getMember( j ) );
			if ( member->name == member2->name )
			{
				if ( otherMember != nullptr ) // second instance with the same name; an obvious (?) error
				{
					// TODO: report error
					assert( 0 );
				}
				otherMember = member2;
				bool matchRet = matchMembers( *member, type1, *otherMember, type2 );
				// TODO: what do we do with failure?
			}
		}

		if ( otherMember == nullptr )
		{
			if ( oper == TREE_DATA_COMPLETION_OPERATION::MATCH ) // TODO: case of strict matching
			{
				// TODO: issue warning
				otherMember = createFakeMember();
			}
			else
			{
				otherMember = createMember( *member, type1, type2 );
			}
			assert( otherMember != nullptr );
			structOverr->addChild( otherMember );
		}

		// add cross-references
		switch ( type1 )
		{
			case Structure::DECLTYPE::IDL: otherMember->idlRepresentation = member; member->idlRepresentation = member; break;
			case Structure::DECLTYPE::MAPPING: otherMember->mappingRepresentation = member; member->mappingRepresentation = member; break;
			case Structure::DECLTYPE::ENCODING: otherMember->encodingRepresentation = member; member->encodingRepresentation = member; break;
			default: 
			{
				assert( 0 );
				break;
			}
		}
		switch ( type2 )
		{
			case Structure::DECLTYPE::IDL: member->idlRepresentation = otherMember; otherMember->idlRepresentation = otherMember; break;
			case Structure::DECLTYPE::MAPPING: member->mappingRepresentation = otherMember; otherMember->mappingRepresentation = otherMember; break;
			case Structure::DECLTYPE::ENCODING: member->encodingRepresentation = otherMember; otherMember->encodingRepresentation = otherMember; break;
			default: 
			{
				assert( 0 );
				break;
			}
		}
	}

	return structOverr;
}

BackStructure* createFakeStructureNode( Structure::DECLTYPE type )
{
	BackStructure* ret = new BackStructure;
	ret->declType = type;
	//ret->type = FAKE;
	return ret;
}

void traverseStructTreesForDataMatchingOrOverridding( vector<unique_ptr<BackStructure>>& tree1, Structure::DECLTYPE type1, vector<unique_ptr<BackStructure>>& tree2, Structure::DECLTYPE type2, TREE_DATA_COMPLETION_OPERATION oper )
{
	for ( auto& it1:tree1 )
	{
		bool found = false;
		BackStructure* ret = nullptr;
		for ( auto& it2:tree2 )
		{
			if ( it1->name == it2->name )
			{
				if ( ret != nullptr ) // second instance with the same name; an obvious (?) error
				{
					// TODO: report error
					assert( 0 );
				}
				ret = doStructureDataMatchingOrOverridding( *it1, type1, &(*it2), type2, oper );
				if ( &(*it2) != ret )
					it2.reset( ret );
			}
		}
		if ( ret == nullptr )
		{
			if ( oper == TREE_DATA_COMPLETION_OPERATION::MATCH )
			{
				createFakeStructureNode( type2 );
				// TODO: warn user
			}
			else
			{
				ret = doStructureDataMatchingOrOverridding( *it1, type1, nullptr, type2, oper );
			}
			tree2.push_back( unique_ptr<BackStructure>(ret) );
		}

		// add cross-references
		switch ( type1 )
		{
			case Structure::DECLTYPE::IDL: ret->idlRepresentation = &(*it1); it1->idlRepresentation = &(*it1); break;
			case Structure::DECLTYPE::MAPPING: ret->mappingRepresentation = &(*it1); it1->mappingRepresentation = &(*it1); break;
			case Structure::DECLTYPE::ENCODING: ret->encodingRepresentation = &(*it1); it1->encodingRepresentation = &(*it1); break;
			default: 
			{
				assert( 0 );
				break;
			}
		}
		switch ( type2 )
		{
			case Structure::DECLTYPE::IDL: it1->idlRepresentation = ret; ret->idlRepresentation = ret; break;
			case Structure::DECLTYPE::MAPPING: it1->mappingRepresentation = ret; ret->mappingRepresentation = ret; break;
			case Structure::DECLTYPE::ENCODING: it1->encodingRepresentation = ret; ret->encodingRepresentation = ret; break;
			default: 
			{
				assert( 0 );
				break;
			}
		}
	}
}

void finalizeTree( BackRoot& root, TREE_DATA_COMPLETION_SCENARIO scenario )
{
	switch ( scenario )
	{
		case TREE_DATA_COMPLETION_SCENARIO::IDL_MAP_ENC:  break;
		case TREE_DATA_COMPLETION_SCENARIO::IDL_ONLY: break;
		case TREE_DATA_COMPLETION_SCENARIO::MAP_ONLY:
		{
			traverseStructTreesForDataMatchingOrOverridding( root.structuresMapping, Structure::DECLTYPE::MAPPING, root.structuresIdl, Structure::DECLTYPE::IDL, TREE_DATA_COMPLETION_OPERATION::OVERRIDE );
			break;
		}
		case TREE_DATA_COMPLETION_SCENARIO::ENC_ONLY: break;
		case TREE_DATA_COMPLETION_SCENARIO::IDL_MAP: break;
		case TREE_DATA_COMPLETION_SCENARIO::IDL_ENC: break;
		case TREE_DATA_COMPLETION_SCENARIO::MAJOR_MAP_ENC: break;
		case TREE_DATA_COMPLETION_SCENARIO::MAJOR_ENC_MAP: break;
	}
#if 0
	STRUCTURE_DATA_SOURCES sources;
	// 1. go through all structures; invalidate cross-ref ptrs
	for ( auto& it:root.structures )
	{
		it->idlRepresentation = nullptr;
		it->mappingRepresentation = nullptr;
		it->encodingRepresentation = nullptr;
	}

	// 2. go through all structures; process IDL structures
	for ( size_t i=0; i<root.structures.size(); ++i )
	{
		if ( root.structures[i]->declType != Structure::DECLTYPE::IDL )
			continue;
		assert( root.structures[i]->mappingRepresentation == nullptr );
		assert( root.structures[i]->encodingRepresentation == nullptr );

		memset( &sources, 0, sizeof(sources) );
		sources.idlExists = true;
		sources.idl = &(*(root.structures[i]));

		// find proper mapping
		bool mapFound = false;
		for ( auto& itMap:root.structures )
			if ( itMap->declType == Structure::DECLTYPE::MAPPING && itMap->type == root.structures[i]->type && itMap->name == root.structures[i]->name ) // TODO: check whether this condition makes sense
			{
				assert( itMap->idlRepresentation == nullptr );
				if ( mapFound )
				{
					// TODO: report error
					assert( 0 );
				}
				mapFound = true;
				root.structures[i]->mappingRepresentation = &(*itMap);
				itMap->idlRepresentation = &(*(root.structures[i]));
				itMap->mappingRepresentation = &(*itMap); // self
				sources.mappingExists = true;
				sources.mapping = &(*itMap);
			}
		if ( !mapFound )
		{ 
			BackStructure* newMap = new BackStructure;
			newMap->declType = Structure::DECLTYPE::MAPPING;
			root.structures.push_back( unique_ptr<BackStructure>(newMap) );
			root.structures[i]->mappingRepresentation = &(*(root.structures.back()));
			(root.structures.back())->idlRepresentation = &(*(root.structures[i]));
			(root.structures.back())->mappingRepresentation = &(*(root.structures.back())); // self
			sources.mapping = &(*(root.structures.back()));
		}

		// find proper encoding
		bool encodingFound = false;
		for ( auto& itEnc:root.structures )
			if ( itEnc->declType == Structure::DECLTYPE::ENCODING && itEnc->type == root.structures[i]->type && itEnc->name == root.structures[i]->name ) // TODO: check whether this condition makes sense
			{
				assert( itEnc->idlRepresentation == nullptr );
				if ( encodingFound )
				{
					// TODO: report error
					assert( 0 );
				}
				encodingFound = true;
				root.structures[i]->encodingRepresentation = &(*itEnc);
				itEnc->idlRepresentation = &(*(root.structures[i]));
				itEnc->encodingRepresentation = &(*itEnc);
				sources.encodingExists = true;
				sources.encoding = &(*itEnc);
			}
		if ( !encodingFound )
		{ 
			BackStructure* newEnc = new BackStructure;
			newEnc->declType = Structure::DECLTYPE::ENCODING;
			root.structures.push_back( unique_ptr<BackStructure>(newEnc) ); // TODO: think about very defaults
			root.structures[i]->encodingRepresentation = &(*(root.structures.back()));
			root.structures.back()->idlRepresentation = &(*(root.structures[i]));
			(root.structures.back())->encodingRepresentation = &(*(root.structures.back())); // self
			sources.encoding = &(*(root.structures.back()));
		}

		// fill cross-ref ptrs between mapping and encoding structs
		root.structures[i]->mappingRepresentation->encodingRepresentation = root.structures[i]->encodingRepresentation;
		root.structures[i]->encodingRepresentation->mappingRepresentation = root.structures[i]->mappingRepresentation;
		root.structures[i]->idlRepresentation = &(*(root.structures[i])); // self

		// fill defaults
		fillDefaultDataWhereApplicable( sources );
	}

	// 3. go through all structures; process MAPPING structures (note that some of them are already processed)
	for ( size_t i=0; i<root.structures.size(); ++i )
	{
		if ( root.structures[i]->declType != Structure::DECLTYPE::MAPPING )
			continue;
		if( root.structures[i]->idlRepresentation != nullptr || root.structures[i]->mappingRepresentation != nullptr || root.structures[i]->encodingRepresentation != nullptr )
		{
			assert( root.structures[i]->idlRepresentation != nullptr && root.structures[i]->mappingRepresentation != nullptr && root.structures[i]->encodingRepresentation != nullptr );
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
		root.structures[i]->idlRepresentation = &(*(root.structures.back()));
		(root.structures.back())->mappingRepresentation = &(*(root.structures[i]));
		(root.structures.back())->idlRepresentation = &(*(root.structures.back())); // self
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
		root.structures[i]->encodingRepresentation = &(*(root.structures.back()));
		root.structures.back()->mappingRepresentation = &(*(root.structures[i]));
		(root.structures.back())->encodingRepresentation = &(*(root.structures.back())); // self
		sources.encoding = &(*(root.structures.back()));

		// fill cross-ref ptrs between mapping and encoding structs
		root.structures[i]->idlRepresentation->encodingRepresentation = root.structures[i]->encodingRepresentation;
		root.structures[i]->encodingRepresentation->idlRepresentation = root.structures[i]->idlRepresentation;
		root.structures[i]->mappingRepresentation = &(*(root.structures[i])); // self

		// fill defaults
		fillDefaultDataWhereApplicable( sources );
	}

	// 4. go through all structures; process ENCODING structures (note that some of them are already processed)
	for ( size_t i=0; i<root.structures.size(); ++i )
	{
		if ( root.structures[i]->declType != Structure::DECLTYPE::ENCODING )
			continue;
		if( root.structures[i]->idlRepresentation != nullptr || root.structures[i]->mappingRepresentation != nullptr || root.structures[i]->encodingRepresentation != nullptr )
		{
			assert( root.structures[i]->idlRepresentation != nullptr && root.structures[i]->mappingRepresentation != nullptr && root.structures[i]->encodingRepresentation != nullptr );
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
		root.structures[i]->idlRepresentation = &(*(root.structures.back()));
		(root.structures.back())->encodingRepresentation = &(*(root.structures[i]));
		(root.structures.back())->idlRepresentation = &(*(root.structures.back())); // self
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
		root.structures[i]->mappingRepresentation = &(*(root.structures.back()));
		root.structures.back()->encodingRepresentation = &(*(root.structures[i]));
		(root.structures.back())->mappingRepresentation = &(*(root.structures.back())); // self
		sources.mapping = &(*(root.structures.back()));

		// fill cross-ref ptrs between mapping and encoding structs
		root.structures[i]->idlRepresentation->mappingRepresentation = root.structures[i]->mappingRepresentation;
		root.structures[i]->mappingRepresentation->idlRepresentation = root.structures[i]->idlRepresentation;
		root.structures[i]->encodingRepresentation = &(*(root.structures[i])); // self

		// fill defaults
		fillDefaultDataWhereApplicable( sources );
	}
#endif // 0
}

void prevalidateTree( BackRoot& root )
{
#if 0
	assert( root.structuresIdl.size() == root.structuresMapping.size() );
	assert( root.structuresIdl.size() == root.structuresEncoding.size() );
	for ( auto& it:root.structuresIdl )
	{
		assert(  it->declType == Structure::DECLTYPE::IDL );
		// no orphan check
		assert( it->idlRepresentation != nullptr );
		assert( it->mappingRepresentation != nullptr );
		assert( it->encodingRepresentation != nullptr );
		assert( it->mappingRepresentation->encodingRepresentation == it->encodingRepresentation );
		assert( it->encodingRepresentation->mappingRepresentation == it->mappingRepresentation );
		assert( it->mappingRepresentation->idlRepresentation == &(*it) );
		assert( it->encodingRepresentation->idlRepresentation == &(*it) );
		// TODO: any further validation
	}
#endif // 0
}
