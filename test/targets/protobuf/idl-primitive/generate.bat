
del output*.*

hare-idl --templatePath=../../../../src/targets/cpp/codegen/protobuf/ --template=main.txt --template=mapping.txt --template=encoding.txt --template=proto.txt --template=dbg_helpers.txt --inputIdl=test.idl

sed --in-place s/"\/\/include-here"/"#include \"output_declare.h\""/g output.cpp
sed --in-place s/"\/\/include-here"/"#include \"output_declare.h\""/g output.h
sed --in-place s/"\/\/include-here"/"#include <string>\nusing namespace std;"/g output_declare.h
del sed*
