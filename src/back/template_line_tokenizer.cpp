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

#include "template_line_tokenizer.h"
#include "template_line_tokens.h"
#include <assert.h> // for assert()

void findSpaces( const string& line, size_t& contentStart )
{
	while ( contentStart < line.size() && (!(line[contentStart] == ' ' || line[contentStart] == '\t')) ) contentStart++;
}

bool readLine( FILE* tf, string& line, int& currentLineNum )
{
	bool somethingFound = false;
	for(;;) // through all chars - just read the line
	{
		char ch;
		size_t readret = fread( &ch, 1, 1, tf );
		if ( readret == 0 )
			break;
		somethingFound = true;
		if ( ch == '\n' )
		{
			++currentLineNum;
			break;
		}
		line.push_back( ch );
	}
	while ( line.size() && *(line.end()-1) == '\r' )
		line.pop_back();
	return somethingFound;
}

void parseExpression( const string& line, size_t& currentPos, vector<ExpressionElement>& expression, int currentLineNum );

void readLineParts( const string& line, size_t& currentPos, vector<LinePart2>& parts, int currentLineNum, string terminator = "" )
{
	// we have to go char by char; if '@' is found, make sure it's not a placeholder, or replace it accordingly
	LinePart2 part;
	size_t sz = line.size();
//	part.type = PLACEHOLDER::VERBATIM;
	part.isVerbatim = true;
	do
	{
		if ( terminator.size() )
		{
			bool terminal = false; 
			size_t inTerm = 0; 
			while ( inTerm < terminator.size() ) if ( terminator[inTerm++] == line[currentPos] ) {terminal = true; break;}
			if ( terminal )
				break;
		}
		if ( line[ currentPos ] != '@' )
		{
			part.verbatim.push_back( line[ currentPos ] );
			++currentPos;
		}
		else
		{
			++currentPos;
#if 0
			SpecialName placehldr = parsePlaceholder( line, currentPos );
			if ( placehldr.id == PLACEHOLDER::VERBATIM )
			{
				part.verbatim.push_back( '@' ); 
			}
			else if ( line[ currentPos ] == '@' )
			{
				++currentPos; //for terminating @
				assert( part.type == PLACEHOLDER::VERBATIM );
				if ( part.verbatim.size() )
					parts.push_back( part ); 
				part.verbatim.clear(); 
				part.type = placehldr.id; 
				part.verbatim = placehldr.specific;
				parts.push_back( part ); 
				part.type = PLACEHOLDER::VERBATIM; 
				part.verbatim.clear(); 
			}
			else
			{
				part.verbatim.push_back( '@' ); 
			}
#else
			assert( part.isVerbatim );
			if ( part.verbatim.size() )
				parts.push_back( part ); 
			part.verbatim.clear(); 
			part.isVerbatim = false;
			parseExpression( line, currentPos, part.expr, currentLineNum );
			skipSpaces( line, currentPos );
			if ( line[ currentPos ] != '@' )
			{
				fmt::print( "line {}: cannot parse embedded expression\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			++currentPos; //for terminating @
			parts.push_back( part ); 
			part.isVerbatim = true; // restore
			part.expr.clear(); 
#endif // 0
		}
	}
	while ( currentPos < sz );

	if ( part.verbatim.size() )
	{
//		assert( part.type == PLACEHOLDER::VERBATIM );
		assert( part.isVerbatim );
		parts.push_back( part ); 
	}
}

int readFunctionArguments( const string& line, size_t& currentPos, vector<ExpressionElement>& expression, int currentLineNum )
{
	int argCnt = 0;
	size_t iniExprSz;
	char terminator;
	bool afterComma = false;
	do
	{
		skipSpaces( line, currentPos );
		iniExprSz = expression.size();
		vector<ExpressionElement> expression2;
		parseExpression( line, currentPos, expression2, currentLineNum );
		if ( expression2.size() == 0 && afterComma )
		{
			fmt::print( "line {}:  expression expected after ','\n", currentLineNum );
			assert( 0 ); // TODO: throw
		}
		for ( auto eit:expression2 )
			expression.push_back( eit );
		skipSpaces( line, currentPos );
		if ( expression.size() > iniExprSz )
			++argCnt;
		terminator = line[currentPos++];
		afterComma = true;
	}
	while ( terminator == ',' );
	if ( terminator != ')' )
	{
		fmt::print( "line {}: error: ')' expected\n", currentLineNum );
		assert( 0 ); // TODO: throw
	}
	skipSpaces( line, currentPos );
	return argCnt;
}

bool parseIdentifier( const string& line, size_t& currentPos, vector<ExpressionElement>& expression, int currentLineNum, vector<ExpressionElement>& postfixOperations, size_t prevPos, bool memberFnCallExpected )
{
		if ( ( line[currentPos] >= 'a' && line[currentPos] <= 'z' ) || 
			      ( line[currentPos] >= 'A' && line[currentPos] <= 'Z' ) ||
			        line[currentPos] == '_' )
		{
			// we expect a predefined function or a PARAM- or LOCAL- placeholder here
			PredefindedFunction fn = parsePredefinedFunction( line, currentPos );
			if ( fn.id == PREDEFINED_FUNCTION::NOT_A_BUILTIN_FUNCTION )
			{
				if ( memberFnCallExpected )
				{
					fmt::print( "line {}: function call expected\n", currentLineNum );
					assert( 0 ); // TODO: throw
				}
				SpecialName ph =parseStandardName( line, currentPos );
				if ( ph.id == PLACEHOLDER::PARAM_MINUS || ph.id == PLACEHOLDER::LOCAL_MINUS )
				{
					ExpressionElement elem;
					elem.oper = OPERATOR::PUSH;
					elem.argtype = ARGTYPE::PLACEHOLDER;
					elem.ph = ph;
//					if ( expression.size() && expression.back().oper == OPERATOR::PUSH && postfixOperations.size() == 0 ) // two elements to push without an operator in between
					if ( expression.size() && postfixOperations.size() == 0 ) // PUSH command to non-empty stack without an operator of fn call
					{
						currentPos = prevPos;
						return false;
					}
					expression.push_back( elem );
					while ( postfixOperations.size() )
					{
						expression.push_back( postfixOperations.back() );
						postfixOperations.pop_back();
					}
					skipSpaces( line, currentPos );
				}
				else if ( ph.id == PLACEHOLDER::FUNCTION_MINUS ) // user-defined function
				{
					if ( memberFnCallExpected )
					{
						fmt::print( "line {}: function {} cannot be called with respect to an object\n", currentLineNum, standardNameToString( ph ) );
						assert( 0 ); // TODO: throw
						return false;
					}
					skipSpaces( line, currentPos );
					if ( line[currentPos] != '(' )
					{
						fmt::print( "line {}:  expected '('\n", currentLineNum );
						assert( 0 ); // TODO: throw
					}
					++currentPos; // for opening '('
					ExpressionElement fncall;
					fncall.oper = OPERATOR::CALL_USERDEF_FN;
					fncall.userDefFunction = ph;
					postfixOperations.push_back( fncall );
					skipSpaces( line, currentPos );
				}
				else if ( ph.id != PLACEHOLDER::VERBATIM )
				{
					// TODO: is it good to do the same with all placeholders?
					ExpressionElement elem;
					elem.oper = OPERATOR::PUSH;
					elem.argtype = ARGTYPE::PLACEHOLDER;
					elem.ph = ph;
//					if ( expression.size() && expression.back().oper == OPERATOR::PUSH && postfixOperations.size() == 0 ) // two elements to push without an operator in between
					if ( expression.size() && postfixOperations.size() == 0 ) // PUSH command to non-empty stack without an operator of fn call
					{
						currentPos = prevPos;
						return false;
					}
					expression.push_back( elem );
					while ( postfixOperations.size() )
					{
						expression.push_back( postfixOperations.back() );
						postfixOperations.pop_back();
					}
					skipSpaces( line, currentPos );
				}
				else
				{
	/*				string unknown = readIdentifier( line, currentPos );
					fmt::print( "line {}:  unexpected token {}\n", currentLineNum, unknown );
					assert( 0 ); // TODO: throw*/
					return false;
				}
			}
			else
			{
				if ( memberFnCallExpected )
				{
					if ( !fn.isMember )
					{
						fmt::print( "line {}: function {} cannot be called with respect to an object\n", currentLineNum, functionNameToString( fn.id ) );
						assert( 0 ); // TODO: throw
						return false;
					}
				}
				else
				{
					if ( fn.isMember )
					{
						fmt::print( "line {}: function {} can be called with respect to an object only\n", currentLineNum, functionNameToString( fn.id ) );
						assert( 0 ); // TODO: throw
						return false;
					}
				}
				skipSpaces( line, currentPos );
				if ( line[currentPos] != '(' )
				{
					fmt::print( "line {}:  expected '('\n", currentLineNum );
					assert( 0 ); // TODO: throw
				}
				++currentPos; // for opening '('
				ExpressionElement fncall;
				fncall.oper = OPERATOR::CALL_BUILTIN_FN;
				fncall.fn = fn;
				postfixOperations.push_back( fncall );
				skipSpaces( line, currentPos );
#if 0
				int argCnt = 0;
				size_t iniExprSz;
				char terminator;
				bool afterComma = false;
				do
				{
					skipSpaces( line, currentPos );
					iniExprSz = expression.size();
					vector<ExpressionElement> expression2;
					parseExpression( line, currentPos, expression2, currentLineNum );
					if ( expression2.size() == 0 && afterComma )
					{
						fmt::print( "line {}:  expression expected after ','\n", currentLineNum );
						assert( 0 ); // TODO: throw
					}
					for ( auto eit:expression2 )
						expression.push_back( eit );
					skipSpaces( line, currentPos );
					if ( expression.size() > iniExprSz )
						++argCnt;
					terminator = line[currentPos++];
					afterComma = true;
				}
				while ( terminator == ',' );
				if ( terminator != ')' )
				{
					fmt::print( "line {}: error: ')' expected\n", currentLineNum );
					assert( 0 ); // TODO: throw
				}
				skipSpaces( line, currentPos );
#else
				int argCnt = readFunctionArguments( line, currentPos, expression, currentLineNum );
#endif
				// quick sanity check for arg'less function
				// TODO: indeed, we can calculate a number of actually supplied args
				if ( fn.argC != argCnt )
				{
					fmt::print( "line {}: function {} takes {} arguments ({} actually supplied)\n", currentLineNum, functionNameToString( fn.id ), fn.argC, argCnt );
					assert( 0 ); // TODO: throw
				}
				while ( postfixOperations.size() )
				{
					expression.push_back( postfixOperations.back() );
					postfixOperations.pop_back();
				}
			}
		}
		else
		{
			assert( 0 == "Identifier is expected" );
		}

		return true;
}

void parseExpression( const string& line, size_t& currentPos, vector<ExpressionElement>& expression, int currentLineNum )
{
	size_t sz = line.size();
	vector<ExpressionElement> postfixOperations;
	size_t prevPos;
	OPERATOR lastOperator = OPERATOR::INVALID;
	bool memberFnCallExpected = false;
	for ( ; currentPos<sz; )
	{
		prevPos = currentPos;
		if ( line[currentPos] == '\"' ) // beginning of a string; an argument; to be pushed
		{
			++currentPos;
			ExpressionElement elem;
			elem.oper = OPERATOR::PUSH;
			elem.argtype = ARGTYPE::STRING;
			readLineParts( line, currentPos, elem.lineParts, currentLineNum, "\"" );
			if ( line[currentPos] != '\"' )
			{
				fmt::print( "line {}: error: string runs away (lost terminating '\"')\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			++currentPos; // for terminating '"'
//			if ( expression.size() && expression.back().oper == OPERATOR::PUSH && postfixOperations.size() == 0 ) // two elements to push without an operator in between
			if ( expression.size() && postfixOperations.size() == 0 ) // PUSH command to non-empty stack without an operator of fn call
			{
				currentPos = prevPos;
				return;
			}
			expression.push_back( elem );
			skipSpaces( line, currentPos );
			while ( postfixOperations.size() )
			{
				expression.push_back( postfixOperations.back() );
				postfixOperations.pop_back();
			}
		}
		else if ( line[currentPos] == '.' )
		{
			if ( expression.size() == 0 )
			{
				fmt::print( "line {}: error: operator \'.\' can follow an object or an expression that can be evaluated to an object only\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			++currentPos;
			skipSpaces( line, currentPos );
			if ( !parseIdentifier( line, currentPos, expression, currentLineNum, postfixOperations, prevPos, true ) )
				return;
		}
		else if ( line[currentPos] == '(' )
		{
			++currentPos;
			skipSpaces( line, currentPos );
			vector<ExpressionElement> expression2;
			parseExpression( line, currentPos, expression2, currentLineNum );
			if ( expression2.size() == 0 )
			{
				fmt::print( "line {}:  expression expected after '('\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			for ( auto eit:expression2 )
				expression.push_back( eit );
			if ( line[currentPos] != ')' )
			{
				fmt::print( "line {}: error: ')' expected\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			++currentPos; // for terminating ')'
			skipSpaces( line, currentPos );
			while ( postfixOperations.size() )
			{
				expression.push_back( postfixOperations.back() );
				postfixOperations.pop_back();
			}
		}
		else if ( line[currentPos] >= '0' && line[currentPos] <= '9' )
		{
			ExpressionElement elem;
			elem.oper = OPERATOR::PUSH;
			elem.argtype = ARGTYPE::NUMBER;
			string num = readIntegralNumericalLiteral( line, currentPos );
			elem.numberValue = atoi( num.c_str() );
//			if ( expression.size() && expression.back().oper == OPERATOR::PUSH && postfixOperations.size() == 0 ) // two elements to push without an operator in between
			if ( expression.size() && postfixOperations.size() == 0 ) // PUSH command to non-empty stack without an operator of fn call
			{
				currentPos = prevPos;
				return;
			}
			expression.push_back( elem );
			while ( postfixOperations.size() )
			{
				expression.push_back( postfixOperations.back() );
				postfixOperations.pop_back();
			}
			skipSpaces( line, currentPos );
			//TODO: THINK ABOUT ADDING FLOATING POINT
		}
		else if ( ( line[currentPos] >= 'a' && line[currentPos] <= 'z' ) || 
			      ( line[currentPos] >= 'A' && line[currentPos] <= 'Z' ) ||
			        line[currentPos] == '_' )
		{
#if 0
			// we expect a predefined function or a PARAM- or LOCAL- placeholder here
			PredefindedFunction fn = parsePredefinedFunction( line, currentPos );
			if ( fn.id == PREDEFINED_FUNCTION::NOT_A_BUILTIN_FUNCTION )
			{
				SpecialName ph =parsePlaceholder( line, currentPos );
				if ( ph.id == PLACEHOLDER::PARAM_MINUS || ph.id == PLACEHOLDER::LOCAL_MINUS )
				{
					ExpressionElement elem;
					elem.oper = OPERATOR::PUSH;
					elem.argtype = ARGTYPE::PLACEHOLDER;
					elem.ph = ph;
//					if ( expression.size() && expression.back().oper == OPERATOR::PUSH && postfixOperations.size() == 0 ) // two elements to push without an operator in between
					if ( expression.size() && postfixOperations.size() == 0 ) // PUSH command to non-empty stack without an operator of fn call
					{
						currentPos = prevPos;
						return;
					}
					expression.push_back( elem );
					while ( postfixOperations.size() )
					{
						expression.push_back( postfixOperations.back() );
						postfixOperations.pop_back();
					}
					skipSpaces( line, currentPos );
				}
				else if ( ph.id != PLACEHOLDER::VERBATIM )
				{
					// TODO: is it good to do the same with all placeholders?
					ExpressionElement elem;
					elem.oper = OPERATOR::PUSH;
					elem.argtype = ARGTYPE::PLACEHOLDER;
					elem.ph = ph;
//					if ( expression.size() && expression.back().oper == OPERATOR::PUSH && postfixOperations.size() == 0 ) // two elements to push without an operator in between
					if ( expression.size() && postfixOperations.size() == 0 ) // PUSH command to non-empty stack without an operator of fn call
					{
						currentPos = prevPos;
						return;
					}
					expression.push_back( elem );
					while ( postfixOperations.size() )
					{
						expression.push_back( postfixOperations.back() );
						postfixOperations.pop_back();
					}
					skipSpaces( line, currentPos );
				}
				else
				{
	/*				string unknown = readIdentifier( line, currentPos );
					fmt::print( "line {}:  unexpected token {}\n", currentLineNum, unknown );
					assert( 0 ); // TODO: throw*/
					return;
				}
			}
			else
			{
				skipSpaces( line, currentPos );
				if ( line[currentPos] != '(' )
				{
					fmt::print( "line {}:  expected '('\n", currentLineNum );
					assert( 0 ); // TODO: throw
				}
				++currentPos; // for opening '('
				ExpressionElement fncall;
				fncall.oper = OPERATOR::CALL;
				fncall.fnCallID = fn.id;
				postfixOperations.push_back( fncall );
				skipSpaces( line, currentPos );
				int argCnt = 0;
				size_t iniExprSz;
				char terminator;
				bool afterComma = false;
				do
				{
					skipSpaces( line, currentPos );
					iniExprSz = expression.size();
					vector<ExpressionElement> expression2;
					parseExpression( line, currentPos, expression2, currentLineNum );
					if ( expression2.size() == 0 && afterComma )
					{
						fmt::print( "line {}:  expression expected after ','\n", currentLineNum );
						assert( 0 ); // TODO: throw
					}
					for ( auto eit:expression2 )
						expression.push_back( eit );
					skipSpaces( line, currentPos );
					if ( expression.size() > iniExprSz )
						++argCnt;
					terminator = line[currentPos++];
					afterComma = true;
				}
				while ( terminator == ',' );
				if ( terminator != ')' )
				{
					fmt::print( "line {}: error: ')' expected\n", currentLineNum );
					assert( 0 ); // TODO: throw
				}
				skipSpaces( line, currentPos );
				// quick sanity check for arg'less function
				// TODO: indeed, we can calculate a number of actually supplied args
				if ( fn.argC != argCnt )
				{
					fmt::print( "line {}: function {} takes {} arguments ({} actually supplied)\n", currentLineNum, functionNameToString( fn.id ), fn.argC, argCnt );
					assert( 0 ); // TODO: throw
				}
				skipSpaces( line, currentPos );
				while ( postfixOperations.size() )
				{
					expression.push_back( postfixOperations.back() );
					postfixOperations.pop_back();
				}
			}
#else
			if ( !parseIdentifier( line, currentPos, expression, currentLineNum, postfixOperations, prevPos, false ) )
				return;
#endif // 0
		}
		else
		{
			PredefindedOperator oper = parsePredefinedOperator( line, currentPos );
			if ( oper.id == OPERATOR::INVALID )
			{
/*				string unknown;
				while ( currentPos < line.size() && currentPos < 4 ) unknown.push_back( line[currentPos++] );
				fmt::print( "line {}:  unrecognized sequence {}\n", currentLineNum, unknown );
				assert( 0 ); // TODO: throw*/
				return;
			}

			ExpressionElement opercall;
			opercall.oper = oper.id;
			if ( lastOperator != OPERATOR::INVALID && lastOperator != opercall.oper )
			{
				fmt::print( "line {}: '(' and ')' must be used to void issues with operator precedence\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			lastOperator = opercall.oper;
			postfixOperations.push_back( opercall );
			skipSpaces( line, currentPos );
		}
	}
}

void formVerbatimLine( const string& line, TemplateLine& tl, int currentLineNum )
{
	// NOTE: when parsed verbatim line is treated as a set of line parts, not an expression
	//       (as otherwise we would require to enclose it in "")
	tl.type = TemplateLine::LINE_TYPE::CONTENT;
	size_t currentPos = 0;
	ExpressionElement arg;
	arg.oper = OPERATOR::PUSH;
	arg.argtype = ARGTYPE::STRING;
	readLineParts( line, currentPos, arg.lineParts, currentLineNum );
	vector<ExpressionElement> expression;
	expression.push_back( arg );
	
	tl.attributes.insert( make_pair(AttributeName(ATTRIBUTE::TEXT, ""), expression ) );
}

KeyWordProps getLineType( const string& line, size_t& pos )
{
	skipSpaces( line, pos );
	return parseMainKeyword( line, pos );
}

void readAttributeName( const string& line, size_t& pos, AttributeName& attrName, int currentLineNum )
{
	size_t sz = line.size();
	skipSpaces( line, pos );
	attrName = parseParam( line, pos );
}

void readAttributeValue( const string& line, size_t& currentPos, vector<ExpressionElement>& expression, int currentLineNum )
{
	// this call should be done only if a value is expected ( attribute nabe is followed by '=')
	size_t sz = line.size();
	skipSpaces( line, currentPos );
	if ( currentPos == sz )
	{
		fmt::print( "line {}: error: attribute value is expected\n", currentLineNum );
		assert( 0 ); // TODO: throw
	}
	parseExpression( line, currentPos, expression, currentLineNum );
}

void readNextParam( const string& line, size_t& pos, TemplateLine& tl, int currentLineNum )
{
	size_t sz = line.size();
	AttributeName attrName;
	readAttributeName( line, pos, attrName, currentLineNum );
	if ( attrName.id == ATTRIBUTE::NONE )
	{
		fmt::print( "line {}: error: unexpected tokens at the end of line\n", currentLineNum );
		assert( 0 ); // TODO: throw
	}
	skipSpaces( line, pos );
	if ( pos == sz )
	{
		vector<ExpressionElement> expression;
		tl.attributes.insert( make_pair(attrName, expression ) );
		return;
	}

	if ( line[ pos ] == '=' )
	{
		++pos;
		vector<ExpressionElement> expression;
		readAttributeValue( line, pos, expression, currentLineNum );
		tl.attributes.insert( make_pair(attrName, expression ) );
	}
	else
	{
		vector<ExpressionElement> expression;
		tl.attributes.insert( make_pair(attrName, expression ) );
	}

}

void readAttributes( const string& line, size_t& pos, TemplateLine& tl, int currentLineNum )
{
	// attributes (with, potentially, their values) are the rest of the line
	size_t sz = line.size();
	skipSpaces( line, pos );
	while ( pos != sz )
	{
		readNextParam( line, pos, tl, currentLineNum );
		skipSpaces( line, pos );
	}
}

bool tokenizeTemplateLines( FILE* tf, vector<TemplateLine>& templateLines, int& currentLineNum )
{
	bool startFound = false;

	string line, nextLine;
	bool useNext = false;
	for( ;;)
	{
		TemplateLine tl;
		tl.srcLineNum = currentLineNum;

		line.clear();
		if ( useNext )			
		{
			line.swap( nextLine );
			useNext = false;
		}
		else
		{
			if ( !readLine( tf, line, currentLineNum ) )
				return false; // no more lines
		}
		for (;;)
		{
			bool readOK = readLine( tf, nextLine, currentLineNum );
			if ( !readOK )
				break;
			size_t pos = 0;
			KeyWordProps props = getLineType( nextLine, pos );
			if ( props.id == TemplateLine::LINE_TYPE::CONTINUED_LINE )
			{
				line.append( nextLine.substr( pos ) );
				nextLine.clear();
			}
			else
			{
				useNext = true;
				break;
			}
		}

		size_t pos = 0;
		KeyWordProps props = getLineType( line, pos );
		tl.type = props.id;

		if ( tl.type == TemplateLine::LINE_TYPE::COMMENTED_LINE )
		{
			continue;
		}
		else if ( tl.type == TemplateLine::LINE_TYPE::CONTENT )
		{
			if ( !startFound )
			{
				pos = 0;
				skipSpaces( line, pos );
				if ( pos == line.size() ) // OK, just no content
					continue;
				else
				{
					fmt::print( "line {}: error: unexpected tokens beyond templates\n", currentLineNum );
					assert( 0 ); // TODO: throw
				}
			}
			formVerbatimLine( line, tl, currentLineNum );
			templateLines.push_back( tl );
			continue;
		}
		else if ( tl.type == TemplateLine::LINE_TYPE::FOR_EACH )
		{
			if ( !startFound )
			{
				fmt::print( "line {}: error: unexpected tokens beyond templates\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			skipSpaces( line, pos );

			size_t sz = line.size();
			AttributeName attrName;
			readAttributeName( line, pos, attrName, currentLineNum );
			skipSpaces( line, pos );
			if ( attrName.id == ATTRIBUTE::END )
			{
				if ( pos != sz )
				{
					fmt::print( "line {}: error: unexpected tokens following {}\n", currentLineNum, attributeNameToString( ATTRIBUTE::END ) );
					assert( 0 ); // TODO: throw
				}
				vector<ExpressionElement> expr;
				tl.attributes.insert( make_pair(attrName, expr ) );
				templateLines.push_back( tl );
				continue;
			}
			if ( attrName.id != ATTRIBUTE::LOCAL )
			{
				fmt::print( "line {}: error: name of variable is expected\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			vector<ExpressionElement> expr;
			tl.attributes.insert( make_pair(attrName, expr ) );
			skipSpaces( line, pos );
			if ( pos == sz )
			{
				fmt::print( "line {}: error: IN <expression> is expected\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}

			AttributeName nameIN = parseParam( line, pos );
			if ( nameIN.id != ATTRIBUTE::IN )
			{
				fmt::print( "line {}: error: IN <expression> is expected\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}

			readAttributeValue( line, pos, tl.expression, currentLineNum );
			skipSpaces( line, pos );
			if ( pos != sz )
			{
				fmt::print( "line {}: error: unexpected tokens following following expression\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}

			templateLines.push_back( tl );
			continue;
		}
		else
		{
			if ( tl.type == TemplateLine::LINE_TYPE::BEGIN_TEMPLATE || tl.type == TemplateLine::LINE_TYPE::BEGIN_FUNCTION )
				startFound = true;
			if ( !startFound )
			{
				fmt::print( "line {}: error: unexpected tokens beyond templates\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			if ( props.expressionRequired )
				parseExpression( line, pos, tl.expression, currentLineNum );
			readAttributes( line, pos, tl, currentLineNum );
			templateLines.push_back( tl );
			if ( tl.type == TemplateLine::LINE_TYPE::END_TEMPLATE || tl.type == TemplateLine::LINE_TYPE::BEGIN_FUNCTION )
				return true;
		}
	}
	return true;
}

#if 0
// let the code be compilable
bool loadTemplates( istream& tf, TemplateNodeSpace& nodeSpace, int& currentLineNum ) 
{
	bool ret;
	do
	{
		vector<TemplateLine> templateLines;
		ret = tokenizeTemplateLines( tf, templateLines, currentLineNum );
	}
	while ( ret );
	return ret;
}
void dbgPrintTemplateTrees( TemplateNodeSpace& nodeSpace ){}
#endif
