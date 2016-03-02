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

//	size_t i, j;

	size_t expressionSz = ifNode.expression.size();
	assert( ( expressionSz == 1 && ifNode.expression[0].oper == ExpressionElement::OPERATION::PUSH ) || 
		    ( expressionSz == 3 && ifNode.expression[0].oper == ExpressionElement::OPERATION::PUSH && ( ifNode.expression[1].oper == ExpressionElement::OPERATION::EQ || ifNode.expression[1].oper == ExpressionElement::OPERATION::NEQ ) &&ifNode.expression[2].oper == ExpressionElement::OPERATION::PUSH ) ); // limitation of a current version; TODO: further development

	if (expressionSz == 3)
	{
		assert( ifNode.expression[0].argtype == ExpressionElement::ARGTYPE::STRING || ifNode.expression[0].argtype == ExpressionElement::ARGTYPE::PLACEHOLDER ); // limitation of a current version; TODO: further development
		assert( ifNode.expression[2].argtype == ExpressionElement::ARGTYPE::STRING || ifNode.expression[2].argtype == ExpressionElement::ARGTYPE::PLACEHOLDER ); // limitation of a current version; TODO: further development
		switch ( ifNode.expression[1].oper )
		{
			case ExpressionElement::OPERATION::EQ:
			{
				string& lstr = ifNode.expression[0].argtype == ExpressionElement::ARGTYPE::STRING ? ifNode.expression[0].stringValue : placeholder( ifNode.expression[0].placeholder );
				string& rstr = ifNode.expression[2].argtype == ExpressionElement::ARGTYPE::STRING ? ifNode.expression[2].stringValue : placeholder( ifNode.expression[2].placeholder );
				ret = lstr == rstr;
				break;
			}
			case ExpressionElement::OPERATION::NEQ:
			{
				string& lstr = ifNode.expression[0].argtype == ExpressionElement::ARGTYPE::STRING ? ifNode.expression[0].stringValue : placeholder( ifNode.expression[0].placeholder );
				string& rstr = ifNode.expression[2].argtype == ExpressionElement::ARGTYPE::STRING ? ifNode.expression[2].stringValue : placeholder( ifNode.expression[2].placeholder );
				ret = !(lstr == rstr);
				break;
			}
			default:
			{
				fmt::print("Type {} is unexpected or unsupported\n", ifNode.expression[1].oper );
				assert(0 == "Error: not supported");
			}
		}
	}
	else
	{
		assert( ifNode.expression[0].argtype == ExpressionElement::ARGTYPE::STRING || ifNode.expression[0].argtype == ExpressionElement::ARGTYPE::PLACEHOLDER ); // limitation of a current version; TODO: further development
		string& lstr = ifNode.expression[0].argtype == ExpressionElement::ARGTYPE::STRING ? ifNode.expression[0].stringValue : placeholder( ifNode.expression[0].placeholder );
		ret = !(lstr == "0" || lstr == "FALSE");
	}
	return ret;
}

void TemplateInstantiator::applyNode( TemplateNode& node )
{
	switch ( node.type )
	{
		case NODE_TYPE::FULL_TEMPLATE:
		{
			for ( size_t k=0; k<node.childNodes.size(); k++ )
				applyNode( node.childNodes[k] );
			break;
		}
		case NODE_TYPE::CONTENT:
		{
			for ( size_t i=0; i<node.lineParts.size(); i++ )
				if ( node.lineParts[i].type == PLACEHOLDER::VERBATIM )
					fmt::print("{}", node.lineParts[i].verbatim.c_str() );
				else
					fmt::print("{}", placeholder( node.lineParts[i].type ).c_str() );
			fmt::print("\n" );
			break;
		}
		case NODE_TYPE::IF_TRUE_BRANCH:
		case NODE_TYPE::IF_FALSE_BRANCH:
		{
			for ( size_t k=0; k<node.childNodes.size(); k++ )
				applyNode( node.childNodes[k] );
			break;
		}
		case NODE_TYPE::IF:
		{
			bool cond = calcConditionOfIfNode( node );
			if ( cond )					
			{
				if ( node.childNodes[0].type == NODE_TYPE::IF_TRUE_BRANCH )
					applyNode( node.childNodes[0] );
			}
			else
			{
				if ( node.childNodes[0].type == NODE_TYPE::IF_FALSE_BRANCH )
					applyNode( node.childNodes[0] );
				else if ( node.childNodes[1].type == NODE_TYPE::IF_FALSE_BRANCH )
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

