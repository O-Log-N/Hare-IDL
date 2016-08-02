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
        OS os(out);
//        state.PauseTiming();
//        state.ResumeTiming();
        for (size_t i = 0; i != data.size(); ++i) {
            os.writeInt(i, data[i]);
        }
        os.flush();
        fclose(out);    
    }
}


//BENCHMARK(serializeVarInt);
//BENCHMARK(serializeDouble);

//BENCHMARK(bl2_serializeVarInt);
//BENCHMARK(bl2_serializeDouble);
BENCHMARK(serializeVarInt)->Repetitions(10);
//BENCHMARK(serializeDouble);

BENCHMARK(bl2_serializeVarInt)->Repetitions(10);

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
