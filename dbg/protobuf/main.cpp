
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <limits>

#include "protobuf/baselib.h"
#include "sample.h"
#include "output.pb.h"
#include "output.h"


//#include "front-back/idl_tree_serializer.h"

#include "dbg_helpers.h"

using namespace std;

/*
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

//unique_ptr<TestClass> createSample() {
//
//    unique_ptr<TestClass> root(new TestClass);
//
//    root->bigInt = INT64_MIN;
//    root->aFloat = 0;
//
//    return root;
//}
*/

BasicTypes makeBasicTypes()
{
    BasicTypes bt;

    bt.max_u32 = UINT32_MAX;
    bt.max_u64 = UINT64_MAX;

    bt.max_s32 = INT32_MIN;
    bt.max_s64 = INT64_MIN;

    bt.aFloat = 1.0;
    bt.aDouble = 2.0;

    bt.description = "Hello world!";

    // enum and bool map to unsigned var int

    //enum Values { Nothing = 0, First = 1, Second = 2 };

    bt.aValue = BasicTypes::Second;

    bt.flag = true;



    return bt;
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

  FakeBufferManager manager(4096);

  OProtobufStream o(manager);

  BasicTypes bt = makeBasicTypes();
  size_t sz = serializeBasicTypes(bt, o);

  BufferGroup buff = o.getBufferSet();

  IProtobufStream i(buff);

  BasicTypes deserialized;

  bool ok = deserializeBasicTypes(deserialized, i);
  assert(ok);

  assertEqualBasicTypes(bt, deserialized);

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}