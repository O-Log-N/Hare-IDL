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

#include "template_instantiator.h"
#include "template_parser.h"
#include <assert.h> // for assert()

bool template_instantiator::calc_condition_of_if_node( TEMPLATE_NODE& if_node )
{
	// NOTE: here we have a quite quick and dirty solution just for a couple of immediately necessary cases
	// TODO: full implementation

	assert( if_node.type == NODE_TYPE::IF || if_node.type == NODE_TYPE::ASSERT );
	bool ret;

	unsigned int i, j;
	vector<std::string> argstack;
	vector<int> commands;
	for ( i=0; i<if_node.line_parts.size(); i++ )
	{
		switch ( if_node.line_parts[i].type )
		{
			case PLACEHOLDER::VERBATIM: argstack.push_back( if_node.line_parts[i].verbatim ); break;
			case OPERATOR::EQ:
			case OPERATOR::NEQ:
			{
				commands.push_back( if_node.line_parts[i].type );
				break;
			}
			case PLACEHOLDER::MEMBER_TYPE:
			{
				argstack.push_back( placeholder( PLACEHOLDER::MEMBER_TYPE ) ); 
				break;
			}
			default:
			{
				printf( "Type %d is unexpected or unsupported\n", if_node.line_parts[i].type );
				assert( 0 == "Error: not supported" );
			}
		}
	}

	unsigned int command_cnt = commands.size();
	unsigned int stacksz = argstack.size();

	assert( ( command_cnt == 1 && stacksz == 2 ) || command_cnt == 0 && stacksz == 1 ); // limitation of a current version; TODO: further development

	if ( command_cnt == 1 )
	{
		for ( j=command_cnt; j; j-- )
		{
			switch ( commands[j-1] )
			{
				case OPERATOR::EQ:
				{
					ret = argstack[0] == argstack[1];
					break;
				}
				case OPERATOR::NEQ:
				{
					ret = !(argstack[0] == argstack[1]);
					break;
				}
				default:
				{
					printf( "Type %d is unexpected or unsupported\n", commands[j-1] );
					assert( 0 == "Error: not supported" );
				}
			}
		}
	}
	else
	{
		ret = !( argstack[0] == "0" || argstack[0] == "FALSE" );
	}
	return ret;
}

void template_instantiator::apply_node( TEMPLATE_NODE& node )
{
	switch ( node.type )
	{
		case NODE_TYPE::TEMPLATE_ROOT:
		{
			for ( unsigned int k=0; k<node.child_nodes.size(); k++ )
				apply_node( node.child_nodes[k]/*, idlmap, context*/ );
			break;
		}
		case NODE_TYPE::CONTENT:
		{
			for ( unsigned int i=0; i<node.line_parts.size(); i++ )
				switch ( node.line_parts[i].type )
				{
					case PLACEHOLDER::VERBATIM:
					{
						printf( node.line_parts[i].verbatim.c_str() ); 
						break;
					}
					case PLACEHOLDER::STRUCTNAME: 
					{
						printf( placeholder( PLACEHOLDER::STRUCTNAME ).c_str() ); 
						break;
					}
					case PLACEHOLDER::MEMBER_TYPE: 
					{
						printf( placeholder( PLACEHOLDER::MEMBER_TYPE ).c_str() ); 
						break;
					}
					case PLACEHOLDER::MEMBER_NAME: 
					{
						printf( placeholder( PLACEHOLDER::MEMBER_NAME ).c_str() ); 
						break;
					}
					default:
					{
						printf( "Unknown line_part.type = %d found", node.line_parts[i].type );
						assert( 0 == "Error: Not Implemented" );
					}
				}
			printf( "\n" ); 
			break;
		}
		case NODE_TYPE::BEGIN_TEMPLATE:
		case NODE_TYPE::IF_TRUE_BRANCHE:
		case NODE_TYPE::IF_FALSE_BRANCHE:
		{
			for ( unsigned int k=0; k<node.child_nodes.size(); k++ )
				apply_node( node.child_nodes[k]/*, idlmap, context*/ );
			break;
		}
		case NODE_TYPE::FOR_EACH_OF_MEMBERS:
		{
			apply_to_each( node );
			break;
		}
		case NODE_TYPE::IF:
		{
			bool cond = calc_condition_of_if_node( node/*, idlmap, context*/ );
			if ( cond )					
			{
				if ( node.child_nodes[0].type == NODE_TYPE::IF_TRUE_BRANCHE )
					apply_node( node.child_nodes[0]/*, idlmap, context*/ );
			}
			else
			{
				if ( node.child_nodes[0].type == NODE_TYPE::IF_FALSE_BRANCHE )
					apply_node( node.child_nodes[0]/*, idlmap, context*/ );
				else if ( node.child_nodes[1].type == NODE_TYPE::IF_FALSE_BRANCHE )
					apply_node( node.child_nodes[1]/*, idlmap, context*/ );
			}
			break;
		}
		case NODE_TYPE::ASSERT:
		{
			bool cond = calc_condition_of_if_node( node/*, idlmap, context*/ );
			if ( !cond )					
			{
				printf( "Instantiation Error: Assertion failed: Line %d\n", node.src_line_num );
			}
			break;
		}
		case NODE_TYPE::INCLUDE:
		{
			assert( 0 == "ERROR: NOT IMPLEMENTED" );
			break;
		}
		default:
		{
			printf( "Unexpected node type %d found\n", node.type );
			assert( 0 == "ERROR: UNEXPECTED" );
		}
	}
}

/////////////////////////////////////////////////////////////////////////

std::string template_instantiator::placeholder( int placeholder_id )
{
	printf( "error_placeholder\n" );
	assert( 0 );
	return "";
}

void template_instantiator::apply_to_each( TEMPLATE_NODE& node )
{
	printf( "error_apply_to_each\n" );
	assert( 0 );
}

/////////////////////////////////////////////////////////////////////////

std::string struct_template_instantiator::placeholder( int placeholder_id )
{
	switch( placeholder_id )
	{
		case PLACEHOLDER::STRUCTNAME:
		{
			return idlmap->name;
		}
		default:
		{
			return template_instantiator::placeholder( placeholder_id );
		}
	}
}

void struct_template_instantiator::apply_to_each( TEMPLATE_NODE& node )
{
	int member_cnt = idlmap->attributes.size();
	for ( int j=0; j<member_cnt; j++ )
	{
		for ( unsigned int k=0; k<node.child_nodes.size(); k++ )
		{
			struct_member_template_instantiator smti( *(idlmap->attributes[j]) );
			smti.apply( node.child_nodes[k] );
		}
	}
}

/////////////////////////////////////////////////////////////////////////

std::string struct_member_template_instantiator::placeholder( int placeholder_id )
{
	switch( placeholder_id )
	{
		case PLACEHOLDER::MEMBER_NAME:
		{
			return attr->name.c_str();
		}
		case PLACEHOLDER::MEMBER_TYPE:
		{
			return attr->type->toString();
		}
		default:
		{
			return template_instantiator::placeholder( placeholder_id );
		}
	}
}

/////////////////////////////////////////////////////////////////////////


void apply( MappingDeclNode& idlmap, ANY_TEMPLATE_ROOT& root_node )
{
	struct_template_instantiator ti( idlmap );
	ti.apply( root_node );
}
