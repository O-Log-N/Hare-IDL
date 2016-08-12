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

vector<uint64_t> constructData64()
{
    vector<uint64_t> data;
    data.reserve(5000);


    for(size_t i = 0; i != 5000; ++i) {

        union {
            uint64_t asUint64;
            int32_t asInt[2];
        } value;
        
        value.asInt[0] = rand();
        value.asInt[1] = rand();

        data.push_back(value.asUint64);
    }
    return data;
}

vector<double> constructDataDouble()
{
    vector<double> data;
    data.reserve(5000);
    vector<uint64_t> uintData = constructData64();
    for (auto each : uintData) {

        union {
            uint64_t asUint;
            double asDouble;
        } value = {each};

        data.push_back(value.asDouble);
    }
    return data;
}


vector<float> constructDataFloat()
{
    vector<float> data;
    data.reserve(5000);
    vector<uint64_t> uintData = constructData64();
    for (auto each : uintData) {

        union {
            uint64_t asUint;
            float asDouble;
        } value = { each };

        data.push_back(value.asDouble);
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

static void serializeVarIntToFile(benchmark::State& state) {

    vector<uint64_t> data = constructData64();
    while (state.KeepRunning()) {

        FILE* out = fopen("varint.protobuf.bin", "w+b");
        OProtobufStream os(out);
//        state.PauseTiming();
//        state.ResumeTiming();
        for (size_t i = 0; i != data.size(); ++i) {
            os.writeUInt(i, data[i]);
        }
        fclose(out);    
    }
}



static void bl2_serializeVarIntToFile(benchmark::State& state) {

//    fstream out("baselib2.protobuf.bin", ios_base::binary| ios_base::out | ios_base::trunc);
    vector<uint64_t> data = constructData64();
    while (state.KeepRunning()) {


        FILE* out = fopen("varint2.protobuf.bin", "w+b");

        typedef bl2::OProtobufStream<bl2::FileWriter> OS;
        uint8_t baseBuff[smallBuffSize];
        bl2::FileWriter wr(out);
        OS os(baseBuff, smallBuffSize, wr);
//        state.PauseTiming();
//        state.ResumeTiming();
        for (size_t i = 0; i != data.size(); ++i) {
            os.writeUInt(i, data[i]);
        }
        os.flush();
        fclose(out);    
    }
}

static void serializeVarInt(benchmark::State& state) {

    vector<uint64_t> data = constructData64();
    while (state.KeepRunning()) {

        uint8_t baseBuff[bigBuffSize];

        uint8_t* dataPtr = baseBuff;
        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr = serializeUnsignedVariantToString(i, data[i], dataPtr);
        }
    }
}

static void bl2_serializeVarInt(benchmark::State& state) {

    vector<uint64_t> data = constructData64();
    while (state.KeepRunning()) {

        uint8_t baseBuff[bigBuffSize];

        uint8_t* dataPtr = baseBuff;
        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr = bl2::serializeHeaderToString(i, bl2::WIRE_TYPE::VARINT, dataPtr);
            dataPtr = bl2::serializeToStringVariantUint64(data[i], dataPtr);
        }
    }
}

static void checkSerializeVarInt(benchmark::State& state) {

    vector<uint64_t> data = constructData64();
    while (state.KeepRunning()) {

        uint8_t baseBuff[bigBuffSize];

        uint8_t* dataPtr = baseBuff;
        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr = serializeUnsignedVariantToString(i, data[i], dataPtr);
        }

        uint8_t baseBuff2[bigBuffSize];

        uint8_t* dataPtr2 = baseBuff2;
        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr2 = bl2::serializeHeaderToString(i, bl2::WIRE_TYPE::VARINT, dataPtr2);
            dataPtr2 = bl2::serializeToStringVariantUint64(data[i], dataPtr2);
        }


        if (dataPtr2 - baseBuff2 != dataPtr - baseBuff)
            throw 0;
        for (size_t i = 0; i != dataPtr - baseBuff; ++i)
            if (baseBuff[i] != baseBuff2[i])
                throw 0;
    }
}


