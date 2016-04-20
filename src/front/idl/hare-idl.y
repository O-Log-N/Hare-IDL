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


%token KW_HASH_LINE
%token KW_PUBLISHABLE_STRUCT
%token KW_TYPEDEF
%token KW_ENUM KW_CLASS
%token KW_MAPPING KW_ENCODING
%token KW_NUMERIC KW_INT
%token KW_FENCE
%token KW_EXTEND KW_TO KW_DEFAULT
%token KW_FILE KW_CLASS_UPP
%token KW_DISCRIMINATED_UNION KW_DISCRIMINANT
%token KW_WHEN_DISCRIMINANT_IN KW_WHEN_DISCRIMINANT_IS

%token IDENTIFIER
%token STRING_LITERAL INTEGER_LITERAL CHAR_LITERAL FLOAT_LITERAL
%token KW_INTEGER KW_FIXED_POINT KW_FLOATING_POINT
%token KW_CHARACTER KW_CHARACTER_STRING KW_BIT_STRING

%token KW_SEQUENCE KW_DICTIONARY
%token KW_PRINTABLE_ASCII_STRING KW_UNICODE_STRING

%token OP_FOUR_DOTS

%error-verbose
%start file
%destructor { releaseYys($$); } <>

%{
#include "parser_helper.h"
extern int yylex();
%}

%%

file : { $$ = 0; }
	| file line_directive { $$ = 0; releaseYys2($1, $2); }
	| file typedef_decl { $$ = addTypedefToFile($1, $2); }
    | file publishable_struct { $$ = addToFile($1, $2); }
	| file mapping { $$ = addToFile($1, $2); }
	| file ext_file_mapping { $$ = processExtFileMapping($1, $2); }
	| file encoding { $$ = addToFile($1, $2); }
    | file discriminated_union { $$ = addToFile($1, $2); }
;

line_directive
	: KW_HASH_LINE INTEGER_LITERAL ';' { $$ = 0; processLineDirective($2, 0); releaseYys2($1, $3); }
	| KW_HASH_LINE INTEGER_LITERAL STRING_LITERAL ';' { $$ = 0; processLineDirective($2, $3); releaseYys2($1, $4); }
;

typedef_decl
	: KW_TYPEDEF data_type IDENTIFIER ';' { $$ = createTypedef($1, $2, $3); releaseYys($4); }
	| KW_TYPEDEF IDENTIFIER IDENTIFIER ';' { $$ = createTypedef($1, createIdType($2), $3); releaseYys($4); }
;

publishable_struct_begin
	: KW_PUBLISHABLE_STRUCT IDENTIFIER '{' { $$ = createPublishableStruct($1, $2); releaseYys($3); }
	| publishable_struct_begin data_type IDENTIFIER ';' { $$ = addToStruct($1, createAttribute($2, $3)); releaseYys($4); }
	| publishable_struct_begin IDENTIFIER IDENTIFIER ';' { $$ = addToStruct($1, createAttribute(createIdType($2), $3)); releaseYys($4); }
;

publishable_struct
	: publishable_struct_begin '}' ';' { $$ = $1; releaseYys2($2, $3); }
;

mapping_begin
	: KW_MAPPING '(' arg_list ')' KW_PUBLISHABLE_STRUCT IDENTIFIER '{' { $$ = createMapping($1, $3, $6); releaseYys4($2, $4, $5, $7); }
	| KW_MAPPING '(' ')' KW_PUBLISHABLE_STRUCT IDENTIFIER '{' { $$ = createMapping($1, 0, $5); releaseYys4($2, $3, $4, $6); }
	| mapping_begin line_directive { $$ = $1; releaseYys($2); }
	| mapping_begin mapping_type IDENTIFIER ';' { $$ = addToStruct($1, createAttribute($2, $3));  releaseYys($4); }
    | mapping_begin IDENTIFIER IDENTIFIER ';' { $$ = addToStruct($1, createAttribute(createMappingType($2), $3));  releaseYys($4); }
;

mapping
	: mapping_begin '}' ';' { $$ = $1; releaseYys2($2, $3); }
;

ext_file_mapping_begin
	: KW_MAPPING '(' arg_list ')' '{' KW_FILE STRING_LITERAL '{' { $$ = createExtFileMapping($1, $3, $7); releaseYys5($2, $4, $5, $6, $8); }
	| ext_file_mapping_begin KW_CLASS_UPP IDENTIFIER';' { $$ = addClassMapping($1, $3); releaseYys2($2, $4); }
