C++2HareIDL
===========

An stand-alone tool using llvm/clang to parse C++ source code to extract
mapping information and output it in a HareIDL parseable format.

How to build
------------

`C++2HareIDL` is built an `llvm/clang` tool, plus a fork with changes over `release_38` of clang.

It is recomended that you are familiar with building clang, intructions can be found at http://clang.llvm.org/get_started.html

To build on Windows, I needed to install Cmake, Ninja (optional but handy), and Visual Studio.
To build on Linux, from Ubuntu 15.10, install gcc, g++, cmake and ninja-build.
 
Need to ckeck out `llvm` at branch `release_38`, and our fork of `clang` at branch `hare_38`.
`llvm` must be on the same folder as `Hare-IDL`, if this is not the case `llvm/tools/clang/tools/C++2HareIDL/CMakeLists.txt` must be updated.

```
git clone --branch develop https://github.com/O-Log-N/Hare-IDL.git
git clone --branch release_38 https://github.com/llvm-mirror/llvm.git
cd llvm/tools
git clone --branch hare_38 https://github.com/O-Log-N/clang.git
```
 
Create a build folder (for out-of-tree build):

```
cd ../..
mkdir build
cd build
```

And run cmake:

```
cmake -G Ninja ../llvm
ninja C++2HareIDL
```
 
Or if you prefer tradicional Makefiles:
 
```
cmake -G Makefiles ../llvm
make C++2HareIDL
```
 
Or you can ask cmake to create Visual Studio solution and build from inside the GUI
 
```
cmake -G "Visual Studio 14" ../llvm
```
 
Or use all of them, just create one folder for each build option.
 
 
After complete build, at `bin` folder, you will find C++2HareIDL.exe
 
Test
---- 
 
You can easily test C++2HareIDL by manually running on any file, just be sure to put double hyphen after command line options:
 
```
C++2HareIDL -find-class=ClassName -find-class=OtherClass file_name.h --
```
 
If you have any issues with missing compiler command line options (like -std=c++11 usually neede on Linux because of GCC compatibility, or -fno-ms-compatibility on Windows when char16_t or char32_t errors) or missing define symbol or missing include folder, you can add any of them after the double hyphen:
 
```
C++2HareIDL -find-class=ClassName file_name.h -- -std=c++11 -Ifolder -DUSE_SOME_DEFINE
```
 
 
Since currently  HareIDL will not be adding any of those options, you may need to add them to MAPPING directive at idl (back slash must be escaped):
 
```
  MAPPING(Lang="C++", Role="Client",
          ClangOptions="-fno-ms-compatibility -D_DEBUG -I..\\..\\..\\src") {
    FILE "sample-with-cpp.h" {
      CLASS Character;
    }
  };
```
 
 