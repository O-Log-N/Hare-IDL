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

#include "template_line_tokens.h"
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

// node type names (not directly derived from keywords
#define NODETYPE_STRING_FULL_TEMPLATE "FULL-TEMPLATE"
#define NODETYPE_STRING_IF_TRUE "IF-TRUE"
#define NODETYPE_STRING_IF_FALSE "IF-FALSE"
#define NODETYPE_STRING_VERBATIM "VERBATIM"

struct KeyWord
{
	const char* kw;
	int size;
	TemplateLine::LINE_TYPE id;
	bool expressionRequired;
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

struct NodeType
{
	const char* kw;
	NODE_TYPE id;
};

const NodeType nodeTypes[] = 
{
	{NODETYPE_STRING_FULL_TEMPLATE, NODE_TYPE::FULL_TEMPLATE},
	{KEYWORD_STRING_FOR_EACH_OF_MEMBERS, NODE_TYPE::FOR_EACH_OF_MEMBERS},
	{KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT, NODE_TYPE::FOR_EACH_PUBLISHABLE_STRUCT},
	{KEYWORD_STRING_IF, NODE_TYPE::IF},
	{NODETYPE_STRING_IF_TRUE, NODE_TYPE::IF_TRUE_BRANCH},
	{NODETYPE_STRING_IF_FALSE, NODE_TYPE::IF_FALSE_BRANCH},
	{KEYWORD_STRING_ASSERT, NODE_TYPE::ASSERT},
	{KEYWORD_STRING_OPEN_OUTPUT_FILE, NODE_TYPE::OPEN_OUTPUT_FILE},
	{KEYWORD_STRING_INCLUDE, NODE_TYPE::INCLUDE},
	{NODETYPE_STRING_VERBATIM, NODE_TYPE::CONTENT},
	{NULL, NODE_TYPE::CONTENT},
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

template<class T> const T* parseSpecialWord( const string& line, size_t& contentStart, T* words )
{
	int i;
	for ( i=0; ; i++ )
	{
		if ( words[i].kw == NULL )
		{
			return words + i;
		}
		else if ( line.compare( contentStart, words[i].size, words[i].kw ) == 0 )
		{
			contentStart += words[i].size;
			return words + i;
		}
	}
}

KeyWordProps parseMainKeyword( const string& line, size_t& contentStart )
{
	if ( line.compare( 0, sizeof(KEYWORD_STD_PREFIX)-1, KEYWORD_STD_PREFIX ) != 0 )
		return {TemplateLine::LINE_TYPE::CONTENT, false};
	contentStart += 2;
	while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
	const KeyWord* kwret = parseSpecialWord( line, contentStart, keywords );
	KeyWordProps ret = {kwret->id, kwret->expressionRequired};
	while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
	return ret;
}

ATTRIBUTE parseParam( const string& line, size_t& contentStart )
{
	while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
	ATTRIBUTE ret = parseSpecialWord( line, contentStart, params )->id;
	return ret;
}

PLACEHOLDER parsePlaceholder( const string& line, size_t& contentStart )
{
	while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
	PLACEHOLDER ret = parseSpecialWord( line, contentStart, placeholders )->id;
	return ret;
}

/////////////////////////////////////////////////////////////


template<class T> string specialWordToString( T* words, int id )
{
	int i;
	for ( i=0; ; i++ )
	{
		if ( words[i].kw == NULL )
			return "???????????";
		if ( id == words[i].id )
			return words[i].kw;
	}
	return "???????????";
}

string mainKeywordToString( TemplateLine::LINE_TYPE kw )
{
	return specialWordToString( keywords, kw );
}

string attributeNameToString( ATTRIBUTE id )
{
	return specialWordToString( params, id );
}

string placeholderToString( PLACEHOLDER id )
{
	return specialWordToString( placeholders, id );
}

string nodeTypesToString( NODE_TYPE id )
{
	return specialWordToString( nodeTypes, id );
}

