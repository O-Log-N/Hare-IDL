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

void pushState(int state);
int popState();

extern "C" int yywrap();
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

YYSTYPE addToStruct(YYSTYPE decl, YYSTYPE attr);

YYSTYPE createAttribute(YYSTYPE type, YYSTYPE id);

YYSTYPE createPublishableStruct(YYSTYPE token, YYSTYPE id);

YYSTYPE createMapping(YYSTYPE token, YYSTYPE arg_list, YYSTYPE id);

YYSTYPE createEncoding(YYSTYPE token, YYSTYPE arg_list, YYSTYPE id);
YYSTYPE addToEncoding(YYSTYPE decl, YYSTYPE elem);
YYSTYPE addFenceToEncoding(YYSTYPE decl, YYSTYPE token);

YYSTYPE createEncodingAttribute(YYSTYPE type, YYSTYPE id, YYSTYPE expr);
YYSTYPE createExtendAttribute(YYSTYPE id, YYSTYPE type);

YYSTYPE createEncodingGroup(YYSTYPE id, YYSTYPE opt_arg_list, YYSTYPE opt_att);
YYSTYPE addToEncodingGroup(YYSTYPE group, YYSTYPE element);
YYSTYPE addEncodingOption(YYSTYPE id, YYSTYPE opt_arg_list, YYSTYPE group);

YYSTYPE createUnion(YYSTYPE token, YYSTYPE discr_id, YYSTYPE id);
YYSTYPE createUnionAttribute(YYSTYPE type, YYSTYPE id, YYSTYPE id_list);


YYSTYPE createIdType(YYSTYPE id, YYSTYPE opt_arg_list);
YYSTYPE createNumeric(YYSTYPE token, bool low_flag, YYSTYPE low_expr, YYSTYPE high_expr, bool high_flag);
YYSTYPE createInt(YYSTYPE token, bool low_flag, YYSTYPE low_expr, YYSTYPE high_expr, bool high_flag);
YYSTYPE createIntegerType(YYSTYPE token, bool low_flag, YYSTYPE low_expr, YYSTYPE high_expr, bool high_flag);
YYSTYPE createFixedPointType(YYSTYPE token, bool low_flag, YYSTYPE low_expr, YYSTYPE precision_expr, YYSTYPE high_expr, bool high_flag);
YYSTYPE createFloatingPointType(YYSTYPE token, YYSTYPE significand_expr, YYSTYPE exponent_expr);
YYSTYPE createCharacterType(YYSTYPE token, YYSTYPE allowed_expr);
YYSTYPE createCharacterStringType(YYSTYPE token, YYSTYPE allowed_expr, YYSTYPE min_expr, YYSTYPE max_expr);
YYSTYPE createBitStringType(YYSTYPE token, YYSTYPE min_expr, YYSTYPE max_expr);
YYSTYPE createSequence(YYSTYPE opt_id, YYSTYPE type);
YYSTYPE createClassReference(YYSTYPE token, YYSTYPE id_type);
YYSTYPE createInlineEnum(YYSTYPE token, YYSTYPE opt_id, YYSTYPE values);

YYSTYPE addEnumValue(YYSTYPE list, YYSTYPE id, YYSTYPE int_lit);

YYSTYPE addString(YYSTYPE list, YYSTYPE str);
YYSTYPE addIdentifier(YYSTYPE list, YYSTYPE id);
YYSTYPE addExpression(YYSTYPE list, YYSTYPE id, YYSTYPE expr);
YYSTYPE createIdentifierExpression(YYSTYPE id);

#endif // PARSER_HELPER_H_INCLUDED
