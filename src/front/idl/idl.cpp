// idl.cpp : Defines the entry point for the console application.
//

#include "../../idlc_include.h"

#include "../../front-back/idl_tree.h"
#include "parser.h"
#include "debug.h"

int main()
{
	try {
		Root* root = parseSourceFile("sample.idl", false);

		dbgDumpLeaks();
		if (root)
			dbgDumpTree(stdout, root);

		return 0;
	}
	catch (...) {
		return 1;
	}
}

