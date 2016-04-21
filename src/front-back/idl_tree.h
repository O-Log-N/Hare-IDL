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

class CharacterRange {
public:
    uint32_t from = 0;
    uint32_t to = 0;

    CharacterRange(uint32_t from, uint32_t to) : from(from), to(to) {}
};

class CharacterSet {
public:
    vector<CharacterRange> ranges;
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
	string mappingName; // used for mapping only
	string encodingName; // used for encoding only
    unique_ptr<DataType> keyType;
    unique_ptr<DataType> paramType;
    Limit lowLimit;
    Limit highLimit;
    double fixedPrecision = 0;
    uint8_t floatingSignificandBits = 0; /* TODO check type */
    uint8_t floatingExponentBits = 0;    /* TODO check type */
    CharacterSet characterSet;
    uint32_t stringMinSize = 0;          /* TODO check type */
    uint32_t stringMaxSize = 0;          /* TODO check type */

    map<string,Variant> encodingAttrs;
    map<string,Variant> mappingAttrs;
	map<string, uint32_t> enumValues;

	DataType* idlRepresentation = nullptr;
	DataType* mappingRepresentation = nullptr;
	DataType* encodingRepresentation = nullptr;

	DataType() = default;
    DataType(const DataType& other)
        : kind(other.kind), name(other.name), mappingName(other.mappingName), encodingName(other.encodingName),
        keyType(other.keyType != nullptr ? new DataType(*(other.keyType)) : nullptr),
        paramType(other.paramType != nullptr ? new DataType(*(other.paramType)) : nullptr),
        lowLimit(other.lowLimit), highLimit(other.highLimit),
        fixedPrecision(other.fixedPrecision), floatingSignificandBits(other.floatingSignificandBits),
        floatingExponentBits(other.floatingExponentBits), characterSet(other.characterSet),
        stringMinSize(other.stringMinSize), stringMaxSize(other.stringMaxSize),
        encodingAttrs(other.encodingAttrs), mappingAttrs(other.mappingAttrs),
        enumValues(other.enumValues) ,
	    idlRepresentation( other.idlRepresentation ), mappingRepresentation( other.mappingRepresentation ), encodingRepresentation( other.encodingRepresentation ) {}

    DataType& operator = ( const DataType& other )
    {
        if(this != &other)
            *this = std::move(DataType(other));

        return *this;
    }

    DataType(DataType&& other) = default;
    DataType& operator = (DataType&& other) = default;
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
public:
    Location location;
    DataType type;
    string name;
};

class Root
{
public:
    vector<Typedef> typedefs;
	vector<unique_ptr<Structure>> structures;
};

inline
string locationToString(const Location& loc)
{
    if (!loc.fileName.empty()) {
        if (loc.lineNumber != 0)
            return fmt::format("@{}:{}", loc.fileName, loc.lineNumber);
        else
            return string("@") + loc.fileName;
    }
    else
        return "";
}


#endif // IDL_TREE_H
