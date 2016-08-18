
C++2HareIDL.exe -find-class=Limit -find-class=Location -find-class=CharacterRange -find-class=CharacterSet -find-class=Variant -find-class=DataType -find-class=EncodingSpecifics -find-class=EncodedOrMember -find-class=DataMember -find-class=EncodedMembers -find-class=Structure -find-class=Typedef -find-class=Root -serialize -o idl_tree.h.idlbin idl_tree.h -- -fno-ms-compatibility -I.. -xc++

hare-idl --templatePath=../targets/sample/template9/ --template=main.txt --template=mapping.txt --template=encoding.txt --inputBinary=idl_tree.h.idlbin

rem sed --in-place s/"\/\/include-here"/"#include \"idl_tree.h\""/g output.h
rem sed --in-place s/"\/\/include-here"/"#include \"idl_tree_serializer.h\""/g output.cpp
del sed*
