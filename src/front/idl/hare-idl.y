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


%token KW_PUBLISHABLE_STRUCT
%token KW_ENUM KW_CLASS
%token KW_MAPPING KW_ENCODING
%token KW_NUMERIC KW_INT KW_SEQUENCE
%token KW_FIXED_POINT KW_BIT
%token KW_EXTEND KW_TO KW_DEFAULT KW_FENCE

%token IDENTIFIER STRING_LITERAL INTEGER_LITERAL CHAR_LITERAL FLOAT_LITERAL


%error-verbose
%start file
%destructor { releaseYys($$); } <>

%{
#include "parser_helper.h"
extern int yylex();
%}

%%

file : { $$ = 0; }
     | file publishable_struct { $$ = addToFile($1, $2); }
	 | file mapping { $$ = addToFile($1, $2); }
	 | file encoding { $$ = addToFile($1, $2); }
;

publishable_struct_begin
	: KW_PUBLISHABLE_STRUCT IDENTIFIER '{' { $$ = createPublishableStruct($1, $2); releaseYys($3); }
	| publishable_struct_begin data_type IDENTIFIER ';' { $$ = addToPublishableStruct($1, $2, $3); releaseYys($4);}
	| publishable_struct_begin IDENTIFIER IDENTIFIER ';' { $$ = addToPublishableStruct($1, createIdType($2, 0), $3); releaseYys($4); }
;

publishable_struct
	: publishable_struct_begin '}' ';' { $$ = $1; releaseYys2($2, $3); }
;

mapping_begin
	: KW_MAPPING '(' arg_list ')' KW_PUBLISHABLE_STRUCT IDENTIFIER '{' { $$ = createMapping($1, $3, $6); releaseYys4($2, $4, $5, $7); }
	| mapping_begin data_type IDENTIFIER ';' { $$ = addToMapping($1, $2, $3);  releaseYys($4); }
    | mapping_begin IDENTIFIER IDENTIFIER ';' { $$ = addToMapping($1, createIdType($2, 0), $3);  releaseYys($4); }
;

mapping
	: mapping_begin '}' ';' { $$ = $1; releaseYys2($2, $3); }
;

encoding_begin
	: KW_ENCODING '(' arg_list ')' KW_PUBLISHABLE_STRUCT IDENTIFIER '{' { $$ = createEncoding($1, $3, $6); releaseYys4($2, $4, $5, $7); }
	| encoding_begin data_element { $$ = addToEncoding($1, $2); }
	| encoding_begin data_group { $$ = addToEncoding($1, $2); }
    | encoding_begin KW_FENCE { $$ = addFenceToEncoding($1, $2); }
;

encoding
	: encoding_begin '}' ';' { $$ = $1; releaseYys2($2, $3); }
;

data_element
	: data_type IDENTIFIER ';' { $$ = createEncodingAttribute($1, $2, 0); releaseYys($3);}
    | data_type IDENTIFIER KW_DEFAULT '=' expr ';' { $$ = createEncodingAttribute($1, $2, $5); releaseYys3($3, $4, $6);}
    | KW_EXTEND IDENTIFIER KW_TO data_type ';' { $$ = createExtendAttribute($2, $4); releaseYys3($1, $3, $5);}
	| IDENTIFIER IDENTIFIER ';' { $$ = createEncodingAttribute(createIdType($1, 0), $2, 0); releaseYys($3); }
    | IDENTIFIER IDENTIFIER KW_DEFAULT '=' expr ';' { $$ = createEncodingAttribute(createIdType($1, 0), $2, $5); releaseYys3($3, $4, $6);}
    | KW_EXTEND IDENTIFIER KW_TO IDENTIFIER ';' { $$ = createExtendAttribute($2, createIdType($4, 0)); releaseYys3($1, $3, $5);}
    | IDENTIFIER '(' arg_list ')' IDENTIFIER ';' { $$ = createEncodingAttribute(createIdType($1, $3), $5, 0); releaseYys3($2, $4, $6); }
    | IDENTIFIER '(' arg_list ')' IDENTIFIER KW_DEFAULT '=' expr ';' { $$ = createEncodingAttribute(createIdType($1, $3), $5, $8); releaseYys5($2, $4, $6, $7, $9);}
    | KW_EXTEND IDENTIFIER KW_TO IDENTIFIER '(' arg_list ')' ';' { $$ = createExtendAttribute($2, createIdType($4, $6)); releaseYys5($1, $3, $5, $7, $8);}
