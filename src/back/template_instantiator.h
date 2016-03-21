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

class TemplateInstantiator
{
protected:
	struct StackElement
	{
		ARGTYPE argtype = ARGTYPE::NO_ARGTYPE; // for operation PUSH: any but NONE
		double numberValue = 0; // argtype: ARGTYPE::NUMBER
		bool boolValue = false; // argtype: ARGTYPE::BOOL
		vector<LinePart> lineParts; // used for ARGTYPE::STRING
		vector<unique_ptr<TemplateInstantiator>> objects; // used for ARGTYPE::OBJPTR_LIST
		unique_ptr<TemplateInstantiator> singleObject = nullptr;
		StackElement() {}
		StackElement ( StackElement & other ) = delete; 
		StackElement ( StackElement && other ) : 
			argtype( other.argtype ), numberValue( other.numberValue ), boolValue( other.boolValue ), 
			lineParts( std::move(other.lineParts) ), objects( std::move(other.objects) ), singleObject( std::move(other.singleObject) ) {}
	};
	typedef vector<StackElement> Stack;

protected:
	virtual void execBuiltinFunction( Stack& stack, PREDEFINED_FUNCTION fnID );
	bool calcConditionOfIfNode( TemplateNode& ifNode );
	void evaluateExpression( const vector<ExpressionElement>& expression, Stack& stack );
	void applyNode( TemplateNode& node );
	virtual string context();
	string resolveLinePartsToString( const vector<LinePart>& lineParts );

	FILE* outstr;
	TemplateNodeSpace& templateSpace;
	map<string, string> resolvedPlaceholders; // those starting from "@PARAM-"

public:
	TemplateInstantiator( TemplateNodeSpace& templateSpace_, FILE* outStr ) : templateSpace( templateSpace_ ), outstr( outStr ) {}

	virtual string placeholder( Placeholder ph );
	virtual ~TemplateInstantiator() {}
};


#endif // TEMPLATE_INSTANTIATOR_H
