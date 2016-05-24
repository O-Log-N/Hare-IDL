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
#include "template_instantiator_derived.h"

void ExpressionObject::execBuiltinFunction( Stack& stack, PredefindedFunction fn )
{
	assert( 0 );
}

string ExpressionObject::context()
{
	fmt::print( "\n" );
	fmt::print("error: context() available\n" );
	assert( 0 );
	return "";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string TemplateInstantiator::specialNameAsString( SpecialName ph )
{
	StackElement& se = placeholder( ph );
	// TODO: here we may need to perform type convergence
	switch ( se.argtype )
	{
		case ARGTYPE::STRING: 
		{
			assert( se.lineParts.size() == 1 );
			assert( se.lineParts[0].isVerbatim );
			return se.lineParts[0].verbatim;
		}
		case ARGTYPE::NUMBER: 
		{
			return fmt::format( "{}", se.numberValue );
		}
		case ARGTYPE::BOOL: 
		{
			return fmt::format( "{}", se.boolValue ); // TODO: think about aomething else...
		}
		default:
		{
			assert(0); // TODO: proper error reporting
			return "";
			break;
		}
	}
}

string TemplateInstantiator::resolveLinePartsToString( const vector<LinePart2>& lineParts )
{
	string ret;
	for ( auto lp:lineParts )
	{
		if ( lp.isVerbatim )
			ret += lp.verbatim;
		else
		{
			Stack stack;
			evaluateExpression( lp.expr, stack );
			assert( stack.size() == 1 );
			if ( stack[0].argtype == ARGTYPE::STRING )
			{
				if ( stack[0].lineParts.size() == 1 && stack[0].lineParts[0].isVerbatim )
					ret += stack[0].lineParts[0].verbatim;
				else
					ret += resolveLinePartsToString( stack[0].lineParts );
			}
			else if ( stack[0].argtype == ARGTYPE::NUMBER )
			{
				ret += fmt::format( "{}", stack[0].numberValue );
			}
			else
			{
				fmt::print( "\n" );
				fmt::print("error: cannot convert type {} to string\n", static_cast<int>(stack[0].argtype) );
				assert( 0 );
			}
		}
	}
	return ret;
}

void TemplateInstantiator::execBuiltinFunction( Stack& stack, PredefindedFunction fn )
{
	assert( stack.size() >= fn.argC );
	if ( fn.isContextSpecific )
	{
		auto argContext = stack.begin() + stack.size() - fn.argC - 1;
		assert( argContext->argtype == ARGTYPE::OBJPTR );
		Stack args( stack.begin() + stack.size() - fn.argC, stack.end() );
		argContext->singleObject->execBuiltinFunction( args, fn );
		stack.erase( stack.begin() + stack.size() - fn.argC - 1, stack.end() );
		for ( auto it:args )
			stack.push_back( it );
	}
	else
	{
		switch ( fn.id )
		{
			case PREDEFINED_FUNCTION::HAS_VALUE:
			{
				assert( stack.size() );
				auto arg1 = stack.begin() + stack.size() - 1;
				StackElement elem;
				elem.argtype = ARGTYPE::BOOL;
				elem.boolValue = arg1->argtype != ARGTYPE::NO_ARGTYPE;
				stack.pop_back();
				stack.push_back( elem );
				break;
			}
// type-checkers
			case PREDEFINED_FUNCTION::IS_ROOT:
			{
				assert( stack.size() );
				auto arg1 = stack.begin() + stack.size() - 1;
				StackElement elem;
				elem.argtype = ARGTYPE::BOOL;
				elem.boolValue = arg1->argtype == ARGTYPE::OBJPTR && arg1->singleObject->context() == "ROOT";
				stack.pop_back();
				stack.push_back( elem );
				break;
			}
			case PREDEFINED_FUNCTION::IS_SERIALIZABLE_OBJECT:
			{
				assert( stack.size() );
				auto arg1 = stack.begin() + stack.size() - 1;
				StackElement elem;
				elem.argtype = ARGTYPE::BOOL;
				elem.boolValue = arg1->argtype == ARGTYPE::OBJPTR && ( arg1->singleObject->context() == "STRUCT" || arg1->singleObject->context() == "DISCRIMINATED-UNION" );
				stack.pop_back();
				stack.push_back( elem );
				break;
			}
			case PREDEFINED_FUNCTION::IS_SERIALIZABLE_STRUCT:
			{
				assert( stack.size() );
				auto arg1 = stack.begin() + stack.size() - 1;
				StackElement elem;
				elem.argtype = ARGTYPE::BOOL;
				elem.boolValue = arg1->argtype == ARGTYPE::OBJPTR && arg1->singleObject->context() == "STRUCT";
				stack.pop_back();
				stack.push_back( elem );
				break;
			}
			case PREDEFINED_FUNCTION::IS_SERIALIZABLE_DISCRIMINATED_UNION:
			{
				assert( stack.size() );
				auto arg1 = stack.begin() + stack.size() - 1;
				StackElement elem;
				elem.argtype = ARGTYPE::BOOL;
				elem.boolValue = arg1->argtype == ARGTYPE::OBJPTR && arg1->singleObject->context() == "DISCRIMINATED-UNION";
				stack.pop_back();
				stack.push_back( elem );
				break;
			}
			case PREDEFINED_FUNCTION::IS_MEMBER:
			{
				assert( stack.size() );
				auto arg1 = stack.begin() + stack.size() - 1;
				StackElement elem;
				elem.argtype = ARGTYPE::BOOL;
				elem.boolValue = arg1->argtype == ARGTYPE::OBJPTR && arg1->singleObject->context() == "STRUCT-MEMBER";
				stack.pop_back();
				stack.push_back( elem );
				break;
			}
			case PREDEFINED_FUNCTION::IS_MEMBER_TYPE:
			{
				assert( stack.size() );
				auto arg1 = stack.begin() + stack.size() - 1;
				StackElement elem;
				elem.argtype = ARGTYPE::BOOL;
				elem.boolValue = arg1->argtype == ARGTYPE::OBJPTR && arg1->singleObject->context() == "DATATYPE";
				stack.pop_back();
				stack.push_back( elem );
				break;
			}
			case PREDEFINED_FUNCTION::IS_ENUM_VALUE:
			{
				assert( stack.size() );
				auto arg1 = stack.begin() + stack.size() - 1;
				StackElement elem;
				elem.argtype = ARGTYPE::BOOL;
				elem.boolValue = arg1->argtype == ARGTYPE::OBJPTR && arg1->singleObject->context() == "ENUMVALUE";
				stack.pop_back();
				stack.push_back( elem );
				break;
			}
			case PREDEFINED_FUNCTION::IS_DU_OPTION:
			{
				assert( stack.size() );
				auto arg1 = stack.begin() + stack.size() - 1;
				StackElement elem;
				elem.argtype = ARGTYPE::BOOL;
				elem.boolValue = arg1->argtype == ARGTYPE::OBJPTR && arg1->singleObject->context() == "DISCRIMINATED-UNION-OPTION";
				stack.pop_back();
				stack.push_back( elem );
				break;
			}
// map-related
			case PREDEFINED_FUNCTION::CREATE_MAP:
			{
				StackElement elem;
				elem.argtype = ARGTYPE::ANY_MAP;
				stack.push_back( elem );
				break;
			}
			case PREDEFINED_FUNCTION::ASSIGN:
			{
				assert( stack.size() >= 3 ); // TODO: it's a common check. Think about generalization
				bool res;
				auto arg1 = stack.begin() + stack.size() - 3;
				auto arg2 = stack.begin() + stack.size() - 2;
				auto arg3 = stack.begin() + stack.size() - 1;
				assert( arg1->argtype == ARGTYPE::ANY_MAP ); // TODO: report an error
				arg1->assignToMapElement( *arg2, *arg3 );
				stack.pop_back();
				stack.pop_back();
				break;
			}
			case PREDEFINED_FUNCTION::FIND_IN_MAP:
			{
				assert( stack.size() >= 2 ); // TODO: it's a common check. Think about generalization
				bool res;
				auto arg1 = stack.begin() + stack.size() - 2;
				auto arg2 = stack.begin() + stack.size() - 1;
				assert( arg1->argtype == ARGTYPE::ANY_MAP ); // TODO: report an error
				StackElement elem;
				arg1->findInMap( *arg2, elem );
				stack.pop_back();
				stack.pop_back();
				stack.push_back( elem );
				break;
			}
// list-related
			case PREDEFINED_FUNCTION::CREATE_LIST:
			{
				StackElement elem;
				elem.argtype = ARGTYPE::ANY_LIST;
				stack.push_back( elem );
				break;
			}
			case PREDEFINED_FUNCTION::APPEND_TO_LIST:
			{
				assert( stack.size() >= 2 ); // TODO: it's a common check. Think about generalization
				bool res;
				auto arg1 = stack.begin() + stack.size() - 2;
				auto arg2 = stack.begin() + stack.size() - 1;
				assert( arg1->argtype == ARGTYPE::ANY_LIST ); // TODO: report an error
				arg1->appendToList( *arg2 );
				stack.pop_back();
				break;
			}
			default:
			{
				// TODO: report an error
				assert( 0 );
			}
		}
	}
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
				switch ( it.argtype )
				{
					case ARGTYPE::STRING:
					{
						LinePart2 part;
						part.isVerbatim = true;
						part.verbatim = resolveLinePartsToString( it.lineParts );
						se.lineParts.push_back( part );
						break;
					}
					case ARGTYPE::NUMBER:
					{
						se.numberValue = it.numberValue;
						break;
					}
					case ARGTYPE::BOOL:
					{
						assert(0); // TODO: support respective ExpressionElement
						break;
					}
					case ARGTYPE::PLACEHOLDER:
					{
						se = placeholder( it. ph );
						break;
					}
					default:
					{
						assert(0); // TODO: proper error reporting
						break;
					}
				}
				stack.push_back( std::move(se) );
				break;
			}
			case OPERATOR::EQ: 
			{
				assert( stack.size() >= 2 ); // TODO: it's a common check. Think about generalization
				bool res;
				auto arg1 = stack.begin() + stack.size() - 2;
				auto arg2 = stack.begin() + stack.size() - 1;
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
				auto arg1 = stack.begin() + stack.size() - 2;
				auto arg2 = stack.begin() + stack.size() - 1;
				if ( arg1->argtype == ARGTYPE::STRING && arg2->argtype == ARGTYPE::STRING )
					res = resolveLinePartsToString( arg1->lineParts ) != resolveLinePartsToString( arg2->lineParts );
				else if ( arg1->argtype == ARGTYPE::NUMBER && arg2->argtype == ARGTYPE::NUMBER )
					res = arg1->numberValue != arg2->numberValue;
				else if ( arg1->argtype == ARGTYPE::BOOL && arg2->argtype == ARGTYPE::BOOL )
					res = arg1->boolValue != arg2->boolValue;
				else
					assert( 0 ); // TODO: think about type conversions

				stack.pop_back();
				stack.pop_back();

				StackElement se;
				se.argtype = ARGTYPE::BOOL;
				se.boolValue = res;
				stack.push_back( std::move(se) );
				break;
			}
			case OPERATOR::CALL_BUILTIN_FN: 
			{
				execBuiltinFunction( stack, it.fn );
				break;
			}
			case OPERATOR::CALL_USERDEF_FN: 
			{
				assert( stack.size() >= it.userDefFunction.argC );
				TemplateRootNode* tn = templateSpace.getTemplate( it.userDefFunction.name );
				if ( tn == nullptr )
				{
					assert( 0 ); // TODO: throw
				}
				if ( it.userDefFunction.argC != tn->params.size() )
				{
					fmt::print("Instantiation error: function call {} has {} parameters while respective template function requires {}", it.userDefFunction.name, it.userDefFunction.argC, tn->params.size() );
					assert(0); // TODO: replace by throwing an exception or alike
				}
				map<string, StackElement> resolvedParamPlaceholdersIni( std::move(resolvedParamPlaceholders) );
				map<string, StackElement> resolvedLocalPlaceholdersIni( std::move(resolvedLocalPlaceholders) );
				map<string, StackElement> resolvedParamPlaceholdersNew;
				resolvedParamPlaceholders = map<string, StackElement>( std::move(resolvedParamPlaceholdersNew) );
				for ( int i=0; i<it.userDefFunction.argC; ++i)
				{
					resolvedParamPlaceholders.insert( make_pair( tn->params[i].ext, *(stack.begin() + stack.size() - it.userDefFunction.argC + i) ) );
				}
				bool ret = applyNode( *tn );
				// restore ini content of resolved params and locals
				resolvedParamPlaceholders = map<string, StackElement>( std::move(resolvedParamPlaceholdersIni) );
				resolvedLocalPlaceholders = map<string, StackElement>( std::move(resolvedLocalPlaceholdersIni) );
				stack.erase( stack.begin() + stack.size() - it.userDefFunction.argC, stack.end() );
				stack.push_back( fromTemplate );
				break;
			}
			case OPERATOR::ADD:
			{
				assert( stack.size() >= 2 ); // TODO: it's a common check. Think about generalization
				StackElement se;
				auto arg1 = stack.begin() + stack.size() - 2;
				auto arg2 = stack.begin() + stack.size() - 1;
				if ( arg1->argtype == ARGTYPE::STRING && arg2->argtype == ARGTYPE::STRING )
				{
					assert( arg1->lineParts.size() == 1 );
					assert( arg1->lineParts[0].isVerbatim );
					assert( arg2->lineParts.size() == 1 );
					assert( arg2->lineParts[0].isVerbatim );
					LinePart2 lp;
					lp.isVerbatim = true;
					lp.verbatim = arg1->lineParts[0].verbatim + arg2->lineParts[0].verbatim;
					se.argtype = ARGTYPE::STRING;
					se.lineParts.push_back( lp );
				}
				else if ( arg1->argtype == ARGTYPE::NUMBER && arg2->argtype == ARGTYPE::NUMBER )
				{
					se.argtype = ARGTYPE::NUMBER;
					se.numberValue = arg1->numberValue + arg2->numberValue;
				}
				else
					assert( 0 ); // TODO: think about type conversions

				stack.pop_back();
				stack.pop_back();
				stack.push_back( std::move(se) );
				break;
			}
			case OPERATOR::OR:
			{
				assert( stack.size() >= 2 ); // TODO: it's a common check. Think about generalization
				StackElement se;
				auto arg1 = stack.begin() + stack.size() - 2;
				auto arg2 = stack.begin() + stack.size() - 1;
				if ( arg1->argtype == ARGTYPE::BOOL && arg2->argtype == ARGTYPE::BOOL )
				{
					se.argtype = ARGTYPE::BOOL;
					se.boolValue = arg1->boolValue || arg2->boolValue;
				}
				else
					assert( 0 ); // TODO: think about type conversions

				stack.pop_back();
				stack.pop_back();
				stack.push_back( std::move(se) );
				break;
			}
			case OPERATOR::AND:
			{
				assert( stack.size() >= 2 ); // TODO: it's a common check. Think about generalization
				StackElement se;
				auto arg1 = stack.begin() + stack.size() - 2;
				auto arg2 = stack.begin() + stack.size() - 1;
				if ( arg1->argtype == ARGTYPE::BOOL && arg2->argtype == ARGTYPE::BOOL )
				{
					se.argtype = ARGTYPE::BOOL;
					se.boolValue = arg1->boolValue && arg2->boolValue;
				}
				else
					assert( 0 ); // TODO: think about type conversions

				stack.pop_back();
				stack.pop_back();
				stack.push_back( std::move(se) );
				break;
			}
			case OPERATOR::GREATER:
			case OPERATOR::LESS:
			case OPERATOR::LEQ:
			case OPERATOR::GEQ:
			case OPERATOR::INCREMENT:
			case OPERATOR::SUBTR:
			case OPERATOR::DECREMENT:
			case OPERATOR::NOT:
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
	else if ( stack[0].argtype == ARGTYPE::NUMBER )
	{
		return stack[0].numberValue != 0;
	}
	else
	{
		// TODO: consider type conversion as a standard operation
		assert( ifNode.expression[0].argtype == ARGTYPE::STRING ); // limitation of a current version; TODO: further development
		string lstr = resolveLinePartsToString( ifNode.expression[0].lineParts );
		return !(lstr == "0" || lstr == "FALSE");
	}
}

