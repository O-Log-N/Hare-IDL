
dbgBack.exe
protoc --cpp_out=. output.proto
sed --in-place s/"\/\/include-here"/"#include \"front-back\/idl_tree.h\""/g output.cpp
sed --in-place s/"\/\/include-here"/"#include \"front-back\/idl_tree.h\""/g output.h

del sed*