;

data_group_begin
	: IDENTIFIER '{' { $$ = createEncodingGroup($1, 0, 0); releaseYys($2); }
	| IDENTIFIER '(' arg_list ')' '{' { $$ = createEncodingGroup($1, $3, 0); releaseYys3($2, $4, $5); }
	| data_group_begin data_element { $$ = addToEncodingGroup($1, $2); }
	| data_group_begin data_group { $$ = addToEncodingGroup($1, $2); }
;

data_group
	: data_group_begin '}' { $$ = $1; releaseYys($2); }
    | IDENTIFIER data_element { $$ = createEncodingGroup($1, 0, $2); }
	| IDENTIFIER '(' arg_list ')' data_element { $$ = createEncodingGroup($1, $3, $5); releaseYys2($2, $4);}
    | IDENTIFIER data_group { $$ = addEncodingOption($1, 0, $2); }
	| IDENTIFIER '(' arg_list ')'  data_group { $$ = addEncodingOption($1, $3, $5); releaseYys2($2, $4);}
;

data_type
	: numeric_type
    | int_type
	| sequence_type
	| inline_enum_type
	| class_ref_type
    | bit_type
    | fixed_point_type
;

numeric_type
	: KW_NUMERIC '[' expr ',' expr ']' { $$ = createNumeric($1, true, $3, $5, true); releaseYys3($2, $4, $6); }
	| KW_NUMERIC '(' expr ',' expr ']' { $$ = createNumeric($1, false, $3, $5, true); releaseYys3($2, $4, $6); }
	| KW_NUMERIC '[' expr ',' expr ')' { $$ = createNumeric($1, true, $3, $5, false); releaseYys3($2, $4, $6); }
	| KW_NUMERIC '(' expr ',' expr ')' { $$ = createNumeric($1, false, $3, $5, false); releaseYys3($2, $4, $6); }
;

int_type
	: KW_INT '[' expr ',' expr ']' { $$ = createInt($1, true, $3, $5, true); releaseYys3($2, $4, $6); }
	| KW_INT '(' expr ',' expr ']' { $$ = createInt($1, false, $3, $5, true); releaseYys3($2, $4, $6); }
	| KW_INT '[' expr ',' expr ')' { $$ = createInt($1, true, $3, $5, false); releaseYys3($2, $4, $6); }
	| KW_INT '(' expr ',' expr ')' { $$ = createInt($1, false, $3, $5, false); releaseYys3($2, $4, $6); }
;

fixed_point_type
    : KW_FIXED_POINT '(' arg_list ')' { $$ = createFixedPoint($1, $3); releaseYys2($2, $4); }
;

bit_type
    : KW_BIT '(' arg_list ')' { $$ = createBit($1, $3); releaseYys2($2, $4); }
;

sequence_type
	: KW_SEQUENCE '<' IDENTIFIER '>' { $$ = createSequence($1, $3); releaseYys2($2, $4); }
;

class_ref_type
	: KW_CLASS IDENTIFIER  { $$ = createClassReference($1, $2); }
;

inline_enum_type
	: KW_ENUM IDENTIFIER '{' enum_values '}' { $$ = createInlineEnum($1, $2, $4); releaseYys2($3, $5); }
;

enum_values
	: IDENTIFIER '=' INTEGER_LITERAL { $$ = addEnumValue(0, $1, $3); releaseYys($2); }
	| enum_values ',' IDENTIFIER '=' INTEGER_LITERAL { $$ = addEnumValue($1, $3, $5); releaseYys2($2, $4); }
;

arg_list
	: IDENTIFIER '='expr { $$ = addExpression(0, $1, $3); releaseYys($2); }
    | arg_list ',' IDENTIFIER '=' expr { $$ = addExpression($1, $3, $5); releaseYys2($2, $4); }
;

expr
	: INTEGER_LITERAL { $$ = $1; }
	| FLOAT_LITERAL { $$ = $1; }
	| STRING_LITERAL { $$ = $1; }
;
