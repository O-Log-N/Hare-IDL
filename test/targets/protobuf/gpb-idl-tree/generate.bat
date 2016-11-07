
del output.*
del dbg_*.*
del idl_tree.h.data


C++2HareIDL.exe -find-class=Root -dependencies -serialize -o idl_tree.h.data ..\..\..\..\src\front-back\idl_tree.h -- -fno-ms-compatibility -I..\..\..\..\src -xc++

hare-idl --template=main_protobuf.txt --template=../../../../src/targets/cpp/codegen/protobuf/mapping.txt --template=../../../../src/targets/cpp/codegen/protobuf/encoding.txt --template=../../../../src/targets/cpp/codegen/protobuf/proto.txt --template=../../../../src/targets/cpp/codegen/protobuf/dbg_helpers.txt --inputBinary=idl_tree.h.data

protoc --cpp_out=. output.proto
