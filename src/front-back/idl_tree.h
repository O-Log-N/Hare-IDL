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

#ifndef IDL_TREE_H
#define IDL_TREE_H

#include "../idlc_include.h"

using namespace std;

class DataType
{
public:
	string name;
	// ... (details to be developed)

	DataType() {}
};

class EncodingAttributes
{
public:
	string name;
	// ... (details to be developed)

	EncodingAttributes() {}
};

struct Location {
	string fileName;
	int lineNumber;
	Location() : fileName(), lineNumber(0) {}
};

class EncodedOrMember
{
public:
	Location location;
	virtual ~EncodedOrMember(){}
};

class DataMember : public EncodedOrMember
{
public:
	DataType type;
	string name;
};

class EncodedMembers : public EncodedOrMember
{
public:
	EncodingAttributes encodingAttr;
	vector<unique_ptr<EncodedOrMember>> members;
};


class Structure : public EncodedMembers
{
public:
	enum DECLTYPE{ IDL, MAPPING, ENCODING };
	enum TYPE{ STRUCT, RPC };
	DECLTYPE declType;
	TYPE type;
	string name;
};

class Root
{
public:
	vector<unique_ptr<Structure>> structures;
};

#endif // IDL_TREE_H
