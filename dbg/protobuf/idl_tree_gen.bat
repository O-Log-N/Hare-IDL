
hare-idl --templatePath=../../src/targets/cpp/codegen/protobuf/ --template=main.txt --template=mapping.txt --template=encoding.txt --template=proto.txt --template=dbg_assert_equal.txt --template=dbg_print.txt --inputBinary=..\..\src\front-back\idl_tree.h.idlbin

sed --in-place s/"\/\/include-here"/"#include \"front-back\/idl_tree.h\""/g output.h
sed --in-place s/"\/\/include-here"/"#include \"front-back\/idl_tree.h\""/g output.cpp
del sed*

protoc --cpp_out=. output.proto


