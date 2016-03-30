// idl.cpp : Defines the entry point for the console application.
//

#include "idlc_include.h"

#include "front-back/idl_tree.h"
#include "front/idl/parser.h"
#include "debug.h"

int main()
{
    // don't try-catch, since this is debug only code, better to have an unhandled exception

    Root* root = parseSourceFile("..\\..\\..\\Hare-IDL\\dbg\\front\\idl\\sample.idl", false);
    HAREASSERT(root);

    dbgDumpLeaks();
    dbgDumpTree(stdout, root, false);

    return 0;
}

