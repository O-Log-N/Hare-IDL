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

#ifndef TEMPLATE_LINE_TOKENIZER_H
#define TEMPLATE_LINE_TOKENIZER_H

#include "../idlc_include.h"
#include "template_line_tokenizer.h"

using namespace std;

enum class ATTRIBUTE
{
	NONE,
	TEXT, // implicit (used with verbatim lines)
	BEGIN,
	END,
	TEMPLATE,
	NAME,
	FILENAME,
	PARAM,
	TYPE,
	MSG,
};

enum class NODE_TYPE {
	FULL_TEMPLATE,
	CONTENT,
	IF,
	INCLUDE,
//	INCLUDE_FOR_TYPE, // necessity is yet to be proven (think about variation of INCLUDE instead)
	ASSERT,
	IF_TRUE_BRANCH,
	IF_FALSE_BRANCH,
	OPEN_OUTPUT_FILE,
	FOR_EACH_OF,
	INCLUDE_WITH,
};

enum class PLACEHOLDER {
	VERBATIM,
	STRUCT_NAME, // used ONLY within STRUCT or down the tree
	MEMBER_TYPE, // used ONLY within STRUCT-MEMBER
	MEMBER_NAME, // used ONLY within STRUCT-MEMBER
	PARAM_MINUS,
};

enum class OPERATOR { 
	INVALID,
	PUSH, 
	CALL, 
	EQ, 
	NEQ,
	GREATER,
	LESS,
	LEQ,
	GEQ,
	ADD,
	INCREMENT,
	SUBTR,
	DECREMENT,
	NOT,
	AND,
	OR,
};

struct Placeholder
{
	PLACEHOLDER id;
	string specific;
};

struct LinePart
{
	PLACEHOLDER type;
	string verbatim;
};

enum class PREDEFINED_FUNCTION
{
	NOT_A_FUNCTION,
	MEMBERS,
	PUBLISHABLE_STRUCTS,
	MEMBER_TYPE,
	COLLECTION_TYPE,
	MAKE_LIST,
	// type-related
	// NOTE: this list is subject to change (see issue #52, for instance)
	// TODO: update as necessary
	IS_PRIMITIVE_DOUBLE,
	IS_PRIMITIVE_INTEGER,
	IS_STRUCTURE,
	IS_ENUM,
	IS_SEQUENCE,
	IS_PARAMETRIZED_DOUBLE,
};

struct PredefindedFunction
{
	PREDEFINED_FUNCTION id;
	size_t argC;
};

struct PredefindedOperator
{
	OPERATOR id;
	size_t argC;
};

enum class ARGTYPE 
{
	NO_ARGTYPE, 
	NUMBER, 
	STRING, 
	BOOL, 
	// internal
	OBJPTR,
	OBJPTR_LIST,
};

struct ExpressionElement
{
	OPERATOR oper;
    ARGTYPE argtype = ARGTYPE::NO_ARGTYPE; // for operation PUSH: any but NONE
	// values below are used in case of PUSH operation
    double numberValue = 0; // argtype: ARGTYPE::NUMBER
	vector<LinePart> lineParts; // used for ARGTYPE::STRING
	PREDEFINED_FUNCTION fnCallID; // used for OPERATION::CALL
};

class AttributeName
{
public:
	ATTRIBUTE id;
	string ext;

	AttributeName() {}
	AttributeName( ATTRIBUTE id_, const string& ext_ ) : id ( id_ ), ext( ext_ ) {}
	bool operator<( const AttributeName& other) const 
	{
		return std::tie(id, ext) < std::tie(other.id, other.ext);
	}
};

struct TemplateLine
{
	enum LINE_TYPE {
		CONTENT = 0,
		BEGIN_TEMPLATE,
		END_TEMPLATE,
		IF,
		ELSE,
		ELIF,
		ENDIF,
		INCLUDE,
//		INCLUDE_FOR_TYPE,
		FOR_EACH_OF,
		ASSERT,
		OPEN_OUTPUT_FILE,
		CLOSE_OUTPUT_FILE,
		INCLUDE_WITH,

		ELIF_TO_IF, // derived
	};

	LINE_TYPE type;
	int srcLineNum;
	map<AttributeName, vector<ExpressionElement>> attributes;
	vector<ExpressionElement> expression; // used only for NODE_TYPE::IF(ELIF) and NODE_TYPE::ASSERT
};

bool tokenizeTemplateLines( FILE* tf, vector<TemplateLine>& templateLines, int& currentLineNum );


#endif // TEMPLATE_LINE_TOKENIZER_H
