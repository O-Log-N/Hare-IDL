
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     KW_HASH_LINE = 258,
     KW_PUBLISHABLE_STRUCT = 259,
     KW_TYPEDEF = 260,
     KW_ENUM = 261,
     KW_CLASS = 262,
     KW_STRUCT = 263,
     KW_MAPPING = 264,
     KW_ENCODING = 265,
     KW_NUMERIC = 266,
     KW_INT = 267,
     KW_FENCE = 268,
     KW_EXTEND = 269,
     KW_TO = 270,
     KW_DEFAULT = 271,
     KW_FILE = 272,
     KW_CLASS_UPP = 273,
     KW_DISCRIMINATED_UNION = 274,
     KW_DISCRIMINANT = 275,
     KW_WHEN_DISCRIMINANT_IN = 276,
     KW_WHEN_DISCRIMINANT_IS = 277,
     IDENTIFIER = 278,
     STRING_LITERAL = 279,
     INTEGER_LITERAL = 280,
     CHAR_LITERAL = 281,
     FLOAT_LITERAL = 282,
     KW_INTEGER = 283,
     KW_FIXED_POINT = 284,
     KW_FLOATING_POINT = 285,
     KW_CHARACTER = 286,
     KW_CHARACTER_STRING = 287,
     KW_BIT_STRING = 288,
     KW_SEQUENCE = 289,
     KW_DICTIONARY = 290,
     KW_PRINTABLE_ASCII_STRING = 291,
     KW_UNICODE_STRING = 292,
     OP_FOUR_DOTS = 293
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


