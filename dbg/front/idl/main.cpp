// idl.cpp : Defines the entry point for the console application.
//

#include "idlc_include.h"

#include "front-back/idl_tree.h"
#include "front/idl/parser.h"
#include "debug.h"

int main()
{
//    try {
        Root* root = parseSourceFile("..\\..\\..\\Hare-IDL\\dbg\\front\\idl\\sample.idl", false);
        HAREASSERT(root);

        dbgDumpLeaks();
        dbgDumpTree(stdout, root, false);

        return 0;
    //}
    //catch (const std::exception& e) {

    //    fmt::print(stderr, "Exception!");
    //    fmt::print(stderr, e.what());
    //    return 1;
    //}
    //catch (...) {
    //    fmt::print(stderr, "Unknown exception!");
    //    return 1;
    //}
}

