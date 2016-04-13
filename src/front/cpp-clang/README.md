C++2HareIDL
===========

An stand-alone tool using llvm/clang to parse C++ source code to extract
mapping information and output in a HareIDL parseable format.

How to build
------------

Follow indications to build llvm/clang http://clang.llvm.org/get_started.html but checkout `release_38` branch instead of `HEAD`.
After clang checkout and before build, apply `C++2HareIDL_release_38.patch`  to clang.
Binary file `C++2HareIDL` will be generated along the rest of the compiler.

