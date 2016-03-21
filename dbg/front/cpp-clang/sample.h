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

#ifndef SAMPLE_H_INCLUDED
#define SAMPLE_H_INCLUDED

#include <cstdint>
#include <string>
#include <vector>

#include "hareidl.h"

using namespace std;

class myharesampleItem {
public:
    string name;
};
 

class myharesampleCharacter {
public:
  int character_id;//can be omitted, as default mapping
                      //  for UINT16 is UINT16
  double x;//all 'double' declarations can be omitted too
  double y;
  double z;
  double vx;
  double vy;
  double vz;
  float angle;//this is the only Encoding specification in this fragment
              //  which makes any difference compared to defaults
              // if we want angle to be double, we can omit it too
  enum Animation {Standing=0,Walking=1, Running=2} anim;
              //can be omitted too
  int animation_frame;//can be omitted, as
                        //  UINT8 is a default mapping for INT[0,120)

  vector<myharesampleItem> inventory;//can be also omitted,
                         //  as default mapping for SEQUENCE<Item>
                         //  is vector<Item>
};


#endif // SAMPLE_H_INCLUDED
