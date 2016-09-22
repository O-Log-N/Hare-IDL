/*******************************************************************************
Copyright (C) 2016 OLogN Technologies AG

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2 as
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*******************************************************************************/

#include "protobuf/baselib.h"
#include "protobuf/baselib2.h"

#include "benchmark/benchmark.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

const size_t bigBuffSize = 100 * 1024;
const size_t dataSetSize = 10 * 1024;

vector<uint64_t> constructData64()
{
    vector<uint64_t> data;
    data.reserve(dataSetSize);


    for(size_t i = 0; i != dataSetSize; ++i) {

        union {
            uint64_t asUint64;
            int32_t asInt[2];
        } value;
        
        //Good enought for the purpose of the test
        value.asInt[0] = rand();
        value.asInt[1] = rand();

        data.push_back(value.asUint64);
    }
    return data;
}

vector<uint64_t> constructData_uint64_t()
{
    return constructData64();
}

vector<uint32_t> constructData32()
{
    vector<uint32_t> data;
    data.reserve(dataSetSize * 2);

    for (size_t i = 0; i != dataSetSize * 2; ++i) {

        union {
            uint32_t asUint32;
            int32_t asInt;
        } value;

        //Good enought for the purpose of the test
        value.asInt = rand();

        data.push_back(value.asUint32);
    }
    return data;
}
vector<uint32_t> constructData_uint32_t()
{
    return constructData32();
}

vector<string> constructDataString()
{
    vector<string> data;
    data.reserve(500);
    for (size_t i = 0; i != 50; ++i) {

        data.push_back(string(1, 'b'));
        data.push_back(string(2, 'b'));
        data.push_back(string(4, 'c'));
        data.push_back(string(8, 'd'));
        data.push_back(string(16, 'e'));

        data.push_back(string(32, 'f'));
        data.push_back(string(64, 'g'));
        data.push_back(string(128, 'h'));
        data.push_back(string(256, 'i'));
        data.push_back(string(512, 'j'));

        // mb original baselib has a 1000 bytes buffer for string
//        data.push_back(string(1024, 'k'));
//        data.push_back(string(2048, 'l'));
//        data.push_back(string(4096, 'm'));
    }
    return data;
}

/*
    mb: checking the result after last iteration of KeepRunnig,
    not only validates the functions are working correctly, but also
    prevents compiler from doing to much optimization and removing the
    loop completely
*/

#define SERIALIZE_GENERIC(T, REF_SERIALIZE, FUNC) \
    vector<T> data = constructData_##T(); \
    uint8_t baseBuff[bigBuffSize]; \
    uint8_t* dataPtr = baseBuff; \
    while (state.KeepRunning()) { \
        dataPtr = baseBuff; \
        for (auto each : data) { \
            dataPtr = FUNC(each, dataPtr); \
        } \
    } \
    uint8_t baseBuff2[bigBuffSize]; \
    uint8_t* dataPtr2 = baseBuff2; \
    for (auto each : data) { \
        dataPtr2 = REF_SERIALIZE(each, dataPtr2); \
    } \
    if(dataPtr2 - baseBuff2 != dataPtr - baseBuff) { \
        state.SkipWithError("Wrong data size"); \
        return; \
    } \
    for (size_t i = 0; i != dataPtr - baseBuff; ++i) { \
        if(baseBuff[i] != baseBuff2[i]) { \
            state.SkipWithError("Wrong data"); \
            return; \
        } \
    } \

#define DESERIALIZE_GENERIC(T, REF_SERIALIZE, FUNC) \
    vector<T> data = constructData_##T(); \
    uint8_t baseBuff[bigBuffSize]; \
    uint8_t* dataPtr = baseBuff; \
    for (auto each : data) { \
        dataPtr = REF_SERIALIZE(each, dataPtr); \
    } \
    vector<T> result; \
    result.reserve(data.size()); \
    while (state.KeepRunning()) { \
        result.clear(); \
        uint8_t* ptr = baseBuff; \
        T value = 0; \
        while (ptr != dataPtr) { \
            ptr = FUNC(value, ptr); \
            result.push_back(value); \
        } \
    } \
    if(data.size() != result.size()) { \
        state.SkipWithError("Wrong data size"); \
        return; \
    } \
    for (size_t i = 0; i != data.size(); ++i) { \
        if(data[i] != result[i]) { \
            state.SkipWithError("Wrong data"); \
            return; \
        } \
    } \


