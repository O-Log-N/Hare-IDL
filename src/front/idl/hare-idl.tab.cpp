
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
#line 43 "hare-idl.y"

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
     KW_UNICODE_STRING = 291
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
#line 157 "hare-idl.tab.c"

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
#define YYLAST   472

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNRULES -- Number of states.  */
#define YYNSTATES  295

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      40,    41,     2,    48,    44,    49,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    37,
      46,    42,    47,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    43,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      35,    36
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
     523,   525,   527,   531,   535
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      51,     0,    -1,    -1,    51,    52,    -1,    51,    53,    -1,
      51,    55,    -1,    51,    57,    -1,    51,    59,    -1,    51,
      61,    -1,    51,    66,    -1,     3,    24,    37,    -1,     3,
      24,    23,    37,    -1,     5,    68,    22,    37,    -1,     5,
      22,    22,    37,    -1,     4,    22,    38,    -1,    54,    68,
      22,    37,    -1,    54,    22,    22,    37,    -1,    54,    39,
      37,    -1,     8,    40,    80,    41,     4,    22,    38,    -1,
      56,    52,    -1,    56,    68,    22,    37,    -1,    56,    22,
      22,    37,    -1,    56,    39,    37,    -1,     8,    40,    80,
      41,    38,    16,    23,    38,    -1,    58,    17,    22,    37,
      -1,    58,    39,    39,    37,    -1,    58,    39,    39,    -1,
       9,    40,    80,    41,     4,    22,    38,    -1,    60,    52,
      -1,    60,    62,    -1,    60,    64,    -1,    60,    12,    -1,
      60,    39,    37,    -1,    68,    22,    37,    -1,    68,    22,
      15,    42,    82,    37,    -1,    13,    22,    14,    68,    37,
      -1,    22,    22,    37,    -1,    22,    22,    15,    42,    82,
      37,    -1,    13,    22,    14,    22,    37,    -1,    22,    40,
      80,    41,    22,    37,    -1,    22,    40,    80,    41,    22,
      15,    42,    82,    37,    -1,    13,    22,    14,    22,    40,
      80,    41,    37,    -1,    22,    38,    -1,    22,    40,    80,
      41,    38,    -1,    63,    62,    -1,    63,    64,    -1,    63,
      39,    -1,    22,    62,    -1,    22,    40,    80,    41,    62,
      -1,    22,    64,    -1,    22,    40,    80,    41,    64,    -1,
      18,    40,    19,    42,    22,    41,    22,    38,    -1,    65,
      67,    -1,    65,    39,    37,    -1,    68,    22,    37,    -1,
      68,    22,    20,    38,    81,    39,    37,    -1,    68,    22,
      21,    22,    37,    -1,    22,    22,    37,    -1,    22,    22,
      20,    38,    81,    39,    37,    -1,    22,    22,    21,    22,
      37,    -1,    69,    -1,    70,    -1,    71,    -1,    72,    -1,
      73,    -1,    74,    -1,    75,    -1,    76,    -1,    78,    -1,
      77,    -1,    35,    -1,    36,    -1,    27,    43,    82,    44,
      82,    45,    -1,    27,    40,    82,    44,    82,    45,    -1,
      27,    43,    82,    44,    82,    41,    -1,    27,    40,    82,
      44,    82,    41,    -1,    28,    43,    82,    44,    82,    44,
      82,    45,    -1,    28,    40,    82,    44,    82,    44,    82,
      45,    -1,    28,    43,    82,    44,    82,    44,    82,    41,
      -1,    28,    40,    82,    44,    82,    44,    82,    41,    -1,
      29,    40,    82,    44,    82,    41,    -1,    30,    38,    23,
      39,    -1,    30,    38,    83,    39,    -1,    31,    38,    23,
      39,    -1,    31,    38,    23,    39,    43,    82,    44,    82,
      45,    -1,    31,    38,    83,    39,    -1,    31,    38,    83,
      39,    43,    82,    44,    82,    45,    -1,    32,    43,    82,
      44,    82,    45,    -1,    33,    46,    68,    47,    -1,    33,
      46,    22,    47,    -1,    22,    46,    68,    47,    -1,    22,
      46,    22,    47,    -1,    34,    46,    68,    44,    68,    47,
      -1,    34,    46,    22,    44,    68,    47,    -1,    34,    46,
      68,    44,    22,    47,    -1,    34,    46,    22,    44,    22,
      47,    -1,     7,    22,    -1,     6,    22,    38,    79,    39,
      -1,    22,    42,    24,    -1,    79,    44,    22,    42,    24,
      -1,    22,    42,    82,    -1,    80,    44,    22,    42,    82,
      -1,    22,    -1,    81,    44,    22,    -1,    24,    -1,    48,
      24,    -1,    49,    24,    -1,    26,    -1,    48,    26,    -1,
      49,    26,    -1,    23,    -1,    24,    -1,    24,    49,    24,
      -1,    83,    44,    24,    -1,    83,    44,    24,    49,    24,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    50,    50,    51,    52,    53,    54,    55,    56,    57,
      61,    62,    66,    67,    71,    72,    73,    77,    81,    82,
      83,    84,    88,    92,    93,    97,    98,   103,   104,   105,
     106,   107,   111,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   127,   128,   129,   130,   134,   135,   136,   137,
     138,   142,   143,   147,   151,   152,   153,   154,   155,   156,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   176,   177,   178,   179,   183,   184,   185,   186,
     190,   194,   195,   199,   200,   201,   202,   206,   210,   211,
     212,   213,   217,   218,   219,   220,   224,   228,   232,   233,
     237,   238,   242,   243,   247,   248,   249,   250,   251,   252,
     253,   257,   258,   259,   260
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
  "KW_PRINTABLE_ASCII_STRING", "KW_UNICODE_STRING", "';'", "'{'", "'}'",
  "'('", "')'", "'='", "'['", "','", "']'", "'<'", "'>'", "'+'", "'-'",
  "$accept", "file", "line_directive", "typedef_decl",
  "publishable_struct_begin", "publishable_struct", "mapping_begin",
  "mapping", "ext_file_mapping_begin", "ext_file_mapping",
  "encoding_begin", "encoding", "data_element", "data_group_begin",
  "data_group", "discriminated_union_begin", "discriminated_union",
  "union_data_element", "data_type", "integer_type", "fixed_point_type",
  "floating_point_type", "character_type", "character_string_type",
  "bit_string_type", "sequence_type", "dictionary_type", "class_ref_type",
  "inline_enum_type", "enum_values", "arg_list", "id_list", "expr",
  "character_set", 0
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
     285,   286,   287,   288,   289,   290,   291,    59,   123,   125,
      40,    41,    61,    91,    44,    93,    60,    62,    43,    45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    51,    51,    51,    51,    51,    51,    51,
      52,    52,    53,    53,    54,    54,    54,    55,    56,    56,
      56,    56,    57,    58,    58,    59,    59,    60,    60,    60,
      60,    60,    61,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    63,    63,    63,    63,    64,    64,    64,    64,
      64,    65,    65,    66,    67,    67,    67,    67,    67,    67,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    69,    69,    69,    70,    70,    70,    70,
      71,    72,    72,    73,    73,    73,    73,    74,    75,    75,
      75,    75,    76,    76,    76,    76,    77,    78,    79,    79,
      80,    80,    81,    81,    82,    82,    82,    82,    82,    82,
      82,    83,    83,    83,    83
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
       1,     1,     3,     3,     5
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
      52,     0,     0,    10,    14,     0,    96,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,     0,    22,     0,
       0,    26,     0,     0,    42,     0,    47,    49,    32,    46,
      44,    45,     0,     0,    53,     0,    11,     0,    13,     0,
       0,   110,   104,   107,     0,     0,     0,     0,     0,     0,
       0,     0,   111,     0,     0,     0,     0,     0,     0,     0,
       0,    12,     0,     0,     0,     0,     0,    16,    15,    21,
      20,    24,    25,     0,     0,    36,     0,     0,    33,     0,
       0,    57,     0,     0,    54,     0,     0,    91,    90,   105,
     108,   106,   109,     0,     0,     0,     0,     0,    81,     0,
      82,     0,    83,    85,     0,    89,    88,     0,     0,   100,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    97,     0,     0,     0,     0,
       0,     0,   112,   113,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,     0,    35,     0,
       0,    43,    48,    50,     0,   102,     0,    59,     0,    56,
      98,     0,    75,    73,    74,    72,     0,     0,    80,     0,
       0,     0,    87,    95,    93,    94,    92,    18,     0,   101,
      27,     0,     0,    37,     0,    39,    34,     0,     0,     0,
       0,     0,     0,   114,     0,     0,    23,    51,     0,     0,
      58,   103,    55,    99,    79,    77,    78,    76,     0,     0,
      41,     0,    84,    86,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,   106,    65,   107,    19,    20,    70,    67,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,   166,
      91,   236,   126,   133
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -81
static const yytype_int16 yypact[] =
{
     -81,    80,   -81,    45,     1,   329,    -8,    21,    51,   -81,
     -81,   263,   -81,   214,   -81,   -12,   -81,   141,   -81,   281,
     -81,    -6,    65,    89,    96,   -13,    39,    97,    92,   103,
     119,   140,   152,   156,   -81,   -81,   139,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   179,   179,   184,
       8,   167,   193,    24,   182,   -81,   200,   201,   186,   -81,
     204,   178,   190,   -81,   -81,   245,   -81,   206,    26,   192,
     -81,   208,   194,   -81,   -81,   195,   -81,   197,   346,     2,
       2,     2,     2,     2,   127,   155,     2,   363,   380,   198,
     196,   101,   105,   212,   202,   -81,   203,   218,   -81,   219,
     220,   222,   223,     7,   -81,   179,   -81,   -81,   -81,   -81,
     -81,   -81,    37,    38,   -81,    44,   -81,   210,   -81,   118,
     213,   -81,   -81,   -81,    66,   112,   217,   221,   224,   227,
     238,   225,   234,   -23,   247,   -20,   256,   135,   215,   116,
     257,   -81,     2,    11,   241,   262,   267,   -81,   -81,   -81,
     -81,   -81,   -81,   397,   264,   -81,   114,   265,   -81,   266,
     283,   -81,   284,   299,   -81,   282,    32,   -81,   -81,   -81,
     -81,   -81,   -81,     2,     2,     2,     2,     2,   -81,   302,
     -81,   303,   280,   285,     2,   -81,   -81,   414,   431,   -81,
     307,   314,   289,   310,   292,    20,   300,     2,   312,     2,
     316,   317,   316,   318,   325,   -81,   344,    22,    60,   323,
     327,   331,   -81,   334,     2,     2,   339,   146,   341,   150,
     342,   362,   378,     2,   367,   384,   -81,   179,   -81,   381,
      93,   -81,   -81,   -81,   385,   -81,    34,   -81,    63,   -81,
     -81,   375,   -81,   -81,   -81,   -81,     2,     2,   -81,   399,
     390,   391,   -81,   -81,   -81,   -81,   -81,   -81,   401,   -81,
     -81,   402,   115,   -81,   409,   -81,   -81,   415,   432,   418,
     433,    68,    69,   -81,     2,     2,   -81,   -81,   419,     2,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   423,   424,
     -81,   434,   -81,   -81,   -81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -81,   -81,    99,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   -10,   -81,    -9,   -81,   -81,   -81,    -1,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -37,   268,   -80,   387
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     127,   128,   129,   130,    36,    57,   136,    64,    66,    77,
      52,    92,    56,    23,    24,   190,   180,    72,    71,   183,
      60,   181,   154,    22,   181,   121,   122,    58,   123,   103,
      94,    73,    47,    78,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,   155,   104,    97,   105,   113,   191,
     124,   125,   157,    78,    78,   110,   111,   226,   159,   160,
     227,    48,   189,   242,   162,   163,    78,   243,   156,    21,
      78,   205,    78,   267,   158,   161,   206,   120,   268,    79,
       2,   164,    80,     3,     4,     5,   138,   140,     6,     7,
     169,    49,   170,   207,   208,   209,   210,   211,     8,    23,
      24,   244,   269,    74,   216,   245,    60,   268,   264,   284,
     286,    75,    55,   285,   287,   103,    63,   229,    76,   234,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
     265,   104,    83,   105,   250,   251,   171,    81,   172,    78,
      82,    84,   143,   259,     3,   144,   145,    23,    24,   144,
     131,   132,   196,    59,    60,   198,   278,    85,   144,   144,
     187,    89,    78,    61,    78,   167,   271,   272,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,   134,   132,
      62,    78,   185,    86,    23,    24,   218,   220,   232,   233,
     262,    60,    78,   253,   288,   289,    78,   255,    87,   291,
     103,    90,    88,    93,    95,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    96,   104,     3,   105,    98,
      23,    24,    99,   100,    78,   101,   102,   108,   112,   114,
     115,   116,   165,   117,   118,   141,    53,   153,   142,   147,
     148,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    23,    24,    54,   146,   149,   150,   151,    60,   152,
     168,   173,   186,   192,   178,   174,   193,    61,   175,    23,
      24,   176,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,   177,   179,   109,    50,   182,    23,    24,   194,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
     184,   188,    51,    68,   200,   201,   197,   199,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    23,    24,
      69,   203,   202,   214,   204,    60,   212,   213,   215,   221,
     222,   223,   224,   225,   230,    23,    24,   228,   235,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,   240,
     231,    25,    23,    24,   237,   239,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,   241,   246,   119,    23,
      24,   247,   248,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,   249,   252,   137,    23,    24,   254,   256,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
     257,   258,   139,    23,    24,   260,   261,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,   270,   263,   195,
      23,    24,   266,   273,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,   274,   275,   217,    23,    24,   276,
     277,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,   279,   280,   219,   281,   282,   290,   283,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,   292,   293,
     238,   294,   135
};

