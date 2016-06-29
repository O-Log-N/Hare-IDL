
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "sample.h"
#include "output.pb.h"
#include "output.h"

using namespace std;

bool areEqual(const Character& left, const pb::Character& right)
{
    return
        left.idU8 == right.idu8() &&
        left.idU16 == right.idu16() &&
        left.idU32 == right.idu32() &&
        //left.idU64 == right.idU64 &&
        //left.idS8 == right.idS8 &&
        //left.idS16 == right.idS16 &&
        //left.idS32 == right.idS32 &&
        //left.idS64 == right.idS64 &&
        left.x == right.x() &&
        left.y == right.y() &&
        left.z == right.z() &&
        left.angle == right.angle() &&
        left.anim == right.anim() &&
        left.flag == (right.flag() != 0) &&
        left.desc == right.desc();
}

void protobufReadAndReply(istream& is, ostream& os, const Character& our)
{
    pb::Character character;
    if (!character.ParseFromIstream(&is)) {
        cerr << "Failed to parse." << endl;
        throw std::runtime_error("Failed to parse.");
    }

    assert(areEqual(our, character));

    if (!character.SerializeToOstream(&os)) {
        cerr << "Failed to write." << endl;
        throw std::runtime_error("Failed to write.");
    }
}

unique_ptr<Character> deserialize(istream& is) {
    unique_ptr<Character> root(new Character);

    IStream i(is);
    if(deserializeCharacter(*root, i))
        return root;

    return unique_ptr<Character>();
}

void serialize(ostream& os, Character& root) {

    OStream o(os);
    serializeCharacter(root, o);
}

unique_ptr<Character> createSample() {

    unique_ptr<Character> character(new Character);

    character->idU8 = numeric_limits<uint8_t>::max();
    character->idU16 = numeric_limits<uint16_t>::max();
    character->idU32 = numeric_limits<uint32_t>::max();
    //character->idU64 = numeric_limits<uint64_t>::max();

    //character->idS8 = numeric_limits<int8_t>::min();
    //character->idS16 = numeric_limits<int16_t>::min();
    //character->idS32 = numeric_limits<int32_t>::min();
    //character->idS64 = numeric_limits<int64_t>::min();

    character->x = 10.0;
    character->y = 10.0;
    character->z = 1.0;
    character->angle = 45;
    character->anim = Character::Walking;
    character->flag = true;
    character->desc = "My description here";

    return character;
}

bool areEqual(const Character& left, const Character& right)
{
    return
        left.idU8 == right.idU8 &&
        left.idU16 == right.idU16 &&
        left.idU32 == right.idU32 &&
        //left.idU64 == right.idU64 &&
        //left.idS8 == right.idS8 &&
        //left.idS16 == right.idS16 &&
        //left.idS32 == right.idS32 &&
        //left.idS64 == right.idS64 &&
        left.x == right.x &&
        left.y == right.y &&
        left.z == right.z &&
        left.angle == right.angle &&
        left.anim == right.anim &&
        left.flag == right.flag &&
        left.desc == right.desc;
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

  unique_ptr<Character> toSend = createSample();

    stringstream ss1;
    stringstream ss2;

    serialize(ss1, *toSend);

   // dumpStream(ss1);

    protobufReadAndReply(ss1, ss2, *toSend);

  unique_ptr<Character> recv = deserialize(ss2);

  assert(recv && areEqual(*toSend, *recv));

  google::protobuf::ShutdownProtobufLibrary();

  return 0;

}