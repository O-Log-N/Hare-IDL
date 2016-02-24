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

#include <iostream>

#include "idl_node.h"
#include "literal_node.h"
#include "debug.h"
#include "parser.h"

using namespace std;

int main()
{

	RootNode* root = new RootNode();

	FileNode* file2 = parseSourceFile("../idl/sample.idl", true, false);
	if (file2)
		root->files.push_back(file2);



	dbgDumpDown(std::cout, root);

	return 0;
}

