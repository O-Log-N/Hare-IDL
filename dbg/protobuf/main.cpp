
#include "sample.h"
#include "output.pb.h"
#include "output.h"

#include <iostream>
#include <fstream>

using namespace std;



void protobufReadAndReply(const char* inFileName, const char* outFileName)
{
    pb::Character character;
    fstream input(inFileName, ios::in | ios::binary);
    if (!input) {
        cout << inFileName << ": File not found." << endl;
        throw std::runtime_error(string(inFileName) + ": File not found.");
    } else if (!character.ParseFromIstream(&input)) {
        cerr << "Failed to parse." << endl;
        throw std::runtime_error("Failed to parse.");
    }


    fstream output(outFileName, ios::out | ios::trunc | ios::binary);
    if (!character.SerializeToOstream(&output)) {
        cerr << "Failed to write." << endl;
        throw std::runtime_error("Failed to write.");
    }
}

unique_ptr<Character> deserializeFromFile(const char* fileName) {
    unique_ptr<Character> root(new Character);
    uint8_t baseBuff[0x10000];
    FILE* in = fopen(fileName, "rb");
    size_t sz = fread(baseBuff, 1, 0x10000, in);
    fclose(in);
    IStream i(baseBuff, sz);
    deserializeCharacter(*root, i);

    return root;
}

void serializeToFile(const char* fileName, Character& root) {

    FILE* out = fopen(fileName, "wb");
    assert(out);
    OStream o(out);

    serializeCharacter(root, o);
    fclose(out);
}

unique_ptr<Character> createSample() {

    unique_ptr<Character> character(new Character);

    character->character_id = 15;
    character->x = 10.0;
    character->y = 10.0;
    character->z = 1.0;
    character->angle = 45;
    character->anim = Character::Standing;

    return character;
}



int main(int argc, char* argv[])
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  const char* sendFile = "sample.send.bin";
  const char* recvFile = "sample.recv.bin";

  unique_ptr<Character> toSend = createSample();

  serializeToFile(sendFile, *toSend);

  protobufReadAndReply(sendFile, recvFile);

  unique_ptr<Character> recv = deserializeFromFile(recvFile);


  google::protobuf::ShutdownProtobufLibrary();

  return 0;

}