bool TemplateInstantiator::applyIncludeNode( TemplateNode& node, bool isReturning )
{
	map<string, StackElement> resolvedParamPlaceholdersNew;
	TemplateRootNode* tn = prepareDataForTemplateInclusion( this, resolvedParamPlaceholdersNew, node, isReturning );
	map<string, StackElement> resolvedParamPlaceholdersIni( std::move(resolvedParamPlaceholders) );
	map<string, StackElement> resolvedLocalPlaceholdersIni( std::move(resolvedLocalPlaceholders) );
	resolvedParamPlaceholders = map<string, StackElement>( std::move(resolvedParamPlaceholdersNew) );
	bool ret = applyNode( *tn );
	// restore ini content of resolved params and locals
	resolvedParamPlaceholders = map<string, StackElement>( std::move(resolvedParamPlaceholdersIni) );
	resolvedLocalPlaceholders = map<string, StackElement>( std::move(resolvedLocalPlaceholdersIni) );

	return ret;
}

TemplateRootNode* TemplateInstantiator::prepareDataForTemplateInclusion( TemplateInstantiator* instantiator, map<string, StackElement>& resolvedParamPlaceholdersToUse, TemplateNode& node, bool isReturning )
{
	Stack stack;
	auto attr = node.attributes.find( {ATTRIBUTE::TEMPLATE, ""} );
	assert( attr != node.attributes.end() );
	auto& expr = attr->second;
	evaluateExpression( expr, stack );
	assert( stack.size() == 1 );
	assert( stack[0].argtype == ARGTYPE::STRING );
	string templateName = stack[0].lineParts[0].verbatim;

	TemplateRootNode* tn = templateSpace.getTemplate( templateName );
	if ( tn == nullptr )
	{
		assert( 0 ); // TODO: throw
	}
	if ( isReturning && (!tn->isFunction) ) // calling non-returning from returning is prohibited
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
			resolvedParamPlaceholdersToUse.insert( make_pair( it.first.ext, move(stack1[0]) ) );
		}
	return tn;
}

