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

string TemplateInstantiator::resolveLinePartsToString( const vector<LinePart>& lineParts )
{
	string ret;
	for ( auto lp:lineParts )
	{
		if ( lp.type == PLACEHOLDER::VERBATIM )
			ret += lp.verbatim;
		else
		{
			Placeholder ph = {lp.type, lp.verbatim};
			ret += placeholder( ph );
		}
	}
	return ret;
}

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
		assert( ifNode.expression[0].argtype == ExpressionElement::ARGTYPE::STRING ); // limitation of a current version; TODO: further development
		assert( ifNode.expression[2].argtype == ExpressionElement::ARGTYPE::STRING ); // limitation of a current version; TODO: further development
		switch ( ifNode.expression[1].oper )
		{
			case ExpressionElement::OPERATION::EQ:
			{
				string lstr = resolveLinePartsToString( ifNode.expression[0].lineParts );
/*				string lstr;
				if ( ifNode.expression[0].argtype == ExpressionElement::ARGTYPE::STRING )
//					lstr = ifNode.expression[0].stringValue;
				else
				{
//					Placeholder ph = {ifNode.expression[0].placeholder, ifNode.expression[0].stringValue};
//					lstr = placeholder( ph );
					lstr = placeholder( ifNode.expression[0].placeholder );
				}*/
				string rstr = resolveLinePartsToString( ifNode.expression[2].lineParts );
/*				string rstr;
				if ( ifNode.expression[2].argtype == ExpressionElement::ARGTYPE::STRING )
					rstr = ifNode.expression[2].stringValue;
				else
				{
//					Placeholder ph = {ifNode.expression[2].placeholder, ifNode.expression[0].stringValue};
//					rstr = placeholder( ph );
					rstr = placeholder( ifNode.expression[2].placeholder );
				}*/
				ret = lstr == rstr;
				break;
			}
			case ExpressionElement::OPERATION::NEQ:
			{
				string lstr = resolveLinePartsToString( ifNode.expression[0].lineParts );
/*				string lstr;
				if ( ifNode.expression[0].argtype == ExpressionElement::ARGTYPE::STRING )
					lstr = ifNode.expression[0].stringValue;
				else
				{
//					Placeholder ph = {ifNode.expression[0].placeholder, ifNode.expression[0].stringValue};
//					lstr = placeholder( ph );
					lstr = placeholder( ifNode.expression[0].placeholder );
				}*/
				string rstr = resolveLinePartsToString( ifNode.expression[2].lineParts );
/*				string rstr;
				if ( ifNode.expression[2].argtype == ExpressionElement::ARGTYPE::STRING )
					rstr = ifNode.expression[2].stringValue;
				else
				{
//					Placeholder ph = {ifNode.expression[2].placeholder, ifNode.expression[0].stringValue};
//					rstr = placeholder( ph );
					rstr = placeholder( ifNode.expression[2].placeholder );
				}*/
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
		assert( ifNode.expression[0].argtype == ExpressionElement::ARGTYPE::STRING ); // limitation of a current version; TODO: further development
		string lstr = resolveLinePartsToString( ifNode.expression[0].lineParts );
/*		string lstr;
		if ( ifNode.expression[0].argtype == ExpressionElement::ARGTYPE::STRING )
			lstr = ifNode.expression[0].stringValue;
		else
		{
//			Placeholder ph = {ifNode.expression[0].placeholder, ifNode.expression[0].stringValue};
//			lstr = placeholder( ph );
			lstr = placeholder( ifNode.expression[0].placeholder );
		}*/
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
			if ( outstr == nullptr )
			{
				fmt::print("Instantiation error at template line{}: no output file", node.srcLineNum );
				assert(0); // TODO: replace by throwing an exception or alike
			}
			auto attr = node.attributes.find( {ATTRIBUTE::TEXT, ""} );
			assert( attr != node.attributes.end() );
			auto& lineParts = attr->second;
			for ( size_t i=0; i<attr->second.size(); i++ )
				if ( lineParts[i].type == PLACEHOLDER::VERBATIM )
					fmt::print( *outstr, "{}", lineParts[i].verbatim.c_str() );
				else
				{
					Placeholder ph = {lineParts[i].type, lineParts[i].verbatim};
					fmt::print(*outstr, "{}", placeholder( ph ).c_str() );
				}
			fmt::print(*outstr, "\n" );
			break;
		}
		case NODE_TYPE::IF_TRUE_BRANCH:
		case NODE_TYPE::IF_FALSE_BRANCH:
		{
			for ( size_t k=0; k<node.childNodes.size(); k++ )
				applyNode( node.childNodes[k] );
			break;
		}
		case NODE_TYPE::OPEN_OUTPUT_FILE:
		{
			if ( outstr != nullptr )
			{
				fmt::print("Instantiation error at template line{}: output file is already open", node.srcLineNum );
				assert(0); // TODO: replace by throwing an exception or alike
			}
			ofstream tf;
			// prepare file name string
			auto attr = node.attributes.find( {ATTRIBUTE::FILENAME, ""} );
			assert( attr != node.attributes.end() );
			string fileName = resolveLinePartsToString( attr->second );
			tf.open ( fileName, ios::out | ios::binary );
			outstr = &tf;
			for ( size_t k=0; k<node.childNodes.size(); k++ )
				applyNode( node.childNodes[k] );
			outstr = nullptr;
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
			auto attr = node.attributes.find( {ATTRIBUTE::TEMPLATE, ""} );
			assert( attr != node.attributes.end() );
			auto& lineParts = attr->second;
			assert( lineParts.size() == 1 ); // see NOTE and TODO below
			string templateName = lineParts[0].verbatim;
			// NOTE: here we implement a quite restricted version
			// TODO: value of ATTRIBUTE::FILENAME can contain placeholders and filename must be built based on the full content

			TemplateNode* tn = templateSpace.getTemplate( templateName, context() );
			if ( tn == nullptr )
			{
				assert( 0 ); // TODO: throw
			}
			// load resolved names, if any
			for ( const auto it:node.attributes )
				if ( it.first.id == ATTRIBUTE::PARAM )
				{
					string resolved = resolveLinePartsToString( it.second );
					resolvedPlaceholders.insert( make_pair( it.first.ext, resolved ) );
				}
			TemplateInstantiator::applyNode( *tn );
			resolvedPlaceholders.clear();
			break;
		}
		default:
		{
			fmt::print("Unexpected node type {} found\n", node.type );
			assert( 0 == "ERROR: UNEXPECTED" );
		}
	}
}

string TemplateInstantiator::placeholder( Placeholder ph )
{
	if ( ph.id == PLACEHOLDER::PARAM_MINUS )
	{
		auto findres = resolvedPlaceholders.find( ph.specific );
		if ( findres != resolvedPlaceholders.end() )
			return findres->second;
	}

	fmt::print( "\n" );
	fmt::print("error_placeholder {}\n", ph.id );
	assert( 0 );
	return "";
}

string TemplateInstantiator::context()
{
	fmt::print( "\n" );
	fmt::print("error: context() available\n" );
	assert( 0 );
	return "";
}

