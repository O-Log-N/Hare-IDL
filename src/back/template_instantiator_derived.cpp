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

#include "template_instantiator_derived.h"

void RootTemplateInstantiatorFactory::execBuiltinFunction( Stack& stack, PredefindedFunction fn )
{
	switch ( fn.id )
	{
		case PREDEFINED_FUNCTION::SERIALIZABLE_OBJECTS:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::ANY_LIST;
			for ( auto& it:root->structuresIdl )
			{
				StackElement el;
				el.argtype = ARGTYPE::OBJPTR;
				StructTemplateInstantiatorFactory* structti = new StructTemplateInstantiatorFactory( *it, templateSpace, outstr );
				el.singleObject.reset( structti );
				elem.anyList.push_back( std::move( el ) );
			}
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::PUBLISHABLE_STRUCTS:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::ANY_LIST;
			for ( auto& it:root->structuresIdl )
			{
				if ( it->type == Structure::TYPE::STRUCT )
				{
					StackElement el;
					el.argtype = ARGTYPE::OBJPTR;
					StructTemplateInstantiatorFactory* structti = new StructTemplateInstantiatorFactory( *it, templateSpace, outstr );
					el.singleObject.reset( structti );
					elem.anyList.push_back( std::move( el ) );
				}
			}
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::PUBLISHABLE_DISCRIMINATED_UNIONS:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::ANY_LIST;
			for ( auto& it:root->structuresIdl )
			{
				if ( it->type == Structure::TYPE::DISCRIMINATED_UNION )
				{
					StackElement el;
					el.argtype = ARGTYPE::OBJPTR;
					DiscriminatedUnionTemplateInstantiatorFactory* structti = new DiscriminatedUnionTemplateInstantiatorFactory( *it, templateSpace, outstr );
					el.singleObject.reset( structti );
					elem.anyList.push_back( std::move( el ) );
				}
			}
			stack.push_back( std::move(elem) );
			break;
		}
		default:
		{
			TemplateInstantiatorFactory::execBuiltinFunction( stack, fn );
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////


void StructTemplateInstantiatorFactory::execBuiltinFunction( Stack& stack, PredefindedFunction fn )
{
	switch ( fn.id )
	{
		case PREDEFINED_FUNCTION::STRUCT_NAME:
		{
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = structure->name;
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::MEMBERS:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::ANY_LIST;
			size_t memberCnt = structure->getChildCount();
			for ( size_t j=0; j<memberCnt; j++ )
			{
				const BackDataMember* member = dynamic_cast<const BackDataMember*>( structure->getConstMember( j ) );
				if ( member != NULL )
				{
					StackElement el;
					el.argtype = ARGTYPE::OBJPTR;
					StructMemberTemplateInstantiatorFactory* smti = new StructMemberTemplateInstantiatorFactory( *member, templateSpace, outstr );
					el.singleObject.reset( smti );
					elem.anyList.push_back( std::move( el ) );
				}
				else
				{
					// TODO: this case requires additional analysis
					assert( 0 );
				}
			}
			stack.push_back( std::move(elem) );
			break;
		}
		default:
		{
			TemplateInstantiatorFactory::execBuiltinFunction( stack, fn );
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////


void StructMemberTemplateInstantiatorFactory::execBuiltinFunction( Stack& stack, PredefindedFunction fn )
{
	switch ( fn.id )
	{
		case PREDEFINED_FUNCTION::MAPPING_MEMBER_NAME:
		{
			assert( member->mappingRepresentation != nullptr );
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = dynamic_cast<BackDataMember*>(member->mappingRepresentation)->name;
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::ENCODING_MEMBER_NAME:
		{
			assert( member->encodingRepresentation != nullptr );
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = dynamic_cast<BackDataMember*>(member->encodingRepresentation)->name;
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::MAPPING_MEMBER_TYPE:
		{
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = dynamic_cast<BackDataMember*>(member->mappingRepresentation)->type.name;
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::ENCODING_MEMBER_TYPE:
		{
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = dynamic_cast<BackDataMember*>(member->encodingRepresentation)->type.name;
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}

		case PREDEFINED_FUNCTION::MEMBER_TYPE:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::OBJPTR;
			DataType* memberType = new DataType( member->type );
			if ( memberType != NULL )
			{
				MemberTypeTemplateInstantiatorFactory* mtti = new MemberTypeTemplateInstantiatorFactory( *memberType, templateSpace, outstr );
				elem.singleObject = unique_ptr<TemplateInstantiatorFactory>(mtti);
			}
			else
			{
				// TODO: this case requires additional analysis
				assert( 0 );
			}
			stack.push_back( std::move(elem) );
			break;
		}
		default:
		{
			TemplateInstantiatorFactory::execBuiltinFunction( stack, fn );
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////


void MemberTypeTemplateInstantiatorFactory::execBuiltinFunction( Stack& stack, PredefindedFunction fn )
{
	switch ( fn.id )
	{
		case PREDEFINED_FUNCTION::MAPPING_MEMBER_TYPE:
		{
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = dataType->mappingRepresentation->mappingName;
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::ENCODING_MEMBER_TYPE:
		{
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = dataType->encodingRepresentation->encodingName;
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}

		case PREDEFINED_FUNCTION::COLLECTION_TYPE:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::OBJPTR;
//			assert( dataType->kind == DataType::KIND::SEQUENCE || dataType->kind == DataType::KIND::DICTIONARY );
			assert( dataType->kind == DataType::KIND::SEQUENCE || dataType->kind == DataType::KIND::DICTIONARY || dataType->kind == DataType::KIND::DISCRIMINATED_UNION ); // TEMPORARY; TODO: go back as soon as proper processing of DISCRIMINATED_UNION is implemented
			MemberTypeTemplateInstantiatorFactory* mtti = new MemberTypeTemplateInstantiatorFactory( *(dataType->paramType), templateSpace, outstr );
			elem.singleObject = unique_ptr<TemplateInstantiatorFactory>(mtti);
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::COLLECTION_TYPE2:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::OBJPTR;
			assert( dataType->kind == DataType::KIND::DICTIONARY );
			MemberTypeTemplateInstantiatorFactory* mtti = new MemberTypeTemplateInstantiatorFactory( *(dataType->keyType), templateSpace, outstr );
			elem.singleObject = unique_ptr<TemplateInstantiatorFactory>(mtti);
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::ENUM_VALUES:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::ANY_LIST;
			for ( auto it:dataType->enumValues )
			{
				string enumValName = it.first;
				assert( dataType->idlRepresentation != nullptr );
				assert( dataType->mappingRepresentation != nullptr );
				assert( dataType->encodingRepresentation != nullptr );
				auto& idlEnumVal = dataType->idlRepresentation->enumValues.find( enumValName );
				assert( idlEnumVal != dataType->idlRepresentation->enumValues.end() );
				auto& mappingEnumVal = dataType->mappingRepresentation->enumValues.find( enumValName );
				assert( mappingEnumVal != dataType->mappingRepresentation->enumValues.end() );
				auto& encodingEnumVal = dataType->encodingRepresentation->enumValues.find( enumValName );
				assert( encodingEnumVal != dataType->encodingRepresentation->enumValues.end() );
				StackElement el;
				el.argtype = ARGTYPE::OBJPTR;
				EnumValueTemplateInstantiatorFactory* evti = new EnumValueTemplateInstantiatorFactory( enumValName, idlEnumVal->second, mappingEnumVal->second, encodingEnumVal->second, templateSpace, outstr );
				el.singleObject.reset( evti );
				elem.anyList.push_back( std::move( el ) );
			}
			stack.push_back( std::move(elem) );
			break;
		}
		// type-related
		// NOTE: this list is subject to change (see issue #52, for instance)
		// TODO: update as necessary
		case PREDEFINED_FUNCTION::IS_STRUCTURE:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::NAMED_TYPE;
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_ENUM:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::ENUM;
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_SEQUENCE:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::SEQUENCE;
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_DICTIONARY:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::DICTIONARY;
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_INTEGER:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::INTEGER;
//			if ( elem.boolValue )
//				assert( dataType->name.size() == 0 );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_FLOATING_POINT:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::FLOATING_POINT;
//			if ( elem.boolValue )
//				assert( dataType->name.size() == 0 );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_FIXED_POINT:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::FIXED_POINT;
//			if ( elem.boolValue )
//				assert( dataType->name.size() == 0 );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_UNSIGNED_INTEGER:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			assert( dataType->kind == DataType::KIND::INTEGER ); // TODO: think about proper error reporting
			elem.boolValue = dataType->lowLimit.inclusive ? dataType->lowLimit.value >= 0 : dataType->lowLimit.value >= -1; // TODO: lowLimit.value is currently double; make sure comparison always work as intended
			assert( dataType->lowLimit.value <= dataType->highLimit.value );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_UNSIGNED_INTEGER_FITTING_UINT:
		{
			assert( dataType->kind == DataType::KIND::INTEGER ); // TODO: think about proper error reporting
			bool unsignedInt = dataType->lowLimit.inclusive ? dataType->lowLimit.value >= 0 : dataType->lowLimit.value >= -1; // TODO: lowLimit.value is currently double; make sure comparison always work as intended
			assert( unsignedInt ); // TODO: think about proper error reporting
			assert( stack.size() );
			auto& arg = stack.back();
			assert( arg.argtype == ARGTYPE::NUMBER );
			assert( arg.numberValue > 0 );
			assert( arg.numberValue <= 64 ); // there is a practical limit here TODO: think about a limit or about addressing other cases
			assert( arg.numberValue > 0 ); // there is a practical limit here TODO: think about a limit or about addressing other cases
			int binCnt = arg.numberValue;
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = binCnt < 64 ? dataType->highLimit.value < ( 1 << binCnt ) : true; // TODO: proper check
			// pop args, push result
			stack.pop_back();
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_SIGNED_INTEGER_FITTING_INT:
		{
			assert( dataType->kind == DataType::KIND::INTEGER ); // TODO: think about proper error reporting
			assert( stack.size() );
			auto& arg = stack.back();
			assert( arg.argtype == ARGTYPE::NUMBER );
			assert( arg.numberValue <= 64 ); // there is a practical limit here TODO: think about a limit or about addressing other cases
			assert( arg.numberValue > 0 ); // there is a practical limit here TODO: think about a limit or about addressing other cases
			int bitCnt = arg.numberValue;

			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			bool OK = bitCnt < 64 ? dataType->highLimit.value <= ( 1 << (bitCnt-1) ) : true;
			elem.boolValue = OK && ( bitCnt < 64 ? dataType->highLimit.value <= ( 1 << (bitCnt-1) ) : true );
			// pop args, push result
			stack.pop_back();
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_FLOATING_POINT_FITTING_FLOAT:
		{
			assert( dataType->kind == DataType::KIND::FLOATING_POINT ); // TODO: think about proper error reporting
			assert( stack.size() > 1 ); // we have two args
			auto significandBits = stack.begin() + stack.size() - 2;
			auto exponentBits = stack.begin() + stack.size() - 1;
			assert( significandBits->argtype == ARGTYPE::NUMBER );
			assert( significandBits->numberValue <= 64 ); // there is a practical limit here TODO: think about a limit or about addressing other cases
			assert( significandBits->numberValue > 0 ); // there is a practical limit here TODO: think about a limit or about addressing other cases
			assert( exponentBits->argtype == ARGTYPE::NUMBER );
			assert( exponentBits->numberValue < 64 ); // there is a practical limit here TODO: think about a limit or about addressing other cases
			assert( exponentBits->numberValue >= 0 ); // there is a practical limit here TODO: think about a limit or about addressing other cases

			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->floatingSignificandBits <= significandBits->numberValue && dataType->floatingExponentBits <= exponentBits->numberValue;
			// pop args, push result
			stack.pop_back();
			stack.pop_back();
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_CHARACTER_STRING:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::CHARACTER_STRING;
			if ( elem.boolValue )
				assert( dataType->name.size() == 0 );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_CHARACTER:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::CHARACTER;
//			if ( elem.boolValue )
//				assert( dataType->name.size() == 0 );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_BIT_STRING:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::BIT_STRING;
//			if ( elem.boolValue )
//				assert( dataType->name.size() == 0 );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_DISCRIMINATED_UNION:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::DISCRIMINATED_UNION;
//			if ( elem.boolValue )
//				assert( dataType->name.size() == 0 );
			stack.push_back( std::move(elem) );
			break;
		}
		default:
		{
			TemplateInstantiatorFactory::execBuiltinFunction( stack, fn );
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////


void EnumValueTemplateInstantiatorFactory::execBuiltinFunction( Stack& stack, PredefindedFunction fn )
{
	switch ( fn.id )
	{
		case PREDEFINED_FUNCTION::ENUM_VALUE_NAME:
		{
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = name;
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::MAPPING_ENUM_VALUE_VALUE:
		{
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = fmt::format( "{}", mappingValue );
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::ENCODING_ENUM_VALUE_VALUE:
		{
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = fmt::format( "{}", encodingValue );
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}
		default:
		{
			TemplateInstantiatorFactory::execBuiltinFunction( stack, fn );
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////


void DiscriminatedUnionTemplateInstantiatorFactory::execBuiltinFunction( Stack& stack, PredefindedFunction fn )
{
	switch ( fn.id )
	{
		case PREDEFINED_FUNCTION::STRUCT_NAME:
		{
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = structure->name;
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::MAPPING_DISCRIMINATOR_NAME:
		{
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = structure->discriminant;
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}

		case PREDEFINED_FUNCTION::MEMBERS:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::ANY_LIST;
			size_t memberCnt = structure->getChildCount();
			for ( size_t j=0; j<memberCnt; j++ )
			{
				StackElement el;
				el.argtype = ARGTYPE::OBJPTR;
				const BackDataMember* member = dynamic_cast<const BackDataMember*>( structure->getConstMember( j ) );
				if ( member != NULL )
				{
					StructMemberTemplateInstantiatorFactory* smti = new StructMemberTemplateInstantiatorFactory( *member, templateSpace, outstr );
					el.singleObject.reset( smti );
					elem.anyList.push_back( std::move( el ) );
				}
				else
				{
					// TODO: this case requires additional analysis
					assert( 0 );
				}
			}
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::DISCRIMINATED_UNION_OPTIONS:
		{
			size_t memberCnt = structure->getChildCount();
			size_t j;
			const BackDataMember* enumMember = nullptr;
			for ( j=0; j<memberCnt; j++ )
			{
				enumMember = dynamic_cast<const BackDataMember*>( structure->getConstMember( j ) );
				if ( enumMember != NULL && enumMember->type.kind == DataType::KIND::ENUM && enumMember->name == structure->discriminant )
					break;
			}
			assert( enumMember != nullptr ); // TODO: report error
			assert( enumMember->idlRepresentation != nullptr );
			assert( enumMember->mappingRepresentation != nullptr );
			assert( enumMember->encodingRepresentation != nullptr );

			StackElement elem;
			elem.argtype = ARGTYPE::ANY_LIST;

			for ( auto itv:enumMember->type.enumValues )
			{
				// we go through discriminating enum values and we add objects if there are members allowed by a respective value
				vector<const BackDataMember*> usedMembers;
				for ( j=0; j<memberCnt; j++ )
				{
					const BackDataMember* member = dynamic_cast<const BackDataMember*>( structure->getConstMember( j ) );
					if ( member != NULL && member != enumMember )
					{
						for ( auto& itIfVal:member->whenDiscriminant )
							if ( itIfVal == itv.first )
							{
								usedMembers.push_back( member );
								break;
							}
					}
				}
				if ( usedMembers.size() )
				{
					StackElement el;
					el.argtype = ARGTYPE::OBJPTR;
					string enumValName = itv.first;
					auto& idlEnumVal = enumMember->type.idlRepresentation->enumValues.find( enumValName );
					assert( idlEnumVal != enumMember->type.idlRepresentation->enumValues.end() );
					auto& mappingEnumVal = enumMember->type.mappingRepresentation->enumValues.find( enumValName );
					assert( mappingEnumVal != enumMember->type.mappingRepresentation->enumValues.end() );
					auto& encodingEnumVal = enumMember->type.encodingRepresentation->enumValues.find( enumValName );
					assert( encodingEnumVal != enumMember->type.encodingRepresentation->enumValues.end() );
					DiscriminatedUnionOptionTemplateInstantiatorFactory* duoti = new DiscriminatedUnionOptionTemplateInstantiatorFactory( *enumMember, usedMembers, enumValName, idlEnumVal->second, mappingEnumVal->second, encodingEnumVal->second, templateSpace, outstr );
					el.singleObject.reset( duoti );
					elem.anyList.push_back( std::move( el ) );
				}
			}
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::DISCRIMINATED_UNION_DISCRIMINATOR:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::OBJPTR;
			size_t memberCnt = structure->getChildCount();
			size_t j;
			const BackDataMember* enumMember = nullptr;
			for ( j=0; j<memberCnt; j++ )
			{
				const BackDataMember* enumMember1 = dynamic_cast<const BackDataMember*>( structure->getConstMember( j ) );
				if ( enumMember1 != NULL && enumMember1->type.kind == DataType::KIND::ENUM && enumMember1->name == structure->discriminant )
				{
					enumMember = enumMember1;
					break;
				}
			}
			assert( enumMember != nullptr ); // TODO: report error

			StructMemberTemplateInstantiatorFactory* smti = new StructMemberTemplateInstantiatorFactory( *enumMember, templateSpace, outstr );
			elem.singleObject = unique_ptr<TemplateInstantiatorFactory>(smti);
			stack.push_back( std::move(elem) );
			break;
		}
		default:
		{
			TemplateInstantiatorFactory::execBuiltinFunction( stack, fn );
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////


void DiscriminatedUnionOptionTemplateInstantiatorFactory::execBuiltinFunction( Stack& stack, PredefindedFunction fn )
{
	switch ( fn.id )
	{
		case PREDEFINED_FUNCTION::ENCODING_DISCRIMINATED_UNION_OPTION_NAME:
		{
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = fmt::format( "{}", enumValueName ); // TODO: revise!!!
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::MAPPING_DISCRIMINATED_UNION_OPTION_VALUE:
		{
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = fmt::format( "{}", mappingValue ); // TODO: revise!!!
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::ENCODING_DISCRIMINATED_UNION_OPTION_VALUE:
		{
			LinePart2 lp;
			lp.isVerbatim = true;
			lp.verbatim = fmt::format( "{}", encodingValue );
			StackElement elem;
			elem.argtype = ARGTYPE::STRING;
			elem.lineParts.push_back( lp );
			stack.push_back( std::move(elem) );
			break;
		}

		case PREDEFINED_FUNCTION::MEMBERS:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::ANY_LIST;
			for ( auto& it:usedMembers )
			{
				assert( it != NULL );
				StackElement el;
				el.argtype = ARGTYPE::OBJPTR;
				StructMemberTemplateInstantiatorFactory* smti = new StructMemberTemplateInstantiatorFactory( *it, templateSpace, outstr );
				el.singleObject.reset( smti );
				elem.anyList.push_back( std::move( el ) );
			}
			stack.push_back( std::move(elem) );
			break;
		}
		default:
		{
			TemplateInstantiatorFactory::execBuiltinFunction( stack, fn );
			break;
		}
	}
}
