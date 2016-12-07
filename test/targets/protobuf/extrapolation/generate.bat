
del output.*
del test.h.idlbin

C++2HareIDL.exe -find-class=TestExtrapolation -serialize -o test.h.idlbin test.h -- -fno-ms-compatibility -I..\..\..\..\src -xc++ -std=c++14 -D__is_assignable=__is_trivially_assignable

hare-idl --template=../../../../src/targets/cpp/codegen/protobuf/main.txt --template=../../../../src/targets/cpp/codegen/protobuf/mapping.txt --template=encoding_extrapolation.txt --template=../../../../src/targets/cpp/codegen/protobuf/proto.txt --template=../../../../src/targets/cpp/codegen/protobuf/dbg_helpers.txt --inputBinary=test.h.idlbin

sed --in-place s/"\/\/include-here"/"#include \"test.h\""/g output.cpp
sed --in-place s/"\/\/include-here"/"#include \"test.h\""/g output.h
del sed*
