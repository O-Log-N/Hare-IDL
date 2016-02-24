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

bool TemplateInstantiator::calcConditionOfIfNode( TemplateNode& ifNode )
{
	// NOTE: here we have a quite quick and dirty solution just for a couple of immediately necessary cases
	// TODO: full implementation

	assert( ifNode.type == NODE_TYPE::IF || ifNode.type == NODE_TYPE::ASSERT );
	bool ret;

	unsigned int i, j;
	vector<string> argstack;
	vector<int> commands;
	for ( i=0; i<ifNode.lineParts.size(); i++ )
	{
		switch ( ifNode.lineParts[i].type )
		{
			case PLACEHOLDER::VERBATIM: argstack.push_back( ifNode.lineParts[i].verbatim ); break;
			case OPERATOR::EQ:
			case OPERATOR::NEQ:
			{
				commands.push_back( ifNode.lineParts[i].type );
				break;
			}
			case PLACEHOLDER::MEMBER_TYPE:
			{
				argstack.push_back( placeholder( PLACEHOLDER::MEMBER_TYPE ) ); 
				break;
			}
			default:
			{
				printf( "Type %d is unexpected or unsupported\n", ifNode.lineParts[i].type );
				assert( 0 == "Error: not supported" );
			}
		}
	}

	unsigned int commandCnt = commands.size();
	unsigned int stacksz = argstack.size();

	assert( ( commandCnt == 1 && stacksz == 2 ) || commandCnt == 0 && stacksz == 1 ); // limitation of a current version; TODO: further development

	if ( commandCnt == 1 )
	{
		for ( j=commandCnt; j; j-- )
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

void TemplateInstantiator::applyNode( TemplateNode& node )
{
	switch ( node.type )
	{
		case NODE_TYPE::TEMPLATE_ROOT:
		{
			for ( unsigned int k=0; k<node.childNodes.size(); k++ )
				applyNode( node.childNodes[k]/*, idlmap, context*/ );
			break;
		}
		case NODE_TYPE::CONTENT:
		{
			for ( unsigned int i=0; i<node.lineParts.size(); i++ )
				switch ( node.lineParts[i].type )
				{
					case PLACEHOLDER::VERBATIM:
					{
						printf( node.lineParts[i].verbatim.c_str() ); 
						break;
					}
					case PLACEHOLDER::STRUCT_NAME: 
					{
						printf( placeholder( PLACEHOLDER::STRUCT_NAME ).c_str() ); 
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
						printf( "Unknown line_part.type = %d found", node.lineParts[i].type );
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
			for ( unsigned int k=0; k<node.childNodes.size(); k++ )
				applyNode( node.childNodes[k]/*, idlmap, context*/ );
			break;
		}
		case NODE_TYPE::FOR_EACH_OF_MEMBERS:
		{
			applyToEach( node );
			break;
		}
		case NODE_TYPE::IF:
		{
			bool cond = calcConditionOfIfNode( node/*, idlmap, context*/ );
			if ( cond )					
			{
				if ( node.childNodes[0].type == NODE_TYPE::IF_TRUE_BRANCHE )
					applyNode( node.childNodes[0]/*, idlmap, context*/ );
			}
			else
			{
				if ( node.childNodes[0].type == NODE_TYPE::IF_FALSE_BRANCHE )
					applyNode( node.childNodes[0]/*, idlmap, context*/ );
				else if ( node.childNodes[1].type == NODE_TYPE::IF_FALSE_BRANCHE )
					applyNode( node.childNodes[1]/*, idlmap, context*/ );
			}
			break;
		}
		case NODE_TYPE::ASSERT:
		{
			bool cond = calcConditionOfIfNode( node/*, idlmap, context*/ );
			if ( !cond )					
			{
				printf( "Instantiation Error: Assertion failed: Line %d\n", node.srcLineNum );
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

string TemplateInstantiator::placeholder( int placeholderId )
{
	printf( "error_placeholder\n" );
	assert( 0 );
	return "";
}

void TemplateInstantiator::applyToEach( TemplateNode& node )
{
	printf( "error_applyToEach\n" );
	assert( 0 );
}

/////////////////////////////////////////////////////////////////////////

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
			if ( structure->isChildAMember(j) )
			{
//				const BackDataMember* member = structure->getConstMember( j );
				BackDataMember* member = structure->getMember( j );
				assert( member != NULL );
				StructMemberTemplateInstantiator smti( *member );
				smti.apply( node.childNodes[k] );
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
