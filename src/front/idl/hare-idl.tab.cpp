
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
#define YYLAST   483

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNRULES -- Number of states.  */
#define YYNSTATES  300

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
      73,    78,    83,    87,    96,   101,   106,   110,   118,   121,
     124,   127,   130,   134,   138,   145,   151,   155,   162,   168,
     175,   185,   194,   197,   203,   206,   209,   212,   215,   221,
     224,   230,   239,   242,   246,   250,   258,   264,   268,   276,
     282,   284,   286,   288,   290,   292,   294,   296,   298,   300,
     302,   304,   306,   313,   320,   327,   334,   343,   352,   361,
     370,   377,   382,   387,   392,   402,   407,   417,   424,   429,
     434,   439,   444,   451,   458,   465,   472,   475,   481,   485,
     491,   495,   501,   503,   507,   509,   512,   515,   517,   520,
     523,   525,   527,   531,   535,   541,   543,   546
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,    -1,    52,    53,    -1,    52,    54,    -1,
      52,    56,    -1,    52,    58,    -1,    52,    60,    -1,    52,
      62,    -1,    52,    67,    -1,     3,    24,    38,    -1,     3,
      24,    23,    38,    -1,     5,    69,    22,    38,    -1,     5,
      22,    22,    38,    -1,     4,    22,    39,    -1,    55,    69,
      22,    38,    -1,    55,    22,    22,    38,    -1,    55,    40,
      38,    -1,     8,    41,    81,    42,     4,    22,    39,    -1,
      57,    53,    -1,    57,    69,    22,    38,    -1,    57,    22,
      22,    38,    -1,    57,    40,    38,    -1,     8,    41,    81,
      42,    39,    16,    23,    39,    -1,    59,    17,    22,    38,
      -1,    59,    40,    40,    38,    -1,    59,    40,    40,    -1,
       9,    41,    81,    42,     4,    22,    39,    -1,    61,    53,
      -1,    61,    63,    -1,    61,    65,    -1,    61,    12,    -1,
      61,    40,    38,    -1,    69,    22,    38,    -1,    69,    22,
      15,    43,    83,    38,    -1,    13,    22,    14,    69,    38,
      -1,    22,    22,    38,    -1,    22,    22,    15,    43,    83,
      38,    -1,    13,    22,    14,    22,    38,    -1,    22,    41,
      81,    42,    22,    38,    -1,    22,    41,    81,    42,    22,
      15,    43,    83,    38,    -1,    13,    22,    14,    22,    41,
      81,    42,    38,    -1,    22,    39,    -1,    22,    41,    81,
      42,    39,    -1,    64,    63,    -1,    64,    65,    -1,    64,
      40,    -1,    22,    63,    -1,    22,    41,    81,    42,    63,
      -1,    22,    65,    -1,    22,    41,    81,    42,    65,    -1,
      18,    41,    19,    43,    22,    42,    22,    39,    -1,    66,
      68,    -1,    66,    40,    38,    -1,    69,    22,    38,    -1,
      69,    22,    20,    39,    82,    40,    38,    -1,    69,    22,
      21,    22,    38,    -1,    22,    22,    38,    -1,    22,    22,
      20,    39,    82,    40,    38,    -1,    22,    22,    21,    22,
      38,    -1,    70,    -1,    71,    -1,    72,    -1,    73,    -1,
      74,    -1,    75,    -1,    76,    -1,    77,    -1,    79,    -1,
      78,    -1,    35,    -1,    36,    -1,    27,    44,    83,    45,
      83,    46,    -1,    27,    41,    83,    45,    83,    46,    -1,
      27,    44,    83,    45,    83,    42,    -1,    27,    41,    83,
      45,    83,    42,    -1,    28,    44,    83,    45,    83,    45,
      83,    46,    -1,    28,    41,    83,    45,    83,    45,    83,
      46,    -1,    28,    44,    83,    45,    83,    45,    83,    42,
      -1,    28,    41,    83,    45,    83,    45,    83,    42,    -1,
      29,    41,    83,    45,    83,    42,    -1,    30,    39,    23,
      40,    -1,    30,    39,    84,    40,    -1,    31,    39,    23,
      40,    -1,    31,    39,    23,    40,    44,    83,    45,    83,
      46,    -1,    31,    39,    84,    40,    -1,    31,    39,    84,
      40,    44,    83,    45,    83,    46,    -1,    32,    44,    83,
      45,    83,    46,    -1,    33,    47,    69,    48,    -1,    33,
      47,    22,    48,    -1,    22,    47,    69,    48,    -1,    22,
      47,    22,    48,    -1,    34,    47,    69,    45,    69,    48,
      -1,    34,    47,    22,    45,    69,    48,    -1,    34,    47,
      69,    45,    22,    48,    -1,    34,    47,    22,    45,    22,
      48,    -1,     7,    85,    -1,     6,    85,    39,    80,    40,
      -1,    22,    43,    24,    -1,    80,    45,    22,    43,    24,
      -1,    22,    43,    83,    -1,    81,    45,    22,    43,    83,
      -1,    22,    -1,    82,    45,    22,    -1,    24,    -1,    49,
      24,    -1,    50,    24,    -1,    26,    -1,    49,    26,    -1,
      50,    26,    -1,    23,    -1,    24,    -1,    24,    50,    24,
      -1,    84,    45,    24,    -1,    84,    45,    24,    50,    24,
      -1,    22,    -1,    37,    22,    -1,    85,    37,    22,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    52,    52,    53,    54,    55,    56,    57,    58,    59,
      63,    64,    68,    69,    73,    74,    75,    79,    83,    84,
      85,    86,    90,    94,    95,    99,   100,   105,   106,   107,
     108,   109,   113,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   129,   130,   131,   132,   136,   137,   138,   139,
     140,   144,   145,   149,   153,   154,   155,   156,   157,   158,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   178,   179,   180,   181,   185,   186,   187,   188,
     192,   196,   197,   201,   202,   203,   204,   208,   212,   213,
     214,   215,   219,   220,   221,   222,   226,   230,   234,   235,
     239,   240,   244,   245,   249,   250,   251,   252,   253,   254,
     255,   259,   260,   261,   262,   266,   267,   268
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
  "encoding_begin", "encoding", "data_element", "data_group_begin",
  "data_group", "discriminated_union_begin", "discriminated_union",
  "union_data_element", "data_type", "integer_type", "fixed_point_type",
  "floating_point_type", "character_type", "character_string_type",
  "bit_string_type", "sequence_type", "dictionary_type", "class_ref_type",
  "inline_enum_type", "enum_values", "arg_list", "id_list", "expr",
  "character_set", "qname", 0
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
      57,    57,    58,    59,    59,    60,    60,    61,    61,    61,
      61,    61,    62,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    64,    64,    64,    64,    65,    65,    65,    65,
      65,    66,    66,    67,    68,    68,    68,    68,    68,    68,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    70,    70,    70,    70,    71,    71,    71,    71,
      72,    73,    73,    74,    74,    74,    74,    75,    76,    76,
      76,    76,    77,    77,    77,    77,    78,    79,    80,    80,
      81,    81,    82,    82,    83,    83,    83,    83,    83,    83,
      83,    84,    84,    84,    84,    85,    85,    85
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       3,     4,     4,     4,     3,     4,     4,     3,     7,     2,
       4,     4,     3,     8,     4,     4,     3,     7,     2,     2,
       2,     2,     3,     3,     6,     5,     3,     6,     5,     6,
       9,     8,     2,     5,     2,     2,     2,     2,     5,     2,
       5,     8,     2,     3,     3,     7,     5,     3,     7,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     6,     6,     6,     6,     8,     8,     8,     8,
       6,     4,     4,     4,     9,     4,     9,     6,     4,     4,
       4,     4,     6,     6,     6,     6,     2,     5,     3,     5,
       3,     5,     1,     3,     1,     2,     2,     1,     2,     2,
       1,     1,     3,     3,     5,     1,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     3,
       4,     0,     5,     0,     6,     0,     7,     0,     8,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    70,    71,     0,    60,    61,    62,
      63,    64,    65,    66,    67,    69,    68,     0,     0,     0,
       0,     0,     0,     0,     0,    19,     0,     0,     0,    31,
       0,     0,     0,    28,    29,     0,    30,     0,     0,     0,
      52,     0,     0,    10,    14,   115,     0,     0,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,     0,
      22,     0,     0,    26,     0,     0,    42,     0,    47,    49,
      32,    46,    44,    45,     0,     0,    53,     0,    11,   116,
       0,     0,    13,     0,     0,   110,   104,   107,     0,     0,
       0,     0,     0,     0,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     0,     0,     0,     0,
       0,    16,    15,    21,    20,    24,    25,     0,     0,    36,
       0,     0,    33,     0,     0,    57,     0,     0,    54,   117,
       0,     0,    91,    90,   105,   108,   106,   109,     0,     0,
       0,     0,     0,    81,     0,    82,     0,    83,    85,     0,
      89,    88,     0,     0,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      97,     0,     0,     0,     0,     0,     0,   112,   113,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    38,     0,    35,     0,     0,    43,    48,    50,     0,
     102,     0,    59,     0,    56,    98,     0,    75,    73,    74,
      72,     0,     0,    80,     0,     0,     0,    87,    95,    93,
      94,    92,    18,     0,   101,    27,     0,     0,    37,     0,
      39,    34,     0,     0,     0,     0,     0,     0,   114,     0,
       0,    23,    51,     0,     0,    58,   103,    55,    99,    79,
      77,    78,    76,     0,     0,    41,     0,    84,    86,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,   108,    65,   109,    19,    20,    70,    67,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,   171,
      93,   241,   130,   137,    77
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -83
static const yytype_int16 yypact[] =
{
     -83,    63,   -83,    45,    71,   345,    60,    69,    83,   -83,
     -83,   277,   -83,   144,   -83,    34,   -83,    99,   -83,   296,
     -83,    -7,    97,    25,    25,   -17,    75,   100,   101,   115,
     126,   137,   138,   139,   -83,   -83,   165,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   166,   166,   170,
       6,   152,   174,    10,   163,   -83,   181,   182,   167,   -83,
     183,   229,   171,   -83,   -83,   260,   -83,   188,    11,   173,
     -83,   190,   175,   -83,   -83,   -83,   192,   -12,   179,   180,
     362,     0,     0,     0,     0,     0,   134,   136,     0,   379,
     396,   195,   176,    49,    98,   187,   199,   -83,   200,   201,
     -83,   203,   205,   206,   231,     7,   -83,   166,   -83,   -83,
     -83,   -83,   -83,   -83,    37,    39,   -83,    65,   -83,   -83,
     224,   225,   -83,   114,   169,   -83,   -83,   -83,    91,   129,
     204,   207,   208,   209,   210,   232,   198,    38,   234,    47,
     226,   116,   202,    78,   230,   -83,     0,     5,   247,   273,
     256,   -83,   -83,   -83,   -83,   -83,   -83,   413,   236,   -83,
     103,   237,   -83,   242,   263,   -83,   258,   264,   -83,   -83,
     255,    50,   -83,   -83,   -83,   -83,   -83,   -83,     0,     0,
       0,     0,     0,   -83,   290,   -83,   291,   257,   272,     0,
     -83,   -83,   430,   447,   -83,   297,   304,   278,   300,   293,
      35,   299,     0,   327,     0,   316,   301,   316,   303,   318,
     -83,   321,   -27,   -25,   302,   305,   306,   -83,   294,     0,
       0,   307,   120,   298,   135,   317,   325,   322,     0,   331,
     349,   -83,   166,   -83,   344,   193,   -83,   -83,   -83,   350,
     -83,    64,   -83,    68,   -83,   -83,   340,   -83,   -83,   -83,
     -83,     0,     0,   -83,   363,   354,   355,   -83,   -83,   -83,
     -83,   -83,   -83,   365,   -83,   -83,   366,   107,   -83,   373,
     -83,   -83,   383,   395,   384,   409,    19,    72,   -83,     0,
       0,   -83,   -83,   400,     0,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   388,   393,   -83,   412,   -83,   -83,   -83
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -83,   -83,    67,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -10,   -83,    -9,   -83,   -83,   -83,    -1,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -37,   244,   -82,   368,   432
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     131,   132,   133,   134,    36,    79,   140,    64,    66,   195,
      52,    94,    56,    23,    24,   247,    72,   249,    71,   248,
      60,   250,   158,   125,   126,   120,   127,   121,    96,   105,
      80,    73,    99,   115,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,   196,   159,   106,    75,   107,   128,
     129,    57,   161,    80,    80,   112,   113,    80,    80,   163,
     164,   289,    76,     2,   194,   290,     3,     4,     5,    21,
     160,     6,     7,   231,    58,   162,   232,   165,   185,   124,
      55,     8,    80,   186,    63,   166,   167,   188,   142,   144,
     210,   147,   186,    22,   148,   211,   212,   213,   214,   215,
     216,    47,     3,   168,   272,    23,    24,   221,   274,   273,
      48,    59,    60,   273,   291,   174,    81,   175,   292,    82,
     234,    61,   239,   192,    49,    80,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    74,   255,   256,    62,
     149,    83,    85,   148,    84,   203,   264,     3,   148,   283,
      23,    24,   148,   176,    86,   177,   201,   135,   136,   138,
     136,    80,   172,    80,   190,    87,    53,    80,   258,   276,
     277,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    88,    80,   260,    54,    89,    90,    91,    92,    95,
      97,   223,   225,   237,   238,   267,    98,   293,   294,    23,
      24,   100,   296,   101,   102,   104,    60,   103,   269,   110,
     114,   116,   117,   118,   119,   105,   120,   173,   122,   146,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
     150,   270,   106,   145,   107,    23,    24,   151,   152,   153,
      80,   154,    60,   155,   156,   157,   169,   170,   184,   178,
     191,   105,   179,   180,   181,   182,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    23,    24,   106,   197,
     107,   189,   183,    60,   187,   193,    80,   198,   199,   202,
     204,   205,    61,    23,    24,   206,   208,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,   207,   209,    50,
     111,   219,    23,    24,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,   217,   218,   220,    51,    68,   226,
     227,   228,   229,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    23,    24,   230,    69,   233,   240,   242,
      60,   244,   245,   246,   254,   263,   259,   251,   253,   235,
     252,    23,    24,   257,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,   262,   261,   236,    25,    23,    24,
     265,   266,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,   268,   275,   123,    23,    24,   278,   271,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,   279,
     280,   141,    23,    24,   281,   282,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,   284,   286,   143,    23,
      24,   285,   287,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,   288,   297,   200,    23,    24,   295,   298,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
     299,   243,   222,    23,    24,   139,    78,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,     0,     0,   224,
       0,     0,     0,     0,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35
};