#define SERIALIZE_VAR_INT(FUNC) SERIALIZE_GENERIC(uint64_t, serializeToStringVariantUint64, FUNC)
#define DESERIALIZE_VAR_INT(FUNC) DESERIALIZE_GENERIC(uint64_t, serializeToStringVariantUint64, FUNC)

void serializeVarInt(benchmark::State& state) {
    SERIALIZE_VAR_INT(bl2::serializeToStringVariantUint64);
}

void serializeVarInt_loop(benchmark::State& state) {
    SERIALIZE_VAR_INT(bl2::serializeToStringVariantUint64_loop);
}

static void deserializeVarInt(benchmark::State& state) {
    DESERIALIZE_VAR_INT(bl2::deserializeFromStringVariantUint64);
}

static void deserializeVarInt_loop(benchmark::State& state) {
    DESERIALIZE_VAR_INT(bl2::deserializeFromStringVariantUint64_loop);
}

#define SERIALIZE_FIXED_64(FUNC) SERIALIZE_GENERIC(uint64_t, bl2::serializeToStringFixedUint64, FUNC)
#define DESERIALIZE_FIXED_64(FUNC) DESERIALIZE_GENERIC(uint64_t, bl2::serializeToStringFixedUint64, FUNC)

void serializeFixed64(benchmark::State& state) {
    SERIALIZE_FIXED_64(bl2::serializeToStringFixedUint64);
}

void serializeFixed64_2(benchmark::State& state) {
    SERIALIZE_FIXED_64(bl2::serializeToStringFixedUint64_2);
}

void serializeFixed64_little(benchmark::State& state) {
    SERIALIZE_FIXED_64(bl2::serializeToStringFixedUint64_little);
}

void serializeFixed64_loop(benchmark::State& state) {
    SERIALIZE_FIXED_64(bl2::serializeToStringFixedUint64_loop);
}

void serializeFixed64_loop2(benchmark::State& state) {
    SERIALIZE_FIXED_64(bl2::serializeToStringFixedUint64_loop2);
}

static void deserializeFixed64(benchmark::State& state) {
    DESERIALIZE_FIXED_64(bl2::deserializeFromStringFixedUint64);
}

static void deserializeFixed64_2(benchmark::State& state) {
    DESERIALIZE_FIXED_64(bl2::deserializeFromStringFixedUint64_2);
}

static void deserializeFixed64_3(benchmark::State& state) {
    DESERIALIZE_FIXED_64(bl2::deserializeFromStringFixedUint64_3);
}

static void deserializeFixed64_little(benchmark::State& state) {
    DESERIALIZE_FIXED_64(bl2::deserializeFromStringFixedUint64_little);
}

static void deserializeFixed64_loop(benchmark::State& state) {
    DESERIALIZE_FIXED_64(bl2::deserializeFromStringFixedUint64_loop);
}

#define SERIALIZE_FIXED_32(FUNC) SERIALIZE_GENERIC(uint32_t, bl2::serializeToStringFixedUint32, FUNC)
#define DESERIALIZE_FIXED_32(FUNC) DESERIALIZE_GENERIC(uint32_t, bl2::serializeToStringFixedUint32, FUNC)

void serializeFixed32(benchmark::State& state) {
    SERIALIZE_FIXED_32(bl2::serializeToStringFixedUint32);
}

static void serializeFixed32_2(benchmark::State& state) {
    SERIALIZE_FIXED_32(bl2::serializeToStringFixedUint32_2);
}

static void serializeFixed32_little(benchmark::State& state) {
    SERIALIZE_FIXED_32(bl2::serializeToStringFixedUint32_little);
}

static void serializeFixed32_loop(benchmark::State& state) {
    SERIALIZE_FIXED_32(bl2::serializeToStringFixedUint32_loop);
}

static void serializeFixed32_loop2(benchmark::State& state) {
    SERIALIZE_FIXED_32(bl2::serializeToStringFixedUint32_loop2);
}

static void deserializeFixed32(benchmark::State& state) {
    DESERIALIZE_FIXED_32(bl2::deserializeFromStringFixedUint32);
}

static void deserializeFixed32_2(benchmark::State& state) {
    DESERIALIZE_FIXED_32(bl2::deserializeFromStringFixedUint32_2);
}

