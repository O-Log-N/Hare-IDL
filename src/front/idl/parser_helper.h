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

/*
This header is used to isolate lex/yacc parser from rest of the code.
It is necesary because of lex.yy.c and parse.tab.c being pure C code,
while the rest of the project is C++.
Also leaves function calls only at scan.l and parse.y files, and
all code goes inside parser_helper.cpp
*/

#ifndef PARSER_HELPER_H_INCLUDED
#define PARSER_HELPER_H_INCLUDED "include guard"

struct YyBase;
typedef struct YyBase* YYSTYPE;
#define YYSTYPE_IS_DECLARED 1

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

	extern int returnState;
	
	void pushState(int state);
	int popState();

	int yywrap();
	void yyerror(const char* msg);
	
	void parserError(const char* msg, const char* text, int line);
	void parserErrorUnknownChar(char text, int line);

	void releaseYys(YYSTYPE yys);
	void releaseYys2(YYSTYPE yys0, YYSTYPE yys1);
	void releaseYys3(YYSTYPE yys0, YYSTYPE yys1, YYSTYPE yys2);
	void releaseYys4(YYSTYPE yys0, YYSTYPE yys1, YYSTYPE yys2, YYSTYPE yys3);
	void releaseYys5(YYSTYPE yys0, YYSTYPE yys1, YYSTYPE yys2, YYSTYPE yys3, YYSTYPE yys4);
	
	YYSTYPE createYyToken(const char* text, int line, int token);
	
	YYSTYPE createIdentifier(const char* text, int line);
	YYSTYPE createIntegerLiteral(const char* text, int line);
	YYSTYPE createHexIntegerLiteral(const char* text, int line);
	YYSTYPE createStringLiteral(const char* text, int line);
	YYSTYPE createCharLiteral(const char* text, int line);
	YYSTYPE createZeroLiteral(const char* text, int line);
	YYSTYPE createBooleanLiteral(const char* text, int line);
	YYSTYPE createFloatLiteral(const char* text, int line);
	
	YYSTYPE addToFile(YYSTYPE file, YYSTYPE item);

	YYSTYPE createPublishableStruct(YYSTYPE token, YYSTYPE id);
	YYSTYPE addToPublishableStruct(YYSTYPE decl, YYSTYPE type, YYSTYPE id);

	YYSTYPE createMapping(YYSTYPE token, YYSTYPE str_list, YYSTYPE id);
	YYSTYPE addToMapping(YYSTYPE decl, YYSTYPE type, YYSTYPE id);

	YYSTYPE createEncoding(YYSTYPE token, YYSTYPE str_lit, YYSTYPE id);
	YYSTYPE addToEncoding(YYSTYPE decl, YYSTYPE elem);
	YYSTYPE addFenceToEncoding(YYSTYPE decl, YYSTYPE token);

	YYSTYPE createEncodingAttribute(YYSTYPE type, YYSTYPE id, YYSTYPE expr);
	YYSTYPE createExtendAttribute(YYSTYPE id, YYSTYPE type);

	YYSTYPE createEncodingGroup(YYSTYPE id, YYSTYPE opt_arg_list, YYSTYPE opt_att);
	YYSTYPE addToEncodingGroup(YYSTYPE group, YYSTYPE element);
	YYSTYPE addEncodingOption(YYSTYPE id, YYSTYPE opt_arg_list, YYSTYPE group);

	YYSTYPE createIdType(YYSTYPE id);
	YYSTYPE createNumeric(YYSTYPE token, bool low_flag, YYSTYPE low_literal, YYSTYPE high_literal, bool high_flag);
	YYSTYPE createInt(YYSTYPE token, bool low_flag, YYSTYPE low_literal, YYSTYPE high_literal, bool high_flag);
	YYSTYPE createFixedPoint(YYSTYPE token, YYSTYPE float_lit);
	YYSTYPE createBit(YYSTYPE token, YYSTYPE int_lit);
	YYSTYPE createSequence(YYSTYPE token, YYSTYPE id_type);
	YYSTYPE createClassReference(YYSTYPE token, YYSTYPE id_type);
	YYSTYPE createInlineEnum(YYSTYPE token, YYSTYPE id, YYSTYPE values);

	YYSTYPE addEnumValue(YYSTYPE list, YYSTYPE id, YYSTYPE int_lit);

	YYSTYPE addString(YYSTYPE list, YYSTYPE str);
	YYSTYPE addExpression(YYSTYPE list, YYSTYPE expr);
	YYSTYPE createIdentifierExpression(YYSTYPE id);
	


	
#ifdef __cplusplus
}
#endif

#endif // PARSER_HELPER_H_INCLUDED
