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

#include "idlc_include.h"

#include "front-back/idl_tree.h"
#include "front/cpp-clang/cpp-parser.h"
#include "../../front-back/debug.h"

int main()
{
    // don't try-catch, since this is debug only code, better to have an unhandled exception

    Root* root =  parseCppSourceFile("..\\..\\..\\..\\Hare-IDL\\dbg\\front\\cpp-clang\\sample.h",
        {"myHareSampleItem", "myHareSampleCharacter"});
    HAREASSERT(root);

    dbgDumpTree(stdout, root, false);

    return 0;
}

