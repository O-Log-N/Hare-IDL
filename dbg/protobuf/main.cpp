
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

template<class T, class U>
bool areEqualSeq(const T& left, const U& right)
{
    auto it1 = left.begin();
    auto it1_end = left.end();
    auto it2 = right.begin();
    auto it2_end = right.end();
    for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2)
        if (*it1 != *it2)
            return false;

    return it1 == it1_end && it2 == it2_end;
}

bool areEqual(const Character& left, const pb::Character& right)
{
    bool ok = true;
    ok = ok && left.max_u8 == right.max_u8();
    ok = ok && left.max_u16 == right.max_u16();
    ////        left.max_u32 == right.max_u32() &&
    //        //left.idU64 == right.idU64 &&
    ok = ok && left.max_s8 == right.max_s8();
    ok = ok && left.max_s16 == right.max_s16();
    ok = ok && left.max_s32 == right.max_s32();
        
    ok = ok && left.min_s8 == right.min_s8();
    ok = ok && left.min_s16 == right.min_s16();
    ok = ok && left.min_s32 == right.min_s32();

    ok = ok && left.x == right.x();
    ok = ok && left.y == right.y();
    ok = ok && left.z == right.z();
//        left.angle == right.angle() &&
//        left.anim == right.anim() &&
    ok = ok && left.flag == right.flag();
    ok = ok && left.desc == right.desc();
    ok = ok && areEqualSeq(left.more_text, right.more_text());
    ok = ok && areEqualSeq(left.some_ints, right.some_ints());
    
    return ok;
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

    character->max_u8 = numeric_limits<uint8_t>::max();
    character->max_u16 = numeric_limits<uint16_t>::max();
//    character->max_u32 = numeric_limits<uint32_t>::max();
    //character->idU64 = numeric_limits<uint64_t>::max();

    character->min_s8 = numeric_limits<int8_t>::min();
    character->min_s16 = numeric_limits<int16_t>::min();
    character->min_s32 = numeric_limits<int32_t>::min();

    character->max_s8 = numeric_limits<int8_t>::max();
    character->max_s16 = numeric_limits<int16_t>::max();
    character->max_s32 = numeric_limits<int32_t>::max();
    ////character->idS64 = numeric_limits<int64_t>::min();


    character->x = 10.0;
    character->y = 10.0;
    character->z = 1.0;
////    character->angle = 45;
////    character->anim = Character::Walking;
    character->flag = true;
    character->desc = "My description here";
    character->more_text.push_back("line1");
    character->more_text.push_back("line2");
    character->more_text.push_back("line3");

    character->some_ints.push_back(10);
    character->some_ints.push_back(100);
    character->some_ints.push_back(1000);

    return character;
}

bool areEqual(const Character& left, const Character& right)
{
    bool ok = true;
    ok = ok && left.max_u8 == right.max_u8;
    ok = ok && left.max_u16 == right.max_u16;
    ////        left.max_u32 == right.max_u32() &&
    //        //left.idU64 == right.idU64 &&
    ok = ok && left.max_s8 == right.max_s8;
    ok = ok && left.max_s16 == right.max_s16;
    ok = ok && left.max_s32 == right.max_s32;

    ok = ok && left.min_s8 == right.min_s8;
    ok = ok && left.min_s16 == right.min_s16;
    ok = ok && left.min_s32 == right.min_s32;

    ok = ok && left.x == right.x;
    ok = ok && left.y == right.y;
    ok = ok && left.z == right.z;
    //        left.angle == right.angle() &&
    //        left.anim == right.anim() &&
    ok = ok && left.flag == right.flag;
    ok = ok && left.desc == right.desc;
    ok = ok && areEqualSeq(left.more_text, right.more_text);
    ok = ok && areEqualSeq(left.some_ints, right.some_ints);

    return ok;
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