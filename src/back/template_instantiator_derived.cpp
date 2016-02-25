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


string StructTemplateInstantiator::placeholder( int placeholderId )
{
	switch( placeholderId )
	{
		case PLACEHOLDER::STRUCT_NAME:
		{
			return structure->name;
		}
		default:
		{
			return TemplateInstantiator::placeholder( placeholderId );
		}
	}
}

void StructTemplateInstantiator::applyToEach( TemplateNode& node )
{
	unsigned int memberCnt = structure->getChildCount();
	for ( unsigned int j=0; j<memberCnt; j++ )
	{
		for ( unsigned int k=0; k<node.childNodes.size(); k++ )
		{
			BackDataMember* member = dynamic_cast<BackDataMember*>( structure->getMember( j ) );
			if ( member != NULL )
			{
				StructMemberTemplateInstantiator smti( *member );
				smti.apply( node.childNodes[k] );
			}
			else
			{
				// TODO: this case requires additional analysis
				assert( 0 );
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////


string StructMemberTemplateInstantiator::placeholder( int placeholderId )
{
	switch( placeholderId )
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
			return TemplateInstantiator::placeholder( placeholderId );
		}
	}
}

/////////////////////////////////////////////////////////////////////////


void apply( BackStructure& structure, AnyTemplateRoot& rootNode )
{
	StructTemplateInstantiator ti( structure );
	ti.apply( rootNode );
}
