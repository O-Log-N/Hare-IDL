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

vector<int64_t> constructData64()
{
    const int64_t base = 15;

    vector<int64_t> data;
    data.reserve(10000);
    for(size_t i = 0; i != 1000; ++i) {

        data.push_back(base);
        data.push_back(base << 8);
        data.push_back(base << 16);
        data.push_back(base << 32);
        data.push_back(base << 32);

        data.push_back(-base);
        data.push_back(-base << 8);
        data.push_back(-base << 16);
        data.push_back(-base << 32);
        data.push_back(-base << 32);

    }
    return data;
}


static void serializeVarInt(benchmark::State& state) {

    vector<int64_t> data = constructData64();
    while (state.KeepRunning()) {
        FILE* out = fopen("baselib.protobuf.bin", "w+b");
        OProtobufStream os(out);
//        state.PauseTiming();
//        state.ResumeTiming();
        for (size_t i = 0; i != data.size(); ++i) {
            os.writeInt(i, data[i]);
        }
        fclose(out);    
    }
}

static void bl2_serializeVarInt(benchmark::State& state) {

//    fstream out("baselib2.protobuf.bin", ios_base::binary| ios_base::out | ios_base::trunc);
    vector<int64_t> data = constructData64();
    while (state.KeepRunning()) {

        typedef bl2::OProtobufStream<bl2::FileWriter, 4000> OS;
        
        FILE* out = fopen("baselib2.protobuf.bin", "w+b");
        bl2::FileWriter wr(out);
        OS os(wr);
//        state.PauseTiming();
//        state.ResumeTiming();
        for (size_t i = 0; i != data.size(); ++i) {
            os.writeInt(i, data[i]);
        }
        os.flush();
        fclose(out);    
    }
}


static void deserializeVarInt(benchmark::State& state) {

    const size_t buffSize = 64 * 1024;
    uint8_t baseBuff[buffSize];
    FILE* in = fopen("baselib.protobuf.bin", "rb");
    size_t sz = fread(baseBuff, 1, buffSize, in);
    assert(sz < buffSize);

    while (state.KeepRunning()) {
        IProtobufStream is(baseBuff, sz);
        while (!is.isEndOfStream()) {
            int field;
            int type;
            int64_t value;
            is.readFieldTypeAndID(type, field);
            is.readVariantInt64(value);
        }
    }
    fclose(in);
}

static void bl2_deserializeVarInt(benchmark::State& state) {

    //    fstream out("baselib2.protobuf.bin", ios_base::binary| ios_base::out | ios_base::trunc);
    typedef bl2::IProtobufStream<bl2::FileReader> IS;

    const size_t buffSize = 64 * 1024;
    uint8_t baseBuff[buffSize];
    FILE* in = fopen("baselib.protobuf.bin", "rb");

    while (state.KeepRunning()) {
        bl2::FileReader rd(in);
        bl2::IProtobufBuffer buff(baseBuff, buffSize);
        IS is(buff, rd);
        while (!is.isEndOfStream()) {
            int field;
            bl2::WIRE_TYPE type;
            int64_t value;
            is.readFieldTypeAndID(type, field);
            is.readVariantInt64(value);
        }
        rewind(in);
    }
    fclose(in);
}

//BENCHMARK(serializeVarInt);
//BENCHMARK(serializeDouble);

//BENCHMARK(bl2_serializeVarInt);
//BENCHMARK(bl2_serializeDouble);
BENCHMARK(deserializeVarInt)->Repetitions(10);
//BENCHMARK(serializeDouble);

BENCHMARK(bl2_deserializeVarInt)->Repetitions(10);

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
