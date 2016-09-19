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

const size_t bigBuffSize = 128 * 1024;
const size_t smallBuffSize = 4 * 1024;
const size_t dataSetSize = 5000;

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

vector<uint32_t> constructData32()
{
    vector<uint32_t> data;
    data.reserve(dataSetSize);


    for (size_t i = 0; i != dataSetSize; ++i) {

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

static void serializeVarInt(benchmark::State& state) {

    vector<uint64_t> data = constructData64();
    uint8_t baseBuff[bigBuffSize];
    while (state.KeepRunning()) {

        uint8_t* dataPtr = baseBuff;
        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr = bl2::serializeToStringVariantUint64(data[i], dataPtr);
        }
    }
}

static void serializeVarInt_loop(benchmark::State& state) {

    vector<uint64_t> data = constructData64();
    uint8_t baseBuff[bigBuffSize];
    while (state.KeepRunning()) {

        uint8_t* dataPtr = baseBuff;
        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr = bl2::serializeToStringVariantUint64_loop(data[i], dataPtr);
        }
    }
}

static void deserializeVarInt(benchmark::State& state) {

    vector<uint64_t> data = constructData64();
    uint8_t baseBuff[bigBuffSize];

    uint8_t* dataPtr = baseBuff;
    for (size_t i = 0; i != data.size(); ++i) {
        dataPtr = bl2::serializeToStringVariantUint64(data[i], dataPtr);
    }

    while (state.KeepRunning()) {

        vector<uint64_t> data;
        data.reserve(dataSetSize);

        uint8_t* ptr = baseBuff;
        uint64_t value;
        bool ok = true;

        while (ptr != dataPtr) {
            ptr = bl2::deserializeFromStringVariantUint64(value, ptr);
            if (ptr > dataPtr) {
                state.SkipWithError("Read past end of buffer");
                break;
            }
            data.push_back(value);
        }
    }
}

static void deserializeVarInt_loop(benchmark::State& state) {

    vector<uint64_t> data = constructData64();
    uint8_t baseBuff[bigBuffSize];

    uint8_t* dataPtr = baseBuff;
    for (size_t i = 0; i != data.size(); ++i) {
        dataPtr = bl2::serializeToStringVariantUint64(data[i], dataPtr);
    }

    while (state.KeepRunning()) {

        vector<uint64_t> data;
        data.reserve(dataSetSize);

        uint8_t* ptr = baseBuff;
        int field;
        int type;
        uint64_t value;
        bool ok = true;

        while (ptr != dataPtr) {
            ptr = bl2::deserializeFromStringVariantUint64_loop(value, ptr);
            if (ptr > dataPtr) {
                state.SkipWithError("Read past end of buffer");
                break;
            }
            data.push_back(value);
        }
    }
}


static void serializeFixed64(benchmark::State& state) {

    vector<uint64_t> data = constructData64();
    uint8_t baseBuff[bigBuffSize];
    while (state.KeepRunning()) {

        uint8_t* dataPtr = baseBuff;

        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr = bl2::serializeToStringFixedUint64(data[i], dataPtr);
        }
    }
}

static void serializeFixed64_little(benchmark::State& state) {

    vector<uint64_t> data = constructData64();
    uint8_t baseBuff[bigBuffSize];
    while (state.KeepRunning()) {

        uint8_t* dataPtr = baseBuff;

        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr = bl2::serializeToStringFixedUint64_little(data[i], dataPtr);
        }
    }
}

static void deserializeFixed64(benchmark::State& state) {

    vector<uint64_t> data = constructData64();
    uint8_t baseBuff[bigBuffSize];

    uint8_t* dataPtr = baseBuff;
    for (size_t i = 0; i != data.size(); ++i) {
        dataPtr = bl2::serializeToStringFixedUint64(data[i], dataPtr);
    }

    vector<uint64_t> result;
    result.reserve(dataSetSize);

    while (state.KeepRunning()) {

        result.clear();

        uint8_t* ptr = baseBuff;
        uint64_t value;

        while (ptr != dataPtr) {
            ptr = bl2::deserializeFromStringFixedUint64(value, ptr);
            if (ptr > dataPtr) {
                state.SkipWithError("Read past end of buffer");
                break;
            }
            result.push_back(value);
        }
    }
}

