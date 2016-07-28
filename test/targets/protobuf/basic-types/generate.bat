del *.protobuf.bin
del test.exe

C++2HareIDL.exe -find-class=TestUnsigned -find-class=TestSigned -find-class=TestFixed -find-class=TestString -find-class=TestMisc -serialize -o test.h.idlbin test.h -- -fno-ms-compatibility -I..\..\..\..\src -xc++

hare-idl --templatePath=../../../../src/targets/cpp/codegen/protobuf/ --template=main.txt --template=mapping.txt --template=encoding.txt --template=proto.txt --template=dbg_assert_equal.txt --inputBinary=test.h.idlbin

sed --in-place s/"\/\/include-here"/"#include \"test.h\""/g output.cpp
sed --in-place s/"\/\/include-here"/"#include \"test.h\""/g output.h
del sed*

cl /EHsc /I../../../../src /I../../../../src/targets/cpp/include main.cpp output.cpp ../../../../src/targets/cpp/libsrc/protobuf/baselib.cpp /link /out:test.exe
del *.obj

test.exe
