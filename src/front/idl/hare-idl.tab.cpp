
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
#line 39 "hare-idl.y"

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
     KW_ENUM = 259,
     KW_CLASS = 260,
     KW_MAPPING = 261,
     KW_ENCODING = 262,
     KW_NUMERIC = 263,
     KW_INT = 264,
     KW_EXTEND = 265,
     KW_TO = 266,
     KW_DEFAULT = 267,
     KW_FENCE = 268,
     KW_DISCRIMINATED_UNION = 269,
     KW_WHEN_DISCRIMINANT_IN = 270,
     KW_WHEN_DISCRIMINANT_IS = 271,
     KW_DISCRIMINANT = 272,
     IDENTIFIER = 273,
     STRING_LITERAL = 274,
     INTEGER_LITERAL = 275,
     CHAR_LITERAL = 276,
     FLOAT_LITERAL = 277,
     KW_INTEGER = 278,
     KW_FIXED_POINT = 279,
     KW_FLOATING_POINT = 280,
     KW_CHARACTER = 281,
     KW_CHARACTER_STRING = 282,
     KW_BIT_STRING = 283,
     KW_SEQUENCE = 284,
     KW_DICTIONARY = 285,
     KW_PRINTABLE_ASCII_STRING = 286,
     KW_UNICODE_STRING = 287
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
#line 153 "hare-idl.tab.c"

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
#define YYLAST   557

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNRULES -- Number of states.  */
#define YYNSTATES  273

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      36,    37,     2,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    34,
      42,    38,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,    35,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    16,    20,    25,
      30,    34,    42,    47,    52,    56,    64,    67,    70,    73,
      77,    81,    88,    94,    98,   105,   111,   118,   128,   137,
     140,   146,   149,   152,   155,   158,   164,   167,   173,   182,
     185,   189,   193,   201,   207,   211,   219,   225,   227,   229,
     231,   233,   235,   237,   239,   241,   243,   245,   247,   249,
     251,   253,   260,   267,   274,   281,   288,   295,   302,   309,
     316,   323,   330,   337,   346,   355,   364,   373,   380,   385,
     390,   400,   407,   412,   417,   422,   427,   434,   441,   448,
     455,   458,   464,   468,   474,   478,   484,   486,   490,   492,
     494
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    -1,    45,    47,    -1,    45,    49,    -1,
      45,    51,    -1,    45,    56,    -1,     3,    18,    33,    -1,
      46,    58,    18,    34,    -1,    46,    18,    18,    34,    -1,
      46,    35,    34,    -1,     6,    36,    72,    37,     3,    18,
      33,    -1,    48,    58,    18,    34,    -1,    48,    18,    18,
      34,    -1,    48,    35,    34,    -1,     7,    36,    72,    37,
       3,    18,    33,    -1,    50,    52,    -1,    50,    54,    -1,
      50,    13,    -1,    50,    35,    34,    -1,    58,    18,    34,
      -1,    58,    18,    12,    38,    74,    34,    -1,    10,    18,
      11,    58,    34,    -1,    18,    18,    34,    -1,    18,    18,
      12,    38,    74,    34,    -1,    10,    18,    11,    18,    34,
      -1,    18,    36,    72,    37,    18,    34,    -1,    18,    36,
      72,    37,    18,    12,    38,    74,    34,    -1,    10,    18,
      11,    18,    36,    72,    37,    34,    -1,    18,    33,    -1,
      18,    36,    72,    37,    33,    -1,    53,    52,    -1,    53,
      54,    -1,    53,    35,    -1,    18,    52,    -1,    18,    36,
      72,    37,    52,    -1,    18,    54,    -1,    18,    36,    72,
      37,    54,    -1,    14,    36,    17,    38,    18,    37,    18,
      33,    -1,    55,    57,    -1,    55,    35,    34,    -1,    58,
      18,    34,    -1,    58,    18,    15,    33,    73,    35,    34,
      -1,    58,    18,    16,    18,    34,    -1,    18,    18,    34,
      -1,    18,    18,    15,    33,    73,    35,    34,    -1,    18,
      18,    16,    18,    34,    -1,    59,    -1,    60,    -1,    61,
      -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,    66,
      -1,    67,    -1,    68,    -1,    70,    -1,    69,    -1,    31,
      -1,    32,    -1,     8,    39,    74,    40,    74,    41,    -1,
       8,    36,    74,    40,    74,    41,    -1,     8,    39,    74,
      40,    74,    37,    -1,     8,    36,    74,    40,    74,    37,
      -1,     9,    39,    74,    40,    74,    41,    -1,     9,    36,
      74,    40,    74,    41,    -1,     9,    39,    74,    40,    74,
      37,    -1,     9,    36,    74,    40,    74,    37,    -1,    23,
      39,    74,    40,    74,    41,    -1,    23,    36,    74,    40,
      74,    41,    -1,    23,    39,    74,    40,    74,    37,    -1,
      23,    36,    74,    40,    74,    37,    -1,    24,    39,    74,
      40,    74,    40,    74,    41,    -1,    24,    36,    74,    40,
      74,    40,    74,    41,    -1,    24,    39,    74,    40,    74,
      40,    74,    37,    -1,    24,    36,    74,    40,    74,    40,
      74,    37,    -1,    25,    36,    74,    40,    74,    37,    -1,
      26,    33,    74,    35,    -1,    27,    33,    74,    35,    -1,
      27,    33,    74,    35,    39,    74,    40,    74,    41,    -1,
      28,    39,    74,    40,    74,    41,    -1,    29,    42,    58,
      43,    -1,    29,    42,    18,    43,    -1,    18,    42,    58,
      43,    -1,    18,    42,    18,    43,    -1,    30,    42,    58,
      40,    58,    43,    -1,    30,    42,    18,    40,    58,    43,
      -1,    30,    42,    58,    40,    18,    43,    -1,    30,    42,
      18,    40,    18,    43,    -1,     5,    18,    -1,     4,    18,
      33,    71,    35,    -1,    18,    38,    20,    -1,    71,    40,
      18,    38,    20,    -1,    18,    38,    74,    -1,    72,    40,
      18,    38,    74,    -1,    18,    -1,    73,    40,    18,    -1,
      20,    -1,    22,    -1,    19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    46,    46,    47,    48,    49,    50,    54,    55,    56,
      60,    64,    65,    66,    70,    74,    75,    76,    77,    81,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    97,
      98,    99,   100,   104,   105,   106,   107,   108,   112,   113,
     117,   121,   122,   123,   124,   125,   126,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   151,   152,   153,   154,   158,   159,   160,   161,   165,
     166,   167,   168,   172,   173,   174,   175,   179,   183,   187,
     188,   192,   196,   197,   198,   199,   203,   204,   205,   206,
     210,   214,   218,   219,   223,   224,   228,   229,   233,   234,
     235
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_PUBLISHABLE_STRUCT", "KW_ENUM",
  "KW_CLASS", "KW_MAPPING", "KW_ENCODING", "KW_NUMERIC", "KW_INT",
  "KW_EXTEND", "KW_TO", "KW_DEFAULT", "KW_FENCE", "KW_DISCRIMINATED_UNION",
  "KW_WHEN_DISCRIMINANT_IN", "KW_WHEN_DISCRIMINANT_IS", "KW_DISCRIMINANT",
  "IDENTIFIER", "STRING_LITERAL", "INTEGER_LITERAL", "CHAR_LITERAL",
  "FLOAT_LITERAL", "KW_INTEGER", "KW_FIXED_POINT", "KW_FLOATING_POINT",
  "KW_CHARACTER", "KW_CHARACTER_STRING", "KW_BIT_STRING", "KW_SEQUENCE",
  "KW_DICTIONARY", "KW_PRINTABLE_ASCII_STRING", "KW_UNICODE_STRING", "'{'",
  "';'", "'}'", "'('", "')'", "'='", "'['", "','", "']'", "'<'", "'>'",
  "$accept", "file", "publishable_struct_begin", "publishable_struct",
  "mapping_begin", "mapping", "encoding_begin", "encoding", "data_element",
  "data_group_begin", "data_group", "discriminated_union_begin",
  "discriminated_union", "union_data_element", "data_type", "numeric_type",
  "int_type", "integer_type", "fixed_point_type", "floating_point_type",
  "character_type", "character_string_type", "bit_string_type",
  "sequence_type", "dictionary_type", "class_ref_type", "inline_enum_type",
  "enum_values", "arg_list", "id_list", "expr", 0
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
     285,   286,   287,   123,    59,   125,    40,    41,    61,    91,
      44,    93,    60,    62
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    45,    45,    45,    46,    46,    46,
      47,    48,    48,    48,    49,    50,    50,    50,    50,    51,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    53,
      53,    53,    53,    54,    54,    54,    54,    54,    55,    55,
      56,    57,    57,    57,    57,    57,    57,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    59,    59,    59,    59,    60,    60,    60,    60,    61,
      61,    61,    61,    62,    62,    62,    62,    63,    64,    65,
      65,    66,    67,    67,    67,    67,    68,    68,    68,    68,
      69,    70,    71,    71,    72,    72,    73,    73,    74,    74,
      74
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     3,     4,     4,
       3,     7,     4,     4,     3,     7,     2,     2,     2,     3,
       3,     6,     5,     3,     6,     5,     6,     9,     8,     2,
       5,     2,     2,     2,     2,     5,     2,     5,     8,     2,
       3,     3,     7,     5,     3,     7,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     8,     8,     8,     8,     6,     4,     4,
       9,     6,     4,     4,     4,     4,     6,     6,     6,     6,
       2,     5,     3,     5,     3,     5,     1,     3,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     3,     0,
       4,     0,     5,     0,     6,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    59,    60,     0,     0,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    58,    57,     0,     0,
       0,     0,    18,     0,     0,    16,     0,    17,     0,     0,
       0,    39,     0,     7,     0,     0,     0,     0,     0,    90,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    10,     0,     0,    14,
       0,     0,     0,    29,     0,    34,    36,    19,    33,    31,
      32,     0,     0,    40,     0,     0,     0,     0,     0,     0,
       0,   100,    98,    99,     0,     0,     0,     0,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,    13,    12,     0,     0,    23,     0,
       0,    20,     0,     0,    44,     0,     0,    41,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
      84,     0,     0,     0,     0,     0,    78,    79,     0,    83,
      82,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    91,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    25,     0,    22,     0,     0,    30,
      35,    37,     0,    96,     0,    46,     0,    43,    11,    95,
      15,     0,    92,     0,    64,    62,    63,    61,    68,    66,
      67,    65,    72,    70,    71,    69,     0,     0,    77,     0,
      81,    89,    87,    88,    86,     0,    24,     0,    26,    21,
       0,     0,     0,    38,     0,     0,     0,     0,     0,     0,
      45,    97,    42,    93,    76,    74,    75,    73,     0,    28,
       0,    80,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     7,     8,     9,    10,    11,    12,    95,    56,
      96,    13,    14,    61,    58,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,   154,    65,   214,
     114
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -72
static const yytype_int16 yypact[] =
{
     -72,    19,   -72,     5,    39,    47,    75,   263,   -72,   292,
     -72,   205,   -72,   321,   -72,     4,    35,    35,    65,   101,
     122,    85,   110,    -4,   112,   114,   108,   135,   137,   132,
     118,   130,   -72,   -72,   139,   138,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,    -3,   140,
     157,   158,   -72,   175,   143,   -72,   234,   -72,   163,     0,
     148,   -72,   169,   -72,   151,   115,   117,   152,   159,   -72,
     123,   123,   123,   123,   162,   380,   123,   123,   123,   123,
     123,   123,   123,   123,   409,   438,   -72,   178,   182,   -72,
     185,   186,    36,   -72,    35,   -72,   -72,   -72,   -72,   -72,
     -72,     9,     1,   -72,    13,   123,   217,   203,   219,   206,
     207,   -72,   -72,   -72,   187,   201,   208,   209,   -72,    46,
     183,   210,   211,   213,   214,   215,   212,   221,   230,    60,
     202,    34,   233,   -72,   -72,   -72,   467,   236,   -72,   121,
     237,   -72,   243,   228,   -72,   244,   260,   -72,   -72,   261,
     242,   264,   246,   247,    15,   123,   123,   123,   123,   -72,
     -72,   123,   123,   123,   123,   123,   -72,   245,   123,   -72,
     -72,   496,   525,    37,   265,   123,   350,   123,   284,   269,
     284,   270,   272,   123,   273,   289,   288,   -72,   291,   -17,
     -10,    40,    58,    59,    64,   271,   274,   275,   123,   287,
      83,   290,   120,   293,   -72,    35,   -72,   279,   105,   -72,
     -72,   -72,   297,   -72,    16,   -72,    17,   -72,   -72,   -72,
     -72,   299,   -72,   296,   -72,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   -72,   -72,   123,   123,   -72,   295,
     -72,   -72,   -72,   -72,   -72,   127,   -72,   300,   -72,   -72,
     303,   322,   307,   -72,   323,    79,    81,   123,   308,   123,
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   316,   -72,
     327,   -72,   -72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,    -7,   -72,
       2,   -72,   -72,   -72,    23,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -14,   184,
     -71
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     115,   116,   117,    66,    55,   121,   122,   123,   124,   125,
     126,   127,   128,    57,    74,    88,   142,   143,   102,     2,
     224,   140,     3,    15,   225,     4,     5,   226,   145,   146,
      35,   227,    50,     6,   148,   144,    62,    63,    75,    75,
      19,    20,    75,   141,    21,    22,    51,   147,   137,    99,
     187,   250,   252,    64,    92,   188,   251,   251,   100,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    93,
     138,   204,    94,   205,   171,    16,    75,   228,    75,    75,
     139,   229,    67,    17,   189,   190,   191,   192,    75,   159,
     193,   194,   195,   196,   197,   230,   232,   199,   120,   231,
     233,   234,    75,   169,   207,   235,   212,   130,   132,    19,
      20,    18,   219,    21,    22,    51,   264,   247,   266,    68,
     265,    70,   267,    92,    71,    75,   241,   239,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    93,   248,
      69,    94,   111,   112,    80,   113,    72,    75,    76,    73,
      78,    77,   106,    79,   108,   107,    87,   107,   176,   174,
      84,   107,    75,   243,   258,   255,   256,   107,    81,   210,
      82,    83,    85,    86,    89,    90,    91,    97,   211,    19,
      20,   101,   103,    21,    22,    51,   268,   104,   270,   105,
     109,   245,   110,    92,   201,   203,   118,   136,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    93,    19,
      20,    94,   133,    21,    22,    51,   134,    75,    52,   135,
     149,   150,   151,    53,   152,   153,   160,   155,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    19,    20,
      54,   156,    21,    22,    51,   170,   179,   166,   157,   158,
     161,   162,    53,   163,   164,   165,   167,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    19,    20,    98,
     168,    21,    22,   172,   175,   177,   178,   180,   181,   182,
     183,    23,   184,   185,   198,   186,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    19,    20,    34,   206,
      21,    22,   213,   215,   217,   218,   220,   221,   222,   223,
      48,   236,   238,   246,   237,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    19,    20,    49,   240,    21,
      22,   249,   253,   242,   254,   257,   244,   260,   259,    59,
     261,   262,   269,   263,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    19,    20,    60,   271,    21,    22,
      51,   272,     0,     0,   216,     0,     0,     0,   208,     0,
       0,     0,     0,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,   209,    19,    20,     0,     0,    21,    22,
       0,     0,     0,     0,     0,     0,     0,     0,   119,     0,
       0,     0,     0,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    19,    20,     0,     0,    21,    22,     0,
       0,     0,     0,     0,     0,     0,     0,   129,     0,     0,
       0,     0,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    19,    20,     0,     0,    21,    22,     0,     0,
       0,     0,     0,     0,     0,     0,   131,     0,     0,     0,
       0,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    19,    20,     0,     0,    21,    22,     0,     0,     0,
       0,     0,     0,     0,     0,   173,     0,     0,     0,     0,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      19,    20,     0,     0,    21,    22,     0,     0,     0,     0,
       0,     0,     0,     0,   200,     0,     0,     0,     0,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    19,
      20,     0,     0,    21,    22,     0,     0,     0,     0,     0,
       0,     0,     0,   202,     0,     0,     0,     0,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33
};