static void deserializeFixed64_little(benchmark::State& state) {

    vector<uint64_t> data = constructData64();
    uint8_t baseBuff[bigBuffSize];

    uint8_t* dataPtr = baseBuff;
    for (size_t i = 0; i != data.size(); ++i) {
        dataPtr = bl2::serializeToStringFixedUint64(data[i], dataPtr);
    }

    vector<uint64_t> result;
    result.reserve(dataSetSize);

    while (state.KeepRunning()) {

        result.clear();
        uint8_t* ptr = baseBuff;
        uint64_t value;

        while (ptr != dataPtr) {
            ptr = bl2::deserializeFromStringFixedUint64_little(value, ptr);
            if (ptr > dataPtr) {
                state.SkipWithError("Read past end of buffer");
                break;
            }
            result.push_back(value);
        }
    }
}

static void serializeFixed32(benchmark::State& state) {

    vector<uint32_t> data = constructData32();
    uint8_t baseBuff[bigBuffSize];
    while (state.KeepRunning()) {

        uint8_t* dataPtr = baseBuff;

        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr = bl2::serializeToStringFixedUint32(data[i], dataPtr);
        }
    }
}

static void serializeFixed32_little(benchmark::State& state) {

    vector<uint32_t> data = constructData32();
    uint8_t baseBuff[bigBuffSize];
    while (state.KeepRunning()) {

        uint8_t* dataPtr = baseBuff;

        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr = bl2::serializeToStringFixedUint32_little(data[i], dataPtr);
        }
    }
}

static void serializeFixed32_loop(benchmark::State& state) {

    vector<uint32_t> data = constructData32();
    uint8_t baseBuff[bigBuffSize];
    while (state.KeepRunning()) {

        uint8_t* dataPtr = baseBuff;

        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr = bl2::serializeToStringFixedUint32_loop(data[i], dataPtr);
        }
    }
}

static void deserializeFixed32(benchmark::State& state) {

    vector<uint32_t> data = constructData32();
    uint8_t baseBuff[bigBuffSize];

    uint8_t* dataPtr = baseBuff;
    for (size_t i = 0; i != data.size(); ++i) {
        dataPtr = bl2::serializeToStringFixedUint32(data[i], dataPtr);
    }

    vector<uint32_t> result;
    result.reserve(dataSetSize);

    while (state.KeepRunning()) {

        result.clear();
        uint8_t* ptr = baseBuff;
        uint32_t value;

        while (ptr != dataPtr) {
            ptr = bl2::deserializeFromStringFixedUint32(value, ptr);
            if (ptr > dataPtr) {
                state.SkipWithError("Read past end of buffer");
                break;
            }
            result.push_back(value);
        }
    }
}

static void deserializeFixed32_little(benchmark::State& state) {

    vector<uint32_t> data = constructData32();
    uint8_t baseBuff[bigBuffSize];

    uint8_t* dataPtr = baseBuff;
    for (size_t i = 0; i != data.size(); ++i) {
        dataPtr = bl2::serializeToStringFixedUint32(data[i], dataPtr);
    }

    vector<uint32_t> result;
    result.reserve(dataSetSize);

    while (state.KeepRunning()) {

        result.clear();
        uint8_t* ptr = baseBuff;
        uint32_t value;

        while (ptr != dataPtr) {
            ptr = bl2::deserializeFromStringFixedUint32_little(value, ptr);
            if (ptr > dataPtr) {
                state.SkipWithError("Read past end of buffer");
                break;
            }
            result.push_back(value);
        }
    }
}

