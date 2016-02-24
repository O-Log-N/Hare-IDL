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

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED "include guard"

#include <string>
#include <cstdio>
#include <cassert>
#include "../../front-back/idl_tree.h"

#define HAREASSERT(condition) assert(condition)

class Node;

const bool NotImplementedYet = false;

struct Location {
	const char* fileName;
	int lineNumber;
	Location() : fileName(0), lineNumber(0) {}

	bool isValid() const {
		return fileName != 0;
	}
	std::string toString() const;
	std::ostream& write(std::ostream& os) const;
};

struct YyBase {
	Location location;
	YyBase();
	virtual ~YyBase() = 0;
	YyBase(const YyBase&) = delete;
	YyBase& operator=(const YyBase&) = delete;
};

void dbgDumpLeaks(std::ostream& os);

/* TODO */
void reportError(const Location& loc, const std::string& msg);
void reportError(const Location& loc, const std::string& msg, const std::string& arg);
void plainError(const std::string& msg, const std::string& arg);


void parseCode(const char* code, const std::string& pseudoFileName, bool debugDump, Root* result);
void parseSourceFile(const std::string& fileName, bool debugDump, Root* result);

#endif // PARSER_H_INCLUDED