static void deserializeVarInt(benchmark::State& state) {

    while (state.KeepRunning()) {
        uint8_t baseBuff[bigBuffSize];
        FILE* in = fopen("varint.protobuf.bin", "rb");
        size_t sz = fread(baseBuff, 1, bigBuffSize, in);
        assert(sz < bigBuffSize);

        IProtobufStream is(baseBuff, sz);
        int field;
        int type;
        int64_t value;
        bool ok = true;

        while (!is.isEndOfStream()) {
            ok = is.readFieldTypeAndID(type, field);
            if(!ok)
                break;
            ok = is.readVariantInt64(value);
            if (!ok)
                break;
        }

        fclose(in);
    }
}

static void bl2_deserializeVarInt(benchmark::State& state) {

    //    fstream out("baselib2.protobuf.bin", ios_base::binary| ios_base::out | ios_base::trunc);
    typedef bl2::IProtobufStream<bl2::FileReader> IS;

    while (state.KeepRunning()) {

        uint8_t baseBuff[bigBuffSize];
        FILE* in = fopen("varint.protobuf.bin", "rb");

        bl2::FileReader rd(in);
        bl2::IProtobufBuffer<bl2::FileReader> buff(baseBuff, bigBuffSize, rd);
        IS is(buff);
        int field;
        int type;
        int64_t value;
        bool ok = true;
        
        while (!is.isEndOfStream()) {
            ok = is.readFieldTypeAndID(type, field);
            if (!ok)
                break;
            ok = is.readVariantInt64(value);
            if (!ok)
                break;
        }

        fclose(in);
    }
}

static void serializeDoubleToFile(benchmark::State& state) {

    vector<double> data = constructDataDouble();
    while (state.KeepRunning()) {
        FILE* out = fopen("double.protobuf.bin", "w+b");
        OProtobufStream os(out);
        for (size_t i = 0; i != data.size(); ++i) {
            os.writeDouble(i, data[i]);
        }
        fclose(out);
    }
}

static void bl2_serializeDoubleToFile(benchmark::State& state) {

    vector<double> data = constructDataDouble();
    while (state.KeepRunning()) {

        FILE* out = fopen("double2.protobuf.bin", "w+b");

        typedef bl2::OProtobufStream<bl2::FileWriter> OS;

        uint8_t baseBuff[smallBuffSize];
        bl2::FileWriter wr(out);
        OS os(baseBuff, smallBuffSize, wr);
        for (size_t i = 0; i != data.size(); ++i) {
            os.writeDouble(i, data[i]);
        }
        os.flush();
        fclose(out);
    }
}

static void checkSerializeDouble(benchmark::State& state) {

    vector<double> data = constructDataDouble();
    while (state.KeepRunning()) {

        uint8_t baseBuff[bigBuffSize];

        uint8_t* dataPtr = baseBuff;
        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr = serializeDoubleToString(i, data[i], dataPtr);
        }

        uint8_t baseBuff2[bigBuffSize];

        uint8_t* dataPtr2 = baseBuff2;
        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr2 = bl2::serializeHeaderToString(i, bl2::WIRE_TYPE::FIXED_64_BIT, dataPtr2);
            dataPtr2 = bl2::serializeToStringFixedUint64(*reinterpret_cast<uint64_t*>(&data[i]), dataPtr2);
        }


        if (dataPtr2 - baseBuff2 != dataPtr - baseBuff)
            throw 0;
        for (size_t i = 0; i != dataPtr - baseBuff; ++i)
            if (baseBuff[i] != baseBuff2[i])
                throw 0;
    }
}


static void serializeDouble(benchmark::State& state) {

    vector<double> data = constructDataDouble();
    while (state.KeepRunning()) {

        uint8_t baseBuff[bigBuffSize];

        uint8_t* dataPtr = baseBuff;
        for (size_t i = 0; i != data.size(); ++i) {
            dataPtr = serializeDoubleToString(i, data[i], dataPtr);
        }
    }
}

static void bl2_serializeDouble(benchmark::State& state) {

    vector<double> data = constructDataDouble();
    while (state.KeepRunning()) {

        uint8_t baseBuff[bigBuffSize];

        uint8_t* dataPtr = baseBuff;

        for (size_t i = 0; i != data.size(); ++i) {
//            dataPtr = bl2::serializeHeaderToString(i, bl2::WIRE_TYPE::FIXED_64_BIT, dataPtr);
            dataPtr = bl2::serializeToStringFixedUint64(*reinterpret_cast<uint64_t*>(&data[i]), dataPtr);
        }
    }
}

