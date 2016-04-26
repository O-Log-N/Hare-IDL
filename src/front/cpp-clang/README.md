C++2HareIDL
===========

An stand-alone tool using llvm/clang to parse C++ source code to extract
mapping information and output it in a HareIDL parseable format.

How to build
------------

C++2HareIDL is built as llvm/clang, plus a patch file (over release_38 of llvm/clang).
It is recomended that you are familiar with building clang, intructions can be found at http://clang.llvm.org/get_started.html

To build on Windows, I needed to install Cmake, Ninja (optional but handy), and Visual Studio.
To build on Linux, from Ubuntu 15.10, install gcc, g++, cmake and ninja-build.
 
Basic steps:
 
  git clone --branch release_38 http://llvm.org/git/llvm.git
  cd llvm/tools
  git clone --branch release_38 http://llvm.org/git/clang.git
 
Now need to apply our patch from front/cpp-clang to clang:
 
  cd clang
  git apply ../../../Hare-IDL/src/front/cpp-clang/C++2HareIDL_release_38.patch
 
  cd ../../..
 
Create a build folder (for out-of-tree build):

  mkdir build
  cd build
 
  cmake -G Ninja ../llvm
  ninja
 
Or if you prefer tradicional Makefiles:
 
  cmake -G Makefiles ../llvm
  make
 
Or you can ask cmake to create Visual Studio solution and build from inside the GUI
 
  cmake -G "Visual Studio 14" ../llvm
 
 
Or use all of them, just create one folder for each build option.
 
 
After complete build, at `bin` folder, you will find C++2HareIDL.exe
 
Test
---- 
 
You can easily test C++2HareIDL by manually running on any file, just be sure to put double hyphen after command line options:
 
  C++2HareIDL -find-class=ClassName -find-class=OtherClass file_name.h --
 
If you have any issues with missing compiler command line options (like -std=c++11 usually neede on Linux because of GCC compatibility, or -fno-ms-compatibility on Windows when char16_t or char32_t errors) or missing define symbol or missing include folder, you can add any of them after the double hyphen:
 
  C++2HareIDL -find-class=ClassName file_name.h -- -std=c++11 -Ifolder -DUSE_SOME_DEFINE
 
 
Since currently  HareIDL will not be adding any of those options, you may need to add them to MAPPING directive at idl (back slash must be escaped):
 
  MAPPING(Lang="C++", Role="Client",
          ClangOptions="-fno-ms-compatibility -D_DEBUG -I..\\..\\..\\src") {
    FILE "sample-with-cpp.h" {
      CLASS Character;
    }
  };
 
 