;

ext_file_mapping
	: ext_file_mapping_begin '}' '}' ';' { $$ = $1; releaseYys3($2, $3, $4); }
	| ext_file_mapping_begin '}' '}' { $$ = $1; releaseYys2($2, $3); }
;


encoding_begin
	: KW_ENCODING '(' arg_list ')' KW_PUBLISHABLE_STRUCT IDENTIFIER '{' { $$ = createEncoding($1, $3, $6); releaseYys4($2, $4, $5, $7); }
	| encoding_begin line_directive { $$ = $1; releaseYys($2); }
	| encoding_begin encoding_element { $$ = addToEncoding($1, $2); }
	| encoding_begin encoding_group { $$ = addToEncoding($1, $2); }
    | encoding_begin KW_FENCE { $$ = addFenceToEncoding($1, $2); }
;

encoding
	: encoding_begin '}' ';' { $$ = $1; releaseYys2($2, $3); }
;

encoding_element
	: data_type IDENTIFIER ';' { $$ = createAttribute($1, $2); releaseYys($3); }
    | data_type IDENTIFIER KW_DEFAULT '=' expr ';' { $$ = createEncodingAttribute($1, $2, $5); releaseYys3($3, $4, $6); }
    | KW_EXTEND IDENTIFIER KW_TO data_type ';' { $$ = createExtendAttribute($2, $4); releaseYys3($1, $3, $5); }
	| IDENTIFIER IDENTIFIER ';' { $$ = createAttribute(createIdType($1), $2); releaseYys($3); }
    | IDENTIFIER IDENTIFIER KW_DEFAULT '=' expr ';' { $$ = createEncodingAttribute(createIdType($1), $2, $5); releaseYys3($3, $4, $6);}
    | KW_EXTEND IDENTIFIER KW_TO IDENTIFIER ';' { $$ = createExtendAttribute($2, createIdType($4)); releaseYys3($1, $3, $5);}
    | IDENTIFIER '(' arg_list ')' IDENTIFIER ';' { $$ = createAttribute(createEncodingType($1, $3), $5); releaseYys3($2, $4, $6); }
    | IDENTIFIER '(' arg_list ')' IDENTIFIER KW_DEFAULT '=' expr ';' { $$ = createEncodingAttribute(createEncodingType($1, $3), $5, $8); releaseYys5($2, $4, $6, $7, $9); }
    | KW_EXTEND IDENTIFIER KW_TO IDENTIFIER '(' arg_list ')' ';' { $$ = createExtendAttribute($2, createEncodingType($4, $6)); releaseYys5($1, $3, $5, $7, $8); }
;

encoding_group_begin
	: IDENTIFIER '{' { $$ = createEncodingGroup($1, 0, 0); releaseYys($2); }
	| IDENTIFIER '(' arg_list ')' '{' { $$ = createEncodingGroup($1, $3, 0); releaseYys3($2, $4, $5); }
	| encoding_group_begin encoding_element { $$ = addToEncodingGroup($1, $2); }
	| encoding_group_begin encoding_group { $$ = addToEncodingGroup($1, $2); }
;

encoding_group
	: encoding_group_begin '}' { $$ = $1; releaseYys($2); }
    | IDENTIFIER encoding_element { $$ = createEncodingGroup($1, 0, $2); }
	| IDENTIFIER '(' arg_list ')' encoding_element { $$ = createEncodingGroup($1, $3, $5); releaseYys2($2, $4); }
    | IDENTIFIER encoding_group { $$ = createEncodingGroup($1, 0, $2); }
	| IDENTIFIER '(' arg_list ')'  encoding_group { $$ = createEncodingGroup($1, $3, $5); releaseYys2($2, $4); }
;

discriminated_union_begin
	: KW_DISCRIMINATED_UNION '(' KW_DISCRIMINANT '=' IDENTIFIER ')' IDENTIFIER '{' { $$ = createUnion($1, $5, $7); releaseYys5($2, $3, $4, $6, $8); }
	| discriminated_union_begin discriminated_union_element { $$ = addToStruct($1, $2); }
;

