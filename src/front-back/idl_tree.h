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

struct Limit {
    bool inclusive = false;
    double value = 0;
};

struct Location {
	string fileName;
	int lineNumber = 0;
};

class Variant {
public:
    enum KIND {NONE, NUMBER, STRING};
    KIND kind = NONE;

    double numberValue = 0;
    string stringValue;
};

class DataType
{
public:
    enum KIND { PRIMITIVE, LIMITED_PRIMITIVE, ENUM, NAMED_TYPE, SEQUENCE, ENCODING_SPECIFIC, MAPPING_SPECIFIC };
    KIND kind = PRIMITIVE;
	string name;
    unique_ptr<DataType> paramType;
    Limit lowLimit;
    Limit highLimit;
    vector<pair<string,Variant> > encodingAttributes;
    vector<pair<string,Variant> > mappingAttributes;
	vector<pair<string, int> > enumValues;
};

class EncodingAttributes
{
public:
	string name;
	vector<pair<string, Variant> > encodingAttributes;
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
	bool extendTo = false;
	Variant defaultValue;
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
	DECLTYPE declType = IDL;
	TYPE type = STRUCT;
	string name;
	vector<pair<string, Variant> > encodingAttributes;
};

class Typedef {
// TBD
};

class Root
{
public:
    vector<Typedef> typedefs;
	vector<unique_ptr<Structure>> structures;
};

#endif // IDL_TREE_H
