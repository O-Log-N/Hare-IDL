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

bool TemplateInstantiator::calcConditionOfIfNode(TemplateNode& ifNode)
{
	// NOTE: here we have a quite quick and dirty solution just for a couple of immediately necessary cases
	// TODO: full implementation

	assert(ifNode.type == NODE_TYPE::IF || ifNode.type == NODE_TYPE::ASSERT);
	bool ret;

	unsigned int i, j;
	vector<string> argstack;
	vector<int> commands;
	for (i = 0; i < ifNode.lineParts.size(); i++)
	{
		auto type = ifNode.lineParts[i].type;
		switch ( type )
		{
			case PLACEHOLDER::VERBATIM: argstack.push_back(ifNode.lineParts[i].verbatim); break;
			case OPERATOR::EQ:
			case OPERATOR::NEQ:
			{
				commands.push_back( type );
				break;
			}
			default:
			{
				argstack.push_back( placeholder( type ) );
				break;
			}
		}
	}

	unsigned int commandCnt = commands.size();
	unsigned int stacksz = argstack.size();

	assert((commandCnt == 1 && stacksz == 2) || commandCnt == 0 && stacksz == 1); // limitation of a current version; TODO: further development

	if (commandCnt == 1)
	{
		for (j = commandCnt; j; j--)
		{
			switch (commands[j - 1])
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
					fmt::print("Type {} is unexpected or unsupported\n", commands[j - 1] );
					assert(0 == "Error: not supported");
				}
			}
		}
	}
	else
	{
		ret = !(argstack[0] == "0" || argstack[0] == "FALSE");
	}
	return ret;
}

void TemplateInstantiator::applyNode( TemplateNode& node )
{
	switch ( node.type )
	{
		case NODE_TYPE::FULL_TEMPLATE:
		{
			for ( unsigned int k=0; k<node.childNodes.size(); k++ )
				applyNode( node.childNodes[k] );
			break;
		}
		case NODE_TYPE::CONTENT:
		{
			for ( unsigned int i=0; i<node.lineParts.size(); i++ )
				if ( node.lineParts[i].type == PLACEHOLDER::VERBATIM )
					fmt::print("{}", node.lineParts[i].verbatim.c_str() );
				else
					fmt::print("{}", placeholder( node.lineParts[i].type ).c_str() );
			fmt::print("\n" );
			break;
		}
		case NODE_TYPE::IF_TRUE_BRANCHE:
		case NODE_TYPE::IF_FALSE_BRANCHE:
		{
			for ( unsigned int k=0; k<node.childNodes.size(); k++ )
				applyNode( node.childNodes[k] );
			break;
		}
		case NODE_TYPE::IF:
		{
			bool cond = calcConditionOfIfNode( node );
			if ( cond )					
			{
				if ( node.childNodes[0].type == NODE_TYPE::IF_TRUE_BRANCHE )
					applyNode( node.childNodes[0] );
			}
			else
			{
				if ( node.childNodes[0].type == NODE_TYPE::IF_FALSE_BRANCHE )
					applyNode( node.childNodes[0] );
				else if ( node.childNodes[1].type == NODE_TYPE::IF_FALSE_BRANCHE )
					applyNode( node.childNodes[1] );
			}
			break;
		}
		case NODE_TYPE::ASSERT:
		{
			bool cond = calcConditionOfIfNode( node );
			if ( !cond )					
			{
				fmt::print("Instantiation Error: Assertion failed: Line {}\n", node.srcLineNum );
			}
			break;
		}
		case NODE_TYPE::INCLUDE:
		{
			assert( 0 == "ERROR: \"NODE_TYPE::INCLUDE\" NOT IMPLEMENTED" );
			break;
		}
		default:
		{
			fmt::print("Unexpected node type {} found\n", node.type );
			assert( 0 == "ERROR: UNEXPECTED" );
		}
	}
}

string TemplateInstantiator::placeholder( int placeholderId )
{
	fmt::print( "\n" );
	fmt::print("error_placeholder {}\n", placeholderId );
	assert( 0 );
	return "";
}