discriminated_union
    : discriminated_union_begin '}' ';' { $$ = $1; releaseYys2($2, $3); }
;

discriminated_union_element
	: data_type IDENTIFIER ';' { $$ = createAttribute($1, $2); releaseYys($3); }
    | data_type IDENTIFIER KW_WHEN_DISCRIMINANT_IN '{' id_list '}' ';' { $$ = createUnionAttribute($1, $2, $5); releaseYys4($3, $4, $6, $7); }
    | data_type IDENTIFIER KW_WHEN_DISCRIMINANT_IS IDENTIFIER ';' { $$ = createUnionAttribute($1, $2, addIdentifier(0, $4)); releaseYys2($3, $5); }
    | IDENTIFIER IDENTIFIER ';' { $$ = createAttribute(createIdType($1), $2); releaseYys($3); }
    | IDENTIFIER IDENTIFIER KW_WHEN_DISCRIMINANT_IN '{' id_list '}' ';' { $$ = createUnionAttribute(createIdType($1), $2, $5); releaseYys4($3, $4, $6, $7); }
    | IDENTIFIER IDENTIFIER KW_WHEN_DISCRIMINANT_IS IDENTIFIER ';' { $$ = createUnionAttribute(createIdType($1), $2, addIdentifier(0, $4)); releaseYys2($3, $5); }
;

/* TODO:check and improve */
mapping_type
	: sequence_type
	| dictionary_type
	| inline_enum_type
	| class_ref_type
;	

data_type
    : integer_type
    | fixed_point_type
    | floating_point_type
    | character_type
    | character_string_type
    | bit_string_type
	| sequence_type
	| dictionary_type
	| inline_enum_type
	| class_ref_type
	| KW_PRINTABLE_ASCII_STRING { $$ = createPrintableAsciiStringType($1); }
	| KW_UNICODE_STRING { $$ = createUnicodeStringType($1); }
;

integer_type
	: KW_INTEGER '[' expr ',' expr ']' { $$ = createIntegerType($1, true, $3, $5, true); releaseYys3($2, $4, $6); }
	| KW_INTEGER '(' expr ',' expr ']' { $$ = createIntegerType($1, false, $3, $5, true); releaseYys3($2, $4, $6); }
	| KW_INTEGER '[' expr ',' expr ')' { $$ = createIntegerType($1, true, $3, $5, false); releaseYys3($2, $4, $6); }
	| KW_INTEGER '(' expr ',' expr ')' { $$ = createIntegerType($1, false, $3, $5, false); releaseYys3($2, $4, $6); }
;

fixed_point_type
	: KW_FIXED_POINT '[' expr ',' expr ',' expr ']' { $$ = createFixedPointType($1, true, $3, $5, $7, true); releaseYys4($2, $4, $6, $8); }
	| KW_FIXED_POINT '(' expr ',' expr ',' expr ']' { $$ = createFixedPointType($1, false, $3, $5, $7, true); releaseYys4($2, $4, $6, $8); }
	| KW_FIXED_POINT '[' expr ',' expr ',' expr ')' { $$ = createFixedPointType($1, true, $3, $5, $7, false); releaseYys4($2, $4, $6, $8); }
	| KW_FIXED_POINT '(' expr ',' expr ',' expr ')' { $$ = createFixedPointType($1, false, $3, $5, $7, false); releaseYys4($2, $4, $6, $8); }
;

floating_point_type
	: KW_FLOATING_POINT '(' expr ',' expr ')' { $$ = createFloatingPointType($1, $3, $5); releaseYys3($2, $4, $6); }
;

character_type
	: KW_CHARACTER '{' STRING_LITERAL '}' { $$ = createCharacterType($1, $3); releaseYys2($2, $4); }
	| KW_CHARACTER '{' character_set '}' { $$ = createCharacterType($1, $3); releaseYys2($2, $4); }
;

character_string_type
	: KW_CHARACTER_STRING '{' STRING_LITERAL '}' { $$ = createCharacterStringType($1, $3, 0, 0); releaseYys2($2, $4); }
	| KW_CHARACTER_STRING '{' STRING_LITERAL '}' '[' expr ',' expr ']' { $$ = createCharacterStringType($1, $3, $6, $8); releaseYys5($2, $4, $5, $7, $9); }
	| KW_CHARACTER_STRING '{' character_set '}' { $$ = createCharacterStringType($1, $3, 0, 0); releaseYys2($2, $4); }
	| KW_CHARACTER_STRING '{' character_set '}' '[' expr ',' expr ']' { $$ = createCharacterStringType($1, $3, $6, $8); releaseYys5($2, $4, $5, $7, $9); }