bool TemplateInstantiator::applyNode( TemplateRootNode& node )
{
	for ( auto& nodeIt: node.childNodes )
		if ( !applyNode( nodeIt ) )
			return false;
	return true;
}

bool TemplateInstantiator::applyNode( TemplateNode& node )
{
	switch ( node.type )
	{
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
			for ( auto& nodeIt: node.childNodes )
				if ( !applyNode( nodeIt ) )
				{
					assert( node.isReturning );
					return false;
				}
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
			for ( auto& nodeIt: node.childNodes )
				if ( !applyNode( nodeIt ) )
				{
					assert( node.isReturning );
					return false;
				}
			outstr = nullptr;
			break;
		}
		case NODE_TYPE::IF:
		{
			bool cond = calcConditionOfIfNode( node );
			assert( node.childNodes.size() >=1 && node.childNodes.size() <= 2 );
			if ( cond )					
			{
				if ( node.childNodes[0].type == NODE_TYPE::IF_TRUE_BRANCH )
				{
					if ( !applyNode( node.childNodes[0] ) )
					{
						assert( node.isReturning );
						return false;
					}
				}
			}
			else
			{
				bool applyRes = true; // NOTE: 'false' branche may or may not exist; no 'false' branche - no return from it
				if ( node.childNodes[0].type == NODE_TYPE::IF_FALSE_BRANCH )
					applyRes = applyNode( node.childNodes[0] );
				else if ( node.childNodes.size() == 2 && node.childNodes[1].type == NODE_TYPE::IF_FALSE_BRANCH )
					applyRes = applyNode( node.childNodes[1] );
				if ( !applyRes )
				{
					assert( node.isReturning );
					return false;
				}
			}
			break;
		}
		case NODE_TYPE::ASSERT:
		{
			bool cond = calcConditionOfIfNode( node );
			if ( !cond )					
			{
				string msg;
				// prepare msg string
				auto attr = node.attributes.find( {ATTRIBUTE::MSG, ""} );
				if ( attr != node.attributes.end() )
				{
					auto& expr = attr->second;
					Stack stack;
					evaluateExpression( expr, stack );
					assert( stack.size() == 1 );
					assert( stack[0].argtype == ARGTYPE::STRING );
					msg = stack[0].lineParts[0].verbatim;
					fmt::print("Instantiation Error: Assertion failed: Line {}, message: {}\n", node.srcLineNum, msg );
				}
				else
				{
					fmt::print("Instantiation Error: Assertion failed: Line {}\n", node.srcLineNum );
				}
			}
			break;
		}
		case NODE_TYPE::DBG_PRINT:
		{
			Stack stack;
			evaluateExpression( node.expression, stack );
			assert( stack.size() == 1 );
			if ( stack[0].argtype == ARGTYPE::STRING )
			{
				string msg = stack[0].lineParts[0].verbatim;
				fmt::print("Line {}: message: {}\n", node.srcLineNum, msg );
			}
			else
			{
				fmt::print("Line {}: message <Error: expression cannot be evaluated to string>\n", node.srcLineNum );
			}
			break;
		}
		case NODE_TYPE::RETURN:
		{
			Stack stack;
			evaluateExpression( node.expression, stack );
			assert( stack.size() == 1 );
			fromTemplate = stack[0];
			return false;
		}
		case NODE_TYPE::INCLUDE:
		{
			if ( !applyIncludeNode( node, false ) )
				return false;
			break;
		}
		case NODE_TYPE::LET:
		{
			auto attr = node.attributes.find( {ATTRIBUTE::TEMPLATE, ""} );
			if( attr != node.attributes.end() )
			{
				// We expect here a returning template that assumes no output
				// we need to check that it's a real case
				// TODO: generalization required!!!
				int currPos = ftell( outstr );
				applyIncludeNode( node, true );
				int newPos = ftell( outstr );
				assert( currPos == newPos );
			}

			// load resolved names, if any
			for ( const auto it:node.attributes )
				if ( it.first.id == ATTRIBUTE::LOCAL )
				{
					auto& expr1 = it.second;
					Stack stack;
					evaluateExpression( expr1, stack );
					assert( stack.size() == 1 );
					resolvedLocalPlaceholders.erase( it.first.ext );
					auto& insret = resolvedLocalPlaceholders.insert( make_pair( it.first.ext, std::move( stack[0] ) ) );
					assert( insret.second );
				}

			break;
		}
		case NODE_TYPE::FOR_EACH:
		{
			Stack stack;
			evaluateExpression( node.expression, stack );
			assert( stack.size() == 1 ); // TODO: error reporting
			assert( stack[0].argtype == ARGTYPE::ANY_LIST ); // TODO: error reporting
			assert( node.attributes.size() == 1 );
			auto& attr = node.attributes.begin();
			assert( attr->first.id == ATTRIBUTE::LOCAL );
			for ( auto& it:stack[0].anyList )
			{
				resolvedLocalPlaceholders.erase( attr->first.ext );
				auto& insret = resolvedLocalPlaceholders.insert( make_pair( attr->first.ext, it ) );
				for ( auto nodeit:node.childNodes )
					if ( !applyNode( nodeit ) )
					{
						assert( node.isReturning );
						return false;
					}
			}
			break;
		}
		case NODE_TYPE::WHILE:
		{
			for (;;)
			{
				Stack stack;
				evaluateExpression( node.expression, stack );
				assert( stack.size() == 1 ); // TODO: error reporting
				assert( stack[0].argtype == ARGTYPE::BOOL ); // TODO: error reporting
				if ( !stack[0].boolValue )
					break;
				for ( auto nodeit:node.childNodes )
					if ( !applyNode( nodeit ) )
					{
						assert( node.isReturning );
						return false;
					}
			}
			break;
		}
		default:
		{
			fmt::print("Unexpected node type {} found\n", static_cast<int>(node.type) );
			assert( 0 == "ERROR: UNEXPECTED" );
		}
	}

	return true;
}

