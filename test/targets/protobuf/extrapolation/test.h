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

#ifndef TEST_H
#define TEST_H


#include <string>
#include <vector>
#include <memory>

#include "hare/hareidl.h"

using namespace std;



struct TestExtrapolation {

  size_t tick = 0;

  HARE_ANNOTATION("OPTIONAL") int64_t optInteger = 0;
  HARE_ANNOTATION("OPTIONAL") float optFloat = 0;
  HARE_ANNOTATION("OPTIONAL") double optDouble = 0;
};


#endif // TEST_H
