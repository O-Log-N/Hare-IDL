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





class DbgDumpWalker : public NodeWalker
{
public:
	std::ostream& os;
	size_t offset;
	vector<string> offsets;

	DbgDumpWalker(std::ostream& os) : os(os), offset(0)
	{
		offsets.push_back("");
	}

	void walkNode(Node* node) {
		HAREASSERT(node);
		os << getOffset(offset);
		dbgDumpNode(os, node);
		++offset;
		node->walk(*this);
		--offset;
	}

	void dbgDumpNullChild() {
	}

	virtual void walkChildNode(Node* parent, Node* child) {
		if (child)
			walkNode(child);
		else {
			os << getOffset(offset) << "!NULL!" << endl;
		}
	}
private:
	void addOffset()
	{
		string r;
		for (size_t i = 0; i < offsets.size() - 1; ++i) {
			r.append("| ");
		}
		r.append("|-");
		offsets.push_back(r);
	}

	const string& getOffset(size_t offset)
	{
		while (offsets.size() <= offset)
			addOffset();

		return offsets[offset];
	}
};


void dbgDumpNode(std::ostream& os, Node* node)
{
	HAREASSERT(node);
	os << "#" << node->nodeId;
	os << " ";
	node->location.write(os);
	const char* name = typeid(*node).name();
	if (strncmp(name, "class ", 6) == 0)
		name += 6;
	if (strncmp(name, "hare::", 6) == 0)
		name += 6;

	os << " '" << name << "'";
	node->dbgDump(os);

	os << endl;
}

void dbgDumpDown(std::ostream& os, Node* node)
{
	HAREASSERT(node);
	DbgDumpWalker walker(os);
	walker.walkNode(node);
}


//	const long ticks = 0;
DbgTimer::DbgTimer(const string& message) : begin(clock()), message(message)
{
}

DbgTimer::~DbgTimer()
{
	long ticks = clock() - begin;
	cout << "'" << message << "' completed in " << ticks << " ticks" << endl;
}
