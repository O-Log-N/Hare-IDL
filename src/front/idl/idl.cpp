// idl.cpp : Defines the entry point for the console application.
//

#include "../../idlc_include.h"

#include "../../front-back/idl_tree.h"
#include "parser.h"
#include "debug.h"

int main()
{
	Root root;
	parseSourceFile("sample.idl", false, &root);

	dbgDumpLeaks();
	dbgDumpTree(stdout, &root);

    return 0;
}

