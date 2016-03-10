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

#ifndef TEMPLATE_LINE_TOKENS_H
#define TEMPLATE_LINE_TOKENS_H

#include "../idlc_include.h"
#include "template_line_tokenizer.h"

using namespace std;

struct KeyWordProps
{
	TemplateLine::LINE_TYPE id;
	bool expressionRequired;
};

KeyWordProps parseMainKeyword( const string& line, size_t& contentStart );
ATTRIBUTE parseParam( const string& line, size_t& contentStart );
PLACEHOLDER parsePlaceholder( const string& line, size_t& contentStart );

string mainKeywordToString( TemplateLine::LINE_TYPE kw );
string attributeNameToString( ATTRIBUTE id );
string placeholderToString( PLACEHOLDER id );
string nodeTypesToString( NODE_TYPE id );

#endif // TEMPLATE_LINE_TOKENS_H
