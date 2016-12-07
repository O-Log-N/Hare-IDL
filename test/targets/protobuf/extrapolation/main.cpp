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

#define _CRT_SECURE_NO_WARNINGS

#include "test.h"
#include "output.h"
#include "../test_helper.h"
#include "dbg_helpers.h"
#include "extrapolation.h"

class Extrapolator {
    size_t lastTick = 0;
    LinearExtrapolator<int64_t> optInteger;
    LinearExtrapolator<float> optFloat;
    LinearExtrapolator<double> optDouble;
public:
    Extrapolator():
        optInteger(1, 8),
        optFloat(0.01, 8),
        optDouble(0.01, 8)
        {}

    deque<bool> getOptMask(const TestExtrapolation& data) {
        deque<bool> mask;

        mask.push_back(optInteger.getMask(data.tick, data.optInteger));
        mask.push_back(optFloat.getMask(data.tick, data.optFloat));
        mask.push_back(optDouble.getMask(data.tick, data.optDouble));

        return mask;
    }

    void extrapolate(TestExtrapolation& data) {
        ++lastTick;

        data.optInteger = optInteger.extrapolate(lastTick);
        data.optFloat = optFloat.extrapolate(lastTick);
        data.optDouble = optDouble.extrapolate(lastTick);
    }

    bool ckeckExtrapolatedTick(TestExtrapolation& data) {
        if(data.tick == lastTick) {
            if(data.optInteger != optInteger.extrapolate(lastTick))
                optInteger.setValue(lastTick, data.optInteger);
            if(data.optFloat != optFloat.extrapolate(lastTick))
                optFloat.setValue(lastTick, data.optFloat);
            if(data.optDouble != optDouble.extrapolate(lastTick))
                optDouble.setValue(lastTick, data.optDouble);

            return true;
        }
        else {
            lastTick = data.tick - 1;
            extrapolate(data);
            return false;
        }
    }


};


void serialize(vector<uint8_t>& toRead, const char* fileName, const TestExtrapolation& tc, deque<bool> mask) {

    string fullName(fileName);
    fullName += ".protobuf.bin";

    FILE* f = fopen(fullName.c_str(), "w+b");
    ASSERT_NE(f, nullptr);
    OProtobufStream o(f);

    size_t sz = serializeTestExtrapolation(tc, o, mask);

    toRead.clear();
    toRead.resize(sz);

    rewind(f);
    size_t readSize = fread(&toRead[0], 1, sz, f);

    ASSERT_EQ(readSize, sz);
    ASSERT_EQ(fgetc(f), EOF);

    fclose(f);
}

void encodedCompare(const vector<uint8_t>& read, const vector<uint8_t>& expected)
{
    ASSERT_EQ(read.size(), expected.size());
    for(size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(read[i], expected[i]);
    }
}

void assertNear(const TestExtrapolation& send, const TestExtrapolation& recv)
{
    ASSERT_EQ(send.tick, recv.tick);
    ASSERT_EQ(send.optInteger, recv.optInteger);
    ASSERT_NEAR(send.optFloat, recv.optFloat, 0.01);
    ASSERT_NEAR(send.optDouble, recv.optDouble, 0.01);
}

TEST(Extrapolation, StandStill)
{
    Extrapolator ext;
    TestExtrapolation tc1;
    tc1.tick = 1;
    tc1.optInteger = 10;
    tc1.optFloat = 20;
    tc1.optDouble = 30;

    TestExtrapolation tc2;
    tc2.tick = 2;
    tc2.optInteger = 10;
    tc2.optFloat = 20;
    tc2.optDouble = 30;

    TestExtrapolation tc3;
    tc3.tick = 3;
    tc3.optInteger = 10;
    tc3.optFloat = 20;
    tc3.optDouble = 30;

    vector<uint8_t> buff1;
    serialize(buff1, "file10", tc1, ext.getOptMask(tc1));
    vector<uint8_t> buff2;
    serialize(buff2, "file11", tc2, ext.getOptMask(tc2));
    vector<uint8_t> buff3;
    serialize(buff3, "file12", tc3, ext.getOptMask(tc3));


    encodedCompare(buff3, {0x08, 0x03});


    IProtobufStream i1(&buff1[0], buff1.size());
    TestExtrapolation de1;
    ext.extrapolate(de1);
    ASSERT_TRUE(deserializeTestExtrapolation(de1, i1));

    ASSERT_TRUE(ext.ckeckExtrapolatedTick(de1));

    IProtobufStream i2(&buff2[0], buff2.size());
    TestExtrapolation de2;
    ext.extrapolate(de2);
    ASSERT_TRUE(deserializeTestExtrapolation(de2, i2));

    ASSERT_TRUE(ext.ckeckExtrapolatedTick(de2));

    IProtobufStream i3(&buff3[0], buff3.size());
    TestExtrapolation de3;
    ext.extrapolate(de3);
    ASSERT_TRUE(deserializeTestExtrapolation(de3, i3));

    ASSERT_TRUE(ext.ckeckExtrapolatedTick(de3));

    assertNear(tc1, de1);
    assertNear(tc2, de2);
    assertNear(tc3, de3);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

