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


void RootTemplateInstantiator::applyNode( TemplateNode& node )
{
	switch ( node.type )
	{
		default:
		{
			TemplateInstantiator::applyNode( node );
		}
	}
}

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
//				BackStructure* structure = dynamic_cast<BackStructure*>( root->structures[j] );
//				if ( structure != NULL )
				{
					StructTemplateInstantiator* structti = new StructTemplateInstantiator( *(root->structures[j]), templateSpace, outstr );
					elem.objects.push_back( structti );
				}
/*				else
				{
					// TODO: this case requires additional analysis
					assert( 0 );
				}*/
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


void StructTemplateInstantiator::applyNode( TemplateNode& node )
{
	switch ( node.type )
	{
		default:
		{
			TemplateInstantiator::applyNode( node );
		}
	}
}

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


void StructMemberTemplateInstantiator::applyNode( TemplateNode& node )
{
	switch ( node.type )
	{
		default:
		{
			TemplateInstantiator::applyNode( node );
		}
	}
}

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