static const yytype_int16 yycheck[] =
{
      71,    72,    73,    17,    11,    76,    77,    78,    79,    80,
      81,    82,    83,    11,    18,    18,    15,    16,    18,     0,
      37,    12,     3,    18,    41,     6,     7,    37,    15,    16,
       7,    41,     9,    14,   105,    34,    13,    33,    42,    42,
       4,     5,    42,    34,     8,     9,    10,    34,    12,    56,
      35,    35,    35,    18,    18,    40,    40,    40,    56,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    34,    36,    36,    40,    36,    42,    37,    42,    42,
      94,    41,    17,    36,   155,   156,   157,   158,    42,    43,
     161,   162,   163,   164,   165,    37,    37,   168,    75,    41,
      41,    37,    42,    43,   175,    41,   177,    84,    85,     4,
       5,    36,   183,     8,     9,    10,    37,    12,    37,    18,
      41,    36,    41,    18,    39,    42,    43,   198,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      18,    36,    19,    20,    36,    22,    36,    42,    36,    39,
      36,    39,    37,    39,    37,    40,    18,    40,    37,   136,
      42,    40,    42,    43,    37,   236,   237,    40,    33,   176,
      33,    39,    42,    34,    34,    18,    18,    34,   176,     4,
       5,    18,    34,     8,     9,    10,   257,    18,   259,    38,
      38,   205,    33,    18,   171,   172,    34,    11,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     4,
       5,    36,    34,     8,     9,    10,    34,    42,    13,    34,
       3,    18,     3,    18,    18,    18,    43,    40,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     4,     5,
      35,    40,     8,     9,    10,    43,    18,    35,    40,    40,
      40,    40,    18,    40,    40,    40,    35,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     4,     5,    35,
      40,     8,     9,    40,    38,    38,    33,    33,    18,    18,
      38,    18,    18,    37,    39,    38,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     4,     5,    35,    34,
       8,     9,    18,    34,    34,    33,    33,    18,    20,    18,
      18,    40,    37,    34,    40,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     4,     5,    35,    41,     8,
       9,    34,    33,    43,    38,    40,    43,    34,    38,    18,
      18,    34,    34,    20,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     4,     5,    35,    41,     8,     9,
      10,    34,    -1,    -1,   180,    -1,    -1,    -1,    18,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,     4,     5,    -1,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,     4,     5,    -1,    -1,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,
      -1,    -1,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,     4,     5,    -1,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     4,     5,    -1,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       4,     5,    -1,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,     4,
       5,    -1,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    45,     0,     3,     6,     7,    14,    46,    47,    48,
      49,    50,    51,    55,    56,    18,    36,    36,    36,     4,
       5,     8,     9,    18,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    35,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    18,    35,
      58,    10,    13,    18,    35,    52,    53,    54,    58,    18,
      35,    57,    58,    33,    18,    72,    72,    17,    18,    18,
      36,    39,    36,    39,    18,    42,    36,    39,    36,    39,
      36,    33,    33,    39,    42,    42,    34,    18,    18,    34,
      18,    18,    18,    33,    36,    52,    54,    34,    35,    52,
      54,    18,    18,    34,    18,    38,    37,    40,    37,    38,
      33,    19,    20,    22,    74,    74,    74,    74,    34,    18,
      58,    74,    74,    74,    74,    74,    74,    74,    74,    18,
      58,    18,    58,    34,    34,    34,    11,    12,    34,    72,
      12,    34,    15,    16,    34,    15,    16,    34,    74,     3,
      18,     3,    18,    18,    71,    40,    40,    40,    40,    43,
      43,    40,    40,    40,    40,    40,    35,    35,    40,    43,
      43,    40,    40,    18,    58,    38,    37,    38,    33,    18,
      33,    18,    18,    38,    18,    37,    38,    35,    40,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    39,    74,
      18,    58,    18,    58,    34,    36,    34,    74,    18,    33,
      52,    54,    74,    18,    73,    34,    73,    34,    33,    74,
      33,    18,    20,    18,    37,    41,    37,    41,    37,    41,
      37,    41,    37,    41,    37,    41,    40,    40,    37,    74,
      41,    43,    43,    43,    43,    72,    34,    12,    34,    34,
      35,    40,    35,    33,    38,    74,    74,    40,    37,    38,
      34,    18,    34,    20,    37,    41,    37,    41,    74,    34,
      74,    41,    34
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
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1342 "hare-idl.tab.c"
	break;
      case 4: /* "KW_ENUM" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1351 "hare-idl.tab.c"
	break;
      case 5: /* "KW_CLASS" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1360 "hare-idl.tab.c"
	break;
      case 6: /* "KW_MAPPING" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1369 "hare-idl.tab.c"
	break;
      case 7: /* "KW_ENCODING" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1378 "hare-idl.tab.c"
	break;
      case 8: /* "KW_NUMERIC" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1387 "hare-idl.tab.c"
	break;
      case 9: /* "KW_INT" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1396 "hare-idl.tab.c"
	break;
      case 10: /* "KW_EXTEND" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1405 "hare-idl.tab.c"
	break;
      case 11: /* "KW_TO" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1414 "hare-idl.tab.c"
	break;
      case 12: /* "KW_DEFAULT" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1423 "hare-idl.tab.c"
	break;
      case 13: /* "KW_FENCE" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1432 "hare-idl.tab.c"
	break;
      case 14: /* "KW_DISCRIMINATED_UNION" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1441 "hare-idl.tab.c"
	break;
      case 15: /* "KW_WHEN_DISCRIMINANT_IN" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1450 "hare-idl.tab.c"
	break;
      case 16: /* "KW_WHEN_DISCRIMINANT_IS" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1459 "hare-idl.tab.c"
	break;
      case 17: /* "KW_DISCRIMINANT" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1468 "hare-idl.tab.c"
	break;
      case 18: /* "IDENTIFIER" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1477 "hare-idl.tab.c"
	break;
      case 19: /* "STRING_LITERAL" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1486 "hare-idl.tab.c"
	break;
      case 20: /* "INTEGER_LITERAL" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1495 "hare-idl.tab.c"
	break;
      case 21: /* "CHAR_LITERAL" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1504 "hare-idl.tab.c"
	break;
      case 22: /* "FLOAT_LITERAL" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1513 "hare-idl.tab.c"
	break;
      case 23: /* "KW_INTEGER" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1522 "hare-idl.tab.c"
	break;
      case 24: /* "KW_FIXED_POINT" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1531 "hare-idl.tab.c"
	break;
      case 25: /* "KW_FLOATING_POINT" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1540 "hare-idl.tab.c"
	break;
      case 26: /* "KW_CHARACTER" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1549 "hare-idl.tab.c"
	break;
      case 27: /* "KW_CHARACTER_STRING" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1558 "hare-idl.tab.c"
	break;
      case 28: /* "KW_BIT_STRING" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1567 "hare-idl.tab.c"
	break;
      case 29: /* "KW_SEQUENCE" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1576 "hare-idl.tab.c"
	break;
      case 30: /* "KW_DICTIONARY" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1585 "hare-idl.tab.c"
	break;
      case 31: /* "KW_PRINTABLE_ASCII_STRING" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1594 "hare-idl.tab.c"
	break;
      case 32: /* "KW_UNICODE_STRING" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1603 "hare-idl.tab.c"
	break;
      case 33: /* "'{'" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1612 "hare-idl.tab.c"
	break;
      case 34: /* "';'" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1621 "hare-idl.tab.c"
	break;
      case 35: /* "'}'" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1630 "hare-idl.tab.c"
	break;
      case 36: /* "'('" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1639 "hare-idl.tab.c"
	break;
      case 37: /* "')'" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1648 "hare-idl.tab.c"
	break;
      case 38: /* "'='" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1657 "hare-idl.tab.c"
	break;
      case 39: /* "'['" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1666 "hare-idl.tab.c"
	break;
      case 40: /* "','" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1675 "hare-idl.tab.c"
	break;
      case 41: /* "']'" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1684 "hare-idl.tab.c"
	break;
      case 42: /* "'<'" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1693 "hare-idl.tab.c"
	break;
      case 43: /* "'>'" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1702 "hare-idl.tab.c"
	break;
      case 45: /* "file" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1711 "hare-idl.tab.c"
	break;
      case 46: /* "publishable_struct_begin" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1720 "hare-idl.tab.c"
	break;
      case 47: /* "publishable_struct" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1729 "hare-idl.tab.c"
	break;
      case 48: /* "mapping_begin" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1738 "hare-idl.tab.c"
	break;
      case 49: /* "mapping" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1747 "hare-idl.tab.c"
	break;
      case 50: /* "encoding_begin" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1756 "hare-idl.tab.c"
	break;
      case 51: /* "encoding" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1765 "hare-idl.tab.c"
	break;
      case 52: /* "data_element" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1774 "hare-idl.tab.c"
	break;
      case 53: /* "data_group_begin" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1783 "hare-idl.tab.c"
	break;
      case 54: /* "data_group" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1792 "hare-idl.tab.c"
	break;
      case 55: /* "discriminated_union_begin" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1801 "hare-idl.tab.c"
	break;
      case 56: /* "discriminated_union" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1810 "hare-idl.tab.c"
	break;
      case 57: /* "union_data_element" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1819 "hare-idl.tab.c"
	break;
      case 58: /* "data_type" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1828 "hare-idl.tab.c"
	break;
      case 59: /* "numeric_type" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1837 "hare-idl.tab.c"
	break;
      case 60: /* "int_type" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1846 "hare-idl.tab.c"
	break;
      case 61: /* "integer_type" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1855 "hare-idl.tab.c"
	break;
      case 62: /* "fixed_point_type" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1864 "hare-idl.tab.c"
	break;
      case 63: /* "floating_point_type" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1873 "hare-idl.tab.c"
	break;
      case 64: /* "character_type" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1882 "hare-idl.tab.c"
	break;
      case 65: /* "character_string_type" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1891 "hare-idl.tab.c"
	break;
      case 66: /* "bit_string_type" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1900 "hare-idl.tab.c"
	break;
      case 67: /* "sequence_type" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1909 "hare-idl.tab.c"
	break;
      case 68: /* "dictionary_type" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1918 "hare-idl.tab.c"
	break;
      case 69: /* "class_ref_type" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1927 "hare-idl.tab.c"
	break;
      case 70: /* "inline_enum_type" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1936 "hare-idl.tab.c"
	break;
      case 71: /* "enum_values" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1945 "hare-idl.tab.c"
	break;
      case 72: /* "arg_list" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1954 "hare-idl.tab.c"
	break;
      case 73: /* "id_list" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1963 "hare-idl.tab.c"
	break;
      case 74: /* "expr" */

/* Line 1000 of yacc.c  */
#line 37 "hare-idl.y"
	{ releaseYys((*yyvaluep)); };

/* Line 1000 of yacc.c  */
#line 1972 "hare-idl.tab.c"
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
#line 46 "hare-idl.y"
    { (yyval) = 0; ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 47 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 48 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 49 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 50 "hare-idl.y"
    { (yyval) = addToFile((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 54 "hare-idl.y"
    { (yyval) = createPublishableStruct((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 55 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]))); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 56 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute(createIdType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)]))); releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 60 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 64 "hare-idl.y"
    { (yyval) = createMapping((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(6) - (7)])); releaseYys4((yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 65 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])));  releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 66 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (4)]), createAttribute(createIdType((yyvsp[(2) - (4)])), (yyvsp[(3) - (4)])));  releaseYys((yyvsp[(4) - (4)])); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 70 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 74 "hare-idl.y"
    { (yyval) = createEncoding((yyvsp[(1) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(6) - (7)])); releaseYys4((yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 75 "hare-idl.y"
    { (yyval) = addToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 76 "hare-idl.y"
    { (yyval) = addToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 77 "hare-idl.y"
    { (yyval) = addFenceToEncoding((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 81 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 85 "hare-idl.y"
    { (yyval) = createAttribute((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 86 "hare-idl.y"
    { (yyval) = createEncodingAttribute((yyvsp[(1) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 87 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); releaseYys3((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 88 "hare-idl.y"
    { (yyval) = createAttribute(createIdType((yyvsp[(1) - (3)])), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 89 "hare-idl.y"
    { (yyval) = createEncodingAttribute(createIdType((yyvsp[(1) - (6)])), (yyvsp[(2) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)]));;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 90 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (5)]), createIdType((yyvsp[(4) - (5)]))); releaseYys3((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 91 "hare-idl.y"
    { (yyval) = createAttribute(createEncodingType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)])), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 92 "hare-idl.y"
    { (yyval) = createEncodingAttribute(createEncodingType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)])), (yyvsp[(5) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 93 "hare-idl.y"
    { (yyval) = createExtendAttribute((yyvsp[(2) - (8)]), createEncodingType((yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]))); releaseYys5((yyvsp[(1) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 97 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, 0); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 98 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), 0); releaseYys3((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 99 "hare-idl.y"
    { (yyval) = addToEncodingGroup((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 100 "hare-idl.y"
    { (yyval) = addToEncodingGroup((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 104 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (2)]); releaseYys((yyvsp[(2) - (2)])); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 105 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 106 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 107 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 108 "hare-idl.y"
    { (yyval) = createEncodingGroup((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 112 "hare-idl.y"
    { (yyval) = createUnion((yyvsp[(1) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)])); releaseYys5((yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 113 "hare-idl.y"
    { (yyval) = addToStruct((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 117 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (3)]); releaseYys2((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 121 "hare-idl.y"
    { (yyval) = createAttribute((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 122 "hare-idl.y"
    { (yyval) = createUnionAttribute((yyvsp[(1) - (7)]), (yyvsp[(2) - (7)]), (yyvsp[(5) - (7)])); releaseYys4((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 123 "hare-idl.y"
    { (yyval) = createUnionAttribute((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), addIdentifier(0, (yyvsp[(4) - (5)]))); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 124 "hare-idl.y"
    { (yyval) = createAttribute(createIdType((yyvsp[(1) - (3)])), (yyvsp[(2) - (3)])); releaseYys((yyvsp[(3) - (3)])); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 125 "hare-idl.y"
    { (yyval) = createUnionAttribute(createIdType((yyvsp[(1) - (7)])), (yyvsp[(2) - (7)]), (yyvsp[(5) - (7)])); releaseYys4((yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 126 "hare-idl.y"
    { (yyval) = createUnionAttribute(createIdType((yyvsp[(1) - (5)])), (yyvsp[(2) - (5)]), addIdentifier(0, (yyvsp[(4) - (5)]))); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 143 "hare-idl.y"
    { (yyval) = createPrintableAsciiStringType((yyvsp[(1) - (1)])); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 144 "hare-idl.y"
    { (yyval) = createUnicodeStringType((yyvsp[(1) - (1)])); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 151 "hare-idl.y"
    { (yyval) = createNumeric((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 152 "hare-idl.y"
    { (yyval) = createNumeric((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 153 "hare-idl.y"
    { (yyval) = createNumeric((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 154 "hare-idl.y"
    { (yyval) = createNumeric((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 158 "hare-idl.y"
    { (yyval) = createInt((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 159 "hare-idl.y"
    { (yyval) = createInt((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 160 "hare-idl.y"
    { (yyval) = createInt((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 161 "hare-idl.y"
    { (yyval) = createInt((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 165 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 166 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), true); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 167 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), true, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 168 "hare-idl.y"
    { (yyval) = createIntegerType((yyvsp[(1) - (6)]), false, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), false); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 172 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), true, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), true); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 173 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), false, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), true); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 174 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), true, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), false); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 175 "hare-idl.y"
    { (yyval) = createFixedPointType((yyvsp[(1) - (8)]), false, (yyvsp[(3) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), false); releaseYys4((yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(8) - (8)])); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 179 "hare-idl.y"
    { (yyval) = createFloatingPointType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 183 "hare-idl.y"
    { (yyval) = createCharacterType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 187 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), 0, 0); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 188 "hare-idl.y"
    { (yyval) = createCharacterStringType((yyvsp[(1) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)])); releaseYys5((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 192 "hare-idl.y"
    { (yyval) = createBitStringType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 196 "hare-idl.y"
    { (yyval) = createSequence(0, (yyvsp[(3) - (4)])); releaseYys3((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 197 "hare-idl.y"
    { (yyval) = createSequence(0, createIdType((yyvsp[(3) - (4)]))); releaseYys3((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 198 "hare-idl.y"
    { (yyval) = createSequence((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 199 "hare-idl.y"
    { (yyval) = createSequence((yyvsp[(1) - (4)]), createIdType((yyvsp[(3) - (4)]))); releaseYys2((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 203 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 204 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), (yyvsp[(5) - (6)])); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 205 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 206 "hare-idl.y"
    { (yyval) = createDictionaryType((yyvsp[(1) - (6)]), createIdType((yyvsp[(3) - (6)])), createIdType((yyvsp[(5) - (6)]))); releaseYys3((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 210 "hare-idl.y"
    { (yyval) = createClassReference((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 214 "hare-idl.y"
    { (yyval) = createInlineEnum((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); releaseYys2((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 218 "hare-idl.y"
    { (yyval) = addEnumValue(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 219 "hare-idl.y"
    { (yyval) = addEnumValue((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 223 "hare-idl.y"
    { (yyval) = addExpression(0, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 224 "hare-idl.y"
    { (yyval) = addExpression((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); releaseYys2((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 228 "hare-idl.y"
    { (yyval) = addIdentifier(0, (yyvsp[(1) - (1)])); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 229 "hare-idl.y"
    { (yyval) = addIdentifier((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); releaseYys((yyvsp[(2) - (3)])); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 233 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 234 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 235 "hare-idl.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2886 "hare-idl.tab.c"
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



