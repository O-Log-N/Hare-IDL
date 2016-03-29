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

class CharacterSet {
    /*TBD*/
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
    enum KIND { ENUM, NAMED_TYPE, SEQUENCE, ENCODING_SPECIFIC, MAPPING_SPECIFIC,
        INTEGER, FIXED_POINT, FLOATING_POINT, CHARACTER, CHARACTER_STRING, BIT_STRING, DICTIONARY};
    KIND kind = NAMED_TYPE;
	string name;
    unique_ptr<DataType> keyType;
    unique_ptr<DataType> paramType;
    Limit lowLimit;
    Limit highLimit;
    double fixedPrecision = 0;
    int floatingSignificandBits = 0; /* TODO check type */
    int floatingExponentBits = 0;    /* TODO check type */
    CharacterSet characterSet;
    int stringMinSize = 0;          /* TODO check type */
    int stringMaxSize = 0;          /* TODO check type */

    map<string,Variant> encodingAttrs;
    map<string,Variant> mappingAttrs;
	map<string, int> enumValues;

	DataType() {}
    DataType(const DataType& other)
        : kind(other.kind), name(other.name),
        keyType(other.keyType != nullptr ? new DataType(*(other.keyType)) : nullptr),
        paramType(other.paramType != nullptr ? new DataType(*(other.paramType)) : nullptr),
        lowLimit(other.lowLimit), highLimit(other.highLimit),
        fixedPrecision(other.fixedPrecision), floatingSignificandBits(other.floatingSignificandBits),
        floatingExponentBits(other.floatingExponentBits), characterSet(other.characterSet),
        stringMinSize(other.stringMinSize), stringMaxSize(other.stringMaxSize),
        encodingAttrs(other.encodingAttrs), mappingAttrs(other.mappingAttrs),
        enumValues(other.enumValues) {}

	DataType& operator = ( const DataType& other )
	{
		kind = other.kind;
		name = other.name;
        keyType.reset(other.keyType != nullptr ? new DataType(*(other.keyType)) : nullptr );
        paramType.reset(other.paramType != nullptr ? new DataType(*(other.paramType)) : nullptr);
        lowLimit = other.lowLimit;
		highLimit = other.highLimit;
        fixedPrecision = other.fixedPrecision;
        floatingSignificandBits = other.floatingSignificandBits;
        floatingExponentBits = other.floatingExponentBits;
        characterSet = other.characterSet;
        stringMinSize = other.stringMinSize;
        stringMaxSize = other.stringMaxSize;
		encodingAttrs = other.encodingAttrs;
		mappingAttrs = other.mappingAttrs;
		enumValues = other.enumValues;
		return *this;
	}

    DataType(DataType&& other)
        : kind(other.kind), name(other.name),
        keyType(other.keyType != nullptr ? std::move(other.keyType) : nullptr),
        paramType(other.keyType != nullptr ? std::move(other.paramType) : nullptr),
        lowLimit(other.lowLimit), highLimit(other.highLimit),
        fixedPrecision(other.fixedPrecision), floatingSignificandBits(other.floatingSignificandBits),
        floatingExponentBits(other.floatingExponentBits), characterSet(other.characterSet),
        stringMinSize(other.stringMinSize), stringMaxSize(other.stringMaxSize),
        encodingAttrs(other.encodingAttrs), mappingAttrs(other.mappingAttrs),
        enumValues(other.enumValues) {}

    DataType& operator = (DataType&& other)
	{
		kind = other.kind;
		name = other.name;
        keyType = std::move(other.keyType);
        paramType = std::move(other.paramType);
        lowLimit = other.lowLimit;
		highLimit = other.highLimit;
        fixedPrecision = other.fixedPrecision;
        floatingSignificandBits = other.floatingSignificandBits;
        floatingExponentBits = other.floatingExponentBits;
        characterSet = other.characterSet;
        stringMinSize = other.stringMinSize;
        stringMaxSize = other.stringMaxSize;
		encodingAttrs = other.encodingAttrs;
		mappingAttrs = other.mappingAttrs;
		enumValues = other.enumValues;
		return *this;
	}

};

class EncodingSpecifics
{
public:
	string name;
	map<string, Variant> attrs;
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
    vector<string> whenDiscriminant;
};

class EncodedMembers : public EncodedOrMember
{
public:
    EncodingSpecifics encodingSpecifics;
	vector<unique_ptr<EncodedOrMember>> members;
};


class Structure : public EncodedMembers
{
public:
	enum DECLTYPE{ IDL, MAPPING, ENCODING };
	enum TYPE{ STRUCT, RPC, DISCRIMINATED_UNION };
	DECLTYPE declType = IDL;
	TYPE type = STRUCT;
	string name;
    string discriminant;    
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