TemplateInstantiator::StackElement TemplateInstantiator::placeholder( SpecialName ph )
{
	if ( ph.id == PLACEHOLDER::PARAM_MINUS )
	{
		auto findres = resolvedParamPlaceholders.find( ph.specific );
		if ( findres != resolvedParamPlaceholders.end() )
//			return move(findres->second);
			return findres->second;
	}
	else if ( ph.id == PLACEHOLDER::LOCAL_MINUS )
	{
		auto findres = resolvedLocalPlaceholders.find( ph.specific );
		if ( findres != resolvedLocalPlaceholders.end() )
//			return move(findres->second);
			return findres->second;
	}
	else if ( ph.id == PLACEHOLDER::FROM_TEMPLATE )
	{
		return fromTemplate;
	}

	fmt::print( "\n" );
	fmt::print("error_placeholder {}\n", static_cast<int>(ph.id) );
	assert( 0 );
	StackElement se;
	return move(se);
}

string TemplateInstantiator::context()
{
//	fmt::print( "\n" );
//	fmt::print("error: context() available\n" );
//	assert( 0 );
	return "";
}


/////////////////////////////////////////////////////////////////////////


void processStructures( BackRoot& structure, TemplateNodeSpace& templateSpace )
{
	TemplateInstantiator ti( templateSpace, nullptr );
	TemplateRootNode* mainT = templateSpace.getTemplate( "MAIN" );
	if ( mainT != nullptr )
	{
		RootExpressionObject rtif( structure, templateSpace, nullptr );
		TemplateInstantiator::StackElement se;
		se.argtype = ARGTYPE::OBJPTR;
		se.singleObject.reset( rtif.clone() );
		ti.resolvedParamPlaceholders.insert( make_pair( "ROOT", se ) );
		ti.applyNode( *mainT );
	}
}
