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

#ifndef IDL_TREE_FINALIZER_H
#define IDL_TREE_FINALIZER_H

#include "../idlc_include.h"
#include "back_idl_tree.h"

enum class TREE_DATA_COMPLETION_SCENARIO
{
	IDL_MAP_ENC, // all present and are to be just matched
	IDL_ONLY, // idl -> mapping, idl -> encoding
	MAP_ONLY, // map -> idl -> encoding
	ENC_ONLY, // encoding -> idl -> mapping
	IDL_MAP, // {idl, mapping: matching}, idl -> encoding
	IDL_ENC, // {idl, encoding: matching}, idl -> mapping
	MAJOR_MAP_ENC, // mapping -> idl, {idl, encoding: matching}
	MAJOR_ENC_MAP, // encoding -> idl, {idl, mapping: matching}
};

enum class TREE_DATA_COMPLETION_OPERATION
{
	MATCH,
	OVERRIDE
};

TREE_DATA_COMPLETION_SCENARIO guessTreeScenario(const BackRoot& root);
void finalizeTree( BackRoot& root, TREE_DATA_COMPLETION_SCENARIO scenario );
void prevalidateTree( BackRoot& root );


#endif //IDL_TREE_FINALIZER_H