static void deserializeFixed32_loop(benchmark::State& state) {

    vector<uint32_t> data = constructData32();
    uint8_t baseBuff[bigBuffSize];

    uint8_t* dataPtr = baseBuff;
    for (size_t i = 0; i != data.size(); ++i) {
        dataPtr = bl2::serializeToStringFixedUint32(data[i], dataPtr);
    }

    vector<uint32_t> result;
    result.reserve(dataSetSize);

    while (state.KeepRunning()) {

        result.clear();
        uint8_t* ptr = baseBuff;
        uint32_t value;

        while (ptr != dataPtr) {
            ptr = bl2::deserializeFromStringFixedUint32_loop(value, ptr);
            if (ptr > dataPtr) {
                state.SkipWithError("Read past end of buffer");
                break;
            }
            result.push_back(value);
        }
    }
}

static void deserializeFloat(benchmark::State& state) {

    vector<uint32_t> data = constructData32();
    uint8_t baseBuff[bigBuffSize];

    uint8_t* dataPtr = baseBuff;
    for (size_t i = 0; i != data.size(); ++i) {
        dataPtr = bl2::serializeToStringFixedUint32(data[i], dataPtr);
    }

    vector<float> result;
    result.reserve(dataSetSize);

    while (state.KeepRunning()) {

        result.clear();
        uint8_t* ptr = baseBuff;
        uint32_t value;

        while (ptr != dataPtr) {
            ptr = bl2::deserializeFromStringFixedUint32(value, ptr);
            if (ptr > dataPtr) {
                state.SkipWithError("Read past end of buffer");
                break;
            }
            result.push_back(*reinterpret_cast<float*>(&value));
        }
    }
}

static void deserializeFloat_little(benchmark::State& state) {

    vector<uint32_t> data = constructData32();
    uint8_t baseBuff[bigBuffSize];

    uint8_t* dataPtr = baseBuff;
    for (size_t i = 0; i != data.size(); ++i) {
        dataPtr = bl2::serializeToStringFixedUint32(data[i], dataPtr);
    }

    vector<float> result;
    result.reserve(dataSetSize);

    while (state.KeepRunning()) {

        result.clear();
        uint8_t* ptr = baseBuff;
        uint32_t value;

        while (ptr != dataPtr) {
            ptr = bl2::deserializeFromStringFixedUint32_little(value, ptr);
            if (ptr > dataPtr) {
                state.SkipWithError("Read past end of buffer");
                break;
            }
            result.push_back(*reinterpret_cast<float*>(&value));
        }
    }
}

static void deserializeFloat_loop(benchmark::State& state) {

    vector<uint32_t> data = constructData32();
    uint8_t baseBuff[bigBuffSize];

    uint8_t* dataPtr = baseBuff;
    for (size_t i = 0; i != data.size(); ++i) {
        dataPtr = bl2::serializeToStringFixedUint32(data[i], dataPtr);
    }

    vector<float> result;
    result.reserve(dataSetSize);

    while (state.KeepRunning()) {

        result.clear();
        uint8_t* ptr = baseBuff;
        uint32_t value;

        while (ptr != dataPtr) {
            ptr = bl2::deserializeFromStringFixedUint32_loop(value, ptr);
            if (ptr > dataPtr) {
                state.SkipWithError("Read past end of buffer");
                break;
            }
            result.push_back(*reinterpret_cast<float*>(&value));
        }
    }
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

BENCHMARK(serializeVarInt);
BENCHMARK(serializeVarInt_loop);
BENCHMARK(deserializeVarInt);
BENCHMARK(deserializeVarInt_loop);

BENCHMARK(serializeFixed64);
BENCHMARK(serializeFixed64_little);
BENCHMARK(deserializeFixed64);
BENCHMARK(deserializeFixed64_little);

BENCHMARK(serializeFixed32);
BENCHMARK(serializeFixed32_little);
BENCHMARK(serializeFixed32_loop);
BENCHMARK(deserializeFixed32);
BENCHMARK(deserializeFixed32_little);
BENCHMARK(deserializeFixed32_loop);

BENCHMARK(deserializeFloat);
BENCHMARK(deserializeFloat_little);
BENCHMARK(deserializeFloat_loop);


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
