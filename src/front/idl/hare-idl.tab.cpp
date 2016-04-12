
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 42 "hare-idl.y"

#include "parser_helper.h"
extern int yylex();


/* Line 189 of yacc.c  */
#line 79 "hare-idl.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     KW_PUBLISHABLE_STRUCT = 258,
     KW_TYPEDEF = 259,
     KW_ENUM = 260,
     KW_CLASS = 261,
     KW_MAPPING = 262,
     KW_ENCODING = 263,
     KW_NUMERIC = 264,
     KW_INT = 265,
     KW_FENCE = 266,
     KW_EXTEND = 267,
     KW_TO = 268,
     KW_DEFAULT = 269,
     KW_FILE = 270,
     KW_CLASS_UPP = 271,
     KW_DISCRIMINATED_UNION = 272,
     KW_DISCRIMINANT = 273,
     KW_WHEN_DISCRIMINANT_IN = 274,
     KW_WHEN_DISCRIMINANT_IS = 275,
     IDENTIFIER = 276,
     STRING_LITERAL = 277,
     INTEGER_LITERAL = 278,
     CHAR_LITERAL = 279,
     FLOAT_LITERAL = 280,
     KW_INTEGER = 281,
     KW_FIXED_POINT = 282,
     KW_FLOATING_POINT = 283,
     KW_CHARACTER = 284,
     KW_CHARACTER_STRING = 285,
     KW_BIT_STRING = 286,
     KW_SEQUENCE = 287,
     KW_DICTIONARY = 288,
     KW_PRINTABLE_ASCII_STRING = 289,
     KW_UNICODE_STRING = 290
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 156 "hare-idl.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   464

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNRULES -- Number of states.  */
#define YYNSTATES  287

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      39,    40,     2,    47,    43,    48,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
      45,    41,    46,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,    44,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    16,    19,    22,
      27,    32,    36,    41,    46,    50,    58,    63,    68,    72,
      81,    86,    91,    95,   103,   106,   109,   112,   116,   120,
     127,   133,   137,   144,   150,   157,   167,   176,   179,   185,
     188,   191,   194,   197,   203,   206,   212,   221,   224,   228,
     232,   240,   246,   250,   258,   264,   266,   268,   270,   272,
     274,   276,   278,   280,   282,   284,   286,   288,   295,   302,
     309,   316,   325,   334,   343,   352,   359,   364,   369,   374,
     384,   389,   399,   406,   411,   416,   421,   426,   433,   440,
     447,   454,   457,   463,   467,   473,   477,   483,   485,   489,
     491,   494,   497,   499,   502,   505,   507,   509,   513,   517
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    -1,    50,    51,    -1,    50,    53,    -1,
      50,    55,    -1,    50,    57,    -1,    50,    59,    -1,    50,
      64,    -1,     4,    66,    21,    36,    -1,     4,    21,    21,
      36,    -1,     3,    21,    37,    -1,    52,    66,    21,    36,
      -1,    52,    21,    21,    36,    -1,    52,    38,    36,    -1,
       7,    39,    78,    40,     3,    21,    37,    -1,    54,    66,
      21,    36,    -1,    54,    21,    21,    36,    -1,    54,    38,
      36,    -1,     7,    39,    78,    40,    37,    15,    22,    37,
      -1,    56,    16,    21,    36,    -1,    56,    38,    38,    36,
      -1,    56,    38,    38,    -1,     8,    39,    78,    40,     3,
      21,    37,    -1,    58,    60,    -1,    58,    62,    -1,    58,
      11,    -1,    58,    38,    36,    -1,    66,    21,    36,    -1,
      66,    21,    14,    41,    80,    36,    -1,    12,    21,    13,
      66,    36,    -1,    21,    21,    36,    -1,    21,    21,    14,
      41,    80,    36,    -1,    12,    21,    13,    21,    36,    -1,
      21,    39,    78,    40,    21,    36,    -1,    21,    39,    78,
      40,    21,    14,    41,    80,    36,    -1,    12,    21,    13,
      21,    39,    78,    40,    36,    -1,    21,    37,    -1,    21,
      39,    78,    40,    37,    -1,    61,    60,    -1,    61,    62,
      -1,    61,    38,    -1,    21,    60,    -1,    21,    39,    78,
      40,    60,    -1,    21,    62,    -1,    21,    39,    78,    40,
      62,    -1,    17,    39,    18,    41,    21,    40,    21,    37,
      -1,    63,    65,    -1,    63,    38,    36,    -1,    66,    21,
      36,    -1,    66,    21,    19,    37,    79,    38,    36,    -1,
      66,    21,    20,    21,    36,    -1,    21,    21,    36,    -1,
      21,    21,    19,    37,    79,    38,    36,    -1,    21,    21,
      20,    21,    36,    -1,    67,    -1,    68,    -1,    69,    -1,
      70,    -1,    71,    -1,    72,    -1,    73,    -1,    74,    -1,
      76,    -1,    75,    -1,    34,    -1,    35,    -1,    26,    42,
      80,    43,    80,    44,    -1,    26,    39,    80,    43,    80,
      44,    -1,    26,    42,    80,    43,    80,    40,    -1,    26,
      39,    80,    43,    80,    40,    -1,    27,    42,    80,    43,
      80,    43,    80,    44,    -1,    27,    39,    80,    43,    80,
      43,    80,    44,    -1,    27,    42,    80,    43,    80,    43,
      80,    40,    -1,    27,    39,    80,    43,    80,    43,    80,
      40,    -1,    28,    39,    80,    43,    80,    40,    -1,    29,
      37,    22,    38,    -1,    29,    37,    81,    38,    -1,    30,
      37,    22,    38,    -1,    30,    37,    22,    38,    42,    80,
      43,    80,    44,    -1,    30,    37,    81,    38,    -1,    30,
      37,    81,    38,    42,    80,    43,    80,    44,    -1,    31,
      42,    80,    43,    80,    44,    -1,    32,    45,    66,    46,
      -1,    32,    45,    21,    46,    -1,    21,    45,    66,    46,
      -1,    21,    45,    21,    46,    -1,    33,    45,    66,    43,
      66,    46,    -1,    33,    45,    21,    43,    66,    46,    -1,
      33,    45,    66,    43,    21,    46,    -1,    33,    45,    21,
      43,    21,    46,    -1,     6,    21,    -1,     5,    21,    37,
      77,    38,    -1,    21,    41,    23,    -1,    77,    43,    21,
      41,    23,    -1,    21,    41,    80,    -1,    78,    43,    21,
      41,    80,    -1,    21,    -1,    79,    43,    21,    -1,    23,
      -1,    47,    23,    -1,    48,    23,    -1,    25,    -1,    47,
      25,    -1,    48,    25,    -1,    22,    -1,    23,    -1,    23,
      48,    23,    -1,    81,    43,    23,    -1,    81,    43,    23,
      48,    23,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    49,    49,    50,    51,    52,    53,    54,    55,    59,
      60,    64,    65,    66,    70,    74,    75,    76,    80,    84,
      85,    89,    90,    95,    96,    97,    98,   102,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   118,   119,   120,
     121,   125,   126,   127,   128,   129,   133,   134,   138,   142,
     143,   144,   145,   146,   147,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   167,   168,   169,
     170,   174,   175,   176,   177,   181,   185,   186,   190,   191,
     192,   193,   197,   201,   202,   203,   204,   208,   209,   210,
     211,   215,   219,   223,   224,   228,   229,   233,   234,   238,
     239,   240,   241,   242,   243,   244,   248,   249,   250,   251
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_PUBLISHABLE_STRUCT", "KW_TYPEDEF",
  "KW_ENUM", "KW_CLASS", "KW_MAPPING", "KW_ENCODING", "KW_NUMERIC",
  "KW_INT", "KW_FENCE", "KW_EXTEND", "KW_TO", "KW_DEFAULT", "KW_FILE",
  "KW_CLASS_UPP", "KW_DISCRIMINATED_UNION", "KW_DISCRIMINANT",
  "KW_WHEN_DISCRIMINANT_IN", "KW_WHEN_DISCRIMINANT_IS", "IDENTIFIER",
  "STRING_LITERAL", "INTEGER_LITERAL", "CHAR_LITERAL", "FLOAT_LITERAL",
  "KW_INTEGER", "KW_FIXED_POINT", "KW_FLOATING_POINT", "KW_CHARACTER",
  "KW_CHARACTER_STRING", "KW_BIT_STRING", "KW_SEQUENCE", "KW_DICTIONARY",
  "KW_PRINTABLE_ASCII_STRING", "KW_UNICODE_STRING", "';'", "'{'", "'}'",
  "'('", "')'", "'='", "'['", "','", "']'", "'<'", "'>'", "'+'", "'-'",
  "$accept", "file", "typedef_decl", "publishable_struct_begin",
  "publishable_struct", "mapping_begin", "mapping",
  "ext_file_mapping_begin", "ext_file_mapping", "encoding_begin",
  "encoding", "data_element", "data_group_begin", "data_group",
  "discriminated_union_begin", "discriminated_union", "union_data_element",
  "data_type", "integer_type", "fixed_point_type", "floating_point_type",
  "character_type", "character_string_type", "bit_string_type",
  "sequence_type", "dictionary_type", "class_ref_type", "inline_enum_type",
  "enum_values", "arg_list", "id_list", "expr", "character_set", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,    59,   123,   125,    40,
      41,    61,    91,    44,    93,    60,    62,    43,    45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    50,    50,    50,    50,    50,    51,
      51,    52,    52,    52,    53,    54,    54,    54,    55,    56,
      56,    57,    57,    58,    58,    58,    58,    59,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    61,    61,    61,
      61,    62,    62,    62,    62,    62,    63,    63,    64,    65,
      65,    65,    65,    65,    65,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    67,    67,    67,
      67,    68,    68,    68,    68,    69,    70,    70,    71,    71,
      71,    71,    72,    73,    73,    73,    73,    74,    74,    74,
      74,    75,    76,    77,    77,    78,    78,    79,    79,    80,
      80,    80,    80,    80,    80,    80,    81,    81,    81,    81
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     4,
       4,     3,     4,     4,     3,     7,     4,     4,     3,     8,
       4,     4,     3,     7,     2,     2,     2,     3,     3,     6,
       5,     3,     6,     5,     6,     9,     8,     2,     5,     2,
       2,     2,     2,     5,     2,     5,     8,     2,     3,     3,
       7,     5,     3,     7,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     6,     6,     6,
       6,     8,     8,     8,     8,     6,     4,     4,     4,     9,
       4,     9,     6,     4,     4,     4,     4,     6,     6,     6,
       6,     2,     5,     3,     5,     3,     5,     1,     3,     1,
       2,     2,     1,     2,     2,     1,     1,     3,     3,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     3,     0,
       4,     0,     5,     0,     6,     0,     7,     0,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,     0,    55,    56,    57,    58,    59,    60,
      61,    62,    64,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    26,     0,     0,     0,    24,
       0,    25,     0,     0,     0,    47,     0,    11,     0,    91,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    14,     0,
       0,    18,     0,     0,    22,     0,     0,    37,     0,    42,
      44,    27,    41,    39,    40,     0,     0,    48,     0,     0,
      10,     0,     0,   105,    99,   102,     0,     0,     0,     0,
       0,     0,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,     9,     0,     0,     0,     0,     0,    13,
      12,    17,    16,    20,    21,     0,     0,    31,     0,     0,
      28,     0,     0,    52,     0,     0,    49,     0,     0,    86,
      85,   100,   103,   101,   104,     0,     0,     0,     0,     0,
      76,     0,    77,     0,    78,    80,     0,    84,    83,     0,
       0,    95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,     0,     0,
       0,     0,     0,     0,   107,   108,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,     0,
      30,     0,     0,    38,    43,    45,     0,    97,     0,    54,
       0,    51,    93,     0,    70,    68,    69,    67,     0,     0,
      75,     0,     0,     0,    82,    90,    88,    89,    87,    15,
       0,    96,    23,     0,     0,    32,     0,    34,    29,     0,
       0,     0,     0,     0,     0,   109,     0,     0,    19,    46,
       0,     0,    53,    98,    50,    94,    74,    72,    73,    71,
       0,     0,    36,     0,    79,    81,    35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    99,    60,   100,    17,    18,    65,    62,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,   158,    84,
     228,   118,   125
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -74
static const yytype_int16 yypact[] =
{
     -74,    62,   -74,    43,   317,    52,    70,    74,   -74,   233,
     -74,   251,   -74,    35,   -74,   143,   -74,   269,   -74,    64,
     110,   114,   -16,    33,    69,    78,   131,   150,   105,   122,
     144,   -74,   -74,   167,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,   169,   169,   173,    11,   159,   175,
      12,   161,   178,   179,   164,   -74,   182,   180,   168,   -74,
     215,   -74,   184,    13,   186,   -74,   195,   -74,   181,   -74,
     187,   334,     2,     2,     2,     2,     2,   128,   130,     2,
     351,   368,   188,   185,    46,    72,   189,   192,   -74,   193,
     196,   -74,   197,   198,   199,   218,     9,   -74,   169,   -74,
     -74,   -74,   -74,   -74,   -74,    41,    40,   -74,    48,   216,
     -74,   111,   194,   -74,   -74,   -74,    -5,   118,   208,   209,
     212,   226,   227,   220,   225,   -12,   238,    44,   244,   113,
     242,   101,   248,   -74,     2,    10,   271,   290,   273,   -74,
     -74,   -74,   -74,   -74,   -74,   385,   267,   -74,    96,   268,
     -74,   274,   289,   -74,   276,   293,   -74,   275,    45,   -74,
     -74,   -74,   -74,   -74,   -74,     2,     2,     2,     2,     2,
     -74,   292,   -74,   294,   277,   278,     2,   -74,   -74,   402,
     419,   -74,   297,   309,   284,   315,   301,   -17,   306,     2,
     300,     2,   332,   318,   332,   322,   336,   -74,   349,   -28,
      34,   328,   333,   335,   -74,   339,     2,     2,   344,   115,
     346,   117,   347,   367,   383,     2,   372,   389,   -74,   169,
     -74,   386,    93,   -74,   -74,   -74,   390,   -74,    47,   -74,
      59,   -74,   -74,   380,   -74,   -74,   -74,   -74,     2,     2,
     -74,   404,   395,   396,   -74,   -74,   -74,   -74,   -74,   -74,
     405,   -74,   -74,   406,    97,   -74,   400,   -74,   -74,   408,
     434,   420,   435,    60,    66,   -74,     2,     2,   -74,   -74,
     421,     2,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
     415,   416,   -74,   425,   -74,   -74,   -74
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,    -8,   -74,    -7,   -74,   -74,   -74,     0,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -35,
     270,   -73,   384
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     119,   120,   121,   122,    33,    70,   128,    59,    61,    49,
      85,    52,   234,   182,    20,    21,   235,    66,   161,   218,
     162,    56,   219,   146,   113,   114,   172,   115,    71,    71,
      96,   173,    87,    90,   106,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,   147,    97,   183,    98,   116,
     117,    53,   103,   104,    71,   149,    71,    71,    71,   151,
     152,   181,     2,   148,    19,     3,     4,   154,   155,     5,
       6,   112,    72,    54,   236,    73,   153,   150,   237,     7,
     130,   132,   175,   197,   156,   259,   135,   173,   198,   136,
     260,    44,   199,   200,   201,   202,   203,   261,    20,    21,
     276,    67,   260,   208,   277,    56,   278,   256,    74,    45,
     279,    75,   137,    46,    96,   136,   221,    76,   226,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,   257,
      97,    68,    98,   242,   243,    69,   190,   270,    71,   136,
     136,   163,   251,   164,   179,   188,    71,    79,    20,    21,
     123,   124,   126,   124,    55,    56,    71,   159,    71,   177,
      71,   245,    71,   247,    57,   263,   264,    80,    77,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,   210,
     212,    58,   224,   225,   254,    20,    21,    78,    82,    81,
      83,    86,    56,   280,   281,    88,    89,    91,   283,    92,
      93,    96,    94,    95,   101,   105,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,   108,    97,   109,    98,
      20,    21,   107,   110,   133,    71,   134,    56,   139,   140,
     138,   145,   141,   142,   143,   144,    57,   157,    20,    21,
     160,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,   165,   166,   102,    47,   167,    20,    21,   170,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,   168,
     169,    48,    50,   171,    20,    21,   174,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,   176,   178,    51,
      63,   180,   184,   185,   186,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    20,    21,    64,   189,   191,
     193,   192,    56,   194,   195,   204,   196,   205,   213,   206,
     207,   222,    20,    21,   214,   215,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,   216,   223,    22,    20,
      21,   217,   220,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,   227,   229,   111,    20,    21,   231,   232,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
     233,   238,   129,    20,    21,   240,   239,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,   241,   244,   131,
      20,    21,   246,   248,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,   249,   250,   187,    20,    21,   252,
     253,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,   262,   255,   209,    20,    21,   258,   265,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,   266,   267,
     211,   271,   268,   269,   272,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,   273,   274,   282,   275,   284,
     285,   286,   127,     0,   230
};

