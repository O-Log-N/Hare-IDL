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

void memberMappingTypeToKind( DataType& type )
{
	// NOTE: in actual implementation mapping name is expected to be at DataType::mappingName
	// TODO: rework/update/expand implementation when FRONT is updated
	switch ( type.kind )
	{
		case DataType::KIND::NAMED_TYPE:
		{
			if ( type.name == "uint32_t" )
			{
				type.kind = DataType::KIND::INTEGER;
				type.name.clear();
				type.lowLimit.value = 0;
				type.lowLimit.inclusive = true;
				type.highLimit.value = 4294967295.;
				type.highLimit.inclusive = true;
			}
			else if ( type.name == "uint16_t" )
			{
				type.kind = DataType::KIND::INTEGER;
				type.name.clear();
				type.lowLimit.value = 0;
				type.lowLimit.inclusive = true;
				type.highLimit.value = 65535;
				type.highLimit.inclusive = true;
			}
			else if ( type.name == "uint8_t" )
			{
				type.kind = DataType::KIND::INTEGER;
				type.name.clear();
				type.lowLimit.value = 0;
				type.lowLimit.inclusive = true;
				type.highLimit.value = 255;
				type.highLimit.inclusive = true;
			}
			else if ( type.name == "double" )
			{
				type.kind = DataType::KIND::FLOATING_POINT;
				type.name.clear();
				type.floatingSignificandBits = 53;
				type.floatingExponentBits = 11;
			}
			else if ( type.name == "float" )
			{
				type.kind = DataType::KIND::FLOATING_POINT;
				type.name.clear();
				type.floatingSignificandBits = 24;
				type.floatingExponentBits = 8;
			}
			break;
		}
	}
}

void structureMembersMappingTypeToKind( BackStructure& structBase )
{
	size_t sz = structBase.getChildCount();
	assert( structBase.declType == Structure::DECLTYPE::MAPPING );
	for ( size_t i=0; i<sz; ++i )
	{
		BackDataMember* member = dynamic_cast<BackDataMember*>( structBase.getMember( i ) );
		assert( member != nullptr );
		memberMappingTypeToKind( member->type );
	}
}

void traverseStructTreesForStructureMembersMappingTypeToKind( vector<unique_ptr<BackStructure>>& mappingTree )
{
	for ( auto& it:mappingTree )
	{
		structureMembersMappingTypeToKind( *it );
	}
}

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
	traverseStructTreesForStructureMembersMappingTypeToKind( root.structuresMapping );
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
