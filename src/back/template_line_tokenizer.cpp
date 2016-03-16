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

bool readLine( istream& tf, string& line, int& currentLineNum )
{
	bool somethingFound = false;
	for(;;) // through all chars - just read the line
	{
		char ch;
		tf.read( &ch, 1);
		if ( !tf )
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
				break;
			}
			else
			{
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

void y( const string& line, size_t& currentPos, vector<LinePart>& parts )
{
	switch ( line[currentPos] )
	{
		case '\"':
		{
		}
	}
}

void parseExpression( const string& line, size_t& currentPos, vector<ExpressionElement>& expression, int currentLineNum )
{
	size_t sz = line.size();
	for ( ; currentPos<sz; )
	{
		if ( line[currentPos] == '\"' )
		{
			vector<LinePart> parts;
			readLineParts( line, currentPos, parts, "\"" );
			if ( line[currentPos] != '\"' )
			{
				fmt::print( "line {}: error: string runs away (lost terminating '\"')\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			++currentPos; // for terminating '"'
		}
		else if ( line[currentPos] == '(' )
		{
			skipSpaces( line, currentPos );
			parseExpression( line, currentPos, expression, currentLineNum );
			if ( line[currentPos] != ')' )
			{
				fmt::print( "line {}: error: ')' expected\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			++currentPos; // for terminating '"'
		}
		else if ( line[currentPos] >= '0' && line[currentPos] <= '9' )
		{
			string num = readIntegralNumericalLiteral( line, currentPos );
		}
		else if ( ( line[currentPos] >= 'a' && line[currentPos] <= 'z' ) || 
			      ( line[currentPos] >= 'A' && line[currentPos] <= 'Z' ) )
		{
			PredefindedFunction fn = parsePredefinedFunction( line, currentPos );
			if ( fn.id == PREDEFINED_FUNCTION::NOT_A_FUNCTION )
			{
				string unknown = readIdentifier( line, currentPos );
				fmt::print( "line {}:  unexpected token {}\n", currentLineNum, unknown );
				assert( 0 ); // TODO: throw
			}
			if ( fn.argC == 0 )
			{
				skipSpaces( line, currentPos );
			}
			else
				for ( size_t i=0; i<fn.argC; ++i )
				{
					skipSpaces( line, currentPos );
				}
			// todo: push, ...
		}
	}
}

void formVerbatimLine( const string& line, TemplateLine& tl )
{
	assert( line.compare( 0, 2, "@@" ) != 0 );
	tl.type = TemplateLine::LINE_TYPE::CONTENT;
	vector<LinePart> parts;
	size_t currentPos = 0;
	readLineParts( line, currentPos, parts );

	tl.attributes.insert( make_pair(AttributeName(ATTRIBUTE::TEXT, ""), parts ) );
//	tl.attributes.insert( map<ATTRIBUTE, string>::value_type(ATTRIBUTE::TEXT, "her") );
}

//TemplateLine::LINE_TYPE getLineType( const string& line, size_t& pos )
KeyWordProps getLineType( const string& line, size_t& pos )
{
	skipSpaces( line, pos );
	return parseMainKeyword( line, pos );
}

void readExpression( const string& line, size_t& pos, vector<ExpressionElement>& expression, int currentLineNum )
{
	// expressions are always in ()
	// expression elements:
	// numbers (so far not supported)
	// strings in "" 
	// placeholders
	// (, ) (so far not supported)
	// ==, != (so far), other (later)

	// note: here we implement quite a simple version working with elementary expressions of one or two args and == and != operators in between where applicable
	// TODO: full implementation
	if ( line[pos] != '(' )
	{
		fmt::print( "line {}: error: '(' is expected;\n", currentLineNum );
		assert( 0 ); // TODO: throw
	}
	++pos;

	// we have to go char by char; if '@' is found, make sure it's not a placeholder, or replace it accordingly
	size_t sz = line.size();
	ExpressionElement element;
	element.oper = ExpressionElement::OPERATION::PUSH;
	element.argtype = ExpressionElement::ARGTYPE::STRING;
	skipSpaces( line, pos );
	while ( pos < sz )
	{
		if ( line[ pos ] == '\"' )
		{
			++pos;
			size_t startpos = pos;
			while ( pos < sz && line[ pos ] != '\"' ) ++pos;
			if ( pos == sz )
			{
				fmt::print( "line {}: error: file name string runs away\n", currentLineNum );
				assert( 0 ); // TODO: throw
			}
			assert( element.oper == ExpressionElement::OPERATION::PUSH );
			assert( element.argtype == ExpressionElement::ARGTYPE::STRING );
			if ( element.stringValue.size() )
				expression.push_back( element ); 
			element.stringValue.clear(); 
			element.argtype = ExpressionElement::ARGTYPE::STRING; 
			element.stringValue = string( line.begin() + startpos, line.begin() + pos );
			expression.push_back( element ); 
			++pos;
		}
		else if ( line[ pos ] == ')' )
		{
			++pos;
			break;
		}
		else if ( line[ pos ] == '@' )
		{
			Placeholder placehldr = parsePlaceholder( line, pos );
			switch ( placehldr.id )
			{
				case PLACEHOLDER::VERBATIM: 
				{
					element.stringValue.push_back( line[ pos ] ); 
					pos ++; 
					break;
				}
				case PLACEHOLDER::MEMBER_TYPE:
				case PLACEHOLDER::MEMBER_NAME:
				case PLACEHOLDER::STRUCT_NAME:
				case PLACEHOLDER::PARAM_MINUS:
				{
					assert( element.oper == ExpressionElement::OPERATION::PUSH );
					assert( element.argtype == ExpressionElement::ARGTYPE::STRING );
					if ( element.stringValue.size() )
					{
						expression.push_back( element );
						element.stringValue.clear();
					}
					element.stringValue.clear(); 
					element.argtype = ExpressionElement::ARGTYPE::PLACEHOLDER; 
					element.placeholder = placehldr.id;
					element.stringValue = placehldr.specific;
					expression.push_back( element ); 
					element.stringValue.clear();
					element.argtype = ExpressionElement::ARGTYPE::STRING; 
					break;
				}
				default:
				{
					assert( 0 == "NOT IMPLEMENTED" );
					break;
				}
			}
		}
		else
		{
			if ( line[ pos ] == ' ' || line[ pos ] == '\t')
			{
				if ( element.stringValue.size() )
				{
					assert( element.oper == ExpressionElement::OPERATION::PUSH );
					assert( element.argtype == ExpressionElement::ARGTYPE::STRING );
					expression.push_back( element );
					element.stringValue.clear();
				}
				pos ++;
			}
			else if ( line.compare( pos, 2, "==" ) == 0 )
			{
				if ( element.stringValue.size() )
				{
					assert( element.oper == ExpressionElement::OPERATION::PUSH );
					assert( element.argtype == ExpressionElement::ARGTYPE::STRING );
					expression.push_back( element );
					element.stringValue.clear();
				}
				element.stringValue.clear();
				element.oper = ExpressionElement::OPERATION::EQ;
				element.argtype = ExpressionElement::ARGTYPE::NONE;
				expression.push_back( element );
				element.oper = ExpressionElement::OPERATION::PUSH;
				element.argtype = ExpressionElement::ARGTYPE::STRING;
				pos += 2;
			}
			else if ( line.compare( pos, 2, "!=" ) == 0 )
			{
				if ( element.stringValue.size() )
				{
					assert( element.oper == ExpressionElement::OPERATION::PUSH );
					assert( element.argtype == ExpressionElement::ARGTYPE::STRING );
					expression.push_back( element );
					element.stringValue.clear();
				}
				element.stringValue.clear();
				element.oper = ExpressionElement::OPERATION::NEQ;
				element.argtype = ExpressionElement::ARGTYPE::NONE;
				expression.push_back( element );
				element.oper = ExpressionElement::OPERATION::PUSH;
				element.argtype = ExpressionElement::ARGTYPE::STRING;
				pos += 2;
			}
			else
			{
				element.stringValue.push_back( line[ pos ] );
				pos ++;
			}
		}
	}

	if ( element.stringValue.size() )
	{
		assert( element.oper == ExpressionElement::OPERATION::PUSH );
		assert( element.argtype == ExpressionElement::ARGTYPE::STRING );
		expression.push_back( element ); 
	}
}

void readAttributeName( const string& line, size_t& pos, AttributeName& attrName, int currentLineNum )
{
	size_t sz = line.size();
	skipSpaces( line, pos );
	attrName = parseParam( line, pos );
/*	string secondPart;
	if ( attrName.id == ATTRIBUTE::PARAM )
	{
		// right after it we expect a qualifying word
		// in present implementation we apply a relaxed check where a space is a terminator
		size_t startpos = pos;
		do { ++pos; } while ( pos < sz && (!( line[pos] == ' ' || line[pos] == '\t' )) );
		attrName.ext = string( line.begin() + startpos, line.begin() + pos );
	}
	else
		attrName.ext.clear();*/
}

void readAttributeValue( const string& line, size_t& pos, vector<LinePart>& parts, int currentLineNum )
{
	// this call should be done only if a value is expected ( attribute nabe is followed by '=')
	size_t sz = line.size();
	skipSpaces( line, pos );
	if ( pos == sz )
	{
		fmt::print( "line {}: error: attribute value is expected\n", currentLineNum );
		assert( 0 ); // TODO: throw
	}
	if ( line[pos] == '\"' )
	{
		++pos;
/*		size_t startpos = pos;
		while ( pos < sz && line[pos] != '\"' ) ++pos;
		if ( pos == sz )
		{
			fmt::print( "line {}: error: attribute value string runs away\n", currentLineNum );
			assert( 0 ); // TODO: throw
		}
		readLineParts( string( line.begin() + startpos, line.begin() + pos ), parts );*/
		readLineParts( line, pos, parts, "\"" );
		if ( line[pos] != '\"' )
		{
			fmt::print( "line {}: error: string runs away (lost terminating '\"')\n", currentLineNum );
			assert( 0 ); // TODO: throw
		}
		++pos; // for closing '"'
	}
	else // single word is expected
	{
		readLineParts( line, pos, parts, " \t" );
	}
}

void readNextParam( const string& line, size_t& pos, TemplateLine& tl, int currentLineNum )
{
	size_t sz = line.size();
	AttributeName attrName;
	vector<LinePart> parts;
	readAttributeName( line, pos, attrName, currentLineNum );
	if ( attrName.id == ATTRIBUTE::NONE )
	{
		fmt::print( "line {}: error: unexpected tokens at the end of line\n", currentLineNum );
		assert( 0 ); // TODO: throw
	}
	skipSpaces( line, pos );
	if ( pos == sz )
	{
		tl.attributes.insert( make_pair(attrName, parts ) );
		return;
	}
	if ( line[ pos ] == '=' )
	{
		++pos;
		readAttributeValue( line, pos, parts, currentLineNum );
	}

	tl.attributes.insert( make_pair(attrName, parts ) );
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

bool tokenizeTemplateLines( istream& tf, vector<TemplateLine>& templateLines, int& currentLineNum )
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
			formVerbatimLine( line, tl );
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
				readExpression( line, pos, tl.expression, currentLineNum );
			readAttributes( line, pos, tl, currentLineNum );
			templateLines.push_back( tl );
			if ( tl.type == TemplateLine::LINE_TYPE::END_TEMPLATE )
				return true;
		}
	}
	return true;
}

/*
NAME
FILENAME
*/

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
