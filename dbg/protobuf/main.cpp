
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "sample.h"
#include "output.pb.h"
#include "output.h"
#include "protobuf/baselib.h"

using namespace std;

bool areEqual(const Character& left, const pb::Character& right)
{
    return
        left.max_u8 == right.max_u8() &&
        left.max_u16 == right.max_u16() &&
        left.max_u32 == right.max_u32() &&
        //left.idU64 == right.idU64 &&
        left.max_s8 == right.max_s8() &&
        left.max_s16 == right.max_s16() &&
        left.max_s32 == right.max_s32() &&

        left.min_s8 == right.min_s8() &&
        left.min_s16 == right.min_s16() &&
        left.min_s32 == right.min_s32() &&

        left.x == right.x() &&
        left.y == right.y() &&
        left.z == right.z() &&
        left.angle == right.angle() &&
        left.anim == right.anim() &&
        left.flag == right.flag() &&
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

    character->max_u8 = numeric_limits<uint8_t>::max();
    character->max_u16 = numeric_limits<uint16_t>::max();
    character->max_u32 = numeric_limits<uint32_t>::max();
    //character->idU64 = numeric_limits<uint64_t>::max();

    character->min_s8 = numeric_limits<int8_t>::min();
    character->min_s16 = numeric_limits<int16_t>::min();
    character->min_s32 = numeric_limits<int32_t>::min();

    character->max_s8 = numeric_limits<int8_t>::max();
    character->max_s16 = numeric_limits<int16_t>::max();
    character->max_s32 = numeric_limits<int32_t>::max();
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
        left.max_u8 == right.max_u8 &&
        left.max_u16 == right.max_u16 &&
        left.max_u32 == right.max_u32 &&

        left.min_s8 == right.min_s8 &&
        left.min_s16 == right.min_s16 &&
        left.min_s32 == right.min_s32 &&

        left.max_s8 == right.max_s8 &&
        left.max_s16 == right.max_s16 &&
        left.max_s32 == right.max_s32 &&

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