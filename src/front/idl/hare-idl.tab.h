
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
     KW_MAPPING = 263,
     KW_ENCODING = 264,
     KW_NUMERIC = 265,
     KW_INT = 266,
     KW_FENCE = 267,
     KW_EXTEND = 268,
     KW_TO = 269,
     KW_DEFAULT = 270,
     KW_FILE = 271,
     KW_CLASS_UPP = 272,
     KW_DISCRIMINATED_UNION = 273,
     KW_DISCRIMINANT = 274,
     KW_WHEN_DISCRIMINANT_IN = 275,
     KW_WHEN_DISCRIMINANT_IS = 276,
     IDENTIFIER = 277,
     STRING_LITERAL = 278,
     INTEGER_LITERAL = 279,
     CHAR_LITERAL = 280,
     FLOAT_LITERAL = 281,
     KW_INTEGER = 282,
     KW_FIXED_POINT = 283,
     KW_FLOATING_POINT = 284,
     KW_CHARACTER = 285,
     KW_CHARACTER_STRING = 286,
     KW_BIT_STRING = 287,
     KW_SEQUENCE = 288,
     KW_DICTIONARY = 289,
     KW_PRINTABLE_ASCII_STRING = 290,
     KW_UNICODE_STRING = 291,
     OP_FOUR_DOTS = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


