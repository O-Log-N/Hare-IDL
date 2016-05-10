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
protected:
	FILE* outstr;
	TemplateNodeSpace& templateSpace;

public:
	TemplateInstantiatorFactory( const TemplateInstantiatorFactory& other ) = default;
	TemplateInstantiatorFactory( TemplateNodeSpace& templateSpace_, FILE* outStr ) : templateSpace( templateSpace_ ), outstr( outStr ) {}
	virtual TemplateInstantiator* create() const {assert(0); return nullptr;}
	virtual TemplateInstantiatorFactory* clone() const {return new TemplateInstantiatorFactory( *this );}
	virtual ~TemplateInstantiatorFactory() {}
};

class TemplateInstantiator
{
protected:
	struct StackElement//: public StackElementBase //: public BaseVariant
	{
		ARGTYPE argtype = ARGTYPE::NO_ARGTYPE; // for operation PUSH: any but NONE
		double numberValue = 0; // argtype: ARGTYPE::NUMBER
		bool boolValue = false; // argtype: ARGTYPE::BOOL
		vector<LinePart> lineParts; // used for ARGTYPE::STRING
		vector<unique_ptr<TemplateInstantiatorFactory>> objects; // used for ARGTYPE::OBJPTR_LIST
		unique_ptr<TemplateInstantiatorFactory> singleObject = nullptr; // used for ARGTYPE::OBJPTR
		vector<pair<StackElement, StackElement>> anyMap; // used for ARGTYPE::ANY_MAP

		StackElement() {}
		StackElement ( const StackElement & other ) :
			argtype( other.argtype ), numberValue( other.numberValue ), boolValue( other.boolValue ), lineParts( (other.lineParts) ), 
			singleObject( other.singleObject != nullptr ? (*other.singleObject).clone() : nullptr ), anyMap( other.anyMap )
		{
			for ( const auto& it:other.objects )
				if ( it != nullptr )
					objects.push_back( unique_ptr<TemplateInstantiatorFactory>( it->clone() ) );
		}
		StackElement& operator = ( const StackElement & other )
		{
			argtype = other.argtype;
			numberValue = other.numberValue;
			boolValue = other.boolValue;
			lineParts = other.lineParts;
			objects.clear();
			for ( const auto& it:other.objects )
				if ( it != nullptr )
					objects.push_back( unique_ptr<TemplateInstantiatorFactory>( it->clone() ) );
			singleObject.reset( other.singleObject != nullptr ? (*other.singleObject).clone() : nullptr ); 
			anyMap.clear();
			for ( const auto& itm:other.anyMap )
				anyMap.push_back( itm );
			return *this;
		}
		StackElement ( StackElement && other ) : 
			argtype( other.argtype ), numberValue( other.numberValue ), boolValue( other.boolValue ), lineParts( (other.lineParts) ), 
			objects( std::move(other.objects) ), singleObject( std::move(other.singleObject) ), anyMap( std::move(other.anyMap ) ) {}
		StackElement& operator = ( StackElement && other ) {
			argtype = other.argtype;
			numberValue = other.numberValue;
			boolValue = other.boolValue;
			lineParts = (other.lineParts );
			objects = std::move(other.objects); 
			singleObject = std::move(other.singleObject); 
			anyMap = std::move(other.anyMap); 
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
					// NOTE: we implement here a strict approach
					size_t sz = lineParts.size();
					if ( sz != other.lineParts.size() )
						return false;
					for ( size_t i=0; i<sz; ++i )
						if ( !( lineParts[i].type == other.lineParts[i].type && lineParts[i].verbatim == other.lineParts[i].verbatim ) )
							return false;
					return true;
				}
				case ARGTYPE::PLACEHOLDER:
				{
					assert( 0 ); // TODO: report internal error: unexpected type
					return false; 
				}
				case ARGTYPE::OBJPTR: return false; 
				case ARGTYPE::OBJPTR_LIST: return false; 
				case ARGTYPE::ANY_MAP: return false; 
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
		void insertToMap( const StackElement& key, const StackElement& value )
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
	};
	typedef vector<StackElement> Stack;

protected:
	virtual void execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID );
	bool calcConditionOfIfNode( TemplateNode& ifNode );
	void evaluateExpression( const vector<ExpressionElement>& expression, Stack& stack );
	void applyNode( TemplateNode& node );
	virtual string context();
	string resolveLinePartsToString( const vector<LinePart>& lineParts );
	string placeholderAsString( Placeholder ph );

	FILE* outstr;
	TemplateNodeSpace& templateSpace;
	map<string, StackElement> resolvedParamPlaceholders; // those starting from "@PARAM-"
	map<string, StackElement> resolvedLocalPlaceholders; // those starting from "@LOCAL-"

public:
	TemplateInstantiator( TemplateNodeSpace& templateSpace_, FILE* outStr ) : templateSpace( templateSpace_ ), outstr( outStr ) {}

	virtual StackElement placeholder( Placeholder ph );
	virtual ~TemplateInstantiator() {}
};

#endif // TEMPLATE_INSTANTIATOR_H
