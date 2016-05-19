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

#ifndef TEMPLATE_INSTANTIATOR_H
#define TEMPLATE_INSTANTIATOR_H

#include "../idlc_include.h"
#include "template_tree_builder.h"
#include "back_idl_tree.h"

class TemplateInstantiator;

class TemplateInstantiatorFactory
{
	friend class TemplateInstantiator;
public:
	struct StackElement//: public StackElementBase //: public BaseVariant
	{
		ARGTYPE argtype = ARGTYPE::NO_ARGTYPE; // for operation PUSH: any but NONE
		double numberValue = 0; // argtype: ARGTYPE::NUMBER
		bool boolValue = false; // argtype: ARGTYPE::BOOL
		vector<LinePart2> lineParts; // used for ARGTYPE::STRING
		unique_ptr<TemplateInstantiatorFactory> singleObject = nullptr; // used for ARGTYPE::OBJPTR
		vector<pair<StackElement, StackElement>> anyMap; // used for ARGTYPE::ANY_MAP
		vector<StackElement> anyList; // used for ARGTYPE::ANY_LIST

		StackElement() {}
		StackElement ( const StackElement & other ) :
			argtype( other.argtype ), numberValue( other.numberValue ), boolValue( other.boolValue ), lineParts( (other.lineParts) ), 
			singleObject( other.singleObject != nullptr ? (*other.singleObject).clone() : nullptr ), anyMap( other.anyMap ), anyList( other.anyList ) {}
		StackElement& operator = ( const StackElement & other )
		{
			argtype = other.argtype;
			numberValue = other.numberValue;
			boolValue = other.boolValue;
			lineParts = other.lineParts;
			singleObject.reset( other.singleObject != nullptr ? (*other.singleObject).clone() : nullptr ); 
			anyMap.clear();
			for ( const auto& itm:other.anyMap )
				anyMap.push_back( itm );
			anyList.clear();
			for ( const auto& itl:other.anyList )
				anyList.push_back( itl );
			return *this;
		}
		StackElement ( StackElement && other ) : 
			argtype( other.argtype ), numberValue( other.numberValue ), boolValue( other.boolValue ), lineParts( (other.lineParts) ), 
			singleObject( std::move(other.singleObject) ), anyMap( std::move(other.anyMap ) ), anyList( std::move(other.anyList ) ) {}
		StackElement& operator = ( StackElement && other ) {
			argtype = other.argtype;
			numberValue = other.numberValue;
			boolValue = other.boolValue;
			lineParts = (other.lineParts );
			singleObject = std::move(other.singleObject); 
			anyMap = std::move(other.anyMap); 
			anyList = std::move(other.anyList); 
			return *this;
		}
		// map operations
		bool operator == ( const StackElement& other ) const
		{
			if ( argtype != other.argtype ) return false;
			switch ( argtype )
			{
				case ARGTYPE::NO_ARGTYPE: return true;
				case ARGTYPE::NUMBER: return numberValue == other.numberValue; 
				case ARGTYPE::BOOL: return boolValue == other.boolValue; 
				case ARGTYPE::STRING:
				{
					// NOTE: we implement here a strict approach when all expressions inside a string are already calculated
					size_t sz = lineParts.size();
					if ( sz != other.lineParts.size() )
						return false;
					for ( size_t i=0; i<sz; ++i )
						if ( !( lineParts[i].isVerbatim && other.lineParts[i].isVerbatim && lineParts[i].verbatim == other.lineParts[i].verbatim ) )
							return false;
					return true;
				}
				case ARGTYPE::PLACEHOLDER:
				{
					assert( 0 ); // TODO: report internal error: unexpected type
					return false; 
				}
				case ARGTYPE::OBJPTR:
				case ARGTYPE::ANY_MAP:
				{
					assert( 0 == "Error: unsupported type" ); // TODO: report detailed error
					return false; 
				}
				default:
				{
					assert(0);
					return false;
				}
			}
		}

		// MAP FUNCTIONS
		void assignToMapElement( const StackElement& key, const StackElement& value )
		{
			for ( auto& it:anyMap )
				if ( it.first == key )
				{
					it.second = value;
					return;
				}
			anyMap.push_back( make_pair(key, value) );
		}
		void findInMap( const StackElement& key, StackElement& value )
		{
			for ( auto& it:anyMap )
				if ( it.first == key )
				{
					value = it.second;
					return;
				}
			value.argtype = ARGTYPE::NO_ARGTYPE;
		}
		void appendToList( const StackElement& value )
		{
			anyList.push_back( value );
		}

		// LIST FUNCTIONS
	};
	typedef vector<StackElement> Stack;

protected:
	FILE* outstr;
	TemplateNodeSpace& templateSpace;

public:
	TemplateInstantiatorFactory( const TemplateInstantiatorFactory& other ) = default;
	TemplateInstantiatorFactory( TemplateNodeSpace& templateSpace_, FILE* outStr ) : templateSpace( templateSpace_ ), outstr( outStr ) {}
	TemplateInstantiator* create();
	virtual TemplateInstantiatorFactory* clone() const {return new TemplateInstantiatorFactory( *this );}
	virtual ~TemplateInstantiatorFactory() {}

protected:
	virtual void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	virtual string context();
};


void processStructures( BackRoot& structure, TemplateNodeSpace& templateSpace );

class TemplateInstantiator
{
protected:
	typedef TemplateInstantiatorFactory::StackElement StackElement;
	typedef vector<TemplateInstantiatorFactory::StackElement> Stack;

protected:
	friend class TemplateInstantiatorFactory;
	friend void processStructures( BackRoot& structure, TemplateNodeSpace& templateSpace );
	FILE* outstr;
	TemplateNodeSpace& templateSpace;
	map<string, TemplateInstantiatorFactory::StackElement> resolvedParamPlaceholders; // those starting from "@PARAM-"
	map<string, TemplateInstantiatorFactory::StackElement> resolvedLocalPlaceholders; // those starting from "@LOCAL-"
	TemplateInstantiatorFactory::StackElement fromTemplate;

protected:
	void execBuiltinFunction( Stack& stack, PredefindedFunction fn );
	bool calcConditionOfIfNode( TemplateNode& ifNode );
	void evaluateExpression( const vector<ExpressionElement>& expression, Stack& stack );
	bool applyNode( TemplateNode& node );
	bool applyIncludeNode( TemplateNode& node, bool isReturning );
	TemplateNode* prepareDataForTemplateInclusion( TemplateInstantiator* instantiator, map<string, TemplateInstantiatorFactory::StackElement>& resolvedParamPlaceholdersToUse, TemplateNode& node, bool isReturning );
	string resolveLinePartsToString( const vector<LinePart2>& lineParts );
	string placeholderAsString( Placeholder ph );
	virtual string context();
	virtual TemplateInstantiatorFactory::StackElement placeholder( Placeholder ph );

public:
	TemplateInstantiator( TemplateNodeSpace& templateSpace_, FILE* outStr ) : templateSpace( templateSpace_ ), outstr( outStr ) {}
	virtual ~TemplateInstantiator() {}
};


void apply( BackRoot& structure, TemplateNodeSpace& templateSpace );

#endif // TEMPLATE_INSTANTIATOR_H
