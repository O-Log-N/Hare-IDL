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


// HAREIDL_USE_CXX11_ATTRIBUTE is internally defined by C++2HareIdl tool

#ifdef HAREIDL_USE_CXX11_ATTRIBUTE
#define HAREIDL(X) [[hare:: X ]]
#define HARE_MAPPING(X) [[hare::mapping(X)]]
#else
#define HAREIDL(X)
#define HARE_MAPPING(X)
#endif

#endif


typedef uint8_t hare_mapping_uint8_t;
typedef int8_t hare_mapping_int8_t;
typedef uint16_t hare_mapping_uint16_t;
typedef int16_t hare_mapping_int16_t;
typedef uint32_t hare_mapping_uint32_t;
typedef int32_t hare_mapping_int32_t;
typedef uint64_t hare_mapping_uint64_t;
typedef int64_t hare_mapping_int64_t;

typedef bool hare_mapping_bool;
typedef float hare_mapping_float;
typedef double hare_mapping_double;
typedef std::string hare_mapping_string;

// std::vector<bool> is specialized so it needs special treatment
typedef std::vector<bool> hare_vectorbool_vector;

typedef std::unique_ptr<void*> hare_owning_ptr_unique_ptr;

typedef std::vector<void*> hare_sequence_vector;
typedef std::list<void*> hare_sequence_list;

typedef std::map<void*, void*> hare_dictionary_map;


/*
Use this type alias samples, to allow to use std:: namespace


using hare_mapping_uint8_t = uint8_t;
using hare_mapping_int8_t = int8_t;
using hare_mapping_uint16_t = uint16_t;
using hare_mapping_int16_t = int16_t;
using hare_mapping_uint32_t = uint32_t;
using hare_mapping_int32_t = int32_t;
using hare_mapping_uint64_t = uint64_t;
using hare_mapping_int64_t = int64_t;
using hare_mapping_bool = bool;
using hare_mapping_float = float;
using hare_mapping_double = double;
using hare_mapping_string HARE_MAPPING("std::string") = std::string;

// std::vector<bool> is specialized so it needs special treatment
using hare_vectorbool_vector HARE_MAPPING("std::vector") = std::vector<bool>;

using hare_owning_ptr_unique_ptr HARE_MAPPING("std::unique_ptr") = std::unique_ptr<void*>;

using hare_sequence_vector HARE_MAPPING("std::vector") = std::vector<void*>;
using hare_sequence_list = std::list<void*>;

using hare_dictionary_map HARE_MAPPING("std::map") = std::map<void*, void*>;
*/

#endif // HAREIDL_H_INCLUDED
