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

void TemplateInstantiator::execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID )
{
}

void TemplateInstantiator::evaluateExpression( const vector<ExpressionElement>& expression, Stack& stack )
{
	for ( auto it:expression )
	{
		switch ( it.oper )
		{
			case OPERATOR::PUSH: 
			{
				StackElement se;
				se.argtype = it.argtype;
				LinePart part;
				part.type = PLACEHOLDER::VERBATIM;
				part.verbatim = resolveLinePartsToString( it.lineParts );
				se.lineParts.push_back( part );
				se.numberValue = it.numberValue;
				stack.push_back( std::move(se) );
				break;
			}
			case OPERATOR::EQ: 
			{
				assert( stack.size() >= 2 ); // TODO: it's a common check. Think about generalization
				bool res;
				auto arg1 = stack.begin() + stack.size() - 1;
				auto arg2 = stack.begin() + stack.size() - 2;
				if ( arg1->argtype == ARGTYPE::STRING && arg2->argtype == ARGTYPE::STRING )
					res = resolveLinePartsToString( arg1->lineParts ) == resolveLinePartsToString( arg2->lineParts );
				else if ( arg1->argtype == ARGTYPE::NUMBER && arg2->argtype == ARGTYPE::NUMBER )
					res = arg1->numberValue == arg2->numberValue;
				else if ( arg1->argtype == ARGTYPE::BOOL && arg2->argtype == ARGTYPE::BOOL )
					res = arg1->boolValue == arg2->boolValue;
				else
					assert( 0 );

				stack.pop_back();
				stack.pop_back();

				StackElement se;
				se.argtype = ARGTYPE::BOOL;
				se.boolValue = res;
				stack.push_back( std::move(se) );
				break;
			}
			case OPERATOR::NEQ:
			{
				assert( stack.size() >= 2 ); // TODO: it's a common check. Think about generalization
				bool res;
				auto arg1 = stack.begin() + stack.size() - 1;
				auto arg2 = stack.begin() + stack.size() - 2;
				if ( arg1->argtype == ARGTYPE::STRING && arg2->argtype == ARGTYPE::STRING )
					res = resolveLinePartsToString( arg1->lineParts ) != resolveLinePartsToString( arg2->lineParts );
				else if ( arg1->argtype == ARGTYPE::NUMBER && arg2->argtype == ARGTYPE::NUMBER )
					res = arg1->numberValue != arg2->numberValue;
				else if ( arg1->argtype == ARGTYPE::BOOL && arg2->argtype == ARGTYPE::BOOL )
					res = arg1->boolValue != arg2->boolValue;
				else
					assert( 0 );

				stack.pop_back();
				stack.pop_back();

				StackElement se;
				se.argtype = ARGTYPE::BOOL;
				se.boolValue = res;
				stack.push_back( std::move(se) );
				break;
			}
			case OPERATOR::CALL: 
			{
				execBuiltinFunction( stack, it.fnCallID );
				break;
			}
			case OPERATOR::GREATER:
			case OPERATOR::LESS:
			case OPERATOR::LEQ:
			case OPERATOR::GEQ:
			case OPERATOR::ADD:
			case OPERATOR::INCREMENT:
			case OPERATOR::SUBTR:
			case OPERATOR::DECREMENT:
			case OPERATOR::NOT:
			case OPERATOR::AND:
			case OPERATOR::OR:
				assert( 0); // TODO: implement
		}
	}
}

