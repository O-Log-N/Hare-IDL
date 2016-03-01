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


%{
#include "parser_helper.h"
#include "hare-idl.tab.h"
#include <stdlib.h>

void jumpToState(int state)
{
	pushState(YYSTATE);
	BEGIN(state);
}

void backToPreviousState()
{
	BEGIN(popState());
}

int createToken(int token)
{
	yylval = createYyToken(yytext, yylineno, token);
	return token;
}

%}

%option yylineno
%option never-interactive
%s COMMENT SLCOMMENT

%%

<COMMENT>{
	"*/" { backToPreviousState(); }
	.|\n { /* ignore */ }
}

<SLCOMMENT>{
	\n { backToPreviousState(); }
	.  { /* ignore */ }
}

<INITIAL>{

	"/*" { jumpToState( COMMENT ) ; }
	"//" { jumpToState( SLCOMMENT ) ; }

	"PUBLISHABLE_STRUCT" { return createToken( KW_PUBLISHABLE_STRUCT ); }
	"enum" { return createToken( KW_ENUM ); }
	"class" { return createToken( KW_CLASS ); }

	"MAPPING" { return createToken( KW_MAPPING ); }
	"ENCODING" { return createToken( KW_ENCODING ); }
    "FENCE" { return createToken( KW_FENCE ); }
    "EXTEND" { return createToken( KW_EXTEND ); }
    "TO" { return createToken( KW_TO ); }
    "DEFAULT" { return createToken( KW_DEFAULT ); }


	"NUMERIC" { return createToken( KW_NUMERIC ); }
    "INT" { return createToken( KW_INT ); }
	"SEQUENCE" { return createToken( KW_SEQUENCE ); }

	[;<>,:=&\[\]\(\)\{\}\?\.] { yylval = 0; return yytext[0];}
	[&|!~/%\*\+\-] { return createToken( yytext[0] );}

	[_a-zA-Z][_0-9a-zA-Z]* { yylval = createIdentifier(yytext, yylineno); return IDENTIFIER; }

	0[0-9]+ { parserError("Octal integer literal not supported '%s'.", yytext, yylineno); }

	[+-]?[1-9][0-9]* { yylval = createIntegerLiteral(yytext, yylineno); return INTEGER_LITERAL; }
	0 { yylval = createZeroLiteral(yytext, yylineno); return INTEGER_LITERAL; }
	0x[a-fA-F0-9]+ { yylval = createHexIntegerLiteral(yytext, yylineno); return INTEGER_LITERAL; }

	[+-]?[0-9]*\.[0-9]+([eE][+-]?[0-9]+)? { yylval = createFloatLiteral(yytext, yylineno); return FLOAT_LITERAL; }
	[+-]?[0-9]+\.[0-9]*([eE][+-]?[0-9]+)? { yylval = createFloatLiteral(yytext, yylineno); return FLOAT_LITERAL; }
	[+-]?[0-9]+[eE][+-]?[0-9]+ { yylval = createFloatLiteral(yytext, yylineno); return FLOAT_LITERAL; }


	\"([^\\"]|\\.)*\" { yylval = createStringLiteral(yytext, yylineno); return STRING_LITERAL; }
	\'([^\\']|\\.)*\' { yylval = createCharLiteral(yytext, yylineno); return CHAR_LITERAL; }

	[\ \t\r\n]+ { /* ignore */ }

	. { parserErrorUnknownChar(*yytext, yylineno); }
}
