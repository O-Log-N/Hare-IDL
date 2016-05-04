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
	if ( type.mappingName.size() == 0 ) // TODO: remove as soon as front puts parsed data at meppingName
	{
		type.mappingName = type.name;
		type.name.clear();
	}
	if ( type.name.size() == 0 ) // TODO: could it be non-empty in a real case (see remark above)?
	{
		type.name = type.mappingName;
	}
	switch ( type.kind )
	{
		case DataType::KIND::SEQUENCE:
		{
			 // NOTE: temporary code!!!
/*			if ( type.mappingName == "unique_ptr" ) // NOTE: temporary code!!!
			{
				type.kind = DataType::KIND::DISCRIMINATED_UNION;
			}*/
			break;
		}
		case DataType::KIND::NAMED_TYPE:
		case DataType::KIND::MAPPING_SPECIFIC:
		{
			if ( type.mappingName == "uint32_t" )
			{
				type.kind = DataType::KIND::INTEGER;
				type.lowLimit.value = 0;
				type.lowLimit.inclusive = true;
				type.highLimit.value = 4294967295.;
				type.highLimit.inclusive = true;
			}
			else if ( type.mappingName == "uint16_t" )
			{
				type.kind = DataType::KIND::INTEGER;
				type.lowLimit.value = 0;
				type.lowLimit.inclusive = true;
				type.highLimit.value = 65535;
				type.highLimit.inclusive = true;
			}
			else if ( type.mappingName == "uint8_t" )
			{
				type.kind = DataType::KIND::INTEGER;
				type.lowLimit.value = 0;
				type.lowLimit.inclusive = true;
				type.highLimit.value = 255;
				type.highLimit.inclusive = true;
			}
			else if ( type.mappingName == "double" )
			{
				type.kind = DataType::KIND::FLOATING_POINT;
				type.floatingSignificandBits = 53;
				type.floatingExponentBits = 11;
			}
			else if ( type.mappingName == "float" )
			{
				type.kind = DataType::KIND::FLOATING_POINT;
				type.floatingSignificandBits = 24;
				type.floatingExponentBits = 8;
			}
			else if ( type.mappingName == "string" )
			{
				type.kind = DataType::KIND::CHARACTER_STRING;
				type.stringMinSize = 0;
				type.stringMaxSize = 65536; // TODO: what is a limit??
			}
			else if ( type.mappingName == "unique_ptr" ) // NOTE: temporary code!!!
			{
//				type.kind = DataType::KIND::DISCRIMINATED_UNION;
				type.kind = DataType::KIND::SEQUENCE;
			}
			break;
		}
	}
	// go in depth
	if ( type.keyType != nullptr )
		memberMappingTypeToKind( *(type.keyType) );
	if ( type.paramType != nullptr )
		memberMappingTypeToKind( *(type.paramType) );
}