static const yytype_uint16 yycheck[] =
{
      80,    81,    82,    83,     5,    17,    86,    17,    17,    22,
      11,    48,    13,     6,     7,     4,    39,    23,    19,    39,
      13,    44,    15,    22,    44,    23,    24,    39,    26,    22,
      22,    37,    40,    46,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    22,    40,    22,    38,
      48,    49,    15,    46,    46,    65,    65,    37,    20,    21,
      40,    40,   142,    41,    20,    21,    46,    45,   105,    24,
      46,    39,    46,    39,    37,    37,    44,    78,    44,    40,
       0,    37,    43,     3,     4,     5,    87,    88,     8,     9,
      24,    40,    26,   173,   174,   175,   176,   177,    18,     6,
       7,    41,    39,    38,   184,    45,    13,    44,    15,    41,
      41,    22,    13,    45,    45,    22,    17,   197,    22,   199,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    40,    40,   214,   215,    24,    40,    26,    46,
      43,    38,    41,   223,     3,    44,    41,     6,     7,    44,
      23,    24,   153,    12,    13,    41,    41,    38,    44,    44,
      44,    22,    46,    22,    46,    47,   246,   247,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    23,    24,
      39,    46,    47,    43,     6,     7,   187,   188,   198,   198,
     227,    13,    46,    47,   274,   275,    46,    47,    46,   279,
      22,    22,    46,    19,    37,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    22,    38,     3,    40,    37,
       6,     7,    22,    22,    46,    39,    22,    37,    22,    37,
      22,    37,    22,    38,    37,    37,    22,    14,    42,    37,
      37,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,     6,     7,    39,    42,    37,    37,    37,    13,    37,
      47,    44,    47,    22,    39,    44,     4,    22,    44,     6,
       7,    44,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    44,    49,    39,    22,    39,     6,     7,    22,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      44,    44,    39,    22,    38,    22,    42,    42,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,     6,     7,
      39,    22,    38,    43,    42,    13,    24,    24,    43,    22,
      16,    42,    22,    41,    22,     6,     7,    37,    22,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    24,
      38,    22,     6,     7,    37,    37,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    22,    44,    22,     6,
       7,    44,    41,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    49,    45,    22,     6,     7,    47,    47,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      38,    23,    22,     6,     7,    38,    22,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    42,    37,    22,
       6,     7,    37,    24,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    44,    44,    22,     6,     7,    38,
      38,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    42,    37,    22,    22,    37,    37,    24,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    45,    45,
     202,    37,    85
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    51,     0,     3,     4,     5,     8,     9,    18,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    65,
      66,    24,    22,     6,     7,    22,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    40,    40,    40,
      22,    39,    68,    22,    39,    52,    68,    17,    39,    12,
      13,    22,    39,    52,    62,    63,    64,    68,    22,    39,
      67,    68,    23,    37,    38,    22,    22,    22,    46,    40,
      43,    40,    43,    40,    38,    38,    43,    46,    46,    22,
      22,    80,    80,    19,    22,    37,    22,    22,    37,    22,
      22,    39,    22,    22,    38,    40,    62,    64,    37,    39,
      62,    64,    22,    22,    37,    22,    37,    38,    37,    22,
      68,    23,    24,    26,    48,    49,    82,    82,    82,    82,
      82,    23,    24,    83,    23,    83,    82,    22,    68,    22,
      68,    37,    42,    41,    44,    41,    42,    37,    37,    37,
      37,    37,    37,    14,    15,    37,    80,    15,    37,    20,
      21,    37,    20,    21,    37,    22,    79,    47,    47,    24,
      26,    24,    26,    44,    44,    44,    44,    44,    39,    49,
      39,    44,    39,    39,    44,    47,    47,    44,    44,    82,
       4,    38,    22,     4,    22,    22,    68,    42,    41,    42,
      38,    22,    38,    22,    42,    39,    44,    82,    82,    82,
      82,    82,    24,    24,    43,    43,    82,    22,    68,    22,
      68,    22,    16,    42,    22,    41,    37,    40,    37,    82,
      22,    38,    62,    64,    82,    22,    81,    37,    81,    37,
      24,    22,    41,    45,    41,    45,    44,    44,    41,    49,
      82,    82,    45,    47,    47,    47,    47,    38,    23,    82,
      38,    22,    80,    37,    15,    37,    37,    39,    44,    39,
      42,    82,    82,    24,    44,    44,    38,    38,    41,    42,
      37,    22,    37,    24,    41,    45,    41,    45,    82,    82,
      37,    82,    45,    45,    37
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
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1349 "hare-idl.tab.c"
	break;
      case 4: /* "KW_PUBLISHABLE_STRUCT" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1358 "hare-idl.tab.c"
	break;
      case 5: /* "KW_TYPEDEF" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1367 "hare-idl.tab.c"
	break;
      case 6: /* "KW_ENUM" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1376 "hare-idl.tab.c"
	break;
      case 7: /* "KW_CLASS" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1385 "hare-idl.tab.c"
	break;
      case 8: /* "KW_MAPPING" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1394 "hare-idl.tab.c"
	break;
      case 9: /* "KW_ENCODING" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1403 "hare-idl.tab.c"
	break;
      case 10: /* "KW_NUMERIC" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1412 "hare-idl.tab.c"
	break;
      case 11: /* "KW_INT" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1421 "hare-idl.tab.c"
	break;
      case 12: /* "KW_FENCE" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1430 "hare-idl.tab.c"
	break;
      case 13: /* "KW_EXTEND" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1439 "hare-idl.tab.c"
	break;
      case 14: /* "KW_TO" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1448 "hare-idl.tab.c"
	break;
      case 15: /* "KW_DEFAULT" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1457 "hare-idl.tab.c"
	break;
      case 16: /* "KW_FILE" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1466 "hare-idl.tab.c"
	break;
      case 17: /* "KW_CLASS_UPP" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1475 "hare-idl.tab.c"
	break;
      case 18: /* "KW_DISCRIMINATED_UNION" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1484 "hare-idl.tab.c"
	break;
      case 19: /* "KW_DISCRIMINANT" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1493 "hare-idl.tab.c"
	break;
      case 20: /* "KW_WHEN_DISCRIMINANT_IN" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1502 "hare-idl.tab.c"
	break;
      case 21: /* "KW_WHEN_DISCRIMINANT_IS" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1511 "hare-idl.tab.c"
	break;
      case 22: /* "IDENTIFIER" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1520 "hare-idl.tab.c"
	break;
      case 23: /* "STRING_LITERAL" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1529 "hare-idl.tab.c"
	break;
      case 24: /* "INTEGER_LITERAL" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1538 "hare-idl.tab.c"
	break;
      case 25: /* "CHAR_LITERAL" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1547 "hare-idl.tab.c"
	break;
      case 26: /* "FLOAT_LITERAL" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1556 "hare-idl.tab.c"
	break;
      case 27: /* "KW_INTEGER" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1565 "hare-idl.tab.c"
	break;
      case 28: /* "KW_FIXED_POINT" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1574 "hare-idl.tab.c"
	break;
      case 29: /* "KW_FLOATING_POINT" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1583 "hare-idl.tab.c"
	break;
      case 30: /* "KW_CHARACTER" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1592 "hare-idl.tab.c"
	break;
      case 31: /* "KW_CHARACTER_STRING" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1601 "hare-idl.tab.c"
	break;
      case 32: /* "KW_BIT_STRING" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1610 "hare-idl.tab.c"
	break;
      case 33: /* "KW_SEQUENCE" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1619 "hare-idl.tab.c"
	break;
      case 34: /* "KW_DICTIONARY" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1628 "hare-idl.tab.c"
	break;
      case 35: /* "KW_PRINTABLE_ASCII_STRING" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1637 "hare-idl.tab.c"
	break;
      case 36: /* "KW_UNICODE_STRING" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1646 "hare-idl.tab.c"
	break;
      case 37: /* "';'" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1655 "hare-idl.tab.c"
	break;
      case 38: /* "'{'" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1664 "hare-idl.tab.c"
	break;
      case 39: /* "'}'" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1673 "hare-idl.tab.c"
	break;
      case 40: /* "'('" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1682 "hare-idl.tab.c"
	break;
      case 41: /* "')'" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1691 "hare-idl.tab.c"
	break;
      case 42: /* "'='" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1700 "hare-idl.tab.c"
	break;
      case 43: /* "'['" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1709 "hare-idl.tab.c"
	break;
      case 44: /* "','" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1718 "hare-idl.tab.c"
	break;
      case 45: /* "']'" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1727 "hare-idl.tab.c"
	break;
      case 46: /* "'<'" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1736 "hare-idl.tab.c"
	break;
      case 47: /* "'>'" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1745 "hare-idl.tab.c"
	break;
      case 48: /* "'+'" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1754 "hare-idl.tab.c"
	break;
      case 49: /* "'-'" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1763 "hare-idl.tab.c"
	break;
      case 51: /* "file" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1772 "hare-idl.tab.c"
	break;
      case 52: /* "line_directive" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1781 "hare-idl.tab.c"
	break;
      case 53: /* "typedef_decl" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1790 "hare-idl.tab.c"
	break;
      case 54: /* "publishable_struct_begin" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1799 "hare-idl.tab.c"
	break;
      case 55: /* "publishable_struct" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1808 "hare-idl.tab.c"
	break;
      case 56: /* "mapping_begin" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1817 "hare-idl.tab.c"
	break;
      case 57: /* "mapping" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1826 "hare-idl.tab.c"
	break;
      case 58: /* "ext_file_mapping_begin" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1835 "hare-idl.tab.c"
	break;
      case 59: /* "ext_file_mapping" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1844 "hare-idl.tab.c"
	break;
      case 60: /* "encoding_begin" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1853 "hare-idl.tab.c"
	break;
      case 61: /* "encoding" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1862 "hare-idl.tab.c"
	break;
      case 62: /* "data_element" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1871 "hare-idl.tab.c"
	break;
      case 63: /* "data_group_begin" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1880 "hare-idl.tab.c"
	break;
      case 64: /* "data_group" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1889 "hare-idl.tab.c"
	break;
      case 65: /* "discriminated_union_begin" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1898 "hare-idl.tab.c"
	break;
      case 66: /* "discriminated_union" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1907 "hare-idl.tab.c"
	break;
      case 67: /* "union_data_element" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1916 "hare-idl.tab.c"
	break;
      case 68: /* "data_type" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1925 "hare-idl.tab.c"
	break;
      case 69: /* "integer_type" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1934 "hare-idl.tab.c"
	break;
      case 70: /* "fixed_point_type" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1943 "hare-idl.tab.c"
	break;
      case 71: /* "floating_point_type" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1952 "hare-idl.tab.c"
	break;
      case 72: /* "character_type" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1961 "hare-idl.tab.c"
	break;
      case 73: /* "character_string_type" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1970 "hare-idl.tab.c"
	break;
      case 74: /* "bit_string_type" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1979 "hare-idl.tab.c"
	break;
      case 75: /* "sequence_type" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1988 "hare-idl.tab.c"
	break;
      case 76: /* "dictionary_type" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1997 "hare-idl.tab.c"
	break;
      case 77: /* "class_ref_type" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2006 "hare-idl.tab.c"
	break;
      case 78: /* "inline_enum_type" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2015 "hare-idl.tab.c"
	break;
      case 79: /* "enum_values" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2024 "hare-idl.tab.c"
	break;
      case 80: /* "arg_list" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2033 "hare-idl.tab.c"
	break;
      case 81: /* "id_list" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2042 "hare-idl.tab.c"
	break;
      case 82: /* "expr" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2051 "hare-idl.tab.c"
	break;
      case 83: /* "character_set" */

/* Line 1000 of yacc.c  */
#line 41 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 2060 "hare-idl.tab.c"
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
#line 50 "hare-idl.y"
    { (yyval) = 0; ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 51 "hare-idl.y"
    { (yyval) = 0; releaseYys2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 52 "hare-idl.y"
    { (yyval) = addTypedefToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 53 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 54 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 55 "hare-idl.y"
    { (yyval) = processExtFileMapping((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 56 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 57 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 61 "hare-idl.y"
    { (yyval) = 0; processLineDirective((yyvsp[(2) - (3)]), 0); releaseYys2((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 62 "hare-idl.y"
    { (yyval) = 0; processLineDirective((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 66 "hare-idl.y"
    { (yyval) = createTypedef((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 67 "hare-idl.y"
    { (yyval) = createTypedef((yyvsp[(1) - (4)]), createIdType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)])); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 71 "hare-idl.y"
    { (yyval) = createPublishableStruct((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 72 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]))); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 73 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute(createIdType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)]))); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 77 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 81 "hare-idl.y"
    { (yyval) = createMapping((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(6) - (7)])); releaseYys4((yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 82 "hare-idl.y"
    { (yyval) = 0; releaseYys2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 83 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])));  releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 84 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute(createIdType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)])));  releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 88 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 92 "hare-idl.y"
    { (yyval) = createExtFileMapping((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(7) - (8)])); releaseYys5((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 93 "hare-idl.y"
    { (yyval) = addClassMapping((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 97 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (4)]); releaseYys3((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 98 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 103 "hare-idl.y"
    { (yyval) = createEncoding((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(6) - (7)])); releaseYys4((yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 104 "hare-idl.y"
    { (yyval) = 0; releaseYys2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 105 "hare-idl.y"
    { (yyval) = addToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 106 "hare-idl.y"
    { (yyval) = addToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 107 "hare-idl.y"
    { (yyval) = addFenceToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 111 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 115 "hare-idl.y"
    { (yyval) = createAttribute((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 116 "hare-idl.y"
    { (yyval) = createEncodingAttribute((yyvsp[(1) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 117 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); releaseYys3((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 118 "hare-idl.y"
    { (yyval) = createAttribute(createIdType((yyvsp[(1) - (3)])), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 119 "hare-idl.y"
    { (yyval) = createEncodingAttribute(createIdType((yyvsp[(1) - (6)])), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)]));;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 120 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (5)]), createIdType((yyvsp[(4) - (5)]))); releaseYys3((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 121 "hare-idl.y"
    { (yyval) = createAttribute(createEncodingType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)])), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 122 "hare-idl.y"
    { (yyval) = createEncodingAttribute(createEncodingType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)])), (yyvsp[(5) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 123 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (8)]), createEncodingType((yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]))); releaseYys5((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 127 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, 0); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 128 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), 0); releaseYys3((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 129 "hare-idl.y"
    { (yyval) = addToEncodingGroup((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 130 "hare-idl.y"
    { (yyval) = addToEncodingGroup((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 134 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (2)]); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 135 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 136 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 137 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 138 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 142 "hare-idl.y"
    { (yyval) = createUnion((yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)])); releaseYys5((yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 143 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 147 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 151 "hare-idl.y"
    { (yyval) = createAttribute((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 152 "hare-idl.y"
    { (yyval) = createUnionAttribute((yyvsp[(1) - (7)]), (yyvsp[(2) - (7)]), (yyvsp[(5) - (7)])); releaseYys4((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 153 "hare-idl.y"
    { (yyval) = createUnionAttribute((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), addIdentifier(0, (yyvsp[(4) - (5)]))); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 154 "hare-idl.y"
    { (yyval) = createAttribute(createIdType((yyvsp[(1) - (3)])), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 155 "hare-idl.y"
    { (yyval) = createUnionAttribute(createIdType((yyvsp[(1) - (7)])), (yyvsp[(2) - (7)]), (yyvsp[(5) - (7)])); releaseYys4((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 156 "hare-idl.y"
    { (yyval) = createUnionAttribute(createIdType((yyvsp[(1) - (5)])), (yyvsp[(2) - (5)]), addIdentifier(0, (yyvsp[(4) - (5)]))); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 171 "hare-idl.y"
    { (yyval) = createPrintableAsciiStringType((yyvsp[(1) - (1)])); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 172 "hare-idl.y"
    { (yyval) = createUnicodeStringType((yyvsp[(1) - (1)])); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 176 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 177 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 178 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 179 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 183 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), true, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), true); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 184 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), false, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), true); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 185 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), true, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), false); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 186 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), false, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), false); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 190 "hare-idl.y"
    { (yyval) = createFloatingPointType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 194 "hare-idl.y"
    { (yyval) = createCharacterType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 195 "hare-idl.y"
    { (yyval) = createCharacterType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 199 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), 0, 0); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 200 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 201 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), 0, 0); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 202 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 206 "hare-idl.y"
    { (yyval) = createBitStringType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 210 "hare-idl.y"
    { (yyval) = createSequence((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 211 "hare-idl.y"
    { (yyval) = createSequence((yyvsp[(1) - (4)]), createIdType((yyvsp[(3) - (4)]))); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 212 "hare-idl.y"
    { (yyval) = createNamedSequence((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 213 "hare-idl.y"
    { (yyval) = createNamedSequence((yyvsp[(1) - (4)]), createIdType((yyvsp[(3) - (4)]))); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 217 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 218 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 219 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 220 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 224 "hare-idl.y"
    { (yyval) = createClassReference((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 228 "hare-idl.y"
    { (yyval) = createInlineEnum((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 232 "hare-idl.y"
    { (yyval) = addEnumValue(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 233 "hare-idl.y"
    { (yyval) = addEnumValue((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 237 "hare-idl.y"
    { (yyval) = addExpression(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 238 "hare-idl.y"
    { (yyval) = addExpression((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 242 "hare-idl.y"
    { (yyval) = addIdentifier(0, (yyvsp[(1) - (1)])); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 243 "hare-idl.y"
    { (yyval) = addIdentifier((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 247 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 248 "hare-idl.y"
    { (yyval) = (yyvsp[(2) - (2)]); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 249 "hare-idl.y"
    { (yyval) = makeMinusIntLit((yyvsp[(2) - (2)])); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 250 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 251 "hare-idl.y"
    { (yyval) = (yyvsp[(2) - (2)]); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 252 "hare-idl.y"
    { (yyval) = makeMinusFloatLit((yyvsp[(2) - (2)])); releaseYys((yyvsp[(1) - (2)])); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 253 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 257 "hare-idl.y"
    { (yyval) = addToCharSet(0, (yyvsp[(1) - (1)]), 0); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 258 "hare-idl.y"
    { (yyval) = addToCharSet(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 259 "hare-idl.y"
    { (yyval) = addToCharSet((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 0);  releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 260 "hare-idl.y"
    { (yyval) = addToCharSet((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;



/* Line 1455 of yacc.c  */
#line 3086 "hare-idl.tab.c"
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



