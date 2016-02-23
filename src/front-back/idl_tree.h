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

#if !defined __IDL_TREE_H__
#define __IDL_TREE_H__

#include <memory>
#include <vector>
using namespace std;

class DataType
{
public:
	std::string name; 
	// ... (details to be developed)

	DataType() {}
	DataType( const DataType& other )
	{
		name = other.name;
		// ...
	}
	DataType& operator = ( const DataType& other )
	{
		name = other.name;
		// ... (details to be developed)
	}
};

class EncodingAttributes
{
public:
	string name; 
	// ...

	EncodingAttributes() {}
	EncodingAttributes( const EncodingAttributes& other )
	{
		name = other.name;
		// ... (details to be developed)
	}
	EncodingAttributes& operator = ( const EncodingAttributes& other )
	{
		name = other.name;
		// ...
	}
};


class EncodedOrMember
{
public:
	~EncodedOrMember(){} 
	virtual bool isMember() const;
};

class DataMember : public EncodedOrMember
{
public:
	virtual bool isMember() const {return true;}
	DataType type; 
	string name; 
};

class EncodedMembers : public EncodedOrMember 
{
public:
	EncodingAttributes encodingAttr; 
	vector<unique_ptr<EncodedOrMember>> members; 
	virtual bool isMember() const {return false;}
};


enum STRUCTURE_DECLARATION_TYPE{ declIDL, declMapping, declEncoding }; 
enum STRUCTURE_TYPE{ typeStruct, typeRPC }; 
class Structure : public EncodedMembers 
{
public:
	STRUCTURE_DECLARATION_TYPE declType; 
	STRUCTURE_TYPE structureType; 
	string name; 
};

typedef vector<unique_ptr<Structure>> VectorOfStructures;

#endif // __IDL_TREE_H__