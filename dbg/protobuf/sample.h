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
	string name;
};

struct Character {
  uint8_t idU8;
  uint16_t idU16;
  uint32_t idU32;
//  uint64_t idU64;

//  int8_t idS8;
//  int16_t idS16;
//  int32_t idS32;
//  int64_t idS64;

  double x;
  double y;
  double z;

  float angle;

  enum Animation {Standing=0,Walking=1, Running=2} anim;

  bool flag;

  string desc;

//  vector<Item> inventory;
};

#endif // SAMPLE_H
