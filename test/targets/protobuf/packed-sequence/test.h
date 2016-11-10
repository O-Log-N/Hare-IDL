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

  enum Values {Nothing = 0, First = 1, Second = 2};

  vector<string> unpackedStrings;
  
  vector<int16_t> packedVarInts;
  vector<double> packedDoubles;

  vector<Values> packedEnum;

  vector<bool> packedBool;
};

#endif // SAMPLE_H
