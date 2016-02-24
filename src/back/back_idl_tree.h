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

#ifndef BACK_IDL_TREE_H
#define BACK_IDL_TREE_H

#include "../idlc_include.h"
#include "../front-back/idl_tree.h"

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
protected:
	vector<unique_ptr<BackEncodedOrMember>> members; 
public:
	EncodingAttributes encodingAttr; 
	void addChild( BackEncodedOrMember* child )
	{
		parent = this;
		members.push_back( unique_ptr<BackEncodedOrMember>(child) );
	}
	unsigned int getChildCount()
	{
		return members.size();
	}
	bool isChildAMember( unsigned int childIndex ) const
	{
		return childIndex < members.size() && dynamic_cast<const BackDataMember*>( &(*members[childIndex])) != NULL;
	}
	const BackDataMember* getConstMember( unsigned int childIndex ) const
	{
		if ( childIndex >= members.size() ) return NULL;
		return dynamic_cast<const BackDataMember*>( &(*members[childIndex]));
	}
	BackDataMember* getMember( unsigned int childIndex )
	{
		if ( childIndex >= members.size() ) return NULL;
		return dynamic_cast<BackDataMember*>( &(*members[childIndex]));
	}
	const BackEncodedMembers* getConstEncodedMembers( unsigned int childIndex ) const
	{
		if ( childIndex >= members.size() ) return NULL;
		return dynamic_cast<const BackEncodedMembers*>( &(*members[childIndex]));
	}
	BackEncodedMembers* getEncodedMembers( unsigned int childIndex )
	{
		if ( childIndex >= members.size() ) return NULL;
		return dynamic_cast<BackEncodedMembers*>( &(*members[childIndex]));
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


void convertToBackTree( const Root& root, BackRoot& backRoot );


#endif // BACK_IDL_TREE_H