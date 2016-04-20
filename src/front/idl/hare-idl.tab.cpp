
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
#line 45 "hare-idl.y"

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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 158 "hare-idl.tab.c"

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
#define YYLAST   480

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNRULES -- Number of states.  */
#define YYNSTATES  308

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      41,    42,     2,    49,    45,    50,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    38,
      47,    43,    48,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
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
      35,    36,    37
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
     480,   487,   490,   496,   500,   506,   510,   516,   518,   522,
     524,   527,   530,   532,   535,   538,   540,   542,   546,   550,
     556,   558,   561
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,    -1,    52,    53,    -1,    52,    54,    -1,
      52,    56,    -1,    52,    58,    -1,    52,    60,    -1,    52,
      62,    -1,    52,    67,    -1,     3,    24,    38,    -1,     3,
      24,    23,    38,    -1,     5,    70,    22,    38,    -1,     5,
      22,    22,    38,    -1,     4,    22,    39,    -1,    55,    70,
      22,    38,    -1,    55,    22,    22,    38,    -1,    55,    40,
      38,    -1,     8,    41,    82,    42,     4,    22,    39,    -1,
       8,    41,    42,     4,    22,    39,    -1,    57,    53,    -1,
      57,    69,    22,    38,    -1,    57,    22,    22,    38,    -1,
      57,    40,    38,    -1,     8,    41,    82,    42,    39,    16,
      23,    39,    -1,    59,    17,    22,    38,    -1,    59,    40,
      40,    38,    -1,    59,    40,    40,    -1,     9,    41,    82,
      42,     4,    22,    39,    -1,    61,    53,    -1,    61,    63,
      -1,    61,    65,    -1,    61,    12,    -1,    61,    40,    38,
      -1,    70,    22,    38,    -1,    70,    22,    15,    43,    84,
      38,    -1,    13,    22,    14,    70,    38,    -1,    22,    22,
      38,    -1,    22,    22,    15,    43,    84,    38,    -1,    13,
      22,    14,    22,    38,    -1,    22,    41,    82,    42,    22,
      38,    -1,    22,    41,    82,    42,    22,    15,    43,    84,
      38,    -1,    13,    22,    14,    22,    41,    82,    42,    38,
      -1,    22,    39,    -1,    22,    41,    82,    42,    39,    -1,
      64,    63,    -1,    64,    65,    -1,    64,    40,    -1,    22,
      63,    -1,    22,    41,    82,    42,    63,    -1,    22,    65,
      -1,    22,    41,    82,    42,    65,    -1,    18,    41,    19,
      43,    22,    42,    22,    39,    -1,    66,    68,    -1,    66,
      40,    38,    -1,    70,    22,    38,    -1,    70,    22,    20,
      39,    83,    40,    38,    -1,    70,    22,    21,    22,    38,
      -1,    22,    22,    38,    -1,    22,    22,    20,    39,    83,
      40,    38,    -1,    22,    22,    21,    22,    38,    -1,    77,
      -1,    78,    -1,    80,    -1,    79,    -1,    71,    -1,    72,
      -1,    73,    -1,    74,    -1,    75,    -1,    76,    -1,    77,
      -1,    78,    -1,    80,    -1,    79,    -1,    35,    -1,    36,
      -1,    27,    44,    84,    45,    84,    46,    -1,    27,    41,
      84,    45,    84,    46,    -1,    27,    44,    84,    45,    84,
      42,    -1,    27,    41,    84,    45,    84,    42,    -1,    28,
      44,    84,    45,    84,    45,    84,    46,    -1,    28,    41,
      84,    45,    84,    45,    84,    46,    -1,    28,    44,    84,
      45,    84,    45,    84,    42,    -1,    28,    41,    84,    45,
      84,    45,    84,    42,    -1,    29,    41,    84,    45,    84,
      42,    -1,    30,    39,    23,    40,    -1,    30,    39,    85,
      40,    -1,    31,    39,    23,    40,    -1,    31,    39,    23,
      40,    44,    84,    45,    84,    46,    -1,    31,    39,    85,
      40,    -1,    31,    39,    85,    40,    44,    84,    45,    84,
      46,    -1,    32,    44,    84,    45,    84,    46,    -1,    33,
      47,    70,    48,    -1,    33,    47,    22,    48,    -1,    22,
      47,    70,    48,    -1,    22,    47,    22,    48,    -1,    34,
      47,    70,    45,    70,    48,    -1,    34,    47,    22,    45,
      70,    48,    -1,    34,    47,    70,    45,    22,    48,    -1,
      34,    47,    22,    45,    22,    48,    -1,     7,    86,    -1,
       6,    86,    39,    81,    40,    -1,    22,    43,    24,    -1,
      81,    45,    22,    43,    24,    -1,    22,    43,    84,    -1,
      82,    45,    22,    43,    84,    -1,    22,    -1,    83,    45,
      22,    -1,    24,    -1,    49,    24,    -1,    50,    24,    -1,
      26,    -1,    49,    26,    -1,    50,    26,    -1,    23,    -1,
      24,    -1,    24,    50,    24,    -1,    85,    45,    24,    -1,
      85,    45,    24,    50,    24,    -1,    22,    -1,    37,    22,
      -1,    86,    37,    22,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    52,    52,    53,    54,    55,    56,    57,    58,    59,
      63,    64,    68,    69,    73,    74,    75,    79,    83,    84,
      85,    86,    87,    91,    95,    96,   100,   101,   106,   107,
     108,   109,   110,   114,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   130,   131,   132,   133,   137,   138,   139,
     140,   141,   145,   146,   150,   154,   155,   156,   157,   158,
     159,   164,   165,   166,   167,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   186,   187,   188,
     189,   193,   194,   195,   196,   200,   204,   205,   209,   210,
     211,   212,   216,   220,   221,   222,   223,   227,   228,   229,
     230,   234,   238,   242,   243,   247,   248,   252,   253,   257,
     258,   259,   260,   261,   262,   263,   267,   268,   269,   270,
     274,   275,   276
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_HASH_LINE", "KW_PUBLISHABLE_STRUCT",
  "KW_TYPEDEF", "KW_ENUM", "KW_CLASS", "KW_MAPPING", "KW_ENCODING",
  "KW_NUMERIC", "KW_INT", "KW_FENCE", "KW_EXTEND", "KW_TO", "KW_DEFAULT",
  "KW_FILE", "KW_CLASS_UPP", "KW_DISCRIMINATED_UNION", "KW_DISCRIMINANT",
  "KW_WHEN_DISCRIMINANT_IN", "KW_WHEN_DISCRIMINANT_IS", "IDENTIFIER",
  "STRING_LITERAL", "INTEGER_LITERAL", "CHAR_LITERAL", "FLOAT_LITERAL",
  "KW_INTEGER", "KW_FIXED_POINT", "KW_FLOATING_POINT", "KW_CHARACTER",
  "KW_CHARACTER_STRING", "KW_BIT_STRING", "KW_SEQUENCE", "KW_DICTIONARY",
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
     285,   286,   287,   288,   289,   290,   291,   292,    59,   123,
     125,    40,    41,    61,    91,    44,    93,    60,    62,    43,
      45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    52,    52,    52,    52,    52,    52,    52,
      53,    53,    54,    54,    55,    55,    55,    56,    57,    57,
      57,    57,    57,    58,    59,    59,    60,    60,    61,    61,
      61,    61,    61,    62,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    64,    64,    64,    64,    65,    65,    65,
      65,    65,    66,    66,    67,    68,    68,    68,    68,    68,
      68,    69,    69,    69,    69,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    71,    71,    71,
      71,    72,    72,    72,    72,    73,    74,    74,    75,    75,
      75,    75,    76,    77,    77,    77,    77,    78,    78,    78,
      78,    79,    80,    81,    81,    82,    82,    83,    83,    84,
      84,    84,    84,    84,    84,    84,    85,    85,    85,    85,
      86,    86,    86
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
       6,     2,     5,     3,     5,     3,     5,     1,     3,     1,
       2,     2,     1,     2,     2,     1,     1,     3,     3,     5,
       1,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     3,
       4,     0,     5,     0,     6,     0,     7,     0,     8,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    75,    76,     0,    65,    66,    67,
      68,    69,    70,    71,    72,    74,    73,     0,     0,     0,
       0,     0,     0,     0,     0,    20,     0,    61,    62,    64,
      63,     0,     0,    32,     0,     0,     0,    29,    30,     0,
      31,     0,     0,     0,    53,     0,     0,    10,    14,   120,
       0,     0,   101,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,     0,    23,     0,     0,    27,     0,
       0,    43,     0,    48,    50,    33,    47,    45,    46,     0,
       0,    54,     0,    11,   121,     0,     0,    13,     0,     0,
     115,   109,   112,     0,     0,     0,     0,     0,     0,     0,
       0,   116,     0,     0,     0,     0,     0,     0,     0,     0,
      12,     0,     0,     0,     0,     0,     0,    16,    15,    22,
      21,    25,    26,     0,     0,    37,     0,     0,    34,     0,
       0,    58,     0,     0,    55,   122,     0,     0,    96,    95,
     110,   113,   111,   114,     0,     0,     0,     0,     0,    86,
       0,    87,     0,    88,    90,     0,    94,    93,     0,     0,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,     0,     0,
       0,     0,     0,     0,   117,   118,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,     0,     0,     0,    39,
       0,    36,     0,     0,    44,    49,    51,     0,   107,     0,
      60,     0,    57,   103,     0,    80,    78,    79,    77,     0,
       0,    85,     0,     0,     0,    92,   100,    98,    99,    97,
      18,     0,   106,    28,     0,     0,    38,     0,    40,    35,
       0,     0,     0,     0,     0,     0,   119,     0,     0,    24,
      52,     0,     0,    59,   108,    56,   104,    84,    82,    83,
      81,     0,     0,    42,     0,    89,    91,    41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,   113,    69,   114,    19,    20,    74,    56,    71,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
     177,    98,   249,   135,   142,    81
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -87
static const yytype_int16 yypact[] =
{
     -87,   163,   -87,    28,     3,   278,    17,    25,    47,   -87,
     -87,   212,   -87,   142,   -87,   -12,   -87,   125,   -87,   229,
     -87,   -11,    68,    69,    69,    -8,   102,   136,   110,   147,
     152,   182,   160,   186,   -87,   -87,   207,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,     0,   233,   249,
      -3,   234,   252,    -2,   237,   -87,   254,   -87,   -87,   -87,
     -87,   255,   238,   -87,   257,    83,   242,   -87,   -87,   181,
     -87,   259,     1,   245,   -87,   264,   265,   -87,   -87,   -87,
     275,    45,   261,   266,   295,    71,    71,    71,    71,    71,
     146,   208,    71,   312,   329,   277,   273,   316,   148,   150,
     289,   283,   -87,   299,   300,   -87,   311,   317,   328,   319,
       2,   -87,   233,   -87,   -87,   -87,   -87,   -87,   -87,    42,
      65,   -87,   106,   -87,   -87,   332,   345,   -87,   190,   302,
     -87,   -87,   -87,   198,   201,   326,   327,   338,   339,   343,
     349,   350,   -19,   361,    16,   358,   202,   356,   183,   360,
     -87,    71,   384,    12,   395,   414,   397,   -87,   -87,   -87,
     -87,   -87,   -87,   346,   377,   -87,   154,   378,   -87,   383,
     401,   -87,   385,   403,   -87,   -87,   386,    89,   -87,   -87,
     -87,   -87,   -87,   -87,    71,    71,    71,    71,    71,   -87,
     402,   -87,   404,   387,   388,    71,   -87,   -87,   363,   380,
     -87,   391,   405,   417,   392,   412,   394,    95,   399,    71,
     260,    71,   416,   406,   416,   407,   415,   -87,   418,     8,
      18,   396,   398,   400,   -87,   408,    71,    71,   409,   206,
     411,   223,   413,   -87,   410,   423,    71,   421,   425,   -87,
     233,   -87,   419,    40,   -87,   -87,   -87,   424,   -87,   138,
     -87,   139,   -87,   -87,   420,   -87,   -87,   -87,   -87,    71,
      71,   -87,   426,   422,   427,   -87,   -87,   -87,   -87,   -87,
     -87,   429,   -87,   -87,   430,   178,   -87,   428,   -87,   -87,
     432,   431,   435,   440,    62,    93,   -87,    71,    71,   -87,
     -87,   436,    71,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   433,   434,   -87,   437,   -87,   -87,   -87
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -87,   -87,   172,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -10,   -87,    -6,   -87,   -87,   -87,   -87,    -1,
     -87,   -87,   -87,   -87,   -87,   -87,   438,   439,   441,   443,
     -87,   -35,   251,   -86,   357,   442
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     136,   137,   138,   139,    36,    61,   145,    68,    23,    24,
      52,    70,    76,    99,    83,    64,   202,   164,    75,   101,
     104,   191,    96,   120,   110,    22,   192,    77,    62,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    84,
     165,   111,    97,   112,    84,    84,    23,    24,    84,    84,
     255,   203,    21,    64,   256,   277,   194,   167,    47,   117,
     257,   192,   110,   118,   258,   200,    48,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,   166,   278,   111,
     168,   112,   125,   129,   126,   169,   170,    84,    49,    23,
      24,    79,   147,   149,   130,   131,    64,   132,   219,   220,
     221,   222,   223,   171,   297,   110,    80,    78,   298,   228,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
     133,   134,   111,   242,   112,   247,   172,   173,     3,   217,
      84,    23,    24,   239,   218,   299,   240,    63,    64,   300,
     263,   264,    84,    85,   174,     3,    86,    65,    23,    24,
     272,    89,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,   208,     2,    53,    66,     3,     4,     5,   140,
     141,     6,     7,   284,   285,    32,    33,    87,   280,   282,
      88,     8,    54,   281,   281,    55,    90,    23,    24,    67,
     153,    91,   155,   154,    64,   154,   210,   230,   232,   154,
     245,   301,   302,    65,   246,   275,   304,    93,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    23,    24,
     291,   116,   180,   154,   181,   182,    92,   183,   198,    95,
      84,   143,   141,    94,    50,    23,    24,    84,   178,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    84,
     196,    72,    51,    84,   266,    96,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    23,    24,   100,    73,
      84,   268,   102,    64,   103,   105,   106,   107,   108,   109,
     115,   119,   243,   121,    23,    24,   122,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,   124,   125,   244,
      25,    23,    24,   123,   127,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,   150,   151,   128,    23,    24,
     152,   157,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,   156,   163,   146,    23,    24,   158,   159,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,   160,
     179,   148,    23,    24,   175,   161,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,   162,   176,   207,    23,
      24,   184,   185,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,   186,   187,   229,    23,    24,   188,   189,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
     190,   193,   231,   195,   197,   199,   201,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,   204,   205,   206,
     209,   211,   212,   213,   214,   215,   224,   234,   225,   216,
     233,   226,   227,   235,   237,   236,   238,   241,   248,   253,
     254,   259,   261,   260,   250,   252,   271,   274,   144,   270,
     286,    57,    58,   294,    59,   265,    60,   276,   262,   267,
     273,   269,   279,   283,   296,   251,    82,   287,   289,   290,
     293,   292,   288,   295,   303,   307,     0,     0,     0,   305,
     306
};

