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


#ifndef HAREIDL_H_INCLUDED
#define HAREIDL_H_INCLUDED

#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>


//#define HAREIDL_USE_GCC_ANNOTATE
//#define HAREIDL_USE_CXX11_ATTRIBUTE

#ifdef HAREIDL_USE_GCC_ANNOTATE
#define HAREIDL(X) __attribute__((annotate("hare::" #X )))
#else

#ifdef HAREIDL_USE_CXX11_ATTRIBUTE
#define HAREIDL(X) [[hare:: X ]]
#else
#define HAREIDL(X)
#endif

#endif

typedef uint8_t hare_uint8_t;
typedef int8_t hare_int8_t;
typedef uint16_t hare_uint16_t;
typedef int16_t hare_int16_t;
typedef uint32_t hare_uint32_t;
typedef int32_t hare_int32_t;
typedef uint64_t hare_uint64_t;
typedef int64_t hare_int64_t;
typedef bool hare__Bool;
typedef float hare_float;
typedef double hare_double;
typedef std::string hare_string;

typedef std::unique_ptr<int> hare_sequence_unique_ptr;
typedef std::vector<int> hare_sequence_vector;
typedef std::list<int> hare_sequence_list;

typedef std::map<int,int> hare_dictionary_map;

//template < class T, class Allocator >
//using hare_sequence_vector = std::vector<T, Allocator>;


#endif // HAREIDL_H_INCLUDED
