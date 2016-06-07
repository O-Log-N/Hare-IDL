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
	map<string, string> annotation;
	BackEncodedOrMember* idlRepresentation = nullptr;
	BackEncodedOrMember* mappingRepresentation = nullptr;
	BackEncodedOrMember* encodingRepresentation = nullptr;

	BackEncodedOrMember() {parent = NULL;}
	virtual ~BackEncodedOrMember(){} 
	BackEncodedMembers* getParent() {return parent;}
};


class BackDataMember : public BackEncodedOrMember
{
public:
	DataType type; 
	string name; 
    bool extendTo = false;
    Variant defaultValue;
    vector<string> whenDiscriminant;
};

class BackEncodedMembers : public BackEncodedOrMember 
{
protected:
	vector<unique_ptr<BackEncodedOrMember>> members; 
public:
	void addChild( BackEncodedOrMember* child )
	{
		parent = this;
		members.push_back( unique_ptr<BackEncodedOrMember>(child) );
	}
	size_t getChildCount() const
	{
		return members.size();
	}
	const BackEncodedOrMember* getConstMember( unsigned int childIndex ) const
	{
		assert( childIndex < members.size() );
		return &(*members[childIndex]);
	}
	BackEncodedOrMember* getMember( unsigned int childIndex )
	{
		assert( childIndex < members.size() );
		return &(*members[childIndex]);
	}
	void moveMembersFrom( BackEncodedMembers& other )
	{
		members = std::move( other.members );
	}
};

class BackStructure : public BackEncodedMembers 
{
public:
	Structure::DECLTYPE declType; 
	Structure::TYPE type; 
	string name; 
    string discriminant; // used with type == Structure::TYPE::DISCRIMINATED_UNION
	string inheritedFrom;
	BackStructure* inheritanceBase = nullptr;
	vector<BackStructure*> derived;
    map<string, uint32_t> derivedObjDiscriminatorValues;
	bool manuallyAdded = false;
};

class BackRoot
{
public:
	vector<unique_ptr<BackStructure>> structuresIdl;
	vector<unique_ptr<BackStructure>> structuresMapping;
	vector<unique_ptr<BackStructure>> structuresEncoding;
};


void convertToBackTree( const Root& root, BackRoot& backRoot );


#endif // BACK_IDL_TREE_H