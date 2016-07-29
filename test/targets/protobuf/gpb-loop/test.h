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
#include <memory>

#include "hare/hareidl.h"

using namespace std;


struct TestClass {

  uint8_t max_u8 = 0;
  uint16_t max_u16 = 0;
  uint32_t max_u32 = 0;
  uint64_t max_u64 = 0;

  int8_t max_s8 = 0;
  int16_t max_s16 = 0;
  int32_t max_s32 = 0;
  int64_t max_s64 = 0;

  float aFloat = 0;
  double aDouble = 0;

  string description;

  enum Values {Nothing = 0, First = 1, Second = 2};

  Values aValue = Nothing;

  bool flag = false;
};

#endif // SAMPLE_H
