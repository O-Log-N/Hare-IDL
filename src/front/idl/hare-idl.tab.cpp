
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
#line 46 "hare-idl.y"

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
     KW_IDENTIFIER = 279,
     STRING_LITERAL = 280,
     INTEGER_LITERAL = 281,
     CHAR_LITERAL = 282,
     FLOAT_LITERAL = 283,
     KW_INTEGER = 284,
     KW_FIXED_POINT = 285,
     KW_FLOATING_POINT = 286,
     KW_CHARACTER = 287,
     KW_CHARACTER_STRING = 288,
     KW_BIT_STRING = 289,
     KW_SEQUENCE = 290,
     KW_DICTIONARY = 291,
     KW_PRINTABLE_ASCII_STRING = 292,
     KW_UNICODE_STRING = 293,
     OP_FOUR_DOTS = 294
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
#line 160 "hare-idl.tab.c"

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
#define YYLAST   595

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNRULES -- Number of states.  */
#define YYNSTATES  332

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      43,    44,     2,    51,    47,    52,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
      49,    45,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,    48,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    16,    19,    22,
      25,    29,    34,    39,    44,    48,    53,    58,    62,    70,
      77,    80,    85,    90,    94,   103,   108,   113,   117,   125,
     128,   131,   134,   137,   141,   145,   152,   158,   162,   169,
     175,   182,   192,   201,   204,   210,   213,   216,   219,   222,
     228,   231,   237,   246,   249,   253,   257,   265,   271,   275,
     283,   289,   291,   293,   295,   297,   299,   301,   303,   305,
     307,   309,   311,   313,   315,   317,   319,   321,   328,   335,
     342,   349,   358,   367,   376,   385,   392,   397,   402,   407,
     417,   422,   432,   439,   444,   449,   454,   459,   466,   473,
     480,   487,   494,   501,   508,   515,   518,   521,   527,   531,
     537,   544,   553,   557,   563,   565,   569,   571,   574,   577,
     579,   582,   585,   587,   589,   593,   597,   603,   605,   608
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      54,     0,    -1,    -1,    54,    55,    -1,    54,    56,    -1,
      54,    58,    -1,    54,    60,    -1,    54,    62,    -1,    54,
      64,    -1,    54,    69,    -1,     3,    26,    40,    -1,     3,
      26,    25,    40,    -1,     5,    72,    23,    40,    -1,     5,
      23,    23,    40,    -1,     4,    23,    41,    -1,    57,    72,
      23,    40,    -1,    57,    23,    23,    40,    -1,    57,    42,
      40,    -1,     9,    43,    84,    44,     4,    23,    41,    -1,
       9,    43,    44,     4,    23,    41,    -1,    59,    55,    -1,
      59,    71,    23,    40,    -1,    59,    23,    23,    40,    -1,
      59,    42,    40,    -1,     9,    43,    84,    44,    41,    17,
      25,    41,    -1,    61,    18,    23,    40,    -1,    61,    42,
      42,    40,    -1,    61,    42,    42,    -1,    10,    43,    84,
      44,     4,    23,    41,    -1,    63,    55,    -1,    63,    65,
      -1,    63,    67,    -1,    63,    13,    -1,    63,    42,    40,
      -1,    72,    23,    40,    -1,    72,    23,    16,    45,    86,
      40,    -1,    14,    23,    15,    72,    40,    -1,    23,    23,
      40,    -1,    23,    23,    16,    45,    86,    40,    -1,    14,
      23,    15,    23,    40,    -1,    23,    43,    84,    44,    23,
      40,    -1,    23,    43,    84,    44,    23,    16,    45,    86,
      40,    -1,    14,    23,    15,    23,    43,    84,    44,    40,
      -1,    23,    41,    -1,    23,    43,    84,    44,    41,    -1,
      66,    65,    -1,    66,    67,    -1,    66,    42,    -1,    23,
      65,    -1,    23,    43,    84,    44,    65,    -1,    23,    67,
      -1,    23,    43,    84,    44,    67,    -1,    19,    43,    20,
      45,    23,    44,    23,    41,    -1,    68,    70,    -1,    68,
      42,    40,    -1,    72,    23,    40,    -1,    72,    23,    21,
      41,    85,    42,    40,    -1,    72,    23,    22,    23,    40,
      -1,    23,    23,    40,    -1,    23,    23,    21,    41,    85,
      42,    40,    -1,    23,    23,    22,    23,    40,    -1,    79,
      -1,    80,    -1,    82,    -1,    81,    -1,    73,    -1,    74,
      -1,    75,    -1,    76,    -1,    77,    -1,    78,    -1,    79,
      -1,    80,    -1,    82,    -1,    81,    -1,    37,    -1,    38,
      -1,    29,    46,    86,    47,    86,    48,    -1,    29,    43,
      86,    47,    86,    48,    -1,    29,    46,    86,    47,    86,
      44,    -1,    29,    43,    86,    47,    86,    44,    -1,    30,
      46,    86,    47,    86,    47,    86,    48,    -1,    30,    43,
      86,    47,    86,    47,    86,    48,    -1,    30,    46,    86,
      47,    86,    47,    86,    44,    -1,    30,    43,    86,    47,
      86,    47,    86,    44,    -1,    31,    43,    86,    47,    86,
      44,    -1,    32,    41,    25,    42,    -1,    32,    41,    87,
      42,    -1,    33,    41,    25,    42,    -1,    33,    41,    25,
      42,    46,    86,    47,    86,    48,    -1,    33,    41,    87,
      42,    -1,    33,    41,    87,    42,    46,    86,    47,    86,
      48,    -1,    34,    46,    86,    47,    86,    48,    -1,    35,
      49,    72,    50,    -1,    35,    49,    23,    50,    -1,    23,
      49,    72,    50,    -1,    23,    49,    23,    50,    -1,    36,
      49,    72,    47,    72,    50,    -1,    36,    49,    23,    47,
      72,    50,    -1,    36,    49,    72,    47,    23,    50,    -1,
      36,    49,    23,    47,    23,    50,    -1,    23,    49,    72,
      47,    72,    50,    -1,    23,    49,    23,    47,    72,    50,
      -1,    23,    49,    72,    47,    23,    50,    -1,    23,    49,
      23,    47,    23,    50,    -1,     7,    88,    -1,     8,    88,
      -1,     6,    88,    41,    83,    42,    -1,    23,    45,    26,
      -1,    83,    47,    23,    45,    26,    -1,    24,    43,    25,
      44,    45,    26,    -1,    83,    47,    24,    43,    25,    44,
      45,    26,    -1,    23,    45,    86,    -1,    84,    47,    23,
      45,    86,    -1,    23,    -1,    85,    47,    23,    -1,    26,
      -1,    51,    26,    -1,    52,    26,    -1,    28,    -1,    51,
      28,    -1,    52,    28,    -1,    25,    -1,    26,    -1,    26,
      52,    26,    -1,    87,    47,    26,    -1,    87,    47,    26,
      52,    26,    -1,    23,    -1,    39,    23,    -1,    88,    39,
      23,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    53,    53,    54,    55,    56,    57,    58,    59,    60,
      64,    65,    69,    70,    74,    75,    76,    80,    84,    85,
      86,    87,    88,    92,    96,    97,   101,   102,   107,   108,
     109,   110,   111,   115,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   131,   132,   133,   134,   138,   139,   140,
     141,   142,   146,   147,   151,   155,   156,   157,   158,   159,
     160,   165,   166,   167,   168,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   187,   188,   189,
     190,   194,   195,   196,   197,   201,   205,   206,   210,   211,
     212,   213,   217,   221,   222,   223,   224,   228,   229,   230,
     231,   232,   233,   234,   235,   239,   240,   244,   248,   249,
     250,   251,   255,   256,   260,   261,   265,   266,   267,   268,
     269,   270,   271,   275,   276,   277,   278,   282,   283,   284
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_HASH_LINE", "KW_PUBLISHABLE_STRUCT",
  "KW_TYPEDEF", "KW_ENUM", "KW_CLASS", "KW_STRUCT", "KW_MAPPING",
  "KW_ENCODING", "KW_NUMERIC", "KW_INT", "KW_FENCE", "KW_EXTEND", "KW_TO",
  "KW_DEFAULT", "KW_FILE", "KW_CLASS_UPP", "KW_DISCRIMINATED_UNION",
  "KW_DISCRIMINANT", "KW_WHEN_DISCRIMINANT_IN", "KW_WHEN_DISCRIMINANT_IS",
  "IDENTIFIER", "KW_IDENTIFIER", "STRING_LITERAL", "INTEGER_LITERAL",
  "CHAR_LITERAL", "FLOAT_LITERAL", "KW_INTEGER", "KW_FIXED_POINT",
  "KW_FLOATING_POINT", "KW_CHARACTER", "KW_CHARACTER_STRING",
  "KW_BIT_STRING", "KW_SEQUENCE", "KW_DICTIONARY",
  "KW_PRINTABLE_ASCII_STRING", "KW_UNICODE_STRING", "OP_FOUR_DOTS", "';'",
  "'{'", "'}'", "'('", "')'", "'='", "'['", "','", "']'", "'<'", "'>'",
  "'+'", "'-'", "$accept", "file", "line_directive", "typedef_decl",
  "publishable_struct_begin", "publishable_struct", "mapping_begin",
  "mapping", "ext_file_mapping_begin", "ext_file_mapping",
  "encoding_begin", "encoding", "encoding_element", "encoding_group_begin",
  "encoding_group", "discriminated_union_begin", "discriminated_union",
  "discriminated_union_element", "mapping_type", "data_type",
  "integer_type", "fixed_point_type", "floating_point_type",
  "character_type", "character_string_type", "bit_string_type",
  "sequence_type", "dictionary_type", "class_ref_type", "inline_enum_type",
  "enum_values", "arg_list", "id_list", "expr", "character_set", "qname", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
      59,   123,   125,    40,    41,    61,    91,    44,    93,    60,
      62,    43,    45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    56,    56,    57,    57,    57,    58,    59,    59,
      59,    59,    59,    60,    61,    61,    62,    62,    63,    63,
      63,    63,    63,    64,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    66,    66,    66,    66,    67,    67,    67,
      67,    67,    68,    68,    69,    70,    70,    70,    70,    70,
      70,    71,    71,    71,    71,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    73,    73,    73,
      73,    74,    74,    74,    74,    75,    76,    76,    77,    77,
      77,    77,    78,    79,    79,    79,    79,    80,    80,    80,
      80,    80,    80,    80,    80,    81,    81,    82,    83,    83,
      83,    83,    84,    84,    85,    85,    86,    86,    86,    86,
      86,    86,    86,    87,    87,    87,    87,    88,    88,    88
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       3,     4,     4,     4,     3,     4,     4,     3,     7,     6,
       2,     4,     4,     3,     8,     4,     4,     3,     7,     2,
       2,     2,     2,     3,     3,     6,     5,     3,     6,     5,
       6,     9,     8,     2,     5,     2,     2,     2,     2,     5,
       2,     5,     8,     2,     3,     3,     7,     5,     3,     7,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     6,     6,     6,
       6,     8,     8,     8,     8,     6,     4,     4,     4,     9,
       4,     9,     6,     4,     4,     4,     4,     6,     6,     6,
       6,     6,     6,     6,     6,     2,     2,     5,     3,     5,
       6,     8,     3,     5,     1,     3,     1,     2,     2,     1,
       2,     2,     1,     1,     3,     3,     5,     1,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     3,
       4,     0,     5,     0,     6,     0,     7,     0,     8,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    75,    76,     0,    65,    66,
      67,    68,    69,    70,    71,    72,    74,    73,     0,     0,
       0,     0,     0,     0,     0,     0,    20,     0,    61,    62,
      64,    63,     0,     0,    32,     0,     0,     0,    29,    30,
       0,    31,     0,     0,     0,    53,     0,     0,    10,    14,
     127,     0,     0,   105,   106,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,     0,     0,    23,     0,     0,
      27,     0,     0,    43,     0,    48,    50,    33,    47,    45,
      46,     0,     0,    54,     0,    11,   128,     0,     0,    13,
       0,     0,   122,   116,   119,     0,     0,     0,     0,     0,
       0,     0,     0,   123,     0,     0,     0,     0,     0,     0,
       0,     0,    12,     0,     0,     0,     0,     0,     0,    16,
      15,    22,    21,    25,    26,     0,     0,    37,     0,     0,
      34,     0,     0,    58,     0,     0,    55,   129,     0,     0,
       0,     0,    96,     0,    95,   117,   120,   118,   121,     0,
       0,     0,     0,     0,    86,     0,    87,     0,    88,    90,
       0,    94,    93,     0,     0,   112,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   124,   125,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,     0,     0,     0,    39,
       0,    36,     0,     0,    44,    49,    51,     0,   114,     0,
      60,     0,    57,   108,     0,     0,     0,   104,   102,   103,
     101,    80,    78,    79,    77,     0,     0,    85,     0,     0,
       0,    92,   100,    98,    99,    97,    18,     0,   113,    28,
       0,     0,    38,     0,    40,    35,     0,     0,     0,     0,
       0,     0,     0,     0,   126,     0,     0,    24,    52,     0,
       0,    59,   115,    56,     0,   109,     0,    84,    82,    83,
      81,     0,     0,    42,     0,   110,     0,    89,    91,    41,
       0,   111
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,   115,    70,   116,    19,    20,    75,    57,    72,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
     180,   100,   259,   137,   144,    82
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -89
static const yytype_int16 yypact[] =
{
     -89,   475,   -89,    62,    43,   292,   -26,    98,   104,   -89,
     -89,   220,   -89,   188,   -89,    30,   -89,   137,   -89,   240,
     -89,   106,   113,    31,    31,    31,    22,    93,   118,   141,
     151,   158,   156,   172,   180,   -89,   -89,   222,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,   -89,   -89,   -89,   -16,   238,
     248,    40,   250,   268,    45,   252,   -89,   270,   -89,   -89,
     -89,   -89,   271,   253,   -89,   274,    84,   272,   -89,   -89,
     202,   -89,   278,    60,   279,   -89,   290,   280,   -89,   -89,
     -89,   308,    67,   293,   293,   297,   310,     5,     5,     5,
       5,     5,   152,   194,     5,   328,   346,   298,   304,   351,
     138,   142,   305,   316,   -89,   327,   333,   -89,   334,   345,
     352,   353,     6,   -89,   238,   -89,   -89,   -89,   -89,   -89,
     -89,    -6,    89,   -89,   102,   -89,   -89,   363,   139,   -89,
      50,   143,   -89,   -89,   -89,    -3,   186,   344,   356,   357,
     362,   374,   368,   370,   -21,   385,   -15,   381,   192,   389,
     166,   393,   -89,     5,   422,    12,   423,   453,   435,   -89,
     -89,   -89,   -89,   -89,   -89,   364,   415,   -89,   153,   416,
     -89,   421,   440,   -89,   441,   454,   -89,   -89,   419,   433,
      17,   382,   -89,   400,   -89,   -89,   -89,   -89,   -89,     5,
       5,     5,     5,     5,   -89,   455,   -89,   457,   442,   443,
       5,   -89,   -89,   418,   436,   -89,   445,   464,   473,   446,
     469,   449,   -25,   456,     5,   273,     5,   472,   458,   472,
     459,   471,   476,   -89,   236,   215,   450,   217,   452,   108,
     109,   460,   461,   462,   -89,   451,     5,     5,   463,   234,
     465,   239,   466,   -89,   468,   479,     5,   477,   482,   -89,
     238,   -89,   470,    44,   -89,   -89,   -89,   474,   -89,    88,
     -89,    90,   -89,   -89,   478,   467,   480,   -89,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,     5,     5,   -89,   487,   481,
     483,   -89,   -89,   -89,   -89,   -89,   -89,   484,   -89,   -89,
     485,   154,   -89,   486,   -89,   -89,   489,   494,   492,   488,
     493,   495,   111,   132,   -89,     5,     5,   -89,   -89,   496,
       5,   -89,   -89,   -89,   498,   -89,   490,   -89,   -89,   -89,
     -89,   491,   497,   -89,   500,   -89,   499,   -89,   -89,   -89,
     501,   -89
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -89,   -89,   121,   -89,   -89,   -89,   -89,   -89,   -89,   -89,
     -89,   -89,    -9,   -89,    -8,   -89,   -89,   -89,   -89,     0,
     -89,   -89,   -89,   -89,   -89,   -89,   508,   522,   524,   525,
     -89,   -45,   322,   -88,   502,   261
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     138,   139,   140,   141,   101,    37,   147,    98,    69,    71,
     169,    53,    23,    24,    25,   249,   207,    48,   250,    76,
      65,   196,   166,   185,    86,   186,   197,   199,    99,   112,
     132,   133,   197,   134,   170,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    85,   167,   113,    62,   114,
      23,    24,    25,   208,    80,    86,   135,   136,    65,   223,
     293,   119,   120,   103,   224,   205,    22,   112,   106,   168,
      81,    86,    63,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,   122,   294,   113,   131,   114,    21,    86,
      23,    24,    25,    86,    86,   149,   151,   181,    65,    86,
     182,   229,   230,   231,   232,   233,   127,   112,   128,    86,
     171,   172,   238,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,   174,   175,   113,   252,   114,   257,   173,
     296,    77,   298,    86,    56,   297,    87,   297,    68,    88,
       3,    49,   176,    23,    24,    25,    78,    50,   279,   280,
      64,    65,   271,   273,    79,   317,   272,   274,   288,   318,
      66,    89,   178,   179,    90,   213,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,   319,   142,   143,    67,
     320,   226,   155,   228,    91,   156,   157,   302,   303,   156,
     183,     3,    92,   184,    23,    24,    25,   215,   309,    93,
     156,   156,    94,   240,   242,   291,   255,   256,    23,    24,
      25,    54,   187,   203,   188,    86,    65,   321,   322,   145,
     143,    95,   324,    33,    34,    66,    23,    24,    25,    96,
      55,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    86,   201,    51,   118,    97,    23,    24,    25,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,   265,
     266,    98,    52,    73,    86,   267,    86,   269,   102,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    23,
      24,    25,    74,    86,   282,    83,    84,    65,    86,   284,
     104,   105,   107,   108,   109,   110,   253,   111,    23,    24,
      25,   121,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,   117,   124,   254,    26,    23,    24,    25,   123,
     125,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,   126,   127,   130,    23,    24,    25,   129,   152,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,   153,
     158,   148,    23,    24,    25,   154,   159,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,   160,   165,   150,
      23,    24,    25,   161,   162,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,   163,   177,   212,    23,    24,
      25,   189,   164,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,   190,   191,   225,    23,    24,    25,   192,
     194,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,   193,   195,   227,    23,    24,    25,   198,   200,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,   202,
     204,   239,    23,    24,    25,   206,   209,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,   210,   211,   241,
     214,   216,   217,   218,   221,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,     2,   222,   220,     3,     4,
       5,   234,   219,   235,     6,     7,   243,   244,   236,   237,
     245,   246,   247,   248,     8,   258,   251,   263,   260,   262,
     268,   264,   270,   278,   287,   290,   277,   275,   276,   286,
     292,   281,   300,   304,   295,   283,   285,   312,   289,   315,
     316,    58,   299,   301,   325,   307,   308,   331,   305,   311,
     306,   310,   313,   314,   326,    59,   323,    60,    61,   327,
     329,   261,     0,     0,   330,   328,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   146
};

