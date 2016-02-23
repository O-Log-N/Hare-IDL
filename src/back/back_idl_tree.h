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

#if !defined __BACK_IDL_TREE_H__
#define __BACK_IDL_TREE_H__

#include <idl_tree.h>

class BackEncodedOrMember
{
	BackEncodedOrMember* parent;
public:
	~BackEncodedOrMember(){} 
	virtual bool isMember();
};


class BackDataMember : public BackEncodedOrMember
{
public:
	DataType type; 
	string name; 
};

class BackEncodedMembers : public BackEncodedOrMember 
{
public:
	EncodingAttributes encodingAttr; 
	vector<unique_ptr<BackEncodedOrMember>> members; 
};

class BackStructure : public BackEncodedMembers 
{
public:
//	enum { declIDL, declMapping, declEncoding } declType; 
//	enum { typeStruct, typeRPC } type; 
	STRUCTURE_DECLARATION_TYPE declType; 
	STRUCTURE_TYPE structureType; 
	string name; 
};

typedef vector<unique_ptr<BackStructure>> VectorOfBackStructures;

#endif // __BACK_IDL_TREE_H__