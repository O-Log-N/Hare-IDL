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

#ifndef SAMPLE_WITH_CPP_H_INCLUDED
#define SAMPLE_WITH_CPP_H_INCLUDED

#include <cstdint>
#include <string>
#include <vector>

#include "hare/hareidl.h"

using namespace std;

class myHareSampleItem {
public:
    string name;
};

typedef vector<myHareSampleItem> mySampleVector;

class HAREIDL(mapping("SomeName")) myHareSampleItem2 {
public:
    string name;
};


class HAREIDL(mapping) myHareSampleCharacter {
public:
  int character_id;
  __attribute__((annotate("hare::encode_as(\"DELTA VLQ\")"))) double x;
  [[hare::encode_as("DELTA VLQ")]] double y;
  HAREIDL(encode_as("DELTA VLQ")) double z;
  HAREIDL(encode_as("DELTA VLQ")) double vx;
  HAREIDL(encode_as("DELTA VLQ")) double vy;
  HAREIDL(encode_as("DELTA VLQ")) double vz;
  float angle;
  enum Animation {Standing=0,Walking=1, Running=2} anim;
  int animation_frame;
  vector<vector<myHareSampleItem>> inventory;
  mySampleVector other_inventory;
};

struct Item {
public:
    string name;
};

typedef int32_t my_type;

class Character {
public:
  my_type character_id;
  double x;
  double y;
  double z;
  double vx;
  double vy;
  double vz;
  float angle;
  enum Animation {Standing=0,Walking=1, Running=2} anim;
  int animation_frame;
  vector<Item> inventory;
};


typedef struct _Some {int i;} Some;

typedef struct {int i;} AnonSome;

typedef Character MyCharacter;

#endif // SAMPLE_WITH_CPP_H_INCLUDED
