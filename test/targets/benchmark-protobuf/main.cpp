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

#include "baselib_func_benchmark.h"

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

    We leave one unused byte between each value we encode, this is to
    force values to be misaligned as they will probably be in a real
    message
*/

#define SERIALIZE_GENERIC(T, REF_SERIALIZE, FUNC) \
    vector<T> data = constructData_##T(); \
    uint8_t baseBuff[bigBuffSize] = {0}; \
    uint8_t* dataPtr = baseBuff; \
    while (state.KeepRunning()) { \
        dataPtr = baseBuff; \
        for (auto each : data) { \
            dataPtr = FUNC(each, dataPtr); \
            ++dataPtr; \
        } \
    } \
    uint8_t baseBuff2[bigBuffSize] = {0}; \
    uint8_t* dataPtr2 = baseBuff2; \
    for (auto each : data) { \
        dataPtr2 = REF_SERIALIZE(each, dataPtr2); \
        ++dataPtr2; \
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
        ++dataPtr; \
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
            ++ptr; \
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


#define DESERIALIZE_GENERIC_CONST(T, REF_SERIALIZE, FUNC) \
    vector<T> data = constructData_##T(); \
    uint8_t baseBuff[bigBuffSize]; \
    uint8_t* dataPtr = baseBuff; \
    for (auto each : data) { \
        dataPtr = REF_SERIALIZE(each, dataPtr); \
        ++dataPtr; \
    } \
    vector<T> result; \
    result.reserve(data.size()); \
    while (state.KeepRunning()) { \
        result.clear(); \
        const uint8_t* ptr = baseBuff; \
        T value = 0; \
        while (ptr != dataPtr) { \
            ptr = FUNC(value, ptr); \
            result.push_back(value); \
            ++ptr; \
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

#define SERIALIZE_GENERIC_REF(T, REF_SERIALIZE, FUNC) \
    vector<T> data = constructData_##T(); \
    uint8_t baseBuff[bigBuffSize] = {0}; \
    uint8_t* dataPtr = baseBuff; \
    while (state.KeepRunning()) { \
        dataPtr = baseBuff; \
        for (auto each : data) { \
            FUNC(each, dataPtr); \
            ++dataPtr; \
        } \
    } \
    uint8_t baseBuff2[bigBuffSize] = {0}; \
    uint8_t* dataPtr2 = baseBuff2; \
    for (auto each : data) { \
        dataPtr2 = REF_SERIALIZE(each, dataPtr2); \
        ++dataPtr2; \
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

#define DESERIALIZE_GENERIC_REF(T, REF_SERIALIZE, FUNC) \
    vector<T> data = constructData_##T(); \
    uint8_t baseBuff[bigBuffSize]; \
    uint8_t* encPtr = baseBuff; \
    for (auto each : data) { \
        encPtr = REF_SERIALIZE(each, encPtr); \
        ++encPtr; \
    } \
    vector<T> result; \
    result.reserve(data.size()); \
    while (state.KeepRunning()) { \
        result.clear(); \
        const uint8_t* ptr = baseBuff; \
        T value = 0; \
        bool ok = true; \
        while (ptr != encPtr) { \
            auto value = FUNC(ptr, ok); \
            result.push_back(value); \
            ++ptr; \
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

#define DESERIALIZE_GENERIC_REF_FIXED(T, REF_SERIALIZE, FUNC) \
    vector<T> data = constructData_##T(); \
    uint8_t baseBuff[bigBuffSize]; \
    uint8_t* encPtr = baseBuff; \
    for (auto each : data) { \
        encPtr = REF_SERIALIZE(each, encPtr); \
        ++encPtr; \
    } \
    vector<T> result; \
    result.reserve(data.size()); \
    while (state.KeepRunning()) { \
        result.clear(); \
        const uint8_t* ptr = baseBuff; \
        T value = 0; \
        while (ptr != encPtr) { \
            auto value = FUNC(ptr); \
            result.push_back(value); \
            ++ptr; \
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

#define SERIALIZE_VAR_INT(FUNC) SERIALIZE_GENERIC(uint64_t, bnchmrk::serializeToStringVariantUint64, FUNC)
#define DESERIALIZE_VAR_INT(FUNC) DESERIALIZE_GENERIC(uint64_t, bnchmrk::serializeToStringVariantUint64, FUNC)

void serializeVarInt(benchmark::State& state) {
    SERIALIZE_VAR_INT(bnchmrk::serializeToStringVariantUint64);
}

void serializeVarInt_loop(benchmark::State& state) {
    SERIALIZE_VAR_INT(bnchmrk::serializeToStringVariantUint64_loop);
}

void serializeVarInt_ref(benchmark::State& state) {
    SERIALIZE_GENERIC_REF(uint64_t, bnchmrk::serializeToStringVariantUint64, bnchmrk::serializeToStringVariantUint64_ref);
}

static void deserializeVarInt(benchmark::State& state) {
    DESERIALIZE_VAR_INT(bnchmrk::deserializeFromStringVariantUint64);
}

static void deserializeVarInt_loop(benchmark::State& state) {
    DESERIALIZE_VAR_INT(bnchmrk::deserializeFromStringVariantUint64_loop);
}

static void deserializeVarInt_ref(benchmark::State& state) {
    DESERIALIZE_GENERIC_REF(uint64_t, bnchmrk::serializeToStringVariantUint64, bnchmrk::deserializeFromStringVariantUint64_ref);
}

static void deserializeVarInt_const(benchmark::State& state) {
    DESERIALIZE_GENERIC_CONST(uint64_t, bnchmrk::serializeToStringVariantUint64, bnchmrk::deserializeFromStringVariantUint64_const);
}

#define SERIALIZE_FIXED_64(FUNC) SERIALIZE_GENERIC(uint64_t, bnchmrk::serializeToStringFixedUint64, FUNC)
#define DESERIALIZE_FIXED_64(FUNC) DESERIALIZE_GENERIC(uint64_t, bnchmrk::serializeToStringFixedUint64, FUNC)

void serializeFixed64(benchmark::State& state) {
    SERIALIZE_FIXED_64(bnchmrk::serializeToStringFixedUint64);
}

void serializeFixed64_2(benchmark::State& state) {
    SERIALIZE_FIXED_64(bnchmrk::serializeToStringFixedUint64_2);
}

void serializeFixed64_little(benchmark::State& state) {
    SERIALIZE_FIXED_64(bnchmrk::serializeToStringFixedUint64_little);
}

void serializeFixed64_loop(benchmark::State& state) {
    SERIALIZE_FIXED_64(bnchmrk::serializeToStringFixedUint64_loop);
}

void serializeFixed64_loop2(benchmark::State& state) {
    SERIALIZE_FIXED_64(bnchmrk::serializeToStringFixedUint64_loop2);
}

static void deserializeFixed64(benchmark::State& state) {
    DESERIALIZE_FIXED_64(bnchmrk::deserializeFromStringFixedUint64);
}

static void deserializeFixed64_2(benchmark::State& state) {
    DESERIALIZE_FIXED_64(bnchmrk::deserializeFromStringFixedUint64_2);
}

static void deserializeFixed64_3(benchmark::State& state) {
    DESERIALIZE_FIXED_64(bnchmrk::deserializeFromStringFixedUint64_3);
}

static void deserializeFixed64_3_ref(benchmark::State& state) {
    DESERIALIZE_GENERIC_REF_FIXED(uint64_t, bnchmrk::serializeToStringFixedUint64, bnchmrk::deserializeFromStringFixedUint64_3_ref);
}

static void deserializeFixed64_little(benchmark::State& state) {
    DESERIALIZE_FIXED_64(bnchmrk::deserializeFromStringFixedUint64_little);
}

static void deserializeFixed64_little_ref(benchmark::State& state) {
    DESERIALIZE_GENERIC_REF_FIXED(uint64_t, bnchmrk::serializeToStringFixedUint64, bnchmrk::deserializeFromStringFixedUint64_little_ref);
}

static void deserializeFixed64_loop(benchmark::State& state) {
    DESERIALIZE_FIXED_64(bnchmrk::deserializeFromStringFixedUint64_loop);
}

#define SERIALIZE_FIXED_32(FUNC) SERIALIZE_GENERIC(uint32_t, bnchmrk::serializeToStringFixedUint32, FUNC)
#define DESERIALIZE_FIXED_32(FUNC) DESERIALIZE_GENERIC(uint32_t, bnchmrk::serializeToStringFixedUint32, FUNC)

void serializeFixed32(benchmark::State& state) {
    SERIALIZE_FIXED_32(bnchmrk::serializeToStringFixedUint32);
}

static void serializeFixed32_2(benchmark::State& state) {
    SERIALIZE_FIXED_32(bnchmrk::serializeToStringFixedUint32_2);
}

static void serializeFixed32_little(benchmark::State& state) {
    SERIALIZE_FIXED_32(bnchmrk::serializeToStringFixedUint32_little);
}

static void serializeFixed32_loop(benchmark::State& state) {
    SERIALIZE_FIXED_32(bnchmrk::serializeToStringFixedUint32_loop);
}

static void serializeFixed32_loop2(benchmark::State& state) {
    SERIALIZE_FIXED_32(bnchmrk::serializeToStringFixedUint32_loop2);
}

static void deserializeFixed32(benchmark::State& state) {
    DESERIALIZE_FIXED_32(bnchmrk::deserializeFromStringFixedUint32);
}

static void deserializeFixed32_2(benchmark::State& state) {
    DESERIALIZE_FIXED_32(bnchmrk::deserializeFromStringFixedUint32_2);
}

static void deserializeFixed32_3(benchmark::State& state) {
    DESERIALIZE_FIXED_32(bnchmrk::deserializeFromStringFixedUint32_3);
}

static void deserializeFixed32_3_ref(benchmark::State& state) {
    DESERIALIZE_GENERIC_REF_FIXED(uint32_t, bnchmrk::serializeToStringFixedUint32, bnchmrk::deserializeFromStringFixedUint32_3_ref);
}

static void deserializeFixed32_little(benchmark::State& state) {
    DESERIALIZE_FIXED_32(bnchmrk::deserializeFromStringFixedUint32_little);
}

static void deserializeFixed32_little_ref(benchmark::State& state) {
    DESERIALIZE_GENERIC_REF_FIXED(uint32_t, bnchmrk::serializeToStringFixedUint32, bnchmrk::deserializeFromStringFixedUint32_little_ref);
}

static void deserializeFixed32_loop(benchmark::State& state) {
    DESERIALIZE_FIXED_32(bnchmrk::deserializeFromStringFixedUint32_loop);
}


BENCHMARK(serializeVarInt);
BENCHMARK(serializeVarInt_ref);
BENCHMARK(serializeVarInt_loop);

BENCHMARK(serializeFixed64_little);
BENCHMARK(serializeFixed64);
BENCHMARK(serializeFixed64_2);
BENCHMARK(serializeFixed64_loop);
BENCHMARK(serializeFixed64_loop2);

BENCHMARK(serializeFixed32_little);
BENCHMARK(serializeFixed32);
BENCHMARK(serializeFixed32_2);
BENCHMARK(serializeFixed32_loop);
BENCHMARK(serializeFixed32_loop2);

BENCHMARK(deserializeVarInt);
BENCHMARK(deserializeVarInt_const);
BENCHMARK(deserializeVarInt_ref);
BENCHMARK(deserializeVarInt_loop);

BENCHMARK(deserializeFixed64_little);
BENCHMARK(deserializeFixed64_little_ref);
BENCHMARK(deserializeFixed64);
BENCHMARK(deserializeFixed64_2);
BENCHMARK(deserializeFixed64_3);
BENCHMARK(deserializeFixed64_3_ref);
BENCHMARK(deserializeFixed64_loop);

BENCHMARK(deserializeFixed32_little);
BENCHMARK(deserializeFixed32_little_ref);
BENCHMARK(deserializeFixed32);
BENCHMARK(deserializeFixed32_2);
BENCHMARK(deserializeFixed32_3);
BENCHMARK(deserializeFixed32_3_ref);
BENCHMARK(deserializeFixed32_loop);


BENCHMARK_MAIN();

