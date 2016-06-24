
dbgBack.exe
echo #include "sample.h" >temp.txt

copy temp.txt + output.cpp ..\..\..\protobuf\test\Test26
copy output.h ..\..\..\protobuf\test\Test26
copy output.proto ..\..\..\protobuf\test\Test26

del temp.txt
del output.cpp
del output.h
del output.proto
