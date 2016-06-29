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

#ifndef SAMPLE_H
#define SAMPLE_H


#include <string>
#include <vector>

#include "hare/hareidl.h"

using namespace std;


struct Item {
	uint8_t id;
  string name;
  bool valid;
};

struct Character {

  uint8_t max_u8;
  uint16_t max_u16;
//  uint32_t max_u32;
//  uint64_t max_u64;

  int8_t min_s8;
  int16_t min_s16;
  int32_t min_s32;
//  int64_t min_s64;

  int8_t max_s8;
  int16_t max_s16;
  int32_t max_s32;
//  int64_t max_s64;

  double x;
  double y;
  double z;

//  float angle;

  //enum Animation {Standing=0,Walking=1, Running=2} anim;

  bool flag;

  string desc;

  vector<string> more_text;
  vector<int16_t> some_ints;

//  Item item;
//  vector<Item> inventory;
};

#endif // SAMPLE_H
