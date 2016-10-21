
del output.*
del dbg_*.*
del idl_tree.h.idlbin

C++2HareIDL.exe -find-class=Limit -find-class=Location -find-class=CharacterRange -find-class=CharacterSet -find-class=Variant -find-class=DataType -find-class=EncodingSpecifics -find-class=EncodedOrMember -find-class=DataMember -find-class=EncodedMembers -find-class=Structure -find-class=Typedef -find-class=Root -serialize -o idl_tree.h.idlbin idl_tree.h -- -fno-ms-compatibility -I..\..\..\..\src -xc++

hare-idl --templatePath=../../../../src/targets/cpp/codegen/protobuf/ --template=main.txt --template=mapping.txt --template=encoding.txt --template=proto.txt --template=dbg_helpers.txt --inputBinary=idl_tree.h.idlbin

sed --in-place s/"\/\/include-here"/"#include \"idl_tree.h\""/g output.cpp
sed --in-place s/"\/\/include-here"/"#include \"idl_tree.h\""/g output.h
del sed*

protoc --cpp_out=. output.proto

