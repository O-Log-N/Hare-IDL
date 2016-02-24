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

#if !defined BACK_IDL_TREE_H
#define BACK_IDL_TREE_H

#include <idl_tree.h>

class BackEncodedMembers;

class BackEncodedOrMember
{
protected:
	BackEncodedMembers* parent;
public:
	BackEncodedOrMember() {parent = NULL;}
	virtual ~BackEncodedOrMember(){} 
	BackEncodedMembers* getParent() {return parent;}
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
	void addChild( BackEncodedOrMember* child )
	{
		parent = this;
		members.push_back( unique_ptr<BackEncodedOrMember>(child) );
	}
};

class BackStructure : public BackEncodedMembers 
{
public:
	Structure::DECLTYPE declType; 
	Structure::TYPE type; 
	string name; 
};

class BackRoot
{
public:
	vector<unique_ptr<BackStructure>> structures;
};

//typedef vector<unique_ptr<BackStructure>> VectorOfBackStructures;

#endif // BACK_IDL_TREE_H