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


string RootTemplateInstantiator::placeholder( Placeholder ph )
{
	switch( ph.id )
	{
		default:
		{
			return TemplateInstantiator::placeholder( ph );
		}
	}
}

void RootTemplateInstantiator::execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID )
{
	switch ( fnID )
	{
		case PREDEFINED_FUNCTION::PUBLISHABLE_STRUCTS:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::OBJPTR_LIST;
			for ( auto& it:root->structures )
			{
				StructTemplateInstantiator* structti = new StructTemplateInstantiator( *it, templateSpace, outstr );
				elem.objects.push_back( unique_ptr<TemplateInstantiator>(structti) );
			}
			stack.push_back( std::move(elem) );
			break;
		}
		default:
		{
			TemplateInstantiator::execBuiltinFunction( stack, fnID );
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////


string StructTemplateInstantiator::placeholder( Placeholder ph )
{
	switch( ph.id )
	{
		case PLACEHOLDER::STRUCT_NAME:
		{
			return structure->name;
		}
		default:
		{
			return TemplateInstantiator::placeholder( ph );
		}
	}
}

void StructTemplateInstantiator::execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID )
{
	switch ( fnID )
	{
		case PREDEFINED_FUNCTION::MEMBERS:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::OBJPTR_LIST;
			size_t memberCnt = structure->getChildCount();
			for ( size_t j=0; j<memberCnt; j++ )
			{
				BackDataMember* member = dynamic_cast<BackDataMember*>( structure->getMember( j ) );
				if ( member != NULL )
				{
					StructMemberTemplateInstantiator* smti = new StructMemberTemplateInstantiator( *member, templateSpace, outstr );
					elem.objects.push_back( unique_ptr<TemplateInstantiator>(smti) );
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
			TemplateInstantiator::execBuiltinFunction( stack, fnID );
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////


string StructMemberTemplateInstantiator::placeholder( Placeholder ph )
{
	switch( ph.id )
	{
		case PLACEHOLDER::MEMBER_NAME:
		{
			return member->name;
		}
		case PLACEHOLDER::MEMBER_TYPE:
		{
			return member->type.name;
		}
		default:
		{
			return TemplateInstantiator::placeholder( ph );
		}
	}
}

void StructMemberTemplateInstantiator::execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID )
{
	switch ( fnID )
	{
		case PREDEFINED_FUNCTION::MEMBER_TYPE:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::OBJPTR;
			DataType* memberType = new DataType( member->type );
			if ( memberType != NULL )
			{
				MemberTypeTemplateInstantiator* mtti = new MemberTypeTemplateInstantiator( *memberType, templateSpace, outstr );
				elem.singleObject = unique_ptr<TemplateInstantiator>(mtti);
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
			TemplateInstantiator::execBuiltinFunction( stack, fnID );
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////


string MemberTypeTemplateInstantiator::placeholder( Placeholder ph )
{
	switch( ph.id )
	{
		case PLACEHOLDER::MEMBER_TYPE:
		{
			return dataType->name;
		}
		default:
		{
			return TemplateInstantiator::placeholder( ph );
		}
	}
}

void MemberTypeTemplateInstantiator::execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID )
{
	switch ( fnID )
	{
		case PREDEFINED_FUNCTION::COLLECTION_TYPE:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::OBJPTR;
			assert( dataType->kind == DataType::KIND::SEQUENCE || dataType->kind == DataType::KIND::DICTIONARY );
			MemberTypeTemplateInstantiator* mtti = new MemberTypeTemplateInstantiator( *(dataType->paramType), templateSpace, outstr );
			elem.singleObject = unique_ptr<TemplateInstantiator>(mtti);
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::COLLECTION_TYPE2:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::OBJPTR;
			assert( dataType->kind == DataType::KIND::DICTIONARY );
			MemberTypeTemplateInstantiator* mtti = new MemberTypeTemplateInstantiator( *(dataType->keyType), templateSpace, outstr );
			elem.singleObject = unique_ptr<TemplateInstantiator>(mtti);
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::ENUM_VALUES:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::OBJPTR_LIST;
			for ( auto it:dataType->enumValues )
			{
				EnumValueTemplateInstantiator* evti = new EnumValueTemplateInstantiator( it.first, it.second, templateSpace, outstr );
				elem.objects.push_back( unique_ptr<TemplateInstantiator>(evti) );
			}
			stack.push_back( std::move(elem) );
			break;
		}
		// type-related
		// NOTE: this list is subject to change (see issue #52, for instance)
		// TODO: update as necessary
		case PREDEFINED_FUNCTION::IS_PRIMITIVE_DOUBLE:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::PRIMITIVE &&dataType->name == "DOUBLE";
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_PRIMITIVE_INTEGER:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::PRIMITIVE && ( dataType->name == "INTEGER" || dataType->name == "UINT16" );
			stack.push_back( std::move(elem) );
			break;
		}
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
		case PREDEFINED_FUNCTION::IS_PARAMETRIZED_DOUBLE:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::LIMITED_PRIMITIVE && dataType->name == "NUMERIC";
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_INTEGER:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::INTEGER;
			if ( elem.boolValue )
				assert( dataType->name.size() == 0 );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_FLOATING_POINT:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::FLOATING_POINT;
			if ( elem.boolValue )
				assert( dataType->name.size() == 0 );
			stack.push_back( std::move(elem) );
			break;
		}
		case PREDEFINED_FUNCTION::IS_FIXED_POINT:
		{
			StackElement elem;
			elem.argtype = ARGTYPE::BOOL;
			elem.boolValue = dataType->kind == DataType::KIND::FIXED_POINT;
			if ( elem.boolValue )
				assert( dataType->name.size() == 0 );
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
		default:
		{
			TemplateInstantiator::execBuiltinFunction( stack, fnID );
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////


string EnumValueTemplateInstantiator::placeholder( Placeholder ph )
{
	switch( ph.id )
	{
		case PLACEHOLDER::ENUM_VALUE_NAME:
		{
			return name;
		}
		case PLACEHOLDER::ENUM_VALUE_VALUE:
		{
			return fmt::format( "{}", value );
		}
		default:
		{
			return TemplateInstantiator::placeholder( ph );
		}
	}
}

void EnumValueTemplateInstantiator::execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID )
{
	switch ( fnID )
	{
		default:
		{
			TemplateInstantiator::execBuiltinFunction( stack, fnID );
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////


void apply( BackRoot& structure, TemplateNodeSpace& templateSpace )
{
	RootTemplateInstantiator rti( structure, templateSpace, nullptr );
	rti.apply();
}
