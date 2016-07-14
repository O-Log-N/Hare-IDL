
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <limits>

#include "front-back/idl_tree.h"
#include "front-back/idl_tree_serializer.h"
#include "output.pb.h"
#include "output.h"
#include "protobuf/baselib.h"
#include "dbg_assert_equal.h"

using namespace std;


void protobufReadAndReply(istream& is, ostream& os, const Root& our)
{
    pb::Root root;
    if (!root.ParseFromIstream(&is)) {
        cerr << "Failed to parse." << endl;
        throw std::runtime_error("Failed to parse.");
    }

    assertEqualRoot(our, root);

    if (!root.SerializeToOstream(&os)) {
        cerr << "Failed to write." << endl;
        throw std::runtime_error("Failed to write.");
    }
}

//unique_ptr<Character> deserialize(istream& is) {
//    unique_ptr<Character> root(new Character);
//
//    IStream i(is);
//    if(deserializeCharacter(*root, i))
//        return root;
//
//    return unique_ptr<Character>();
//}
//
//void serialize(ostream& os, Character& root) {
//
//    OStream o(os);
//    serializeCharacter(root, o);
//}

unique_ptr<Root> protobufDeserializeFromFile(const char* fileName) {
    unique_ptr<Root> root(new Root);
    uint8_t baseBuff[0x10000];
    FILE* in = fopen(fileName, "rb");
    size_t sz = fread(baseBuff, 1, 0x10000, in);
    fclose(in);
    IProtobufStream i(baseBuff, sz);
    bool ok = deserializeRoot(*root, i);

    return ok ? std::move(root) : nullptr;
}

void protobufSerializeToFile(const char* fileName, Root& root) {

    FILE* out = fopen(fileName, "wb");
    assert(out);
    OProtobufStream o(out);

    serializeRoot(root, o);
    fclose(out);
}

unique_ptr<Root> deserializeFile(const char* fileName) {
    unique_ptr<Root> root(new Root());
    uint8_t baseBuff[0x10000];
    FILE* in = fopen(fileName, "rb");
    size_t sz = fread(baseBuff, 1, 0x10000, in);
    fclose(in);
    IStream i(baseBuff, sz);
    bool ok = deserializeRoot(*root, i);

    return ok ? std::move(root) : nullptr;
}


void dumpStream(istream& is)
{
    while (is) {
        cout << setw(2) << hex << is.get() << " ";
    }
}

int main(int argc, char* argv[])
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  const char* sendFile = "character.send.bin";
  const char* recvFile = "character.recv.bin";

  unique_ptr<Root> toSend = deserializeFile("../../Hare-IDL/dbg/protobuf/idl_tree.h.idlbin");
//  unique_ptr<Root> toSend = deserializeFile("idl_tree.h.idlbin");

    protobufSerializeToFile(sendFile, *toSend);

    {
        fstream is(sendFile, ios::in | ios::binary);
        fstream os(recvFile, ios::out | ios::trunc | ios::binary);

        protobufReadAndReply(is, os, *toSend);
    }
  unique_ptr<Root> recv = protobufDeserializeFromFile(sendFile);

  assert(recv);
  assertEqualRoot(*toSend, *recv);

  google::protobuf::ShutdownProtobufLibrary();

  return 0;

}