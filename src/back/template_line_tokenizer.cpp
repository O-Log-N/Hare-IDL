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
#include <assert.h> // for assert()

// main keywords
#define KEYWORD_STD_PREFIX "@@"
#define KEYWORD_STRING_BEGIN_TEMPLATE "BEGIN-TEMPLATE"
#define KEYWORD_STRING_END_TEMPLATE "END-TEMPLATE"
#define KEYWORD_STRING_FOR_EACH_OF_MEMBERS "FOR-EACH-OF-MEMBERS"
#define KEYWORD_STRING_IF "IF"
#define KEYWORD_STRING_ELSE "ELSE"
#define KEYWORD_STRING_ELIF "ELIF"
#define KEYWORD_STRING_ENDIF "ENDIF"
#define KEYWORD_STRING_ASSERT "ASSERT"

#define KEYWORD_STRING_OPEN_OUTPUT_FILE "OPEN-OUTPUT-FILE"
#define KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT "FOR-EACH-PUBLISHABLE-STRUCT"
#define KEYWORD_STRING_CLOSE_OUTPUT_FILE "CLOSE-OUTPUT-FILE"
#define KEYWORD_STRING_INCLUDE "INCLUDE"

// parameters
#define PARAM_STRING_TYPE "TYPE"
#define PARAM_STRING_BEGIN "BEGIN"
#define PARAM_STRING_END "END"
#define PARAM_STRING_TEMPLATE "TEMPLATE"
#define PARAM_STRING_PARAM "PARAM-"
#define PARAM_STRING_NAME "NAME"
#define PARAM_STRING_FILENAME "FILENAME"

// main keywords ( starting from '@@' )
#define PLACEHOLDER_STRING_STRUCTNAME "@STRUCT-NAME@"
#define PLACEHOLDER_STRING_MEMBER_TYPE "@MEMBER-TYPE@"
#define PLACEHOLDER_STRING_MEMBER_NAME "@MEMBER-NAME@"

//typedef vector<TemplateLine>::iterator TEMPLATE_LINES_ITERATOR;

struct KeyWordProps
{
	TemplateLine::LINE_TYPE id;
	bool expressionRequired;
};

struct KeyWord
{
	const char* kw;
	int size;
	KeyWordProps id;
};

struct ParameterWord
{
	const char* kw;
	int size;
	ATTRIBUTE id;
};

struct PlaceholderWord
{
	const char* kw;
	int size;
	PLACEHOLDER id;
};

const KeyWord keywords[] = 
{
	{KEYWORD_STRING_BEGIN_TEMPLATE, sizeof(KEYWORD_STRING_BEGIN_TEMPLATE)-1, TemplateLine::LINE_TYPE::BEGIN_TEMPLATE, false},
	{KEYWORD_STRING_END_TEMPLATE, sizeof(KEYWORD_STRING_END_TEMPLATE)-1, TemplateLine::LINE_TYPE::END_TEMPLATE, false},
	{KEYWORD_STRING_FOR_EACH_OF_MEMBERS, sizeof(KEYWORD_STRING_FOR_EACH_OF_MEMBERS)-1, TemplateLine::LINE_TYPE::FOR_EACH_OF_MEMBERS, false},
	{KEYWORD_STRING_IF, sizeof(KEYWORD_STRING_IF)-1, TemplateLine::LINE_TYPE::IF, true},
	{KEYWORD_STRING_ENDIF, sizeof(KEYWORD_STRING_ENDIF)-1, TemplateLine::LINE_TYPE::ENDIF, false},
	{KEYWORD_STRING_ELIF, sizeof(KEYWORD_STRING_ELIF)-1, TemplateLine::LINE_TYPE::ELIF, true},
	{KEYWORD_STRING_ELSE, sizeof(KEYWORD_STRING_ELSE)-1, TemplateLine::LINE_TYPE::ELSE, false},
	{KEYWORD_STRING_ASSERT, sizeof(KEYWORD_STRING_ASSERT)-1, TemplateLine::LINE_TYPE::ASSERT, true},
	{KEYWORD_STRING_OPEN_OUTPUT_FILE, sizeof(KEYWORD_STRING_OPEN_OUTPUT_FILE)-1, TemplateLine::LINE_TYPE::OPEN_OUTPUT_FILE, false},
	{KEYWORD_STRING_CLOSE_OUTPUT_FILE, sizeof(KEYWORD_STRING_CLOSE_OUTPUT_FILE)-1, TemplateLine::LINE_TYPE::CLOSE_OUTPUT_FILE, false},
	{KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT, sizeof(KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT)-1, TemplateLine::LINE_TYPE::FOR_EACH_PUBLISHABLE_STRUCT, false},
	{KEYWORD_STRING_INCLUDE, sizeof(KEYWORD_STRING_INCLUDE)-1, TemplateLine::LINE_TYPE::INCLUDE, false},
	{NULL, 0, TemplateLine::LINE_TYPE::CONTENT, false},
};