static const yytype_int16 yycheck[] =
{
      88,    89,    90,    91,    49,     5,    94,    23,    17,    17,
      16,    11,     6,     7,     8,    40,     4,    43,    43,    19,
      14,    42,    16,    26,    49,    28,    47,    42,    44,    23,
      25,    26,    47,    28,    40,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    23,    40,    41,    18,    43,
       6,     7,     8,    41,    23,    49,    51,    52,    14,    42,
      16,    70,    70,    23,    47,   153,    23,    23,    23,   114,
      39,    49,    42,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    23,    40,    41,    86,    43,    26,    49,
       6,     7,     8,    49,    49,    95,    96,    47,    14,    49,
      50,   189,   190,   191,   192,   193,    39,    23,    41,    49,
      21,    22,   200,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    21,    22,    41,   214,    43,   216,    40,
      42,    25,    42,    49,    13,    47,    43,    47,    17,    46,
       3,    43,    40,     6,     7,     8,    40,    43,   236,   237,
      13,    14,    44,    44,    41,    44,    48,    48,   246,    48,
      23,    43,    23,    24,    46,   165,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    44,    25,    26,    42,
      48,   181,    44,   183,    43,    47,    44,   275,   276,    47,
      47,     3,    41,    50,     6,     7,     8,    44,    44,    41,
      47,    47,    46,   203,   204,   250,   215,   215,     6,     7,
       8,    23,    26,    47,    28,    49,    14,   305,   306,    25,
      26,    49,   310,    35,    36,    23,     6,     7,     8,    49,
      42,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    49,    50,    23,    42,    23,     6,     7,     8,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    23,
      24,    23,    42,    23,    49,    50,    49,    50,    20,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,     6,
       7,     8,    42,    49,    50,    24,    25,    14,    49,    50,
      40,    23,    40,    23,    23,    42,    23,    23,     6,     7,
       8,    23,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    40,    23,    41,    23,     6,     7,     8,    40,
      40,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    23,    39,    23,     6,     7,     8,    40,    40,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    45,
      45,    23,     6,     7,     8,     4,    40,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    40,    15,    23,
       6,     7,     8,    40,    40,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    40,    23,    23,     6,     7,
       8,    47,    40,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    47,    47,    23,     6,     7,     8,    47,
      42,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    47,    52,    23,     6,     7,     8,    42,    47,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    50,
      47,    23,     6,     7,     8,    23,    23,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,     4,    23,    23,
      45,    45,    41,    23,    45,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,     0,    43,    23,     3,     4,
       5,    26,    41,    26,     9,    10,    41,    23,    46,    46,
      17,    45,    23,    44,    19,    23,    40,    26,    40,    40,
      50,    25,    50,    52,    25,    23,    44,    47,    47,    41,
      40,    48,    45,    26,    40,    50,    50,    23,    41,    26,
      25,    13,    44,    43,    26,    41,    41,    26,    47,    40,
      47,    45,    40,    45,    44,    13,    40,    13,    13,    48,
      40,   219,    -1,    -1,    45,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    54,     0,     3,     4,     5,     9,    10,    19,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    68,
      69,    26,    23,     6,     7,     8,    23,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    43,    43,
      43,    23,    42,    72,    23,    42,    55,    71,    79,    80,
      81,    82,    18,    42,    13,    14,    23,    42,    55,    65,
      66,    67,    72,    23,    42,    70,    72,    25,    40,    41,
      23,    39,    88,    88,    88,    23,    49,    43,    46,    43,
      46,    43,    41,    41,    46,    49,    49,    23,    23,    44,
      84,    84,    20,    23,    40,    23,    23,    40,    23,    23,
      42,    23,    23,    41,    43,    65,    67,    40,    42,    65,
      67,    23,    23,    40,    23,    40,    23,    39,    41,    40,
      23,    72,    25,    26,    28,    51,    52,    86,    86,    86,
      86,    86,    25,    26,    87,    25,    87,    86,    23,    72,
      23,    72,    40,    45,     4,    44,    47,    44,    45,    40,
      40,    40,    40,    40,    40,    15,    16,    40,    84,    16,
      40,    21,    22,    40,    21,    22,    40,    23,    23,    24,
      83,    47,    50,    47,    50,    26,    28,    26,    28,    47,
      47,    47,    47,    47,    42,    52,    42,    47,    42,    42,
      47,    50,    50,    47,    47,    86,    23,     4,    41,    23,
       4,    23,    23,    72,    45,    44,    45,    41,    23,    41,
      23,    45,    43,    42,    47,    23,    72,    23,    72,    86,
      86,    86,    86,    86,    26,    26,    46,    46,    86,    23,
      72,    23,    72,    41,    23,    17,    45,    23,    44,    40,
      43,    40,    86,    23,    41,    65,    67,    86,    23,    85,
      40,    85,    40,    26,    25,    23,    24,    50,    50,    50,
      50,    44,    48,    44,    48,    47,    47,    44,    52,    86,
      86,    48,    50,    50,    50,    50,    41,    25,    86,    41,
      23,    84,    40,    16,    40,    40,    42,    47,    42,    44,
      45,    43,    86,    86,    26,    47,    47,    41,    41,    44,
      45,    40,    23,    40,    45,    26,    25,    44,    48,    44,
      48,    86,    86,    40,    86,    26,    44,    48,    48,    40,
      45,    26
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
      case 3: /* "KW_HASH_LINE" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1401 "hare-idl.tab.c"
	break;
      case 4: /* "KW_PUBLISHABLE_STRUCT" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1410 "hare-idl.tab.c"
	break;
      case 5: /* "KW_TYPEDEF" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1419 "hare-idl.tab.c"
	break;
      case 6: /* "KW_ENUM" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1428 "hare-idl.tab.c"
	break;
      case 7: /* "KW_CLASS" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1437 "hare-idl.tab.c"
	break;
      case 8: /* "KW_STRUCT" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1446 "hare-idl.tab.c"
	break;
      case 9: /* "KW_MAPPING" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1455 "hare-idl.tab.c"
	break;
      case 10: /* "KW_ENCODING" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1464 "hare-idl.tab.c"
	break;
      case 11: /* "KW_NUMERIC" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1473 "hare-idl.tab.c"
	break;
      case 12: /* "KW_INT" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1482 "hare-idl.tab.c"
	break;
      case 13: /* "KW_FENCE" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1491 "hare-idl.tab.c"
	break;
      case 14: /* "KW_EXTEND" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1500 "hare-idl.tab.c"
	break;
      case 15: /* "KW_TO" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1509 "hare-idl.tab.c"
	break;
      case 16: /* "KW_DEFAULT" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1518 "hare-idl.tab.c"
	break;
      case 17: /* "KW_FILE" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1527 "hare-idl.tab.c"
	break;
      case 18: /* "KW_CLASS_UPP" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1536 "hare-idl.tab.c"
	break;
      case 19: /* "KW_DISCRIMINATED_UNION" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1545 "hare-idl.tab.c"
	break;
      case 20: /* "KW_DISCRIMINANT" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1554 "hare-idl.tab.c"
	break;
      case 21: /* "KW_WHEN_DISCRIMINANT_IN" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1563 "hare-idl.tab.c"
	break;
      case 22: /* "KW_WHEN_DISCRIMINANT_IS" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1572 "hare-idl.tab.c"
	break;
      case 23: /* "IDENTIFIER" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1581 "hare-idl.tab.c"
	break;
      case 24: /* "KW_IDENTIFIER" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1590 "hare-idl.tab.c"
	break;
      case 25: /* "STRING_LITERAL" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1599 "hare-idl.tab.c"
	break;
      case 26: /* "INTEGER_LITERAL" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1608 "hare-idl.tab.c"
	break;
      case 27: /* "CHAR_LITERAL" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1617 "hare-idl.tab.c"
	break;
      case 28: /* "FLOAT_LITERAL" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1626 "hare-idl.tab.c"
	break;
      case 29: /* "KW_INTEGER" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1635 "hare-idl.tab.c"
	break;
      case 30: /* "KW_FIXED_POINT" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1644 "hare-idl.tab.c"
	break;
      case 31: /* "KW_FLOATING_POINT" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1653 "hare-idl.tab.c"
	break;
      case 32: /* "KW_CHARACTER" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1662 "hare-idl.tab.c"
	break;
      case 33: /* "KW_CHARACTER_STRING" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1671 "hare-idl.tab.c"
	break;
      case 34: /* "KW_BIT_STRING" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1680 "hare-idl.tab.c"
	break;
      case 35: /* "KW_SEQUENCE" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1689 "hare-idl.tab.c"
	break;
      case 36: /* "KW_DICTIONARY" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1698 "hare-idl.tab.c"
	break;
      case 37: /* "KW_PRINTABLE_ASCII_STRING" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1707 "hare-idl.tab.c"
	break;
      case 38: /* "KW_UNICODE_STRING" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1716 "hare-idl.tab.c"
	break;
      case 39: /* "OP_FOUR_DOTS" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1725 "hare-idl.tab.c"
	break;
      case 40: /* "';'" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1734 "hare-idl.tab.c"
	break;
      case 41: /* "'{'" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1743 "hare-idl.tab.c"
	break;
      case 42: /* "'}'" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1752 "hare-idl.tab.c"
	break;
      case 43: /* "'('" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1761 "hare-idl.tab.c"
	break;
      case 44: /* "')'" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1770 "hare-idl.tab.c"
	break;
      case 45: /* "'='" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1779 "hare-idl.tab.c"
	break;
      case 46: /* "'['" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1788 "hare-idl.tab.c"
	break;
      case 47: /* "','" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1797 "hare-idl.tab.c"
	break;
      case 48: /* "']'" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1806 "hare-idl.tab.c"
	break;
      case 49: /* "'<'" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1815 "hare-idl.tab.c"
	break;
      case 50: /* "'>'" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1824 "hare-idl.tab.c"
	break;
      case 51: /* "'+'" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1833 "hare-idl.tab.c"
	break;
      case 52: /* "'-'" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1842 "hare-idl.tab.c"
	break;
      case 54: /* "file" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1851 "hare-idl.tab.c"
	break;
      case 55: /* "line_directive" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1860 "hare-idl.tab.c"
	break;
      case 56: /* "typedef_decl" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1869 "hare-idl.tab.c"
	break;
      case 57: /* "publishable_struct_begin" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1878 "hare-idl.tab.c"
	break;
      case 58: /* "publishable_struct" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1887 "hare-idl.tab.c"
	break;
      case 59: /* "mapping_begin" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1896 "hare-idl.tab.c"
	break;
      case 60: /* "mapping" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1905 "hare-idl.tab.c"
	break;
      case 61: /* "ext_file_mapping_begin" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1914 "hare-idl.tab.c"
	break;
      case 62: /* "ext_file_mapping" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1923 "hare-idl.tab.c"
	break;
      case 63: /* "encoding_begin" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1932 "hare-idl.tab.c"
	break;
      case 64: /* "encoding" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1941 "hare-idl.tab.c"
	break;
      case 65: /* "encoding_element" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1950 "hare-idl.tab.c"
	break;
      case 66: /* "encoding_group_begin" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1959 "hare-idl.tab.c"
	break;
      case 67: /* "encoding_group" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1968 "hare-idl.tab.c"
	break;
      case 68: /* "discriminated_union_begin" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1977 "hare-idl.tab.c"
	break;
      case 69: /* "discriminated_union" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1986 "hare-idl.tab.c"
	break;
      case 70: /* "discriminated_union_element" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1995 "hare-idl.tab.c"
	break;
      case 71: /* "mapping_type" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2004 "hare-idl.tab.c"
	break;
      case 72: /* "data_type" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2013 "hare-idl.tab.c"
	break;
      case 73: /* "integer_type" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2022 "hare-idl.tab.c"
	break;
      case 74: /* "fixed_point_type" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2031 "hare-idl.tab.c"
	break;
      case 75: /* "floating_point_type" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2040 "hare-idl.tab.c"
	break;
      case 76: /* "character_type" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2049 "hare-idl.tab.c"
	break;
      case 77: /* "character_string_type" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2058 "hare-idl.tab.c"
	break;
      case 78: /* "bit_string_type" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2067 "hare-idl.tab.c"
	break;
      case 79: /* "sequence_type" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2076 "hare-idl.tab.c"
	break;
      case 80: /* "dictionary_type" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2085 "hare-idl.tab.c"
	break;
      case 81: /* "class_ref_type" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2094 "hare-idl.tab.c"
	break;
      case 82: /* "inline_enum_type" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2103 "hare-idl.tab.c"
	break;
      case 83: /* "enum_values" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2112 "hare-idl.tab.c"
	break;
      case 84: /* "arg_list" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2121 "hare-idl.tab.c"
	break;
      case 85: /* "id_list" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2130 "hare-idl.tab.c"
	break;
      case 86: /* "expr" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2139 "hare-idl.tab.c"
	break;
      case 87: /* "character_set" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2148 "hare-idl.tab.c"
	break;
      case 88: /* "qname" */

/* Line 1000 of yacc.c  */
#line 44 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2157 "hare-idl.tab.c"
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
#line 53 "hare-idl.y"
    { (yyval) = 0; ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 54 "hare-idl.y"
    { (yyval) = 0; releaseYys2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 55 "hare-idl.y"
    { (yyval) = addTypedefToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 56 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 57 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 58 "hare-idl.y"
    { (yyval) = processExtFileMapping((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 59 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 60 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 64 "hare-idl.y"
    { (yyval) = 0; processLineDirective((yyvsp[(2) - (3)]), 0); releaseYys2((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 65 "hare-idl.y"
    { (yyval) = 0; processLineDirective((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 69 "hare-idl.y"
    { (yyval) = createTypedef((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 70 "hare-idl.y"
    { (yyval) = createTypedef((yyvsp[(1) - (4)]), createIdType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)])); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 74 "hare-idl.y"
    { (yyval) = createPublishableStruct((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 75 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]))); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 76 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute(createIdType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)]))); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 80 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 84 "hare-idl.y"
    { (yyval) = createMapping((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(6) - (7)])); releaseYys4((yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 85 "hare-idl.y"
    { (yyval) = createMapping((yyvsp[(1) - (6)]), 0, (yyvsp[(5) - (6)])); releaseYys4((yyvsp[(2) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 86 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (2)]); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 87 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])));  releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 88 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute(createMappingType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)])));  releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 92 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 96 "hare-idl.y"
    { (yyval) = createExtFileMapping((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(7) - (8)])); releaseYys5((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 97 "hare-idl.y"
    { (yyval) = addClassMapping((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 101 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (4)]); releaseYys3((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 102 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 107 "hare-idl.y"
    { (yyval) = createEncoding((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(6) - (7)])); releaseYys4((yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 108 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (2)]); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 109 "hare-idl.y"
    { (yyval) = addToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 110 "hare-idl.y"
    { (yyval) = addToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 111 "hare-idl.y"
    { (yyval) = addFenceToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 115 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 119 "hare-idl.y"
    { (yyval) = createAttribute((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 120 "hare-idl.y"
    { (yyval) = createEncodingAttribute((yyvsp[(1) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 121 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); releaseYys3((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 122 "hare-idl.y"
    { (yyval) = createAttribute(createIdType((yyvsp[(1) - (3)])), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 123 "hare-idl.y"
    { (yyval) = createEncodingAttribute(createIdType((yyvsp[(1) - (6)])), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)]));;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 124 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (5)]), createIdType((yyvsp[(4) - (5)]))); releaseYys3((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 125 "hare-idl.y"
    { (yyval) = createAttribute(createEncodingType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)])), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 126 "hare-idl.y"
    { (yyval) = createEncodingAttribute(createEncodingType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)])), (yyvsp[(5) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 127 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (8)]), createEncodingType((yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]))); releaseYys5((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 131 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, 0); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 132 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), 0); releaseYys3((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 133 "hare-idl.y"
    { (yyval) = addToEncodingGroup((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 134 "hare-idl.y"
    { (yyval) = addToEncodingGroup((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 138 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (2)]); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 139 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 140 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 141 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 142 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 146 "hare-idl.y"
    { (yyval) = createUnion((yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)])); releaseYys5((yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 147 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 151 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 155 "hare-idl.y"
    { (yyval) = createAttribute((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 156 "hare-idl.y"
    { (yyval) = createUnionAttribute((yyvsp[(1) - (7)]), (yyvsp[(2) - (7)]), (yyvsp[(5) - (7)])); releaseYys4((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 157 "hare-idl.y"
    { (yyval) = createUnionAttribute((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), addIdentifier(0, (yyvsp[(4) - (5)]))); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 158 "hare-idl.y"
    { (yyval) = createAttribute(createIdType((yyvsp[(1) - (3)])), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 159 "hare-idl.y"
    { (yyval) = createUnionAttribute(createIdType((yyvsp[(1) - (7)])), (yyvsp[(2) - (7)]), (yyvsp[(5) - (7)])); releaseYys4((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 160 "hare-idl.y"
    { (yyval) = createUnionAttribute(createIdType((yyvsp[(1) - (5)])), (yyvsp[(2) - (5)]), addIdentifier(0, (yyvsp[(4) - (5)]))); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 182 "hare-idl.y"
    { (yyval) = createPrintableAsciiStringType((yyvsp[(1) - (1)])); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 183 "hare-idl.y"
    { (yyval) = createUnicodeStringType((yyvsp[(1) - (1)])); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 187 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 188 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 189 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 190 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 194 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), true, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), true); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 195 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), false, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), true); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 196 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), true, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), false); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 197 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), false, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), false); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 201 "hare-idl.y"
    { (yyval) = createFloatingPointType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 205 "hare-idl.y"
    { (yyval) = createCharacterType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 206 "hare-idl.y"
    { (yyval) = createCharacterType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 210 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), 0, 0); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 211 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 212 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), 0, 0); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 213 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 217 "hare-idl.y"
    { (yyval) = createBitStringType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 221 "hare-idl.y"
    { (yyval) = createSequence((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 222 "hare-idl.y"
    { (yyval) = createSequence((yyvsp[(1) - (4)]), createIdType((yyvsp[(3) - (4)]))); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 223 "hare-idl.y"
    { (yyval) = createNamedSequence((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 224 "hare-idl.y"
    { (yyval) = createNamedSequence((yyvsp[(1) - (4)]), createIdType((yyvsp[(3) - (4)]))); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 228 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 229 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 230 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 231 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 232 "hare-idl.y"
    { (yyval) = createNamedDictionary((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 233 "hare-idl.y"
    { (yyval) = createNamedDictionary((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 234 "hare-idl.y"
    { (yyval) = createNamedDictionary((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 235 "hare-idl.y"
    { (yyval) = createNamedDictionary((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 239 "hare-idl.y"
    { (yyval) = createClassReference((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 240 "hare-idl.y"
    { (yyval) = createClassReference((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 244 "hare-idl.y"
    { (yyval) = createInlineEnum((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 248 "hare-idl.y"
    { (yyval) = addEnumValue(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 249 "hare-idl.y"
    { (yyval) = addEnumValue((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 250 "hare-idl.y"
    { (yyval) = addEnumValue(0, (yyvsp[(3) - (6)]), (yyvsp[(6) - (6)])); releaseYys4((yyvsp[(1) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)])); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 251 "hare-idl.y"
    { (yyval) = addEnumValue((yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(8) - (8)])); releaseYys3((yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(4) - (8)])); releaseYys2((yyvsp[(6) - (8)]), (yyvsp[(7) - (8)])); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 255 "hare-idl.y"
    { (yyval) = addExpression(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 256 "hare-idl.y"
    { (yyval) = addExpression((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 260 "hare-idl.y"
    { (yyval) = addIdentifier(0, (yyvsp[(1) - (1)])); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 261 "hare-idl.y"
    { (yyval) = addIdentifier((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 265 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 266 "hare-idl.y"
    { (yyval) = (yyvsp[(2) - (2)]); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 267 "hare-idl.y"
    { (yyval) = makeMinusIntLit((yyvsp[(2) - (2)])); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 268 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 269 "hare-idl.y"
    { (yyval) = (yyvsp[(2) - (2)]); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 270 "hare-idl.y"
    { (yyval) = makeMinusFloatLit((yyvsp[(2) - (2)])); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 271 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 275 "hare-idl.y"
    { (yyval) = addToCharSet(0, (yyvsp[(1) - (1)]), 0); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 276 "hare-idl.y"
    { (yyval) = addToCharSet(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 277 "hare-idl.y"
    { (yyval) = addToCharSet((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 0);  releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 278 "hare-idl.y"
    { (yyval) = addToCharSet((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 282 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 283 "hare-idl.y"
    { (yyval) = makeFourDotsPrefix((yyvsp[(2) - (2)])); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 284 "hare-idl.y"
    { (yyval) = addFourDotsName((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;



/* Line 1455 of yacc.c  */
#line 3260 "hare-idl.tab.c"
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



