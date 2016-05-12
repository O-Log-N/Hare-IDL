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
	LOCAL,
	TYPE,
	MSG,
	POST_PROCESS,
	POST_PROCESS_SEPARATOR,
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
	FOR_EACH_OF_ENTER_BLOCK,
	FOR_EACH_OF_INCLUDE_TEMPLATE,
	FOR_SINGLE_ENTER_BLOCK,
	FOR_SINGLE_INCLUDE_TEMPLATE,
	LET,
	RETURN,
};

enum class PLACEHOLDER {
	VERBATIM,
	STRUCT_NAME, // used ONLY within STRUCT or down the tree
	IDL_MEMBER_TYPE, // used ONLY within STRUCT-MEMBER
	MAPPING_MEMBER_TYPE,
	ENCODING_MEMBER_TYPE,
	MAPPING_DISCRIMINATOR_NAME, // used ONLY with discriminated unions
	IDL_MEMBER_NAME, // used ONLY within STRUCT-MEMBER
	MAPPING_MEMBER_NAME, // used ONLY within STRUCT-MEMBER
	ENCODING_MEMBER_NAME, // used ONLY within STRUCT-MEMBER
	PARAM_MINUS,
	LOCAL_MINUS,
	ENUM_VALUE_NAME,
	ENCODING_ENUM_VALUE_VALUE,
	MAPPING_ENUM_VALUE_VALUE,
	ENCODING_DISCRIMINATED_UNION_OPTION_NAME,
	MAPPING_DISCRIMINATED_UNION_OPTION_VALUE,
	ENCODING_DISCRIMINATED_UNION_OPTION_VALUE,
	FROM_TEMPLATE,
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
	COLLECTION_TYPE2,
	ENUM_VALUES,
//	DISCRIMINATED_UNION_ALLOWED_PAIRS,
	PUBLISHABLE_DISCRIMINATED_UNIONS,
	DISCRIMINATED_UNION_DISCRIMINATOR,
	DISCRIMINATED_UNION_OPTIONS,
	// type-related
	// NOTE: this list is subject to change (see issue #52, for instance)
	// TODO: update as necessary
	IS_STRUCTURE,
	IS_ENUM,
	IS_SEQUENCE,
	IS_DICTIONARY,
	IS_INTEGER,
	IS_FLOATING_POINT,
	IS_FIXED_POINT,
	IS_UNSIGNED_INTEGER,
	IS_UNSIGNED_INTEGER_FITTING_UINT,
	IS_SIGNED_INTEGER_FITTING_INT,
	IS_FLOATING_POINT_FITTING_FLOAT,
	IS_CHARACTER_STRING,
	IS_CHARACTER,
	IS_BIT_STRING,
	IS_DISCRIMINATED_UNION,
	CREATE_MAP,
	INSERT_TO_MAP,
	FIND_IN_MAP,
};

struct PredefindedFunction
{
	PREDEFINED_FUNCTION id;
	size_t argC;
	bool isMember;
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
	PLACEHOLDER,
	// internal
	OBJPTR,
	ANY_MAP,
	ANY_LIST,
};

struct ExpressionElement
{
	OPERATOR oper;
    ARGTYPE argtype = ARGTYPE::NO_ARGTYPE; // for operation PUSH: any but NONE
	// values below are used in case of PUSH operation
    double numberValue = 0; // argtype: ARGTYPE::NUMBER
	vector<LinePart> lineParts; // used for ARGTYPE::STRING
	PREDEFINED_FUNCTION fnCallID; // used for OPERATION::CALL
	Placeholder ph; // used for OPERATION::PUSH, ARGTYPE::PLACEHOLDER
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
		COMMENTED_LINE,
		CONTINUED_LINE,
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
		FOR_SINGLE,
		LET,
		RETURN,

		ELIF_TO_IF, // derived
	};

	LINE_TYPE type;
	int srcLineNum;
	map<AttributeName, vector<ExpressionElement>> attributes;
	vector<ExpressionElement> expression; // used only for NODE_TYPE::IF(ELIF) and NODE_TYPE::ASSERT
};

bool tokenizeTemplateLines( FILE* tf, vector<TemplateLine>& templateLines, int& currentLineNum );


#endif // TEMPLATE_LINE_TOKENIZER_H