const PlaceholderWord placeholders[] = 
{
	{PLACEHOLDER_STRING_STRUCTNAME, sizeof(PLACEHOLDER_STRING_STRUCTNAME)-1, PLACEHOLDER::STRUCT_NAME},
	{PLACEHOLDER_STRING_MEMBER_TYPE, sizeof(PLACEHOLDER_STRING_MEMBER_TYPE)-1, PLACEHOLDER::MEMBER_TYPE},
	{PLACEHOLDER_STRING_MEMBER_NAME, sizeof(PLACEHOLDER_STRING_MEMBER_NAME)-1, PLACEHOLDER::MEMBER_NAME},
	{NULL, 0, PLACEHOLDER::VERBATIM},
};

const ParameterWord params[] = 
{
	{PARAM_STRING_BEGIN, sizeof(PARAM_STRING_BEGIN)-1, ATTRIBUTE::BEGIN},
	{PARAM_STRING_END, sizeof(PARAM_STRING_END)-1, ATTRIBUTE::END},
	{PARAM_STRING_TEMPLATE, sizeof(PARAM_STRING_TEMPLATE)-1, ATTRIBUTE::TEMPLATE},
	{PARAM_STRING_NAME, sizeof(PARAM_STRING_NAME)-1, ATTRIBUTE::NAME},
	{PARAM_STRING_FILENAME, sizeof(PARAM_STRING_FILENAME)-1, ATTRIBUTE::FILENAME},
	{PARAM_STRING_TYPE, sizeof(PARAM_STRING_TYPE)-1, ATTRIBUTE::TYPE},
	{PARAM_STRING_PARAM, sizeof(PARAM_STRING_PARAM)-1, ATTRIBUTE::PARAM},
	{NULL, 0, ATTRIBUTE::NONE},
};

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

template<class T> auto  parseSpecialWord( const string& line, size_t& contentStart, T* words ) -> decltype( words->id )
//template<class T> T*  parseSpecialWord( const string& line, size_t& contentStart, T* words )
{
	int i;
	for ( i=0; ; i++ )
	{
		if ( words[i].size == 0 )
		{
			return words[i].id;
//			return words + i;
		}
		else if ( line.compare( contentStart, words[i].size, words[i].kw ) == 0 )
		{
			contentStart += words[i].size;
			return words[i].id;
//			return words + i;
		}
	}
}

//TemplateLine::LINE_TYPE const parseMainKeyword( const string& line, size_t& contentStart )
//pair<TemplateLine::LINE_TYPE, bool> parseMainKeyword( const string& line, size_t& contentStart )
KeyWordProps parseMainKeyword( const string& line, size_t& contentStart )
{
	if ( line.compare( 0, sizeof(KEYWORD_STD_PREFIX)-1, KEYWORD_STD_PREFIX ) != 0 )
		return {TemplateLine::LINE_TYPE::CONTENT, false};
	contentStart += 2;
	while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
//	TemplateLine::LINE_TYPE ret = parseSpecialWord( line, contentStart, keywords );
//	const KeyWord* ret = parseSpecialWord( line, contentStart, keywords );
	KeyWordProps ret = parseSpecialWord( line, contentStart, keywords );
	while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
//	return make_pair(ret->id, ret->expressionRequired);
	return ret;
}

ATTRIBUTE parseParam( const string& line, size_t& contentStart )
{
	while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
	ATTRIBUTE ret = parseSpecialWord( line, contentStart, params );
	return ret;
}

PLACEHOLDER parsePlaceholder( const string& line, size_t& contentStart )
{
	while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
	PLACEHOLDER ret = parseSpecialWord( line, contentStart, placeholders );
	return ret;
}

void skipSpaces( const string& line, size_t& contentStart )
{
	while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
}

void findSpaces( const string& line, size_t& contentStart )
{
	while ( contentStart < line.size() && (!(line[contentStart] == ' ' || line[contentStart] == '\t')) ) contentStart++;
}