bool TemplateInstantiator::calcConditionOfIfNode(TemplateNode& ifNode)
{
	// NOTE: here we have a quite quick and dirty solution just for a couple of immediately necessary cases
	// TODO: full implementation

	assert(ifNode.type == NODE_TYPE::IF || ifNode.type == NODE_TYPE::ASSERT);

	Stack stack;
	evaluateExpression( ifNode.expression, stack );
	assert( stack.size() == 1 );
	if ( stack[0].argtype == ARGTYPE::BOOL )
		return stack[0].boolValue;
	else
	{
		// TODO: consider type conversion as a standard operation
		assert( ifNode.expression[0].argtype == ARGTYPE::STRING ); // limitation of a current version; TODO: further development
		string lstr = resolveLinePartsToString( ifNode.expression[0].lineParts );
		return !(lstr == "0" || lstr == "FALSE");
	}
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
			auto& expr = attr->second;
			Stack stack;
			evaluateExpression( expr, stack );
			assert( stack.size() == 1 );
			assert( stack[0].argtype == ARGTYPE::STRING );
			fmt::print( outstr, "{}", stack[0].lineParts[0].verbatim.c_str() );
			fmt::print( outstr, "\n" );
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
			// prepare file name string
			auto attr = node.attributes.find( {ATTRIBUTE::FILENAME, ""} );
			assert( attr != node.attributes.end() );
			auto& expr = attr->second;
			Stack stack;
			evaluateExpression( expr, stack );
			assert( stack.size() == 1 );
			assert( stack[0].argtype == ARGTYPE::STRING );
			string fileName = stack[0].lineParts[0].verbatim;
			FILE* tf = fopen( fileName.c_str(), "wb" );
			outstr = tf;
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
			auto& expr = attr->second;
			Stack stack;
			evaluateExpression( expr, stack );
			assert( stack.size() == 1 );
			assert( stack[0].argtype == ARGTYPE::STRING );
			string templateName = stack[0].lineParts[0].verbatim;

			string tContext = context();
			TemplateNode* tn = templateSpace.getTemplate( templateName, tContext );
			if ( tn == nullptr )
			{
				assert( 0 ); // TODO: throw
			}
			// load resolved names, if any
			for ( const auto it:node.attributes )
				if ( it.first.id == ATTRIBUTE::PARAM )
				{
					auto& expr1 = it.second;
					Stack stack1;
					evaluateExpression( expr1, stack1 );
					assert( stack1.size() == 1 );
					assert( stack1[0].argtype == ARGTYPE::STRING );
					string resolved = stack1[0].lineParts[0].verbatim;
					resolvedPlaceholders.insert( make_pair( it.first.ext, resolved ) );
				}
			TemplateInstantiator::applyNode( *tn );
			resolvedPlaceholders.clear();
			break;
		}
		case NODE_TYPE::INCLUDE_WITH:
		{
			auto attr = node.attributes.find( {ATTRIBUTE::TEMPLATE, ""} );
			assert( attr != node.attributes.end() );
			auto& expr = attr->second;
			Stack stack;
			evaluateExpression( expr, stack );
			assert( stack.size() == 1 );
			assert( stack[0].argtype == ARGTYPE::STRING );
			string templateName = stack[0].lineParts[0].verbatim;

			stack.clear();
			evaluateExpression( node.expression, stack );
			assert( stack.size() == 1 );
			assert( stack[0].argtype == ARGTYPE::OBJPTR );

			// load resolved names, if any
			for ( const auto it:node.attributes )
				if ( it.first.id == ATTRIBUTE::PARAM )
				{
					auto& expr1 = it.second;
					Stack stack1;
					evaluateExpression( expr1, stack1 );
					assert( stack1.size() == 1 );
					assert( stack1[0].argtype == ARGTYPE::STRING );
					string resolved = stack1[0].lineParts[0].verbatim;
					stack[0].singleObject->resolvedPlaceholders.insert( make_pair( it.first.ext, resolved ) );
				}

			TemplateNode* tn = templateSpace.getTemplate( templateName, stack[0].singleObject->context() );
			if ( tn == nullptr )
			{
				assert( 0 ); // TODO: throw
			}
			for ( auto nodeit:tn->childNodes )
			{
				stack[0].singleObject->applyNode( nodeit );
			}
			resolvedPlaceholders.clear();
			break;
		}
		case NODE_TYPE::FOR_EACH_OF:
		{
			Stack stack;
			evaluateExpression( node.expression, stack );
			assert( stack.size() == 1 );
			assert( stack[0].argtype == ARGTYPE::OBJPTR_LIST );
			for ( auto &obj:stack[0].objects )
				for ( auto nodeit:node.childNodes )
				{
					obj->applyNode(nodeit );
				}
			break;
		}
		default:
		{
			fmt::print("Unexpected node type {} found\n", static_cast<int>(node.type) );
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
	fmt::print("error_placeholder {}\n", static_cast<int>(ph.id) );
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