static const yytype_int16 yycheck[] =
{
      73,    74,    75,    76,     4,    21,    79,    15,    15,     9,
      45,    11,    40,     3,     5,     6,    44,    17,    23,    36,
      25,    12,    39,    14,    22,    23,    38,    25,    45,    45,
      21,    43,    21,    21,    21,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    37,    39,    47,
      48,    16,    60,    60,    45,    14,    45,    45,    45,    19,
      20,   134,     0,    98,    21,     3,     4,    19,    20,     7,
       8,    71,    39,    38,    40,    42,    36,    36,    44,    17,
      80,    81,    38,    38,    36,    38,    40,    43,    43,    43,
      43,    39,   165,   166,   167,   168,   169,    38,     5,     6,
      40,    37,    43,   176,    44,    12,    40,    14,    39,    39,
      44,    42,    40,    39,    21,    43,   189,    39,   191,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    21,    39,   206,   207,    21,    40,    40,    45,    43,
      43,    23,   215,    25,    43,   145,    45,    42,     5,     6,
      22,    23,    22,    23,    11,    12,    45,    46,    45,    46,
      45,    46,    45,    46,    21,   238,   239,    45,    37,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,   179,
     180,    38,   190,   190,   219,     5,     6,    37,    21,    45,
      21,    18,    12,   266,   267,    36,    21,    36,   271,    21,
      21,    21,    38,    21,    36,    21,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    21,    37,    37,    39,
       5,     6,    36,    36,    36,    45,    41,    12,    36,    36,
      41,    13,    36,    36,    36,    36,    21,    21,     5,     6,
      46,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    43,    43,    38,    21,    43,     5,     6,    38,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    43,
      43,    38,    21,    48,     5,     6,    38,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    43,    46,    38,
      21,    43,    21,     3,    21,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,     5,     6,    38,    41,    41,
      21,    37,    12,    37,    21,    23,    41,    23,    21,    42,
      42,    21,     5,     6,    15,    41,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    21,    37,    21,     5,
       6,    40,    36,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    21,    36,    21,     5,     6,    36,    23,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      21,    43,    21,     5,     6,    40,    43,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    48,    44,    21,
       5,     6,    46,    46,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    37,    22,    21,     5,     6,    37,
      21,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    41,    36,    21,     5,     6,    36,    23,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    43,    43,
      21,    41,    37,    37,    36,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    21,    36,    36,    23,    44,
      44,    36,    78,    -1,   194
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,     0,     3,     4,     7,     8,    17,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    63,    64,    21,
       5,     6,    21,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    39,    39,    39,    21,    38,    66,
      21,    38,    66,    16,    38,    11,    12,    21,    38,    60,
      61,    62,    66,    21,    38,    65,    66,    37,    21,    21,
      21,    45,    39,    42,    39,    42,    39,    37,    37,    42,
      45,    45,    21,    21,    78,    78,    18,    21,    36,    21,
      21,    36,    21,    21,    38,    21,    21,    37,    39,    60,
      62,    36,    38,    60,    62,    21,    21,    36,    21,    37,
      36,    21,    66,    22,    23,    25,    47,    48,    80,    80,
      80,    80,    80,    22,    23,    81,    22,    81,    80,    21,
      66,    21,    66,    36,    41,    40,    43,    40,    41,    36,
      36,    36,    36,    36,    36,    13,    14,    36,    78,    14,
      36,    19,    20,    36,    19,    20,    36,    21,    77,    46,
      46,    23,    25,    23,    25,    43,    43,    43,    43,    43,
      38,    48,    38,    43,    38,    38,    43,    46,    46,    43,
      43,    80,     3,    37,    21,     3,    21,    21,    66,    41,
      40,    41,    37,    21,    37,    21,    41,    38,    43,    80,
      80,    80,    80,    80,    23,    23,    42,    42,    80,    21,
      66,    21,    66,    21,    15,    41,    21,    40,    36,    39,
      36,    80,    21,    37,    60,    62,    80,    21,    79,    36,
      79,    36,    23,    21,    40,    44,    40,    44,    43,    43,
      40,    48,    80,    80,    44,    46,    46,    46,    46,    37,
      22,    80,    37,    21,    78,    36,    14,    36,    36,    38,
      43,    38,    41,    80,    80,    23,    43,    43,    37,    37,
      40,    41,    36,    21,    36,    23,    40,    44,    40,    44,
      80,    80,    36,    80,    44,    44,    36
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 3: /* "KW_PUBLISHABLE_STRUCT" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1336 "hare-idl.tab.c"
	break;
      case 4: /* "KW_TYPEDEF" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1345 "hare-idl.tab.c"
	break;
      case 5: /* "KW_ENUM" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1354 "hare-idl.tab.c"
	break;
      case 6: /* "KW_CLASS" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1363 "hare-idl.tab.c"
	break;
      case 7: /* "KW_MAPPING" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1372 "hare-idl.tab.c"
	break;
      case 8: /* "KW_ENCODING" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1381 "hare-idl.tab.c"
	break;
      case 9: /* "KW_NUMERIC" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1390 "hare-idl.tab.c"
	break;
      case 10: /* "KW_INT" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1399 "hare-idl.tab.c"
	break;
      case 11: /* "KW_FENCE" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1408 "hare-idl.tab.c"
	break;
      case 12: /* "KW_EXTEND" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1417 "hare-idl.tab.c"
	break;
      case 13: /* "KW_TO" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1426 "hare-idl.tab.c"
	break;
      case 14: /* "KW_DEFAULT" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1435 "hare-idl.tab.c"
	break;
      case 15: /* "KW_FILE" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1444 "hare-idl.tab.c"
	break;
      case 16: /* "KW_CLASS_UPP" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1453 "hare-idl.tab.c"
	break;
      case 17: /* "KW_DISCRIMINATED_UNION" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1462 "hare-idl.tab.c"
	break;
      case 18: /* "KW_DISCRIMINANT" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1471 "hare-idl.tab.c"
	break;
      case 19: /* "KW_WHEN_DISCRIMINANT_IN" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1480 "hare-idl.tab.c"
	break;
      case 20: /* "KW_WHEN_DISCRIMINANT_IS" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1489 "hare-idl.tab.c"
	break;
      case 21: /* "IDENTIFIER" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1498 "hare-idl.tab.c"
	break;
      case 22: /* "STRING_LITERAL" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1507 "hare-idl.tab.c"
	break;
      case 23: /* "INTEGER_LITERAL" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1516 "hare-idl.tab.c"
	break;
      case 24: /* "CHAR_LITERAL" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1525 "hare-idl.tab.c"
	break;
      case 25: /* "FLOAT_LITERAL" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1534 "hare-idl.tab.c"
	break;
      case 26: /* "KW_INTEGER" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1543 "hare-idl.tab.c"
	break;
      case 27: /* "KW_FIXED_POINT" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1552 "hare-idl.tab.c"
	break;
      case 28: /* "KW_FLOATING_POINT" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1561 "hare-idl.tab.c"
	break;
      case 29: /* "KW_CHARACTER" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1570 "hare-idl.tab.c"
	break;
      case 30: /* "KW_CHARACTER_STRING" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1579 "hare-idl.tab.c"
	break;
      case 31: /* "KW_BIT_STRING" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1588 "hare-idl.tab.c"
	break;
      case 32: /* "KW_SEQUENCE" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1597 "hare-idl.tab.c"
	break;
      case 33: /* "KW_DICTIONARY" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1606 "hare-idl.tab.c"
	break;
      case 34: /* "KW_PRINTABLE_ASCII_STRING" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1615 "hare-idl.tab.c"
	break;
      case 35: /* "KW_UNICODE_STRING" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1624 "hare-idl.tab.c"
	break;
      case 36: /* "';'" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1633 "hare-idl.tab.c"
	break;
      case 37: /* "'{'" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1642 "hare-idl.tab.c"
	break;
      case 38: /* "'}'" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1651 "hare-idl.tab.c"
	break;
      case 39: /* "'('" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1660 "hare-idl.tab.c"
	break;
      case 40: /* "')'" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1669 "hare-idl.tab.c"
	break;
      case 41: /* "'='" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1678 "hare-idl.tab.c"
	break;
      case 42: /* "'['" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1687 "hare-idl.tab.c"
	break;
      case 43: /* "','" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1696 "hare-idl.tab.c"
	break;
      case 44: /* "']'" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1705 "hare-idl.tab.c"
	break;
      case 45: /* "'<'" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1714 "hare-idl.tab.c"
	break;
      case 46: /* "'>'" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1723 "hare-idl.tab.c"
	break;
      case 47: /* "'+'" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1732 "hare-idl.tab.c"
	break;
      case 48: /* "'-'" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1741 "hare-idl.tab.c"
	break;
      case 50: /* "file" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1750 "hare-idl.tab.c"
	break;
      case 51: /* "typedef_decl" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1759 "hare-idl.tab.c"
	break;
      case 52: /* "publishable_struct_begin" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1768 "hare-idl.tab.c"
	break;
      case 53: /* "publishable_struct" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1777 "hare-idl.tab.c"
	break;
      case 54: /* "mapping_begin" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1786 "hare-idl.tab.c"
	break;
      case 55: /* "mapping" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1795 "hare-idl.tab.c"
	break;
      case 56: /* "ext_file_mapping_begin" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1804 "hare-idl.tab.c"
	break;
      case 57: /* "ext_file_mapping" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1813 "hare-idl.tab.c"
	break;
      case 58: /* "encoding_begin" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1822 "hare-idl.tab.c"
	break;
      case 59: /* "encoding" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1831 "hare-idl.tab.c"
	break;
      case 60: /* "data_element" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1840 "hare-idl.tab.c"
	break;
      case 61: /* "data_group_begin" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1849 "hare-idl.tab.c"
	break;
      case 62: /* "data_group" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1858 "hare-idl.tab.c"
	break;
      case 63: /* "discriminated_union_begin" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1867 "hare-idl.tab.c"
	break;
      case 64: /* "discriminated_union" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1876 "hare-idl.tab.c"
	break;
      case 65: /* "union_data_element" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1885 "hare-idl.tab.c"
	break;
      case 66: /* "data_type" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1894 "hare-idl.tab.c"
	break;
      case 67: /* "integer_type" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1903 "hare-idl.tab.c"
	break;
      case 68: /* "fixed_point_type" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1912 "hare-idl.tab.c"
	break;
      case 69: /* "floating_point_type" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1921 "hare-idl.tab.c"
	break;
      case 70: /* "character_type" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1930 "hare-idl.tab.c"
	break;
      case 71: /* "character_string_type" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1939 "hare-idl.tab.c"
	break;
      case 72: /* "bit_string_type" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1948 "hare-idl.tab.c"
	break;
      case 73: /* "sequence_type" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1957 "hare-idl.tab.c"
	break;
      case 74: /* "dictionary_type" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1966 "hare-idl.tab.c"
	break;
      case 75: /* "class_ref_type" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1975 "hare-idl.tab.c"
	break;
      case 76: /* "inline_enum_type" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1984 "hare-idl.tab.c"
	break;
      case 77: /* "enum_values" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1993 "hare-idl.tab.c"
	break;
      case 78: /* "arg_list" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2002 "hare-idl.tab.c"
	break;
      case 79: /* "id_list" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2011 "hare-idl.tab.c"
	break;
      case 80: /* "expr" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2020 "hare-idl.tab.c"
	break;
      case 81: /* "character_set" */

/* Line 1000 of yacc.c  */
#line 40 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2029 "hare-idl.tab.c"
	break;

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 49 "hare-idl.y"
    { (yyval) = 0; ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 50 "hare-idl.y"
    { (yyval) = addTypedefToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 51 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 52 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 53 "hare-idl.y"
    { (yyval) = processExtFileMapping((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 54 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 55 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 59 "hare-idl.y"
    { (yyval) = createTypedef((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 60 "hare-idl.y"
    { (yyval) = createTypedef((yyvsp[(1) - (4)]), createIdType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)])); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 64 "hare-idl.y"
    { (yyval) = createPublishableStruct((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 65 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]))); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 66 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute(createIdType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)]))); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 70 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 74 "hare-idl.y"
    { (yyval) = createMapping((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(6) - (7)])); releaseYys4((yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 75 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])));  releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 76 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute(createIdType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)])));  releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 80 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 84 "hare-idl.y"
    { (yyval) = createExtFileMapping((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(7) - (8)])); releaseYys5((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 85 "hare-idl.y"
    { (yyval) = addClassMapping((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 89 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (4)]); releaseYys3((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 90 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 95 "hare-idl.y"
    { (yyval) = createEncoding((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(6) - (7)])); releaseYys4((yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 96 "hare-idl.y"
    { (yyval) = addToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 97 "hare-idl.y"
    { (yyval) = addToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 98 "hare-idl.y"
    { (yyval) = addFenceToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 102 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 106 "hare-idl.y"
    { (yyval) = createAttribute((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 107 "hare-idl.y"
    { (yyval) = createEncodingAttribute((yyvsp[(1) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 108 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); releaseYys3((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 109 "hare-idl.y"
    { (yyval) = createAttribute(createIdType((yyvsp[(1) - (3)])), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 110 "hare-idl.y"
    { (yyval) = createEncodingAttribute(createIdType((yyvsp[(1) - (6)])), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)]));;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 111 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (5)]), createIdType((yyvsp[(4) - (5)]))); releaseYys3((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 112 "hare-idl.y"
    { (yyval) = createAttribute(createEncodingType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)])), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 113 "hare-idl.y"
    { (yyval) = createEncodingAttribute(createEncodingType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)])), (yyvsp[(5) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 114 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (8)]), createEncodingType((yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]))); releaseYys5((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 118 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, 0); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 119 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), 0); releaseYys3((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 120 "hare-idl.y"
    { (yyval) = addToEncodingGroup((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 121 "hare-idl.y"
    { (yyval) = addToEncodingGroup((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 125 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (2)]); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 126 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 127 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 128 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 129 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 133 "hare-idl.y"
    { (yyval) = createUnion((yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)])); releaseYys5((yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 134 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 138 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 142 "hare-idl.y"
    { (yyval) = createAttribute((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 143 "hare-idl.y"
    { (yyval) = createUnionAttribute((yyvsp[(1) - (7)]), (yyvsp[(2) - (7)]), (yyvsp[(5) - (7)])); releaseYys4((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 144 "hare-idl.y"
    { (yyval) = createUnionAttribute((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), addIdentifier(0, (yyvsp[(4) - (5)]))); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 145 "hare-idl.y"
    { (yyval) = createAttribute(createIdType((yyvsp[(1) - (3)])), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 146 "hare-idl.y"
    { (yyval) = createUnionAttribute(createIdType((yyvsp[(1) - (7)])), (yyvsp[(2) - (7)]), (yyvsp[(5) - (7)])); releaseYys4((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 147 "hare-idl.y"
    { (yyval) = createUnionAttribute(createIdType((yyvsp[(1) - (5)])), (yyvsp[(2) - (5)]), addIdentifier(0, (yyvsp[(4) - (5)]))); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 162 "hare-idl.y"
    { (yyval) = createPrintableAsciiStringType((yyvsp[(1) - (1)])); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 163 "hare-idl.y"
    { (yyval) = createUnicodeStringType((yyvsp[(1) - (1)])); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 167 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 168 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 169 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 170 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 174 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), true, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), true); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 175 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), false, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), true); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 176 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), true, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), false); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 177 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), false, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), false); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 181 "hare-idl.y"
    { (yyval) = createFloatingPointType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 185 "hare-idl.y"
    { (yyval) = createCharacterType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 186 "hare-idl.y"
    { (yyval) = createCharacterType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 190 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), 0, 0); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 191 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 192 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), 0, 0); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 193 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 197 "hare-idl.y"
    { (yyval) = createBitStringType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 201 "hare-idl.y"
    { (yyval) = createSequence((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 202 "hare-idl.y"
    { (yyval) = createSequence((yyvsp[(1) - (4)]), createIdType((yyvsp[(3) - (4)]))); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 203 "hare-idl.y"
    { (yyval) = createNamedSequence((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 204 "hare-idl.y"
    { (yyval) = createNamedSequence((yyvsp[(1) - (4)]), createIdType((yyvsp[(3) - (4)]))); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 208 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 209 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 210 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 211 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 215 "hare-idl.y"
    { (yyval) = createClassReference((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 219 "hare-idl.y"
    { (yyval) = createInlineEnum((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 223 "hare-idl.y"
    { (yyval) = addEnumValue(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 224 "hare-idl.y"
    { (yyval) = addEnumValue((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 228 "hare-idl.y"
    { (yyval) = addExpression(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 229 "hare-idl.y"
    { (yyval) = addExpression((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 233 "hare-idl.y"
    { (yyval) = addIdentifier(0, (yyvsp[(1) - (1)])); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 234 "hare-idl.y"
    { (yyval) = addIdentifier((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 238 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 239 "hare-idl.y"
    { (yyval) = (yyvsp[(2) - (2)]); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 240 "hare-idl.y"
    { (yyval) = makeMinusIntLit((yyvsp[(2) - (2)])); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 241 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 242 "hare-idl.y"
    { (yyval) = (yyvsp[(2) - (2)]); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 243 "hare-idl.y"
    { (yyval) = makeMinusFloatLit((yyvsp[(2) - (2)])); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 244 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 248 "hare-idl.y"
    { (yyval) = addToCharSet(0, (yyvsp[(1) - (1)]), 0); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 249 "hare-idl.y"
    { (yyval) = addToCharSet(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 250 "hare-idl.y"
    { (yyval) = addToCharSet((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 0);  releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 251 "hare-idl.y"
    { (yyval) = addToCharSet((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;



/* Line 1455 of yacc.c  */
#line 3020 "hare-idl.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