;

bit_string_type
	: KW_BIT_STRING '[' expr ',' expr ']' { $$ = createBitStringType($1, $3, $5); releaseYys3($2, $4, $6); }
;

sequence_type
    : KW_SEQUENCE '<' data_type '>' { $$ = createSequence($1, $3); releaseYys2($2, $4); }
    | KW_SEQUENCE '<' IDENTIFIER '>' { $$ = createSequence($1, createIdType($3)); releaseYys2($2, $4); }
	| IDENTIFIER '<' data_type '>' { $$ = createNamedSequence($1, $3); releaseYys2($2, $4); }
    | IDENTIFIER '<' IDENTIFIER '>' { $$ = createNamedSequence($1, createIdType($3)); releaseYys2($2, $4); }
;

dictionary_type
    : KW_DICTIONARY '<' data_type ',' data_type '>' { $$ = createDictionaryType($1, $3, $5); releaseYys3($2, $4, $6); }
    | KW_DICTIONARY '<' IDENTIFIER ',' data_type '>' { $$ = createDictionaryType($1, createIdType($3), $5); releaseYys3($2, $4, $6); }
    | KW_DICTIONARY '<' data_type ',' IDENTIFIER '>' { $$ = createDictionaryType($1, $3, createIdType($5)); releaseYys3($2, $4, $6); }
    | KW_DICTIONARY '<' IDENTIFIER ',' IDENTIFIER '>' { $$ = createDictionaryType($1, createIdType($3), createIdType($5)); releaseYys3($2, $4, $6); }
;

class_ref_type
	: KW_CLASS qname  { $$ = createClassReference($1, $2); }
;

inline_enum_type
	: KW_ENUM qname '{' enum_values '}' { $$ = createInlineEnum($1, $2, $4); releaseYys2($3, $5); }
;

enum_values
	: IDENTIFIER '=' INTEGER_LITERAL { $$ = addEnumValue(0, $1, $3); releaseYys($2); }
	| enum_values ',' IDENTIFIER '=' INTEGER_LITERAL { $$ = addEnumValue($1, $3, $5); releaseYys2($2, $4); }
;

arg_list
	: IDENTIFIER '='expr { $$ = addExpression(0, $1, $3); releaseYys($2); }
    | arg_list ',' IDENTIFIER '=' expr { $$ = addExpression($1, $3, $5); releaseYys2($2, $4); }
;

id_list
	: IDENTIFIER { $$ = addIdentifier(0, $1); }
    | id_list ',' IDENTIFIER { $$ = addIdentifier($1, $3); releaseYys($2); }
;

expr
	: INTEGER_LITERAL { $$ = $1; }
	| '+' INTEGER_LITERAL { $$ = $2; releaseYys($1); }
	| '-' INTEGER_LITERAL { $$ = makeMinusIntLit($2); releaseYys($1); }
	| FLOAT_LITERAL { $$ = $1; }
	| '+' FLOAT_LITERAL { $$ = $2; releaseYys($1); }
	| '-' FLOAT_LITERAL { $$ = makeMinusFloatLit($2); releaseYys($1); }
	| STRING_LITERAL { $$ = $1; }
;

character_set
	: INTEGER_LITERAL { $$ = addToCharSet(0, $1, 0); }
	| INTEGER_LITERAL '-' INTEGER_LITERAL { $$ = addToCharSet(0, $1, $3); releaseYys($2); }
	| character_set ',' INTEGER_LITERAL { $$ = addToCharSet($1, $3, 0);  releaseYys($2); }
	| character_set ',' INTEGER_LITERAL '-' INTEGER_LITERAL { $$ = addToCharSet($1, $3, $5); releaseYys2($2, $4); }
;

qname
	: IDENTIFIER { $$ = $1; }
	| OP_FOUR_DOTS IDENTIFIER { $$ = makeFourDotsPrefix($2); releaseYys($1); }
	| qname OP_FOUR_DOTS IDENTIFIER { $$ = addFourDotsName($1, $3); releaseYys($2); }
;