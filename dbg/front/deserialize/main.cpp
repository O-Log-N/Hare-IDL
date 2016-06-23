// idl.cpp : Defines the entry point for the console application.
//

#include "idlc_include.h"

#include <iostream>

#include "front-back/idl_tree.h"
#include "front-back/idl_tree_serializer.h"
#include "../../front-back/debug.h"



int main(int argc, char *argv[])
{
    // don't try-catch, since this is debug only code, better to have an unhandled exception

	// deserialize tree
    const char* fileName = "idl_tree.h.idlbin";
    if (argc > 2) {
        fileName = argv[1];
    }

	Root root;
	uint8_t baseBuff[0x10000];
	FILE* in = fopen(fileName, "rb" );
	size_t sz = fread( baseBuff, 1, 0x10000, in );
	fclose( in );
	IStream i( baseBuff, sz );
	deserializeRoot( root, i );

    dbgDumpTree(stdout, &root, false);

    return 0;
}

