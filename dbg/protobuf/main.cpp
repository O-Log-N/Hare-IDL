
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <limits>

#include "sample.h"
#include "output.pb.h"
#include "output.h"
#include "protobuf/baselib.h"


using namespace std;

bool areEqual(const Character& left, const pb::Character& right)
{
    return
        //        left.max_u8 == right.max_u8() &&
        //        left.max_u16 == right.max_u16() &&
        ////        left.max_u32 == right.max_u32() &&
        //        //left.idU64 == right.idU64 &&
        //        left.max_s8 == right.max_s8() &&
        //        left.max_s16 == right.max_s16() &&
        //        left.max_s32 == right.max_s32() &&
        //
        //        left.min_s8 == right.min_s8() &&
        //        left.min_s16 == right.min_s16() &&
        //        left.min_s32 == right.min_s32() &&

        left.x == right.x() &&
        left.y == right.y();// &&
        //left.z == right.z() &&
//        left.angle == right.angle() &&
//        left.anim == right.anim() &&
        //left.flag == right.flag() &&
        //left.desc == right.desc();
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

    //character->max_u8 = numeric_limits<uint8_t>::max();
    //character->max_u16 = numeric_limits<uint16_t>::max();
//    character->max_u32 = numeric_limits<uint32_t>::max();
    //character->idU64 = numeric_limits<uint64_t>::max();

    //character->min_s8 = numeric_limits<int8_t>::min();
    //character->min_s16 = numeric_limits<int16_t>::min();
    //character->min_s32 = numeric_limits<int32_t>::min();

    //character->max_s8 = numeric_limits<int8_t>::max();
    //character->max_s16 = numeric_limits<int16_t>::max();
    //character->max_s32 = numeric_limits<int32_t>::max();
    ////character->idS64 = numeric_limits<int64_t>::min();


    character->x = 10.0;
    character->y = 10.0;
//    character->z = 1.0;
////    character->angle = 45;
////    character->anim = Character::Walking;
//    character->flag = true;
//    character->desc = "My description here";

    return character;
}

bool areEqual(const Character& left, const Character& right)
{
    return
        //left.max_u8 == right.max_u8 &&
        //left.max_u16 == right.max_u16 &&
//        left.max_u32 == right.max_u32 &&

        //left.min_s8 == right.min_s8 &&
        //left.min_s16 == right.min_s16 &&
        //left.min_s32 == right.min_s32 &&

        //left.max_s8 == right.max_s8 &&
        //left.max_s16 == right.max_s16 &&
        //left.max_s32 == right.max_s32 &&

        //left.idU64 == right.idU64 &&
        //left.idS8 == right.idS8 &&
        //left.idS16 == right.idS16 &&
        //left.idS32 == right.idS32 &&
        //left.idS64 == right.idS64 &&
        left.x == right.x &&
        left.y == right.y;// &&
        //left.z == right.z &&
        //left.angle == right.angle &&
        //left.anim == right.anim &&
        //left.flag == right.flag &&
        //left.desc == right.desc;
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


  unique_ptr<Character> toSend = createSample();

    serializeToFile(sendFile, *toSend);

    {
        fstream is(sendFile, ios::in | ios::binary);
        fstream os(recvFile, ios::out | ios::trunc | ios::binary);

        protobufReadAndReply(is, os, *toSend);
    }
  unique_ptr<Character> recv = deserializeFromFile(sendFile);

  assert(recv && areEqual(*toSend, *recv));

  google::protobuf::ShutdownProtobufLibrary();

  return 0;

}