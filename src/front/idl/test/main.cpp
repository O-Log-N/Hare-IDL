// idl.cpp : Defines the entry point for the console application.
//

#include "../../../idlc_include.h"

#include "../../../front-back/idl_tree.h"
#include "../parser.h"
#include "debug.h"

int main()
{
    try {
        Root* root = parseSourceFile("test/sample.idl", true);

        dbgDumpLeaks();
        if (root)
            dbgDumpTree(stdout, root, false);

        return 0;
    }
    catch (...) {
        return 1;
    }
}