string getTypeFromIdl( DataType& type, Structure::DECLTYPE declType )
{
	switch ( type.kind )
	{
		case DataType::KIND::ENUM:
		{
			if ( declType == Structure::DECLTYPE::MAPPING )
				return type.name;
			else
			{
				assert( declType == Structure::DECLTYPE::ENCODING );
				assert( type.enumValues.size() != 0 ); // TODO: what?
				uint32_t size = type.enumValues.size();
				if ( size < 256 )
					return "uint8_t";
				else if ( size < 65536 )
					return "uint16_t";
				else if ( size < 4294967296. )
					return "uint32_t";
				else if ( size < 4294967296. * 4294967296. ) // TODO: unsafe! - fix
					return "uint64_t";
				else
				{
					assert( 0 ); // TODO: address!
				}
			}
		}
		case DataType::KIND::NAMED_TYPE:
		{
			return type.name;
		}
		case DataType::KIND::INTEGER:
		{
			Limit tmpLow, tmpHigh; // this is just to not think about type of Limit::value
			tmpLow.value = type.lowLimit.inclusive ? type.lowLimit.value : type.lowLimit.value + 1;
			tmpHigh.value = type.highLimit.inclusive ? type.highLimit.value : type.highLimit.value - 1 ;
			if ( tmpLow.value >= 0 ) // signed
			{
				if ( tmpHigh.value < 256 )
					return "uint8_t";
				else if ( tmpHigh.value < 65536 )
					return "uint16_t";
				else if ( tmpHigh.value < 4294967296. )
					return "uint32_t";
				else if ( tmpHigh.value < 4294967296. * 4294967296. ) // TODO: unsafe! - fix
					return "uint64_t";
				else
				{
					assert( 0 ); // TODO: address!
				}
			}
			else // signed
			{
				if ( tmpLow.value >= -128 && tmpHigh.value < 128 )
					return "int8_t";
				else if ( tmpLow.value >= -32768 && tmpHigh.value < 32768 )
					return "int16_t";
				else if ( tmpLow.value >= -2147483648. && tmpHigh.value < 2147483648. )
					return "int32_t";
				else if ( tmpLow.value >= 4294967296. * (-2147483648.) && tmpHigh.value < 4294967296. * 2147483648. ) // TODO: unsafe! - fix
					return "int64_t";
				else
				{
					assert( 0 ); // TODO: address!
				}
			}
		}
		case DataType::KIND::FLOATING_POINT:
		{
			if ( type.floatingExponentBits <= 8 && type.floatingSignificandBits <= 24 )
				return "float";
			else if ( type.floatingExponentBits <= 11 && type.floatingSignificandBits <= 53 )
				return "double";
			else
			{
				assert( 0 ); // TODO: address!
			}
		}
		case DataType::KIND::FIXED_POINT:
		{
			return "double"; // TODO: something smarter
		}
		case DataType::KIND::SEQUENCE:
		{
			return "vector";
		}
/*		case DataType::KIND::DISCRIMINATED_UNION:
		{
			// NOTE: temporary code!!!
			return type.name;
		}*/
		default:
		{
			assert( 0 ); // TODO: address!
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

void initDataType( DataType& srcType, DataType& targetType, Structure::DECLTYPE baseDeclType, Structure::DECLTYPE retDeclType )
{
	if ( baseDeclType == Structure::DECLTYPE::MAPPING )
	{
		// NOTE: mapping could be a base for only IDL
		assert( retDeclType == Structure::DECLTYPE::IDL );
		memberMappingTypeToKind( targetType );
		// TODO: other steps [...]
		srcType.idlRepresentation = &targetType;
		targetType.mappingRepresentation = &srcType;
		targetType.idlRepresentation = &targetType; // self
		srcType.mappingRepresentation = &srcType; // self
		if ( srcType.encodingRepresentation != nullptr )
		{
			assert( srcType.encodingRepresentation->encodingRepresentation = srcType.encodingRepresentation );
			srcType.encodingRepresentation->idlRepresentation = &targetType;
			targetType.encodingRepresentation = srcType.encodingRepresentation;
		}
	}
	else if ( baseDeclType == Structure::DECLTYPE::IDL )
	{
		assert( retDeclType != Structure::DECLTYPE::IDL );
		if ( retDeclType == Structure::DECLTYPE::MAPPING )
		{
			targetType.mappingName = getTypeFromIdl( srcType, Structure::DECLTYPE::MAPPING );
			srcType.mappingRepresentation = &targetType;
			targetType.idlRepresentation = &srcType;
			targetType.mappingRepresentation = &targetType; // self
			if ( srcType.encodingRepresentation != nullptr )
			{
				assert( srcType.encodingRepresentation->encodingRepresentation = srcType.encodingRepresentation );
				srcType.encodingRepresentation->mappingRepresentation = &targetType;
				targetType.encodingRepresentation = srcType.encodingRepresentation;
			}
		}
		else
		{
			assert( retDeclType == Structure::DECLTYPE::ENCODING );
			targetType.encodingName = getTypeFromIdl( srcType, Structure::DECLTYPE::ENCODING );
			switch ( srcType.kind )
			{
				case DataType::KIND::ENUM:
				{
					assert( srcType.enumValues.size() != 0 ); // TODO: what?
					// TODO: think about a proper way of getting independency on value type of enumValues
					uint32_t val = 0;
					for ( auto& it:targetType.enumValues )
						it.second = val++;
				}
			}
			// set cross-ref ptrs
			targetType.idlRepresentation = &srcType;
			targetType.encodingRepresentation = &targetType; // self
			if ( srcType.mappingRepresentation != nullptr )
			{
				assert( srcType.mappingRepresentation->mappingRepresentation = srcType.mappingRepresentation );
				srcType.mappingRepresentation->encodingRepresentation = &targetType;
				targetType.mappingRepresentation = srcType.mappingRepresentation;
			}
		}
		srcType.idlRepresentation = &srcType; // self
	}
	else
	{
		assert( retDeclType == Structure::DECLTYPE::ENCODING );
		// TODO: implement
		assert( 0 ); // until implemented
	}

	// go in depth
	if ( srcType.keyType != nullptr )
		initDataType( *(srcType.keyType), *(targetType.keyType), baseDeclType, retDeclType );
	if ( srcType.paramType != nullptr )
		initDataType( *(srcType.paramType), *(targetType.paramType), baseDeclType, retDeclType );
	srcType.encodingRepresentation = &targetType;
}

BackDataMember* createMember( BackDataMember& base, Structure::DECLTYPE baseDeclType, Structure::DECLTYPE retDeclType )
{
	BackDataMember* ret = new BackDataMember;
	// experimental logic
	// TODO: actual implementation
	if ( baseDeclType == Structure::DECLTYPE::MAPPING )
	{
		assert( retDeclType == Structure::DECLTYPE::IDL );
		ret->name = base.name;
		ret->type = base.type; // TODO: actual implementation
		initDataType( base.type, ret->type, baseDeclType, retDeclType );
	}
	else if ( baseDeclType == Structure::DECLTYPE::IDL )
	{
		assert( retDeclType != Structure::DECLTYPE::IDL );
		ret->name = base.name;
		if ( retDeclType == Structure::DECLTYPE::MAPPING )
		{
			ret->type = base.type;
			initDataType( base.type, ret->type, baseDeclType, retDeclType );
		}
		else
		{
			ret->type = base.type;
			initDataType( base.type, ret->type, baseDeclType, retDeclType );
		}
	}
	else
	{
		assert( baseDeclType == Structure::DECLTYPE::ENCODING );
		assert( 0 ); // until implemented
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
		structOverr->type = structBase.type;
		structOverr->discriminant = structBase.discriminant;
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
		case TREE_DATA_COMPLETION_SCENARIO::IDL_ONLY:
		{
			traverseStructTreesForDataMatchingOrOverridding( root.structuresIdl, Structure::DECLTYPE::IDL, root.structuresMapping, Structure::DECLTYPE::MAPPING, TREE_DATA_COMPLETION_OPERATION::OVERRIDE );
			traverseStructTreesForDataMatchingOrOverridding( root.structuresIdl, Structure::DECLTYPE::IDL, root.structuresEncoding, Structure::DECLTYPE::ENCODING, TREE_DATA_COMPLETION_OPERATION::OVERRIDE );
			break;
		}
		case TREE_DATA_COMPLETION_SCENARIO::MAP_ONLY:
		{
			traverseStructTreesForDataMatchingOrOverridding( root.structuresMapping, Structure::DECLTYPE::MAPPING, root.structuresIdl, Structure::DECLTYPE::IDL, TREE_DATA_COMPLETION_OPERATION::OVERRIDE );
			traverseStructTreesForDataMatchingOrOverridding( root.structuresIdl, Structure::DECLTYPE::IDL, root.structuresEncoding, Structure::DECLTYPE::ENCODING, TREE_DATA_COMPLETION_OPERATION::OVERRIDE );
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