static const yytype_int16 yycheck[] =
{
      82,    83,    84,    85,     5,    22,    88,    17,    17,     4,
      11,    48,    13,     6,     7,    42,    23,    42,    19,    46,
      13,    46,    15,    23,    24,    37,    26,    39,    22,    22,
      47,    38,    22,    22,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    39,    38,    39,    22,    41,    49,
      50,    17,    15,    47,    47,    65,    65,    47,    47,    20,
      21,    42,    37,     0,   146,    46,     3,     4,     5,    24,
     107,     8,     9,    38,    40,    38,    41,    38,    40,    80,
      13,    18,    47,    45,    17,    20,    21,    40,    89,    90,
      40,    42,    45,    22,    45,    45,   178,   179,   180,   181,
     182,    41,     3,    38,    40,     6,     7,   189,    40,    45,
      41,    12,    13,    45,    42,    24,    41,    26,    46,    44,
     202,    22,   204,    45,    41,    47,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    39,   219,   220,    40,
      42,    41,    41,    45,    44,    42,   228,     3,    45,    42,
       6,     7,    45,    24,    39,    26,   157,    23,    24,    23,
      24,    47,    48,    47,    48,    39,    22,    47,    48,   251,
     252,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    44,    47,    48,    40,    47,    47,    22,    22,    19,
      38,   192,   193,   203,   203,   232,    22,   279,   280,     6,
       7,    38,   284,    22,    22,    22,    13,    40,    15,    38,
      22,    38,    22,    38,    22,    22,    37,    48,    38,    43,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      43,    38,    39,    38,    41,     6,     7,    38,    38,    38,
      47,    38,    13,    38,    38,    14,    22,    22,    50,    45,
      48,    22,    45,    45,    45,    45,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,     6,     7,    39,    22,
      41,    45,    40,    13,    40,    45,    47,     4,    22,    43,
      43,    39,    22,     6,     7,    22,    22,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    39,    43,    22,
      40,    44,     6,     7,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    24,    24,    44,    40,    22,    22,
      16,    43,    22,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,     6,     7,    42,    40,    38,    22,    38,
      13,    38,    24,    22,    50,    23,    48,    45,    42,    22,
      45,     6,     7,    46,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    39,    48,    39,    22,     6,     7,
      39,    22,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    38,    43,    22,     6,     7,    24,    38,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    45,
      45,    22,     6,     7,    39,    39,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    43,    22,    22,     6,
       7,    38,    38,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    24,    46,    22,     6,     7,    38,    46,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      38,   207,    22,     6,     7,    87,    24,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    52,     0,     3,     4,     5,     8,     9,    18,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    66,
      67,    24,    22,     6,     7,    22,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    41,    41,    41,
      22,    40,    69,    22,    40,    53,    69,    17,    40,    12,
      13,    22,    40,    53,    63,    64,    65,    69,    22,    40,
      68,    69,    23,    38,    39,    22,    37,    85,    85,    22,
      47,    41,    44,    41,    44,    41,    39,    39,    44,    47,
      47,    22,    22,    81,    81,    19,    22,    38,    22,    22,
      38,    22,    22,    40,    22,    22,    39,    41,    63,    65,
      38,    40,    63,    65,    22,    22,    38,    22,    38,    22,
      37,    39,    38,    22,    69,    23,    24,    26,    49,    50,
      83,    83,    83,    83,    83,    23,    24,    84,    23,    84,
      83,    22,    69,    22,    69,    38,    43,    42,    45,    42,
      43,    38,    38,    38,    38,    38,    38,    14,    15,    38,
      81,    15,    38,    20,    21,    38,    20,    21,    38,    22,
      22,    80,    48,    48,    24,    26,    24,    26,    45,    45,
      45,    45,    45,    40,    50,    40,    45,    40,    40,    45,
      48,    48,    45,    45,    83,     4,    39,    22,     4,    22,
      22,    69,    43,    42,    43,    39,    22,    39,    22,    43,
      40,    45,    83,    83,    83,    83,    83,    24,    24,    44,
      44,    83,    22,    69,    22,    69,    22,    16,    43,    22,
      42,    38,    41,    38,    83,    22,    39,    63,    65,    83,
      22,    82,    38,    82,    38,    24,    22,    42,    46,    42,
      46,    45,    45,    42,    50,    83,    83,    46,    48,    48,
      48,    48,    39,    23,    83,    39,    22,    81,    38,    15,
      38,    38,    40,    45,    40,    43,    83,    83,    24,    45,
      45,    39,    39,    42,    43,    38,    22,    38,    24,    42,
      46,    42,    46,    83,    83,    38,    83,    46,    46,    38
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
#line 1353 "hare-idl.tab.c"
	break;
      case 4: /* "KW_PUBLISHABLE_STRUCT" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1362 "hare-idl.tab.c"
	break;
      case 5: /* "KW_TYPEDEF" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1371 "hare-idl.tab.c"
	break;
      case 6: /* "KW_ENUM" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1380 "hare-idl.tab.c"
	break;
      case 7: /* "KW_CLASS" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1389 "hare-idl.tab.c"
	break;
      case 8: /* "KW_MAPPING" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1398 "hare-idl.tab.c"
	break;
      case 9: /* "KW_ENCODING" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1407 "hare-idl.tab.c"
	break;
      case 10: /* "KW_NUMERIC" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1416 "hare-idl.tab.c"
	break;
      case 11: /* "KW_INT" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1425 "hare-idl.tab.c"
	break;
      case 12: /* "KW_FENCE" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1434 "hare-idl.tab.c"
	break;
      case 13: /* "KW_EXTEND" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1443 "hare-idl.tab.c"
	break;
      case 14: /* "KW_TO" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1452 "hare-idl.tab.c"
	break;
      case 15: /* "KW_DEFAULT" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1461 "hare-idl.tab.c"
	break;
      case 16: /* "KW_FILE" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1470 "hare-idl.tab.c"
	break;
      case 17: /* "KW_CLASS_UPP" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1479 "hare-idl.tab.c"
	break;
      case 18: /* "KW_DISCRIMINATED_UNION" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1488 "hare-idl.tab.c"
	break;
      case 19: /* "KW_DISCRIMINANT" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1497 "hare-idl.tab.c"
	break;
      case 20: /* "KW_WHEN_DISCRIMINANT_IN" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1506 "hare-idl.tab.c"
	break;
      case 21: /* "KW_WHEN_DISCRIMINANT_IS" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1515 "hare-idl.tab.c"
	break;
      case 22: /* "IDENTIFIER" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1524 "hare-idl.tab.c"
	break;
      case 23: /* "STRING_LITERAL" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1533 "hare-idl.tab.c"
	break;
      case 24: /* "INTEGER_LITERAL" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1542 "hare-idl.tab.c"
	break;
      case 25: /* "CHAR_LITERAL" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1551 "hare-idl.tab.c"
	break;
      case 26: /* "FLOAT_LITERAL" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1560 "hare-idl.tab.c"
	break;
      case 27: /* "KW_INTEGER" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1569 "hare-idl.tab.c"
	break;
      case 28: /* "KW_FIXED_POINT" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1578 "hare-idl.tab.c"
	break;
      case 29: /* "KW_FLOATING_POINT" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1587 "hare-idl.tab.c"
	break;
      case 30: /* "KW_CHARACTER" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1596 "hare-idl.tab.c"
	break;
      case 31: /* "KW_CHARACTER_STRING" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1605 "hare-idl.tab.c"
	break;
      case 32: /* "KW_BIT_STRING" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1614 "hare-idl.tab.c"
	break;
      case 33: /* "KW_SEQUENCE" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1623 "hare-idl.tab.c"
	break;
      case 34: /* "KW_DICTIONARY" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1632 "hare-idl.tab.c"
	break;
      case 35: /* "KW_PRINTABLE_ASCII_STRING" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1641 "hare-idl.tab.c"
	break;
      case 36: /* "KW_UNICODE_STRING" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1650 "hare-idl.tab.c"
	break;
      case 37: /* "OP_FOUR_DOTS" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1659 "hare-idl.tab.c"
	break;
      case 38: /* "';'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1668 "hare-idl.tab.c"
	break;
      case 39: /* "'{'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1677 "hare-idl.tab.c"
	break;
      case 40: /* "'}'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1686 "hare-idl.tab.c"
	break;
      case 41: /* "'('" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1695 "hare-idl.tab.c"
	break;
      case 42: /* "')'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1704 "hare-idl.tab.c"
	break;
      case 43: /* "'='" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1713 "hare-idl.tab.c"
	break;
      case 44: /* "'['" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1722 "hare-idl.tab.c"
	break;
      case 45: /* "','" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1731 "hare-idl.tab.c"
	break;
      case 46: /* "']'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1740 "hare-idl.tab.c"
	break;
      case 47: /* "'<'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1749 "hare-idl.tab.c"
	break;
      case 48: /* "'>'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1758 "hare-idl.tab.c"
	break;
      case 49: /* "'+'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1767 "hare-idl.tab.c"
	break;
      case 50: /* "'-'" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1776 "hare-idl.tab.c"
	break;
      case 52: /* "file" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1785 "hare-idl.tab.c"
	break;
      case 53: /* "line_directive" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1794 "hare-idl.tab.c"
	break;
      case 54: /* "typedef_decl" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1803 "hare-idl.tab.c"
	break;
      case 55: /* "publishable_struct_begin" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1812 "hare-idl.tab.c"
	break;
      case 56: /* "publishable_struct" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1821 "hare-idl.tab.c"
	break;
      case 57: /* "mapping_begin" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1830 "hare-idl.tab.c"
	break;
      case 58: /* "mapping" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1839 "hare-idl.tab.c"
	break;
      case 59: /* "ext_file_mapping_begin" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1848 "hare-idl.tab.c"
	break;
      case 60: /* "ext_file_mapping" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1857 "hare-idl.tab.c"
	break;
      case 61: /* "encoding_begin" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1866 "hare-idl.tab.c"
	break;
      case 62: /* "encoding" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1875 "hare-idl.tab.c"
	break;
      case 63: /* "data_element" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1884 "hare-idl.tab.c"
	break;
      case 64: /* "data_group_begin" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1893 "hare-idl.tab.c"
	break;
      case 65: /* "data_group" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1902 "hare-idl.tab.c"
	break;
      case 66: /* "discriminated_union_begin" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1911 "hare-idl.tab.c"
	break;
      case 67: /* "discriminated_union" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1920 "hare-idl.tab.c"
	break;
      case 68: /* "union_data_element" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1929 "hare-idl.tab.c"
	break;
      case 69: /* "data_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1938 "hare-idl.tab.c"
	break;
      case 70: /* "integer_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1947 "hare-idl.tab.c"
	break;
      case 71: /* "fixed_point_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1956 "hare-idl.tab.c"
	break;
      case 72: /* "floating_point_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1965 "hare-idl.tab.c"
	break;
      case 73: /* "character_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1974 "hare-idl.tab.c"
	break;
      case 74: /* "character_string_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1983 "hare-idl.tab.c"
	break;
      case 75: /* "bit_string_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1992 "hare-idl.tab.c"
	break;
      case 76: /* "sequence_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2001 "hare-idl.tab.c"
	break;
      case 77: /* "dictionary_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2010 "hare-idl.tab.c"
	break;
      case 78: /* "class_ref_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2019 "hare-idl.tab.c"
	break;
      case 79: /* "inline_enum_type" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2028 "hare-idl.tab.c"
	break;
      case 80: /* "enum_values" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2037 "hare-idl.tab.c"
	break;
      case 81: /* "arg_list" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2046 "hare-idl.tab.c"
	break;
      case 82: /* "id_list" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2055 "hare-idl.tab.c"
	break;
      case 83: /* "expr" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2064 "hare-idl.tab.c"
	break;
      case 84: /* "character_set" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2073 "hare-idl.tab.c"
	break;
      case 85: /* "qname" */

/* Line 1000 of yacc.c  */
#line 43 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2082 "hare-idl.tab.c"
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
    { (yyval) = (yyvsp[(1) - (2)]); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 85 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])));  releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 86 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute(createIdType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)])));  releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 90 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 94 "hare-idl.y"
    { (yyval) = createExtFileMapping((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(7) - (8)])); releaseYys5((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 95 "hare-idl.y"
    { (yyval) = addClassMapping((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 99 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (4)]); releaseYys3((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 100 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 105 "hare-idl.y"
    { (yyval) = createEncoding((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(6) - (7)])); releaseYys4((yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 106 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (2)]); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 107 "hare-idl.y"
    { (yyval) = addToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 108 "hare-idl.y"
    { (yyval) = addToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 109 "hare-idl.y"
    { (yyval) = addFenceToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 113 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 117 "hare-idl.y"
    { (yyval) = createAttribute((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 118 "hare-idl.y"
    { (yyval) = createEncodingAttribute((yyvsp[(1) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 119 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); releaseYys3((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 120 "hare-idl.y"
    { (yyval) = createAttribute(createIdType((yyvsp[(1) - (3)])), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 121 "hare-idl.y"
    { (yyval) = createEncodingAttribute(createIdType((yyvsp[(1) - (6)])), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)]));;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 122 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (5)]), createIdType((yyvsp[(4) - (5)]))); releaseYys3((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 123 "hare-idl.y"
    { (yyval) = createAttribute(createEncodingType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)])), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 124 "hare-idl.y"
    { (yyval) = createEncodingAttribute(createEncodingType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)])), (yyvsp[(5) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 125 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (8)]), createEncodingType((yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]))); releaseYys5((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 129 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, 0); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 130 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), 0); releaseYys3((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 131 "hare-idl.y"
    { (yyval) = addToEncodingGroup((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 132 "hare-idl.y"
    { (yyval) = addToEncodingGroup((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 136 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (2)]); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 137 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 138 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 139 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 140 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 144 "hare-idl.y"
    { (yyval) = createUnion((yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)])); releaseYys5((yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 145 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 149 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 153 "hare-idl.y"
    { (yyval) = createAttribute((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 154 "hare-idl.y"
    { (yyval) = createUnionAttribute((yyvsp[(1) - (7)]), (yyvsp[(2) - (7)]), (yyvsp[(5) - (7)])); releaseYys4((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 155 "hare-idl.y"
    { (yyval) = createUnionAttribute((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), addIdentifier(0, (yyvsp[(4) - (5)]))); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 156 "hare-idl.y"
    { (yyval) = createAttribute(createIdType((yyvsp[(1) - (3)])), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 157 "hare-idl.y"
    { (yyval) = createUnionAttribute(createIdType((yyvsp[(1) - (7)])), (yyvsp[(2) - (7)]), (yyvsp[(5) - (7)])); releaseYys4((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 158 "hare-idl.y"
    { (yyval) = createUnionAttribute(createIdType((yyvsp[(1) - (5)])), (yyvsp[(2) - (5)]), addIdentifier(0, (yyvsp[(4) - (5)]))); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 173 "hare-idl.y"
    { (yyval) = createPrintableAsciiStringType((yyvsp[(1) - (1)])); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 174 "hare-idl.y"
    { (yyval) = createUnicodeStringType((yyvsp[(1) - (1)])); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 178 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 179 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 180 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 181 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 185 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), true, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), true); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 186 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), false, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), true); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 187 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), true, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), false); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 188 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), false, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), false); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 192 "hare-idl.y"
    { (yyval) = createFloatingPointType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 196 "hare-idl.y"
    { (yyval) = createCharacterType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 197 "hare-idl.y"
    { (yyval) = createCharacterType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 201 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), 0, 0); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 202 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 203 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), 0, 0); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 204 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 208 "hare-idl.y"
    { (yyval) = createBitStringType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 212 "hare-idl.y"
    { (yyval) = createSequence((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 213 "hare-idl.y"
    { (yyval) = createSequence((yyvsp[(1) - (4)]), createIdType((yyvsp[(3) - (4)]))); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 214 "hare-idl.y"
    { (yyval) = createNamedSequence((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 215 "hare-idl.y"
    { (yyval) = createNamedSequence((yyvsp[(1) - (4)]), createIdType((yyvsp[(3) - (4)]))); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 219 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 220 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 221 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 222 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 226 "hare-idl.y"
    { (yyval) = createClassReference((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 230 "hare-idl.y"
    { (yyval) = createInlineEnum((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 234 "hare-idl.y"
    { (yyval) = addEnumValue(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 235 "hare-idl.y"
    { (yyval) = addEnumValue((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 239 "hare-idl.y"
    { (yyval) = addExpression(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 240 "hare-idl.y"
    { (yyval) = addExpression((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 244 "hare-idl.y"
    { (yyval) = addIdentifier(0, (yyvsp[(1) - (1)])); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 245 "hare-idl.y"
    { (yyval) = addIdentifier((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 249 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 250 "hare-idl.y"
    { (yyval) = (yyvsp[(2) - (2)]); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 251 "hare-idl.y"
    { (yyval) = makeMinusIntLit((yyvsp[(2) - (2)])); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 252 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 253 "hare-idl.y"
    { (yyval) = (yyvsp[(2) - (2)]); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 254 "hare-idl.y"
    { (yyval) = makeMinusFloatLit((yyvsp[(2) - (2)])); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 255 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 259 "hare-idl.y"
    { (yyval) = addToCharSet(0, (yyvsp[(1) - (1)]), 0); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 260 "hare-idl.y"
    { (yyval) = addToCharSet(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 261 "hare-idl.y"
    { (yyval) = addToCharSet((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 0);  releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 262 "hare-idl.y"
    { (yyval) = addToCharSet((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 266 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 267 "hare-idl.y"
    { (yyval) = makeFourDotsPrefix((yyvsp[(2) - (2)])); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 268 "hare-idl.y"
    { (yyval) = addFourDotsName((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;



/* Line 1455 of yacc.c  */
#line 3129 "hare-idl.tab.c"
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



