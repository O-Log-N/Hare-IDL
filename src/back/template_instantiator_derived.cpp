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
			size_t structCnt = root->structures.size();
			for ( size_t j=0; j<structCnt; j++ )
			{
				StructTemplateInstantiator* structti = new StructTemplateInstantiator( *(root->structures[j]), templateSpace, outstr );
				elem.objects.push_back( structti );
			}
			stack.push_back( elem );
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
					elem.objects.push_back( smti );
				}
				else
				{
					// TODO: this case requires additional analysis
					assert( 0 );
				}
			}
			stack.push_back( elem );
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
//			size_t memberCnt = structure->getChildCount();
//			for ( size_t j=0; j<memberCnt; j++ )
			{
//				DataType* memberType = dynamic_cast<DataType*>( &(member->type) );
				DataType* memberType = new DataType( member->type );
				if ( memberType != NULL )
				{
					MemberTypeTemplateInstantiator* mtti = new MemberTypeTemplateInstantiator( *memberType, templateSpace, outstr );
					elem.singleObject = mtti;
				}
				else
				{
					// TODO: this case requires additional analysis
					assert( 0 );
				}
			}
			stack.push_back( elem );
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
