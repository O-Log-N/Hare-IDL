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

const int FILE_BUFFER_SIZE = 16000;

// symbols defined inside lex.yy.cpp without any header declaration
int yyparse();
extern int yydebug;
extern int yylineno;
//extern FILE *yyin;
//extern FILE *yyout;

struct yy_buffer_state; //forward
yy_buffer_state* yy_create_buffer(FILE* file, int size);
void yy_switch_to_buffer(yy_buffer_state* new_buffer);
//yy_buffer_state* yy_scan_buffer(char* buffer, unsigned int size);
yy_buffer_state* yy_scan_string(const char* yy_str);
//yy_buffer_state* yy_scan_bytes(const char* bytes, int len);
void yy_delete_buffer(yy_buffer_state*);


#endif // LEX_H_INCLUDED