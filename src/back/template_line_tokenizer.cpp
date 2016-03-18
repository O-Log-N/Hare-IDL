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

void readLineParts( const string& line, size_t& currentPos, vector<LinePart>& parts, string terminator = "" )
{
	// we have to go char by char; if '@' is found, make sure it's not a placeholder, or replace it accordingly
	LinePart part;
	size_t sz = line.size();
	part.type = PLACEHOLDER::VERBATIM;
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
			Placeholder placehldr = parsePlaceholder( line, currentPos );
			if ( placehldr.id == PLACEHOLDER::VERBATIM )
			{
				part.verbatim.push_back( line[ currentPos ] ); 
				++currentPos; 
			}
			else
			{
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
		}
	}
	while ( currentPos < sz );

	if ( part.verbatim.size() )
	{
		assert( part.type == PLACEHOLDER::VERBATIM );
		parts.push_back( part ); 
	}
}

void parseExpression( const string& line, size_t& currentPos, vector<ExpressionElement>& expression, int currentLineNum )
{
	size_t sz = line.size();
	vector<ExpressionElement> postfixOperations;
	for ( ; currentPos<sz; )
	{
		if ( line[currentPos] == '\"' ) // beginning of a string; an argument; to be pushed
		{
			++currentPos;
			ExpressionElement elem;
			elem.oper = OPERATOR::PUSH;
			elem.argtype = ARGTYPE::STRING;
			readLineParts( line, currentPos, elem.lineParts, "\"" );
			if ( line[currentPos] != '\"' )
			{
				fmt::print( "line {}: error: string runs away (lost terminating '\"')\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			++currentPos; // for terminating '"'
			expression.push_back( elem );
			skipSpaces( line, currentPos );
			while ( postfixOperations.size() )
			{
				expression.push_back( postfixOperations.back() );
				postfixOperations.pop_back();
			}
		}
		else if ( line[currentPos] == '(' )
		{
			++currentPos;
			skipSpaces( line, currentPos );
			parseExpression( line, currentPos, expression, currentLineNum );
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
			string num = readIntegralNumericalLiteral( line, currentPos );
			assert( 0 ); //TODO: need to define an exact processing
		}
		else if ( ( line[currentPos] >= 'a' && line[currentPos] <= 'z' ) || 
			      ( line[currentPos] >= 'A' && line[currentPos] <= 'Z' ) )
		{
			PredefindedFunction fn = parsePredefinedFunction( line, currentPos );
			if ( fn.id == PREDEFINED_FUNCTION::NOT_A_FUNCTION )
			{
/*				string unknown = readIdentifier( line, currentPos );
				fmt::print( "line {}:  unexpected token {}\n", currentLineNum, unknown );
				assert( 0 ); // TODO: throw*/
				return;
			}
			skipSpaces( line, currentPos );
			if ( line[currentPos] != '(' )
			{
				fmt::print( "line {}:  unexpected '('\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			++currentPos; // for opening '('
			ExpressionElement fncall;
			fncall.oper = OPERATOR::CALL;
			fncall.fnCallID = fn.id;
			postfixOperations.push_back( fncall );
			size_t inisz = expression.size();
			skipSpaces( line, currentPos );
			parseExpression( line, currentPos, expression, currentLineNum );
			if ( line[currentPos] != ')' )
			{
				fmt::print( "line {}: error: ')' expected\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			++currentPos; // for terminating ')'
			skipSpaces( line, currentPos );
			size_t newsz = expression.size();
			// quick sanity check for arg'less function
			// TODO: indeed, we can calculate a number of actually supplied args
			if ( fn.argC == 0 && inisz != newsz )
			{
				fmt::print( "line {}: function {} takes {} arguments\n", currentLineNum, functionNameToString( fn.id ), fn.argC );
				assert( 0 ); // TODO: throw
			}
			skipSpaces( line, currentPos );
			while ( postfixOperations.size() )
			{
				expression.push_back( postfixOperations.back() );
				postfixOperations.pop_back();
			}
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
	readLineParts( line, currentPos, arg.lineParts );
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

	for( ;;) // through all nodes, find template beginning
	{
//		fmt::print( "line {}\n", currentLineNum );
		string line;
		TemplateLine tl;
		tl.srcLineNum = currentLineNum;
		if ( !readLine( tf, line, currentLineNum ) )
			return false; // no more lines

		size_t pos = 0;
		KeyWordProps props = getLineType( line, pos );
//		tl.type = getLineType( line, pos );
		tl.type = props.id;

		if ( tl.type == TemplateLine::LINE_TYPE::CONTENT )
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
		else
		{
			if ( tl.type == TemplateLine::LINE_TYPE::BEGIN_TEMPLATE )
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
			if ( tl.type == TemplateLine::LINE_TYPE::END_TEMPLATE )
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
