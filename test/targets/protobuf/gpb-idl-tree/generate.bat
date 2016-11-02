
del output.*
del dbg_*.*
del idl_tree.h.idlbin

C++2HareIDL.exe -find-class=Limit -find-class=Location -find-class=CharacterRange -find-class=CharacterSet -find-class=Variant -find-class=DataType -find-class=EncodingSpecifics -find-class=EncodedOrMember -find-class=DataMember -find-class=EncodedMembers -find-class=Structure -find-class=Typedef -find-class=Root -serialize -o idl_tree.h.idlbin ..\..\..\..\src\front-back\idl_tree.h -- -fno-ms-compatibility -I..\..\..\..\src -xc++

hare-idl --template=main_protobuf.txt --template=../../../../src/targets/cpp/codegen/protobuf/mapping.txt --template=../../../../src/targets/cpp/codegen/protobuf/encoding.txt --template=../../../../src/targets/cpp/codegen/protobuf/proto.txt --template=../../../../src/targets/cpp/codegen/protobuf/dbg_helpers.txt --inputBinary=idl_tree.h.idlbin

protoc --cpp_out=. output.proto