static const yytype_int16 yycheck[] =
{
      86,    87,    88,    89,     5,    17,    92,    17,     6,     7,
      11,    17,    23,    48,    22,    13,     4,    15,    19,    22,
      22,    40,    22,    22,    22,    22,    45,    38,    40,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    47,
      38,    39,    42,    41,    47,    47,     6,     7,    47,    47,
      42,    39,    24,    13,    46,    15,    40,    15,    41,    69,
      42,    45,    22,    69,    46,   151,    41,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,   112,    38,    39,
      38,    41,    37,    84,    39,    20,    21,    47,    41,     6,
       7,    22,    93,    94,    23,    24,    13,    26,   184,   185,
     186,   187,   188,    38,    42,    22,    37,    39,    46,   195,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      49,    50,    39,   209,    41,   211,    20,    21,     3,    40,
      47,     6,     7,    38,    45,    42,    41,    12,    13,    46,
     226,   227,    47,    41,    38,     3,    44,    22,     6,     7,
     236,    41,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,   163,     0,    22,    40,     3,     4,     5,    23,
      24,     8,     9,   259,   260,    33,    34,    41,    40,    40,
      44,    18,    40,    45,    45,    13,    39,     6,     7,    17,
      42,    39,    42,    45,    13,    45,    42,   198,   199,    45,
     210,   287,   288,    22,   210,   240,   292,    47,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,     6,     7,
      42,    40,    24,    45,    26,    24,    44,    26,    45,    22,
      47,    23,    24,    47,    22,     6,     7,    47,    48,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    47,
      48,    22,    40,    47,    48,    22,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,     6,     7,    19,    40,
      47,    48,    38,    13,    22,    38,    22,    22,    40,    22,
      38,    22,    22,    38,     6,     7,    22,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    22,    37,    39,
      22,     6,     7,    38,    38,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    38,    43,    22,     6,     7,
       4,    38,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    43,    14,    22,     6,     7,    38,    38,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    38,
      48,    22,     6,     7,    22,    38,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    38,    22,    22,     6,
       7,    45,    45,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    45,    45,    22,     6,     7,    45,    40,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      50,    40,    22,    45,    48,    45,    22,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    22,     4,    22,
      43,    43,    39,    22,    39,    22,    24,    22,    24,    43,
      39,    44,    44,    16,    22,    43,    42,    38,    22,    24,
      22,    45,    42,    45,    38,    38,    23,    22,    91,    39,
      24,    13,    13,    22,    13,    46,    13,    38,    50,    48,
      39,    48,    38,    43,    24,   214,    24,    45,    39,    39,
      38,    43,    45,    38,    38,    38,    -1,    -1,    -1,    46,
      46
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    52,     0,     3,     4,     5,     8,     9,    18,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    66,
      67,    24,    22,     6,     7,    22,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    41,    41,    41,
      22,    40,    70,    22,    40,    53,    69,    77,    78,    79,
      80,    17,    40,    12,    13,    22,    40,    53,    63,    64,
      65,    70,    22,    40,    68,    70,    23,    38,    39,    22,
      37,    86,    86,    22,    47,    41,    44,    41,    44,    41,
      39,    39,    44,    47,    47,    22,    22,    42,    82,    82,
      19,    22,    38,    22,    22,    38,    22,    22,    40,    22,
      22,    39,    41,    63,    65,    38,    40,    63,    65,    22,
      22,    38,    22,    38,    22,    37,    39,    38,    22,    70,
      23,    24,    26,    49,    50,    84,    84,    84,    84,    84,
      23,    24,    85,    23,    85,    84,    22,    70,    22,    70,
      38,    43,     4,    42,    45,    42,    43,    38,    38,    38,
      38,    38,    38,    14,    15,    38,    82,    15,    38,    20,
      21,    38,    20,    21,    38,    22,    22,    81,    48,    48,
      24,    26,    24,    26,    45,    45,    45,    45,    45,    40,
      50,    40,    45,    40,    40,    45,    48,    48,    45,    45,
      84,    22,     4,    39,    22,     4,    22,    22,    70,    43,
      42,    43,    39,    22,    39,    22,    43,    40,    45,    84,
      84,    84,    84,    84,    24,    24,    44,    44,    84,    22,
      70,    22,    70,    39,    22,    16,    43,    22,    42,    38,
      41,    38,    84,    22,    39,    63,    65,    84,    22,    83,
      38,    83,    38,    24,    22,    42,    46,    42,    46,    45,
      45,    42,    50,    84,    84,    46,    48,    48,    48,    48,
      39,    23,    84,    39,    22,    82,    38,    15,    38,    38,
      40,    45,    40,    43,    84,    84,    24,    45,    45,    39,
      39,    42,    43,    38,    22,    38,    24,    42,    46,    42,
      46,    84,    84,    38,    84,    46,    46,    38
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
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1362 "hare-idl.tab.c"
	break;
      case 4: /* "KW_PUBLISHABLE_STRUCT" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1371 "hare-idl.tab.c"
	break;
      case 5: /* "KW_TYPEDEF" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1380 "hare-idl.tab.c"
	break;
      case 6: /* "KW_ENUM" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1389 "hare-idl.tab.c"
	break;
      case 7: /* "KW_CLASS" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1398 "hare-idl.tab.c"
	break;
      case 8: /* "KW_MAPPING" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1407 "hare-idl.tab.c"
	break;
      case 9: /* "KW_ENCODING" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1416 "hare-idl.tab.c"
	break;
      case 10: /* "KW_NUMERIC" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1425 "hare-idl.tab.c"
	break;
      case 11: /* "KW_INT" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1434 "hare-idl.tab.c"
	break;
      case 12: /* "KW_FENCE" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1443 "hare-idl.tab.c"
	break;
      case 13: /* "KW_EXTEND" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1452 "hare-idl.tab.c"
	break;
      case 14: /* "KW_TO" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1461 "hare-idl.tab.c"
	break;
      case 15: /* "KW_DEFAULT" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1470 "hare-idl.tab.c"
	break;
      case 16: /* "KW_FILE" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1479 "hare-idl.tab.c"
	break;
      case 17: /* "KW_CLASS_UPP" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1488 "hare-idl.tab.c"
	break;
      case 18: /* "KW_DISCRIMINATED_UNION" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1497 "hare-idl.tab.c"
	break;
      case 19: /* "KW_DISCRIMINANT" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1506 "hare-idl.tab.c"
	break;
      case 20: /* "KW_WHEN_DISCRIMINANT_IN" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1515 "hare-idl.tab.c"
	break;
      case 21: /* "KW_WHEN_DISCRIMINANT_IS" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1524 "hare-idl.tab.c"
	break;
      case 22: /* "IDENTIFIER" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1533 "hare-idl.tab.c"
	break;
      case 23: /* "STRING_LITERAL" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1542 "hare-idl.tab.c"
	break;
      case 24: /* "INTEGER_LITERAL" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1551 "hare-idl.tab.c"
	break;
      case 25: /* "CHAR_LITERAL" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1560 "hare-idl.tab.c"
	break;
      case 26: /* "FLOAT_LITERAL" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1569 "hare-idl.tab.c"
	break;
      case 27: /* "KW_INTEGER" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1578 "hare-idl.tab.c"
	break;
      case 28: /* "KW_FIXED_POINT" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1587 "hare-idl.tab.c"
	break;
      case 29: /* "KW_FLOATING_POINT" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1596 "hare-idl.tab.c"
	break;
      case 30: /* "KW_CHARACTER" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1605 "hare-idl.tab.c"
	break;
      case 31: /* "KW_CHARACTER_STRING" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1614 "hare-idl.tab.c"
	break;
      case 32: /* "KW_BIT_STRING" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1623 "hare-idl.tab.c"
	break;
      case 33: /* "KW_SEQUENCE" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1632 "hare-idl.tab.c"
	break;
      case 34: /* "KW_DICTIONARY" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1641 "hare-idl.tab.c"
	break;
      case 35: /* "KW_PRINTABLE_ASCII_STRING" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1650 "hare-idl.tab.c"
	break;
      case 36: /* "KW_UNICODE_STRING" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1659 "hare-idl.tab.c"
	break;
      case 37: /* "OP_FOUR_DOTS" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1668 "hare-idl.tab.c"
	break;
      case 38: /* "';'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1677 "hare-idl.tab.c"
	break;
      case 39: /* "'{'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1686 "hare-idl.tab.c"
	break;
      case 40: /* "'}'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1695 "hare-idl.tab.c"
	break;
      case 41: /* "'('" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1704 "hare-idl.tab.c"
	break;
      case 42: /* "')'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1713 "hare-idl.tab.c"
	break;
      case 43: /* "'='" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1722 "hare-idl.tab.c"
	break;
      case 44: /* "'['" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1731 "hare-idl.tab.c"
	break;
      case 45: /* "','" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1740 "hare-idl.tab.c"
	break;
      case 46: /* "']'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1749 "hare-idl.tab.c"
	break;
      case 47: /* "'<'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1758 "hare-idl.tab.c"
	break;
      case 48: /* "'>'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1767 "hare-idl.tab.c"
	break;
      case 49: /* "'+'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1776 "hare-idl.tab.c"
	break;
      case 50: /* "'-'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1785 "hare-idl.tab.c"
	break;
      case 52: /* "file" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1794 "hare-idl.tab.c"
	break;
      case 53: /* "line_directive" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1803 "hare-idl.tab.c"
	break;
      case 54: /* "typedef_decl" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1812 "hare-idl.tab.c"
	break;
      case 55: /* "publishable_struct_begin" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1821 "hare-idl.tab.c"
	break;
      case 56: /* "publishable_struct" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1830 "hare-idl.tab.c"
	break;
      case 57: /* "mapping_begin" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1839 "hare-idl.tab.c"
	break;
      case 58: /* "mapping" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1848 "hare-idl.tab.c"
	break;
      case 59: /* "ext_file_mapping_begin" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1857 "hare-idl.tab.c"
	break;
      case 60: /* "ext_file_mapping" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1866 "hare-idl.tab.c"
	break;
      case 61: /* "encoding_begin" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1875 "hare-idl.tab.c"
	break;
      case 62: /* "encoding" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1884 "hare-idl.tab.c"
	break;
      case 63: /* "encoding_element" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1893 "hare-idl.tab.c"
	break;
      case 64: /* "encoding_group_begin" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1902 "hare-idl.tab.c"
	break;
      case 65: /* "encoding_group" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1911 "hare-idl.tab.c"
	break;
      case 66: /* "discriminated_union_begin" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1920 "hare-idl.tab.c"
	break;
      case 67: /* "discriminated_union" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1929 "hare-idl.tab.c"
	break;
      case 68: /* "discriminated_union_element" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1938 "hare-idl.tab.c"
	break;
      case 69: /* "mapping_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1947 "hare-idl.tab.c"
	break;
      case 70: /* "data_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1956 "hare-idl.tab.c"
	break;
      case 71: /* "integer_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1965 "hare-idl.tab.c"
	break;
      case 72: /* "fixed_point_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1974 "hare-idl.tab.c"
	break;
      case 73: /* "floating_point_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1983 "hare-idl.tab.c"
	break;
      case 74: /* "character_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1992 "hare-idl.tab.c"
	break;
      case 75: /* "character_string_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2001 "hare-idl.tab.c"
	break;
      case 76: /* "bit_string_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2010 "hare-idl.tab.c"
	break;
      case 77: /* "sequence_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2019 "hare-idl.tab.c"
	break;
      case 78: /* "dictionary_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2028 "hare-idl.tab.c"
	break;
      case 79: /* "class_ref_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2037 "hare-idl.tab.c"
	break;
      case 80: /* "inline_enum_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2046 "hare-idl.tab.c"
	break;
      case 81: /* "enum_values" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2055 "hare-idl.tab.c"
	break;
      case 82: /* "arg_list" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2064 "hare-idl.tab.c"
	break;
      case 83: /* "id_list" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2073 "hare-idl.tab.c"
	break;
      case 84: /* "expr" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2082 "hare-idl.tab.c"
	break;
      case 85: /* "character_set" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2091 "hare-idl.tab.c"
	break;
      case 86: /* "qname" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2100 "hare-idl.tab.c"
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
#line 52 "hare-idl.y"
    { (yyval) = 0; ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 53 "hare-idl.y"
    { (yyval) = 0; releaseYys2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 54 "hare-idl.y"
    { (yyval) = addTypedefToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 55 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 56 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 57 "hare-idl.y"
    { (yyval) = processExtFileMapping((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 58 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 59 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 63 "hare-idl.y"
    { (yyval) = 0; processLineDirective((yyvsp[(2) - (3)]), 0); releaseYys2((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 64 "hare-idl.y"
    { (yyval) = 0; processLineDirective((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 68 "hare-idl.y"
    { (yyval) = createTypedef((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 69 "hare-idl.y"
    { (yyval) = createTypedef((yyvsp[(1) - (4)]), createIdType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)])); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 73 "hare-idl.y"
    { (yyval) = createPublishableStruct((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 74 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]))); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 75 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute(createIdType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)]))); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 79 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 83 "hare-idl.y"
    { (yyval) = createMapping((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(6) - (7)])); releaseYys4((yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 84 "hare-idl.y"
    { (yyval) = createMapping((yyvsp[(1) - (6)]), 0, (yyvsp[(5) - (6)])); releaseYys4((yyvsp[(2) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 85 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (2)]); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 86 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])));  releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 87 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute(createMappingType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)])));  releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 91 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 95 "hare-idl.y"
    { (yyval) = createExtFileMapping((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(7) - (8)])); releaseYys5((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 96 "hare-idl.y"
    { (yyval) = addClassMapping((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 100 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (4)]); releaseYys3((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 101 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 106 "hare-idl.y"
    { (yyval) = createEncoding((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(6) - (7)])); releaseYys4((yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 107 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (2)]); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 108 "hare-idl.y"
    { (yyval) = addToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 109 "hare-idl.y"
    { (yyval) = addToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 110 "hare-idl.y"
    { (yyval) = addFenceToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 114 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 118 "hare-idl.y"
    { (yyval) = createAttribute((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 119 "hare-idl.y"
    { (yyval) = createEncodingAttribute((yyvsp[(1) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 120 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); releaseYys3((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 121 "hare-idl.y"
    { (yyval) = createAttribute(createIdType((yyvsp[(1) - (3)])), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 122 "hare-idl.y"
    { (yyval) = createEncodingAttribute(createIdType((yyvsp[(1) - (6)])), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)]));;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 123 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (5)]), createIdType((yyvsp[(4) - (5)]))); releaseYys3((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 124 "hare-idl.y"
    { (yyval) = createAttribute(createEncodingType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)])), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 125 "hare-idl.y"
    { (yyval) = createEncodingAttribute(createEncodingType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)])), (yyvsp[(5) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 126 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (8)]), createEncodingType((yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]))); releaseYys5((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 130 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, 0); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 131 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), 0); releaseYys3((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 132 "hare-idl.y"
    { (yyval) = addToEncodingGroup((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 133 "hare-idl.y"
    { (yyval) = addToEncodingGroup((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 137 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (2)]); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 138 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 139 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 140 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 141 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 145 "hare-idl.y"
    { (yyval) = createUnion((yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)])); releaseYys5((yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 146 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 150 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 154 "hare-idl.y"
    { (yyval) = createAttribute((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 155 "hare-idl.y"
    { (yyval) = createUnionAttribute((yyvsp[(1) - (7)]), (yyvsp[(2) - (7)]), (yyvsp[(5) - (7)])); releaseYys4((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 156 "hare-idl.y"
    { (yyval) = createUnionAttribute((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), addIdentifier(0, (yyvsp[(4) - (5)]))); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 157 "hare-idl.y"
    { (yyval) = createAttribute(createIdType((yyvsp[(1) - (3)])), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 158 "hare-idl.y"
    { (yyval) = createUnionAttribute(createIdType((yyvsp[(1) - (7)])), (yyvsp[(2) - (7)]), (yyvsp[(5) - (7)])); releaseYys4((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 159 "hare-idl.y"
    { (yyval) = createUnionAttribute(createIdType((yyvsp[(1) - (5)])), (yyvsp[(2) - (5)]), addIdentifier(0, (yyvsp[(4) - (5)]))); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 181 "hare-idl.y"
    { (yyval) = createPrintableAsciiStringType((yyvsp[(1) - (1)])); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 182 "hare-idl.y"
    { (yyval) = createUnicodeStringType((yyvsp[(1) - (1)])); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 186 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 187 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 188 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 189 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 193 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), true, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), true); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 194 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), false, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), true); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 195 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), true, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), false); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 196 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), false, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), false); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 200 "hare-idl.y"
    { (yyval) = createFloatingPointType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 204 "hare-idl.y"
    { (yyval) = createCharacterType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 205 "hare-idl.y"
    { (yyval) = createCharacterType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 209 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), 0, 0); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 210 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 211 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), 0, 0); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 212 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 216 "hare-idl.y"
    { (yyval) = createBitStringType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 220 "hare-idl.y"
    { (yyval) = createSequence((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 221 "hare-idl.y"
    { (yyval) = createSequence((yyvsp[(1) - (4)]), createIdType((yyvsp[(3) - (4)]))); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 222 "hare-idl.y"
    { (yyval) = createNamedSequence((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 223 "hare-idl.y"
    { (yyval) = createNamedSequence((yyvsp[(1) - (4)]), createIdType((yyvsp[(3) - (4)]))); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 227 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 228 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 229 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 230 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 234 "hare-idl.y"
    { (yyval) = createClassReference((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 238 "hare-idl.y"
    { (yyval) = createInlineEnum((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 242 "hare-idl.y"
    { (yyval) = addEnumValue(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 243 "hare-idl.y"
    { (yyval) = addEnumValue((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 247 "hare-idl.y"
    { (yyval) = addExpression(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 248 "hare-idl.y"
    { (yyval) = addExpression((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 252 "hare-idl.y"
    { (yyval) = addIdentifier(0, (yyvsp[(1) - (1)])); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 253 "hare-idl.y"
    { (yyval) = addIdentifier((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 257 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 258 "hare-idl.y"
    { (yyval) = (yyvsp[(2) - (2)]); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 259 "hare-idl.y"
    { (yyval) = makeMinusIntLit((yyvsp[(2) - (2)])); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 260 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 261 "hare-idl.y"
    { (yyval) = (yyvsp[(2) - (2)]); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 262 "hare-idl.y"
    { (yyval) = makeMinusFloatLit((yyvsp[(2) - (2)])); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 263 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 267 "hare-idl.y"
    { (yyval) = addToCharSet(0, (yyvsp[(1) - (1)]), 0); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 268 "hare-idl.y"
    { (yyval) = addToCharSet(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 269 "hare-idl.y"
    { (yyval) = addToCharSet((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 0);  releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 270 "hare-idl.y"
    { (yyval) = addToCharSet((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 274 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 275 "hare-idl.y"
    { (yyval) = makeFourDotsPrefix((yyvsp[(2) - (2)])); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 276 "hare-idl.y"
    { (yyval) = addFourDotsName((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;



/* Line 1455 of yacc.c  */
#line 3154 "hare-idl.tab.c"
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



