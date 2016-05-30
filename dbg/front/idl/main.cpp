// idl.cpp : Defines the entry point for the console application.
//

#include "idlc_include.h"

#include <iostream>

#include "front-back/idl_tree.h"
#include "front/idl/parser.h"
#include "../../front-back/debug.h"


int main(int argc, char *argv[])
{
    // don't try-catch, since this is debug only code, better to have an unhandled exception

    string fileName = "sample2.idl";
    if (argc == 2)
        fileName = argv[1];

    Root* root = parseSourceFile(fileName, false);
    HAREASSERT(root);

    dbgDumpLeaks();
    dbgDumpTree(stdout, root, true);

    return 0;
}

