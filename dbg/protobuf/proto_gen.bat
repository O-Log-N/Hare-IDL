
hare-idl --templatePath=../../src/targets/cpp/codegen/protobuf/ --template=main.txt --template=mapping.txt --template=encoding.txt --template=proto.txt --template=dbg_helpers.txt --inputBinary=sample.h.idlbin

sed --in-place s/"\/\/include-here"/"#include \"sample.h\""/g output.h
sed --in-place s/"\/\/include-here"/"#include \"sample.h\""/g output.cpp
del sed*

protoc --cpp_out=. output.proto


