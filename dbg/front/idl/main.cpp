// idl.cpp : Defines the entry point for the console application.
//

#include "idlc_include.h"

#include <iostream>

#include "front-back/idl_tree.h"
#include "front-back/idl_tree_serializer.h"
#include "front/idl/parser.h"
#include "../../front-back/debug.h"

void serializeToFile(const char* fileName, Root& root) {

    FILE* out = fopen(fileName, "wb");
    assert(out);
    OStream o(out);

    serializeRoot(root, o);
    fclose(out);
}


int main(int argc, char *argv[])
{
    // don't try-catch, since this is debug only code, better to have an unhandled exception

    string fileName = "idl_tree.idl";
    if (argc == 2)
        fileName = argv[1];

    Root* root = parseSourceFile(fileName, false);
    HAREASSERT(root);

    dbgDumpLeaks();
    dbgDumpTree(stdout, root, false);

    string outFile = fileName + ".bin";
    serializeToFile(outFile.c_str(), *root);

    return 0;
}