static void deserializeFixed32_3(benchmark::State& state) {
    DESERIALIZE_FIXED_32(bl2::deserializeFromStringFixedUint32_3);
}

static void deserializeFixed32_little(benchmark::State& state) {
    DESERIALIZE_FIXED_32(bl2::deserializeFromStringFixedUint32_little);
}

static void deserializeFixed32_loop(benchmark::State& state) {
    DESERIALIZE_FIXED_32(bl2::deserializeFromStringFixedUint32_loop);
}

static void serializeString(benchmark::State& state) {

    vector<string> data = constructDataString();
    while (state.KeepRunning()) {
        FILE* out = fopen("string.protobuf.bin", "w+b");
        OProtobufStream os(out);
        for (size_t i = 0; i != data.size(); ++i) {
            os.writeString(i, data[i]);
        }
        fclose(out);
    }
}

static void bl2_serializeString(benchmark::State& state) {

    vector<string> data = constructDataString();
    while (state.KeepRunning()) {

        FILE* out = fopen("string2.protobuf.bin", "w+b");

        typedef bl2::OProtobufStream<bl2::FileWriter> OS;

        uint8_t baseBuff[bigBuffSize];
        bl2::FileWriter wr(out);
        OS os(baseBuff, bigBuffSize, wr);
        for (size_t i = 0; i != data.size(); ++i) {
            os.writeString(i, data[i]);
        }
        os.flush();
        fclose(out);
    }
}

static void deserializeString(benchmark::State& state) {

    while (state.KeepRunning()) {

        uint8_t baseBuff[bigBuffSize];
        FILE* in = fopen("string.protobuf.bin", "rb");
        size_t sz = fread(baseBuff, 1, bigBuffSize, in);
        assert(sz < bigBuffSize);


        IProtobufStream is(baseBuff, sz);
        int field;
        int type;
        string value;
        while (!is.isEndOfStream()) {
            if (is.readFieldTypeAndID(type, field));
                is.readString(value);
        }

        fclose(in);
    }
}

static void bl2_deserializeString(benchmark::State& state) {

    typedef bl2::IProtobufStream<bl2::FileReader> IS;

    while (state.KeepRunning()) {

        uint8_t baseBuff[bigBuffSize];
        FILE* in = fopen("string.protobuf.bin", "rb");

        bl2::FileReader rd(in);
        bl2::IProtobufBuffer<bl2::FileReader> buff(baseBuff, bigBuffSize, rd);
        IS is(buff);
        int field;
        int type;
        string value;
        while (!is.isEndOfStream()) {
            if (is.readFieldTypeAndID(type, field))
                is.readString(value);
        }

        fclose(in);
    }
}

BENCHMARK(serializeVarInt_loop);
BENCHMARK(serializeVarInt);

BENCHMARK(serializeFixed64_little);
BENCHMARK(serializeFixed64_2);
BENCHMARK(serializeFixed64_loop);
BENCHMARK(serializeFixed64);
BENCHMARK(serializeFixed64_loop2);

BENCHMARK(serializeFixed32_little);
BENCHMARK(serializeFixed32);
BENCHMARK(serializeFixed32_2);
BENCHMARK(serializeFixed32_loop);
BENCHMARK(serializeFixed32_loop2);


BENCHMARK(deserializeVarInt);
BENCHMARK(deserializeVarInt_loop);

BENCHMARK(deserializeFixed64_little);
BENCHMARK(deserializeFixed64);
BENCHMARK(deserializeFixed64_3);
BENCHMARK(deserializeFixed64_2);
BENCHMARK(deserializeFixed64_loop);


BENCHMARK(deserializeFixed32_little);
BENCHMARK(deserializeFixed32);
BENCHMARK(deserializeFixed32_3);
BENCHMARK(deserializeFixed32_2);
BENCHMARK(deserializeFixed32_loop);

//BENCHMARK(serializeString);
//BENCHMARK(serializeString);
//BENCHMARK(bl2_serializeString);

//BENCHMARK(deserializeString)->Repetitions(10);
//BENCHMARK(bl2_deserializeString)->Repetitions(10);

BENCHMARK_MAIN();

/*
int main()
{
    vector<int64_t> data = constructData64();
    FILE* out = fopen("baselib2.protobuf.bin", "w+b");
    bl2::OProtobufStream os(out);
    for (size_t i = 0; i != data.size(); ++i) {
        os.writeInt(i, data[i]);
    }
//    fclose(out);
}
*/
