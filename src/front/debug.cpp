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

#include "debug.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>

#include "common.h"
#include "base_node.h"
#include "error.h"


using namespace std;

vector<string> offsets;

string createOffset(size_t offset)
{
	string r;
	if (offset != 0) {
		for (size_t i = 0; i < offset; ++i) {
			if (i != 0)
				r.push_back(' ');

			r.push_back('|');
		}
		r.push_back('-');
	}
	return r;
}

const string& getOffset(size_t offset)
{
	while (offsets.size() <= offset)
		offsets.push_back(createOffset(offset));

	return offsets[offset];
}


class DumpWalker : public NodeWalker
{
public:
	std::ostream& os;
	size_t offset;
	DumpWalker(std::ostream& os) : os(os), offset(0) {}

	void walkNode(Node* node) {
		ASSERT(node);
		os << getOffset(offset);
		dumpNode(os, node);
		++offset;
		node->walk(*this);
		node->dumpSymbols(getOffset(offset), os);
		--offset;
	}

	void dumpNullChild() {
	}

	virtual void walkChildNode(Node* parent, Node* child) {
		if (child)
			walkNode(child);
		else {
			os << getOffset(offset) << "!NULL!" << endl;
		}
	}
};


void dumpNode(std::ostream& os, Node* node)
{
	ASSERT(node);
	os << "#" << node->nodeId;
	os << " ";
	node->location.write(os);
	const char* name = typeid(*node).name();
	if (strncmp(name, "class ", 6) == 0)
		name += 6;
	if (strncmp(name, "hare::", 6) == 0)
		name += 6;

	os << " '" << name << "'";
	node->dump(os);

	os << endl;
}

void dumpDown(std::ostream& os, Node* node)
{
	ASSERT(node);
	DumpWalker walker(os);
	walker.walkNode(node);
}
void dumpUp(std::ostream& os, Node* node)
{
	size_t offset = 0;
	Node* current = node;
	while (current) {
		for (size_t i = 0; i < offset; ++i)
			os << "|<";

		os << "Node #" << node->nodeId;
		os << " '" << typeid(*node).name() << "'";
		if (node->location.isValid()) {
			os << " ";
			node->location.write(os);
		}

		node->dump(os);
		++offset;
		current = node->parent;
	}
}

//	const long ticks = 0;
DebugTimer::DebugTimer(const string& message) : begin(clock()), message(message)
{
}

DebugTimer::~DebugTimer()
{
	long ticks = clock() - begin;
	cout << "'" << message << "' completed in " << ticks << " ticks" << endl;
}
