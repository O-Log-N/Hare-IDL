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

#ifndef LEX_H_INCLUDED
#define LEX_H_INCLUDED "include guard"

#include "../../idlc_include.h"

// symbols defined inside lex.yy.cpp without any header declaration
int yyparse();
extern int yydebug;
extern int yylineno;
extern FILE *yyin;
extern FILE *yyout;


#endif // LEX_H_INCLUDED