static void deserializeDouble(benchmark::State& state) {

    while (state.KeepRunning()) {

        uint8_t baseBuff[bigBuffSize];
        FILE* in = fopen("double.protobuf.bin", "rb");
        size_t sz = fread(baseBuff, 1, bigBuffSize, in);
        assert(sz < bigBuffSize);

        IProtobufStream is(baseBuff, sz);
        int field;
        int type;
        double value;
        bool ok = true;
        while (!is.isEndOfStream()) {

            ok = is.readFieldTypeAndID(type, field);
            if (!ok)
                break;
            ok = is.readFixed64Bit(value);
            if (!ok)
                break;
        }

        fclose(in);
    }
}

static void bl2_deserializeDouble(benchmark::State& state) {

    typedef bl2::IProtobufStream<bl2::FileReader> IS;

    while (state.KeepRunning()) {

        uint8_t baseBuff[bigBuffSize];
        FILE* in = fopen("double.protobuf.bin", "rb");

        bl2::FileReader rd(in);
        bl2::IProtobufBuffer<bl2::FileReader> buff(baseBuff, bigBuffSize, rd);
        IS is(buff);
        int field;
        int type;
        double value;
        bool ok = true;
        while (!is.isEndOfStream()) {
            ok = is.readFieldTypeAndID(type, field);
            if (!ok)
                break;
            ok = is.readFixed64Bit(value);
            if (!ok)
                break;
        }

        fclose(in);
    }
}

static void serializeFloatToFile(benchmark::State& state) {

    vector<float> data = constructDataFloat();
    while (state.KeepRunning()) {
        FILE* out = fopen("float.protobuf.bin", "w+b");
        OProtobufStream os(out);
        for (size_t i = 0; i != data.size(); ++i) {
            os.writeFloat(i, data[i]);
        }
        fclose(out);
    }
}

static void bl2_serializeFloat(benchmark::State& state) {

    vector<float> data = constructDataFloat();
    while (state.KeepRunning()) {

        uint8_t baseBuff[bigBuffSize];

        uint8_t* dataPtr = baseBuff;

        for (size_t i = 0; i != data.size(); ++i) {
//            dataPtr = bl2::serializeHeaderToString(i, bl2::WIRE_TYPE::FIXED_32_BIT, dataPtr);
            dataPtr = bl2::serializeToStringFixedUint32(*reinterpret_cast<uint32_t*>(&data[i]), dataPtr);
        }
    }
}


static void bl2_deserializeFloat(benchmark::State& state) {

    typedef bl2::IProtobufStream<bl2::FileReader> IS;

    while (state.KeepRunning()) {

        uint8_t baseBuff[bigBuffSize];
        FILE* in = fopen("double.protobuf.bin", "rb");

        bl2::FileReader rd(in);
        bl2::IProtobufBuffer<bl2::FileReader> buff(baseBuff, bigBuffSize, rd);
        IS is(buff);
        int field;
        int type;
        float value;
        bool ok = true;
        while (!is.isEndOfStream()) {
            ok = is.readFieldTypeAndID(type, field);
            if (!ok)
                break;
            ok = is.readFixed32Bit(value);
            if (!ok)
                break;
        }

        fclose(in);
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

//BENCHMARK(serializeVarIntToFile);
//BENCHMARK(bl2_serializeVarIntToFile);
//BENCHMARK(checkSerializeVarInt);
//BENCHMARK(serializeVarInt)->Repetitions(10);
//BENCHMARK(bl2_serializeVarInt)->Repetitions(10);

//BENCHMARK(deserializeVarInt)->Repetitions(10);
//BENCHMARK(bl2_deserializeVarInt)->Repetitions(10);

//BENCHMARK(serializeDoubleToFile);
//BENCHMARK(bl2_serializeDoubleToFile);

//BENCHMARK(checkSerializeDouble);
//BENCHMARK(serializeDouble)->Repetitions(10);
BENCHMARK(bl2_serializeDouble)->Repetitions(10);

//BENCHMARK(deserializeDouble)->Repetitions(10);
BENCHMARK(bl2_deserializeDouble)->Repetitions(10);

//BENCHMARK(serializeFloatToFile);
BENCHMARK(bl2_serializeFloat)->Repetitions(10);
BENCHMARK(bl2_deserializeFloat)->Repetitions(10);

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
