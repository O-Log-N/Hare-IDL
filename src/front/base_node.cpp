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

#include "base_node.h"

#include <set>

#include "error.h"
#include "debug.h"


using namespace std;

const bool dbgEnableLeakDetector = true;
set<YyBase*> dbgLeakDetector;

YyBase::YyBase()
{
	if (dbgEnableLeakDetector)
		dbgLeakDetector.insert(this);
}

YyBase::~YyBase()
{
	if (dbgEnableLeakDetector)
		dbgLeakDetector.erase(this);
}

size_t Node::nodeIdNext = 0;

void dbgDumpLeaks(std::ostream& os)
{
	for (set<YyBase*>::const_iterator it = dbgLeakDetector.begin(); it != dbgLeakDetector.end(); ++it) {
		if (Node* n = dynamic_cast<Node*>(*it))
			dbgDumpNode(os, n);
		else {
			(*it)->location.write(os);
			os << endl;
		}
	}
}