void readLineParts( const string& line, vector<LinePart>& parts )
{
	// we have to go char by char; if '@' is found, make sure it's not a placeholder, or replace it accordingly
	LinePart part;
	unsigned int pos = 0;
	size_t sz = line.size();
	part.type = PLACEHOLDER::VERBATIM;
	do
	{
		if ( line[ pos ] != '@' )
		{
			part.verbatim.push_back( line[ pos ] );
			pos ++;
		}
		else
		{
			int placehldr = parsePlaceholder( line, pos );
			switch ( placehldr )
			{
				case PLACEHOLDER::VERBATIM: 
				{
					part.verbatim.push_back( line[ pos ] ); 
					pos ++; 
					break;
				}
				case PLACEHOLDER::STRUCT_NAME:
				case PLACEHOLDER::MEMBER_TYPE:
				case PLACEHOLDER::MEMBER_NAME:
				{
					parts.push_back( part ); 
					part.verbatim.clear(); 
					part.type = placehldr; 
					parts.push_back( part ); 
					part.type = PLACEHOLDER::VERBATIM; 
					break;
				}
				default:
				{
					assert( 0 == "NOT IMPLEMENTED" );
					break;
				}
			}
		}
	}
	while ( pos < sz );

	if ( part.verbatim.size() )
	{
		assert( part.type == PLACEHOLDER::VERBATIM );
		parts.push_back( part ); 
	}
}

void formVerbatimLine( const string& line, TemplateLine& tl )
{
	assert( line.compare( 0, 2, "@@" ) != 0 );
	tl.type = TemplateLine::LINE_TYPE::CONTENT;
	vector<LinePart> parts;
	readLineParts( line, parts );

	tl.attributes.insert( make_pair(AttributeName(ATTRIBUTE::TEXT, ""), parts ) );
//	tl.attributes.insert( map<ATTRIBUTE, string>::value_type(ATTRIBUTE::TEXT, "her") );
}

//TemplateLine::LINE_TYPE getLineType( const string& line, size_t& pos )
KeyWordProps getLineType( const string& line, size_t& pos )
{
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
			PLACEHOLDER placehldr = parsePlaceholder( line, pos );
			switch ( placehldr )
			{
				case PLACEHOLDER::VERBATIM: 
				{
					element.stringValue.push_back( line[ pos ] ); 
					pos ++; 
					break;
				}
				case PLACEHOLDER::MEMBER_TYPE:
				case PLACEHOLDER::MEMBER_NAME:
				{
					assert( element.oper == ExpressionElement::OPERATION::PUSH );
					assert( element.argtype == ExpressionElement::ARGTYPE::STRING );
					if ( element.stringValue.size() )
						expression.push_back( element ); 
					element.stringValue.clear(); 
					element.argtype = ExpressionElement::ARGTYPE::PLACEHOLDER; 
					element.placeholder = placehldr;
					expression.push_back( element ); 
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
	attrName.id = parseParam( line, pos );
	string secondPart;
	if ( attrName.id == ATTRIBUTE::PARAM )
	{
		// right after it we expect a qualifying word
		// in present implementation we apply a relaxed check where a space is a terminator
		size_t startpos = pos;
		do { ++pos; } while ( pos < sz && (!( line[pos] == ' ' || line[pos] == '\t' )) );
		attrName.ext = string( line.begin() + startpos, line.begin() + pos );
	}
	else
		attrName.ext.clear();
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
		size_t startpos = pos;
		while ( pos < sz && line[pos] != '\"' ) ++pos;
		if ( pos == sz )
		{
			fmt::print( "line {}: error: attribute value string runs away\n", currentLineNum );
			assert( 0 ); // TODO: throw
		}
		readLineParts( string( line.begin() + startpos, line.begin() + pos ), parts );
		++pos; // for closing '"'
	}
	else // single word is expected
	{
		size_t startpos = pos;
		findSpaces( line, pos );
		readLineParts( string( line.begin() + startpos, line.begin() + pos ), parts );
	}
}

void readNextParam( const string& line, size_t& pos, TemplateLine& tl, int currentLineNum )
{
	size_t sz = line.size();
	AttributeName attrName;
//	readAttributeName( line, pos, attrName, currentLineNum );
	vector<LinePart> parts;
	readAttributeName( line, pos, attrName, currentLineNum );
	if ( attrName.id == ATTRIBUTE::NONE )
	{
		fmt::print( "line {}: error: unexpected tokens at the end of line\n", currentLineNum );
		assert( 0 ); // TODO: throw
	}
	skipSpaces( line, pos );
	if ( pos == sz )
		return;
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
