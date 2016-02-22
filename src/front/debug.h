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

#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED "include guard"

#include <ostream>


class Node;

void dbgDumpNode(std::ostream& os, Node* node);
void dbgDumpDown(std::ostream& os, Node* node);

class DbgTimer
{
	long begin;
	std::string message;
public:
	DbgTimer(const std::string& message);
	~DbgTimer();
};

#endif // DEBUG_H_INCLUDED
