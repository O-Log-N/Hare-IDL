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

// mb: because of rounding when converting 64 bits integer constants,
// we can not compare for strict lower than MAX limit
// this has inexactitudes on big values, but for now is good enought
static_assert(double((4294967296. * 4294967296.) - 1) == double(UINT64_MAX), "");
static_assert(double(4294967296. * 4294967296.) == double(UINT64_MAX), "");

static_assert(double((2147483648. * 4294967296.) - 1) == double(INT64_MAX), "");
static_assert(double(2147483648. * 4294967296.) == double(INT64_MAX), "");

static_assert(double(-2147483648. * 4294967296.) == double(INT64_MIN), "");


bool isUniquePtr( DataType& dt )
{
	return dt.kind == DataType::KIND::SEQUENCE && (dt.name == "unique_ptr" || dt.name == "std::unique_ptr");
}

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
            if (type.mappingName == "uint64_t")
            {
                type.kind = DataType::KIND::INTEGER;
                type.lowLimit.value = 0;
                type.lowLimit.inclusive = true;
                type.highLimit.value = double(UINT64_MAX);
                type.highLimit.inclusive = true;
            }
            if ( type.mappingName == "uint32_t" )
			{
				type.kind = DataType::KIND::INTEGER;
				type.lowLimit.value = 0;
				type.lowLimit.inclusive = true;
				type.highLimit.value = UINT32_MAX;
				type.highLimit.inclusive = true;
			}
			else if ( type.mappingName == "uint16_t" )
			{
				type.kind = DataType::KIND::INTEGER;
				type.lowLimit.value = 0;
				type.lowLimit.inclusive = true;
				type.highLimit.value = UINT16_MAX;
				type.highLimit.inclusive = true;
			}
			else if ( type.mappingName == "uint8_t" )
			{
				type.kind = DataType::KIND::INTEGER;
				type.lowLimit.value = 0;
				type.lowLimit.inclusive = true;
				type.highLimit.value = UINT8_MAX;
				type.highLimit.inclusive = true;
			}
            else if (type.mappingName == "int64_t")
            {
                type.kind = DataType::KIND::INTEGER;
                type.lowLimit.value = double(INT64_MIN);
                type.lowLimit.inclusive = true;
                type.highLimit.value = double(INT64_MAX);
                type.highLimit.inclusive = true;
            }
            else if (type.mappingName == "int32_t")
            {
                type.kind = DataType::KIND::INTEGER;
                type.lowLimit.value = INT32_MIN;
                type.lowLimit.inclusive = true;
                type.highLimit.value = INT32_MAX;
                type.highLimit.inclusive = true;
            }
            else if (type.mappingName == "int16_t")
            {
                type.kind = DataType::KIND::INTEGER;
                type.lowLimit.value = INT16_MIN;
                type.lowLimit.inclusive = true;
                type.highLimit.value = INT16_MAX;
                type.highLimit.inclusive = true;
            }
            else if (type.mappingName == "int8_t")
            {
                type.kind = DataType::KIND::INTEGER;
                type.lowLimit.value = INT8_MIN;
                type.lowLimit.inclusive = true;
                type.highLimit.value = INT16_MAX;
                type.highLimit.inclusive = true;
            }
            else if (type.mappingName == "bool" || type.mappingName == "_Bool")
            {
                type.kind = DataType::KIND::INTEGER;
                type.lowLimit.value = 0;
                type.lowLimit.inclusive = true;
                type.highLimit.value = 1;
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
			else if ( type.mappingName == "string" || type.mappingName == "std::string")
			{
				type.kind = DataType::KIND::CHARACTER_STRING;
				type.stringMinSize = 0;
				type.stringMaxSize = 65536; // TODO: what is a limit??
			}
			else if ( type.mappingName == "unique_ptr" || type.mappingName == "std::unique_ptr") // NOTE: temporary code!!!
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
				if ( size <= UINT8_MAX )
					return "uint8_t";
				else if ( size <= UINT16_MAX)
					return "uint16_t";
				else if ( size <= UINT32_MAX)
					return "uint32_t";
				else
				{
					assert( 0 ); // TODO: address!
				}
			}
		}
		case DataType::KIND::DISCRIMINATED_UNION:
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
				if ( tmpHigh.value <= UINT8_MAX )
					return "uint8_t";
				else if ( tmpHigh.value <= UINT16_MAX)
					return "uint16_t";
				else if ( tmpHigh.value <= UINT32_MAX)
					return "uint32_t";
				else if ( tmpHigh.value <= UINT64_MAX)
					return "uint64_t";
				else
				{
					assert( 0 ); // TODO: address!
				}
			}
			else // signed
			{
				if ( tmpLow.value >= INT8_MIN && tmpHigh.value <= INT8_MAX)
					return "int8_t";
				else if ( tmpLow.value >= INT16_MIN && tmpHigh.value <= INT16_MAX)
					return "int16_t";
				else if ( tmpLow.value >= INT32_MIN && tmpHigh.value <= INT32_MAX)
					return "int32_t";
				else if ( tmpLow.value >= INT64_MIN && tmpHigh.value <= INT64_MAX)
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
		case DataType::KIND::MAPPING_SPECIFIC:
		{
			if ( type.name == "_Bool" )
				return "bool";
			else
				return type.name;
			assert( 0 ); // TODO: address!
		}
		case DataType::KIND::DICTIONARY:
		{
			return "map";
			assert( 0 ); // TODO: address!
		}
		case DataType::KIND::CHARACTER_STRING:
		{
			return "string";
		}
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
		// TODO: code below is HIGHLY temporary; get rid of it ASAP
		//if ( base.type.kind == DataType::KIND::MAPPING_SPECIFIC &&  base.type.name == "_Bool" )
		//{
		//	base.type.name = "uint8_t";
		//	base.type.mappingName = "uint8_t";
		//	base.type.kind == DataType::KIND::INTEGER;
		//	base.type.lowLimit.inclusive = true;
		//	base.type.lowLimit.value = 0;
		//	base.type.highLimit.inclusive = true;
		//	base.type.highLimit.value = 1;
		//}
		//else
        if ( base.type.kind == DataType::KIND::DICTIONARY )
		{
			base.type.name = "map";
			base.type.mappingName = "map";
		}
		ret->type = base.type; // TODO: actual implementation
		initDataType( base.type, ret->type, baseDeclType, retDeclType );
		ret->whenDiscriminant = base.whenDiscriminant;
	}
	else if ( baseDeclType == Structure::DECLTYPE::IDL )
	{
		assert( retDeclType != Structure::DECLTYPE::IDL );
		ret->name = base.name;
		if ( retDeclType == Structure::DECLTYPE::MAPPING )
		{
			ret->type = base.type;
			ret->whenDiscriminant = base.whenDiscriminant;
			initDataType( base.type, ret->type, baseDeclType, retDeclType );
		}
		else
		{
			ret->type = base.type;
			ret->whenDiscriminant = base.whenDiscriminant;
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

void addCrossReferences( BackStructure* s1, Structure::DECLTYPE type1, BackStructure* s2, Structure::DECLTYPE type2 )
{
	assert( s1 != nullptr );
	assert( s2 != nullptr );
	switch ( type1 )
	{
		case Structure::DECLTYPE::IDL: s2->idlRepresentation = s1; s1->idlRepresentation = s1; break;
		case Structure::DECLTYPE::MAPPING: s2->mappingRepresentation = s1; s1->mappingRepresentation = s1; break;
		case Structure::DECLTYPE::ENCODING: s2->encodingRepresentation = s1; s1->encodingRepresentation = s1; break;
		default: 
		{
			assert( 0 );
			break;
		}
	}
	switch ( type2 )
	{
		case Structure::DECLTYPE::IDL: s1->idlRepresentation = s2; s2->idlRepresentation = s2; break;
		case Structure::DECLTYPE::MAPPING: s1->mappingRepresentation = s2; s2->mappingRepresentation = s2; break;
		case Structure::DECLTYPE::ENCODING: s1->encodingRepresentation = s2; s2->encodingRepresentation = s2; break;
		default: 
		{
			assert( 0 );
			break;
		}
	}
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
		addCrossReferences( &(*it1), type1, ret, type2 );
/*		switch ( type1 )
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
		}*/
	}
}

void inheritanceTreeToDUs( BackRoot& root )
{
	for ( auto& it:root.structuresMapping )
		if ( it->inheritedFrom == "" && it->derived.size() ) // has derived and is base
		{
			BackStructure* base = new BackStructure;
			base->type = it->type;
			base->declType = it->declType;
			base->moveMembersFrom( *it );
			base->name = it->name;
			it->type = Structure::TYPE::DISCRIMINATED_UNION;
			it->discriminant = "__inheritance";
			BackDataMember* discriminant = new BackDataMember;
			discriminant->name = "__inheritance";
			discriminant->type.kind = DataType::KIND::ENUM;
			discriminant->type.name = "__inheritance";
//			discriminant->type.enumValues
//			for( auto& chit:it->
//			base.addChild
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

void expandInheritanceData( BackRoot& root )
{
	for ( auto& it:root.structuresMapping )
		if ( it->inheritedFrom != "" )		
		{
			bool found = false;
			for ( auto& it1:root.structuresMapping )
				if ( it->inheritedFrom == it1->name )
				{
					it->inheritanceBase = &(*it1);
					it1->derived.push_back( &(*it) );
					found = true;

					BackDataMember* parentMember = new BackDataMember;
					parentMember->annotation.insert( make_pair( "PARENT", "yes" ) );
					parentMember->name = "__parent";
					assert( it1->type == Structure::TYPE::STRUCT ); // TODO: consider other options
					parentMember->type.kind = DataType::KIND::NAMED_TYPE;
					parentMember->type.name = it1->name;
					parentMember->type.mappingName = it1->name;
					parentMember->type.encodingName = it1->name;
					it->addChild( parentMember );

					break;
				}
			if ( !found )
				assert( 0 ); // TODO: report an error
		}
}

BackStructure* getTypeDescriptionWhenTypeIsStruct( BackRoot& root, const string& name )
{
	for ( auto& it:root.structuresMapping )
		if ( it->name == name )
			return &(*it);
	return nullptr;
}


void processPolymorphicOwningPointerInUniquePtr( BackRoot& root, BackDataMember& member, DataType& dt )
{
	assert( isUniquePtr( dt ) );
	if ( dt.paramType->kind == DataType::KIND::NAMED_TYPE )
	{
		string nameIdl = "__unique_ptr_";
		nameIdl += dt.paramType->name;
		string nameMapping = "unique_ptr<";
		nameMapping += dt.paramType->name;
		nameMapping += ">";

		bool found = false;
		for ( auto& it:root.structuresMapping )
			if ( it->manuallyAdded && it->name == nameMapping )
			{
				found = true;
				break;
			}
		if ( !found )
		{
			BackStructure* innerstruct = getTypeDescriptionWhenTypeIsStruct( root, dt.paramType->name );
			assert( innerstruct != nullptr ); // TODO: convert to error reporting

			// add an entry to mapping tree
			// DU itself
			BackStructure* duMapping = new BackStructure;
			duMapping->declType = Structure::DECLTYPE::MAPPING;
			duMapping->type = Structure::TYPE::DISCRIMINATED_UNION;
			duMapping->name = nameMapping;
			duMapping->discriminant = "__ptr";
			duMapping->manuallyAdded = true;
			// discriminant and members
			BackDataMember* discriminant = new BackDataMember;
			discriminant->name = "__ptr";
			discriminant->type.name = "__ptr";
			discriminant->type.kind = DataType::KIND::ENUM;
			discriminant->type.enumValues.insert( make_pair( "nullptr", 0 ) );
			duMapping->addChild( discriminant );
			uint32_t ctr = 1;
			// self
			{
				discriminant->type.enumValues.insert( make_pair( dt.paramType->name, ctr++ ) );
				BackDataMember* member = new BackDataMember;
				member->annotation.insert( make_pair( "POLY-POINTER-TYPE", dt.paramType->name ) );
				member->name = dt.paramType->name;
				member->whenDiscriminant.push_back( dt.paramType->name );
				member->type.kind = DataType::KIND::NAMED_TYPE;
				member->type.name = dt.paramType->name;
				duMapping->addChild( member );
			}
			// other
			for ( auto itd: innerstruct->derived )
			{
				discriminant->type.enumValues.insert( make_pair( itd->name, ctr++ ) );
				BackDataMember* member = new BackDataMember;
				member->annotation.insert( make_pair( "POLY-POINTER-TYPE", itd->name ) );
				member->name = itd->name;
				member->whenDiscriminant.push_back( itd->name );
				member->type.kind = DataType::KIND::NAMED_TYPE;
				member->type.name = itd->name;
				duMapping->addChild( member );
			}

			duMapping->annotation.insert( make_pair( "OWNING-PTR", "yes" ) );
			root.structuresMapping.push_back( unique_ptr<BackStructure>( duMapping ) );
			BackStructure* idlStruct = doStructureDataMatchingOrOverridding( *duMapping, Structure::DECLTYPE::MAPPING, nullptr, Structure::DECLTYPE::IDL, TREE_DATA_COMPLETION_OPERATION::OVERRIDE );
			addCrossReferences( duMapping, Structure::DECLTYPE::MAPPING, idlStruct, Structure::DECLTYPE::IDL );
			idlStruct->name = nameIdl;
			root.structuresIdl.push_back( unique_ptr<BackStructure>( idlStruct ) );
			BackStructure* encodingStruct = doStructureDataMatchingOrOverridding( *idlStruct, Structure::DECLTYPE::IDL, nullptr, Structure::DECLTYPE::ENCODING, TREE_DATA_COMPLETION_OPERATION::OVERRIDE );
			addCrossReferences( idlStruct, Structure::DECLTYPE::IDL, encodingStruct, Structure::DECLTYPE::ENCODING );
			addCrossReferences( duMapping, Structure::DECLTYPE::MAPPING, encodingStruct, Structure::DECLTYPE::ENCODING );
			root.structuresEncoding.push_back( unique_ptr<BackStructure>( encodingStruct ) );
		}

		dt.kind = DataType::KIND::NAMED_TYPE;
		dt.name = nameIdl;
		dt.mappingName = nameMapping;
		dt.encodingName = nameIdl;
		dt.paramType.reset( nullptr );

		dt.idlRepresentation->kind = DataType::KIND::NAMED_TYPE;
		dt.idlRepresentation->name = nameIdl;
		dt.idlRepresentation->mappingName = nameMapping;
		dt.idlRepresentation->encodingName = nameIdl;
		dt.idlRepresentation->paramType.reset( nullptr );

		dt.encodingRepresentation->kind = DataType::KIND::NAMED_TYPE;
		dt.encodingRepresentation->name = nameIdl;
		dt.encodingRepresentation->mappingName = nameMapping;
		dt.encodingRepresentation->encodingName = nameIdl;
		dt.encodingRepresentation->paramType.reset( nullptr );
	}
}

void processPolymorphicOwningPointerInDictionary( BackRoot& root, BackDataMember& member, DataType& dt );
void processPolymorphicOwningPointerInSequence( BackRoot& root, BackDataMember& member, DataType& dt )
{
	assert( dt.kind == DataType::KIND::SEQUENCE );
	if ( isUniquePtr( *(dt.paramType) ) )
		processPolymorphicOwningPointerInUniquePtr( root, member, *(dt.paramType) );
	else if ( dt.paramType->kind == DataType::KIND::SEQUENCE )
		processPolymorphicOwningPointerInSequence( root, member, *(dt.paramType) );
	else if ( dt.paramType->kind == DataType::KIND::SEQUENCE )
		processPolymorphicOwningPointerInDictionary( root, member, *(dt.paramType) );
}

void processPolymorphicOwningPointerInDictionary( BackRoot& root, BackDataMember& member, DataType& dt )
{
	assert( dt.kind == DataType::KIND::DICTIONARY );
	if ( isUniquePtr( *(dt.paramType) ) )
		processPolymorphicOwningPointerInUniquePtr( root, member, *(dt.paramType) );
	else if ( dt.paramType->kind == DataType::KIND::SEQUENCE )
		processPolymorphicOwningPointerInSequence( root, member, *(dt.paramType) );
	else if ( dt.paramType->kind == DataType::KIND::SEQUENCE )
		processPolymorphicOwningPointerInDictionary( root, member, *(dt.paramType) );
	if ( isUniquePtr( *(dt.keyType) ) )
		processPolymorphicOwningPointerInUniquePtr( root, member, *(dt.keyType) );
	else if ( dt.keyType->kind == DataType::KIND::SEQUENCE )
		processPolymorphicOwningPointerInSequence( root, member, *(dt.keyType) );
	else if ( dt.keyType->kind == DataType::KIND::SEQUENCE )
		processPolymorphicOwningPointerInDictionary( root, member, *(dt.keyType) );
}

void processPolymorphicOwningPointers( BackRoot& root )
{
//	for ( auto& strit:root.structuresIdl )
	size_t sz = root.structuresMapping.size();
	for ( size_t i=0; i<sz; ++i )
	{
		auto& strit = *(root.structuresMapping.begin() + i );
		BackStructure* s = &(*strit);
		size_t cnt = strit->getChildCount();
		for ( size_t i=0; i<cnt; ++i )
		{
			BackDataMember* member = dynamic_cast<BackDataMember*>(s->getMember( i ));
			assert( member ); // TODO: currently we do not expect anything else here; revise as necessary
			// We're looking here for the following cases:
			// - unique_ptr
			// - SEQUENCE< ... unique_ptr<X> ... >
			// - DICTIONARY< ... unique_ptr<X> ... >
			// When found, we check whether there are types inherited from X
			// If yes, then a respective DU is constructed (unless already added), and X is replaced by (or is annotated to use) that DU
			if ( isUniquePtr( member->type ) )
				processPolymorphicOwningPointerInUniquePtr( root, *member, member->type );
			else if ( member->type.kind == DataType::KIND::SEQUENCE )
				processPolymorphicOwningPointerInSequence( root, *member, member->type );
			else if ( member->type.kind == DataType::KIND::DICTIONARY )
				processPolymorphicOwningPointerInDictionary( root, *member, member->type );
		}
	}
}

/*
void inheritanceAddDiscriminatorValues( BackStructure& s, vector<map<string, uint32_t>*>& derivedObjDiscriminatorValues, string base, int& value )
{
	base = base + s.name;
	for ( auto& it:derivedObjDiscriminatorValues )
		it->insert( make_pair( base, value ) );
	++value;
	derivedObjDiscriminatorValues.push_back( &(s.derivedObjDiscriminatorValues) );
	for ( auto& it: s.derived )
		inheritanceAddDiscriminatorValues( *it, derivedObjDiscriminatorValues, base, value );
	derivedObjDiscriminatorValues.pop_back();
}

void inheritanceAddDiscriminatorValues( BackRoot& root )
{
	for ( auto& it:root.structuresMapping )
		if ( it->inheritedFrom == "" && it->derived.size() ) // has derived and is base
		{
			vector<map<string, uint32_t>*> duValues;
			int value = 0;
			inheritanceAddDiscriminatorValues( *it, duValues, "", value );
//			fmt::print( "base struct {}: {} children in depth\n", it->name, value );
		}
}
*/

TREE_DATA_COMPLETION_SCENARIO guessTreeScenario(const BackRoot& root)
{
    bool hasIdl = !root.structuresIdl.empty();
    bool hasMapping = !root.structuresMapping.empty();
    bool hasEncoding = !root.structuresEncoding.empty();

    if (hasIdl && hasMapping && hasEncoding) {
        assert(false);
        //        return TREE_DATA_COMPLETION_SCENARIO::IDL_MAP_ENC;
    }
    else if (hasIdl && hasMapping) {
        assert(false);
//        return TREE_DATA_COMPLETION_SCENARIO::IDL_MAP;
    }
    else if (hasIdl && hasEncoding) {
        assert(false);
//        return TREE_DATA_COMPLETION_SCENARIO::IDL_ENC;
    }
    else if (hasIdl) {
        return TREE_DATA_COMPLETION_SCENARIO::IDL_ONLY;
    }
    else if (hasMapping && hasEncoding) {
        assert(false);
//        return TREE_DATA_COMPLETION_SCENARIO::MAJOR_MAP_ENC; //TODO also may be MAJOR_ENC_MAP
    }
    else if (hasMapping) {
        return TREE_DATA_COMPLETION_SCENARIO::MAP_ONLY;
    }
    else if (hasEncoding) {
        assert(false);
//        return TREE_DATA_COMPLETION_SCENARIO::ENC_ONLY;
    } 
    else {
        assert(false);
//        return TREE_DATA_COMPLETION_SCENARIO::IDL_MAP_ENC; //TODO error?
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
			expandInheritanceData( root );
//			inheritanceTreeToDUs( root );
			traverseStructTreesForDataMatchingOrOverridding( root.structuresMapping, Structure::DECLTYPE::MAPPING, root.structuresIdl, Structure::DECLTYPE::IDL, TREE_DATA_COMPLETION_OPERATION::OVERRIDE );
			traverseStructTreesForDataMatchingOrOverridding( root.structuresIdl, Structure::DECLTYPE::IDL, root.structuresEncoding, Structure::DECLTYPE::ENCODING, TREE_DATA_COMPLETION_OPERATION::OVERRIDE );
			processPolymorphicOwningPointers( root );
			break;
		}
		case TREE_DATA_COMPLETION_SCENARIO::ENC_ONLY: break;
		case TREE_DATA_COMPLETION_SCENARIO::IDL_MAP: break;
		case TREE_DATA_COMPLETION_SCENARIO::IDL_ENC: break;
		case TREE_DATA_COMPLETION_SCENARIO::MAJOR_MAP_ENC: break;
		case TREE_DATA_COMPLETION_SCENARIO::MAJOR_ENC_MAP: break;
	}
}
