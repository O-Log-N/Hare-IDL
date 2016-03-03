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
		case NODE_TYPE::FOR_EACH_PUBLISHABLE_STRUCT:
		{
			size_t structCnt = root->structures.size();
			for ( size_t j=0; j<structCnt; j++ )
			{
				for ( size_t k=0; k<node.childNodes.size(); k++ )
				{
					StructTemplateInstantiator structti( *(root->structures[j]), templateSpace, outstr );
					structti.apply( node.childNodes[k] );
				}
			}
			break;
		}
		default:
		{
			TemplateInstantiator::applyNode( node );
		}
	}
}

string RootTemplateInstantiator::placeholder( int placeholderId )
{
	switch( placeholderId )
	{
		default:
		{
			return TemplateInstantiator::placeholder( placeholderId );
		}
	}
}

/////////////////////////////////////////////////////////////////////////


void StructTemplateInstantiator::applyNode( TemplateNode& node )
{
	switch ( node.type )
	{
		case NODE_TYPE::FOR_EACH_OF_MEMBERS:
		{
			size_t memberCnt = structure->getChildCount();
			for ( size_t j=0; j<memberCnt; j++ )
			{
				for ( size_t k=0; k<node.childNodes.size(); k++ )
				{
					BackDataMember* member = dynamic_cast<BackDataMember*>( structure->getMember( j ) );
					if ( member != NULL )
					{
						StructMemberTemplateInstantiator smti( *member, templateSpace, outstr );
						smti.apply( node.childNodes[k] );
					}
					else
					{
						// TODO: this case requires additional analysis
						assert( 0 );
					}
				}
			}
			break;
		}
		default:
		{
			TemplateInstantiator::applyNode( node );
		}
	}
}

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


void apply( BackRoot& structure, TemplateNodeSpace& templateSpace )
{
	RootTemplateInstantiator rti( structure, templateSpace, nullptr );
	rti.apply();
}
