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
    enum KIND { PLAIN, ENUM, CLASS, SEQUENCE, VECTOR } typeKind;
	string name;
	vector<float> arguments;
	vector<pair<string, int> > enumValues;

	DataType() : typeKind(PLAIN) {}
};

class EncodingAttributes
{
public:
	string name;
	vector<float> arguments;

	EncodingAttributes() {}
};

struct Location {
	string fileName;
	int lineNumber;

	Location() : lineNumber(0) {}
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
	bool extendTo;
	float defaulValue;

	DataMember() : extendTo(false), defaulValue(0) {}
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
	vector<string> tags;

	Structure(): declType(IDL), type(STRUCT) {}
};

class Root
{
public:
	vector<unique_ptr<Structure>> structures;
};

#endif // IDL_TREE_H
