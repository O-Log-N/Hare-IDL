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

#ifndef LITERAL_NODE_H_INCLUDED
#define LITERAL_NODE_H_INCLUDED "include guard"

#include <list>

#include "common.h"
#include "forward_decl.h"
#include "base_node.h"


bool isIntegerConstant(const ExpressionNode* expr);
const IntegerLiteralExprNode* getIntegerConstantExpression(const ExpressionNode* expr);
std::pair<bool, int> tryGetIntegerConstantValue(const ExpressionNode* expr);


class CalculatedBooleanExprNode;

class BooleanLiteralExprNode : public ExpressionNode
{
public:
	static const std::string booleanTrue;
	static const std::string booleanFalse;

	bool value;

	BooleanLiteralExprNode() :value(false) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }

	virtual void resolveE(ExpressionResolver& resolver) {
		cType.initialize(Ctype::Bool);
	}

	virtual void dump(std::ostream& os) const {
		dumpAttribute(os, "value", value ? booleanTrue : booleanFalse);
	}

	void setBooleanLiteral(bool value) { this->value = value; }
	void setBooleanLiteral(const char* text);
};


class IntegerLiteralExprNode : public ExpressionNode
{
public:
	typedef long long IntegerType;
	static const std::string integerMax;
	static const IntegerType intMax;
	static const IntegerType intMin;

	IntegerType value;

	IntegerLiteralExprNode() :value(0) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }

	virtual void resolveE(ExpressionResolver& resolver) {
		cType.initialize(Ctype::Int);
	}

	virtual void dump(std::ostream& os) const {
		dumpAttribute(os, "value", value);
	}

	virtual IntegerLiteralExprNode* getIntegerLiteral() { return this; }
	virtual const ExpressionNode* getConstantValue() const { return this; }

	void setIntegerLiteral(IntegerType value) {
		this->value = value;
	}
	void setIntegerLiteral(const std::string& textValue) {
		setIntegerLiteral(textToValue(location, textValue));
	}

	int getIntValue() const;

	static IntegerType textToValue(const Location& loc, const std::string& textValue);
	static int textToIntValue(const Location& loc, const std::string& textValue);
};


class FloatLiteralExprNode : public ExpressionNode
{
public:
	typedef double FloatType;
	//static const std::string integerMax;
	//static const IntegerType intMax;
	//static const IntegerType intMin;

	FloatType value;

	FloatLiteralExprNode() :value(0) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }

	virtual void resolveE(ExpressionResolver& resolver) {
		cType.initialize(Ctype::Int);
	}

	virtual void dump(std::ostream& os) const {
		dumpAttribute(os, "value", value);
	}

	//virtual IntegerLiteralExprNode* getIntegerLiteral() { return this; }
	//virtual const ExpressionNode* getConstantValue() const { return this; }

	void setFloatLiteral(FloatType value) {
		this->value = value;
	}
	void setFloatLiteral(const std::string& textValue) {
		setFloatLiteral(textToValue(location, textValue));
	}

	//IntegerType getValue() const {
	//	return integerValue;
	//}

	//int getIntValue() const;

	static FloatType textToValue(const Location& loc, const std::string& textValue);
};

/*
	IntegerCastExprNode
	Handles automatic integer casts, and has the target type as its own type
	Is needed by verilog to know the bit width of literal constants
*/
class IntegerCastExprNode : public ExpressionNode
{
public:
	Child<ExpressionNode> expression;

	IntegerCastExprNode() :expression(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		walker.walkChild(this, expression);
	}

	virtual void resolveE(ExpressionResolver& resolver) { cType.assertResolved(); }

	void setResolvedType(const ResolvedType& rtype) {
		cType = rtype;
	}

	static void insertLiteralCast(const ResolvedType& rtype, std::unique_ptr<ExpressionNode>& expr);
	static void insertIntExtension(const ResolvedType& rtype, std::unique_ptr<ExpressionNode>& expr);
};

#endif // LITERAL_NODE_H_INCLUDED
