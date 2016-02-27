Hare-IDL Style Guide
====================

This is a style guide for Hare-IDL project. Many of the rules here are merely for consintency 
(a.k.a. "It just so happened that we want to do it this way"), so don't complain when something looks arbitrary -
it probably is.

I. C++ for IDL Compiler
-----------------------

### I.0 General

We're using very standard C++11.

### I.1 Naming conventions

Naming conventions examplegls:

1. class TheVeryBestClass //also applies to structs, unions, and typedefs
2. function prettyMuchUnnecessaryFunction(); //also apples to members
3. enum BACKGROUND_COLOR { RED, GREEN, BLUE }; //see below on constants
4. #define MY_STRING "abracadabra" //see below on #defines
5. #ifndef FILE_NAME_INCLUDED //"include guard"
6. **MUST NOT** use identifiers starting with an underscore OR containing adjacent double underscore (technically reserved for C++)
7. Classes and functions which are used ONLY for debugging purposes (such as "dumpSomething()") SHOULD start with Dbg*/dbg*() respectively
8. file names: file_name.h

### I.2 On #includes

1. **MUST NOT** have any duplicate declarations for the same entity. In particular, function declarations in .cpp files are **PROHIBITED** for non-static functions
2. Each include **MUST** have "include guard" consisting of #ifndef FILE_NAME_INCLUDED - #define FILE_NAME_INCLUDED
    - #pragma once SHOULD NOT be used as non-standard
3. ALL C++ standard includes SHOULD be within /src/idlc_include.h, and **MUST** be included as `<include_file_name.h>`
4. The very first #include file for ALL the .cpp files SHOULD be `#include "../idlc_include.h"` (with different number of '../' as necessary) 
5. Our own includes **MUST** be included via "include_file_name.h" (with a relative path if necessary(!))

### I.3 On Constants and #defines

1. integer constants SHOULD be declared as C++11's enum BACKGROUND_COLOR { RED, GREEN, BLUE } (and used as BACKGROUND_COLOR::RED etc.)
2. string constants MAY be declared via #define

### I.4 C++11 vs C++03 vs C

1. **MUST NOT** use C-style casts; use appropriate C++ *_cast<> instead
2. SHOULD use std containers
3. SHOULD NOT use pointers where possible, DO use references instead wherever applicable
4. SHOULD NOT use C-style typedef struct _X {} X; stuff. DO use C++-ush struct X {}; instead
5. SHOULD use C++11-style "range-based for loops" such as for(int i:v) {} where applicable
6. SHOULD use C++11 auto for iterators such as auto it = v.begin(); where applicable. This also SHOULD reduce the need for iterator typedefs
7. SHOULD NOT overuse C++11 auto for short-and-obvious types.
8. SHOULD use "f() = delete;" to prohibit calling functions (instead of C++03's declaring as private and not implementing)
9. namespace policy:
    - project-specific stuff belongs to global namespace
    - libraries which are shared among projects, belong to separate folder /src/hare/<library-name>, AND to hare::<library-name> namespace
    - if by any chance, libraries do need macros, they SHOULD be prefixed with HARE, for example: HAREASSERT()
10. **MUST** use `override` for all overridden functions
11. SHOULD use C++11 member initializers over constructors for 'member default' values 

### I.5 Misc

1. iterations over the vector SHOULD use  size_t as index variable type: for(size_t i=0; i < v.size(); ++i)
2. prefixed increment SHOULD be used in standalone statements: for(auto it=v.begin();;++it) is preferred over for(auto it=v.begin();;it++)
3. All text-formatted file/console output SHOULD be done via C++ Format library: https://github.com/cppformat/cppformat . This library is available as 'git submodule' within /3rdparty/cppformat/ .
4. All file/console I/O (except for-text-formatted output, see item I.5.3 right above) SHOULD be done via std::iostream
5. non-constant global data SHOULD NOT be used unless absolutely necessary
6. non-constant static data **MUST NOT** be used
7. const modifier SHOULD be used wherever applicable
8. On asserting: **MUST NOT** use assert(), **MUST** use HAREASSERT()/HAREASSERTM() instead
   - asserts are STRONGLY encouraged
9. There **MUST NOT** be garbage in the program. All variables of primitive types **MUST** be initialized, including member variables. See I.4.11 about the proper way of initializing member variables.
10. We ARE using a concept of "discriminated unions". However, at the moment we DON'T care much about memory usage (nor about potential for field misuses), so we're using the following simple form (NB: we MAY change this form in the future if it becomes necessary):

    //DISCRIMINATED UNION: SOMETYPE some_name

    enum SOMETYPE { <list of values> } some_name;

    string name;//used ONLY for SOMETYPE::X and SOMETYPE::Y

    int val;//used ONLY for SOMETYPE::X and SOMETYPE::Z
    
