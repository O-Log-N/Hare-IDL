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

#include "literal_node.h"

#include <memory>
#include <utility>

#include "error.h"
#include "visitor.h"


using namespace std;

bool isIntegerConstant(const ExpressionNode* expr)
{
	const ExpressionNode* ic = expr->getConstantValue();
	if (ic) {
		const IntegerLiteralExprNode* lit = dynamic_cast<const IntegerLiteralExprNode*>(ic);
		if (lit)
			return true;
	}

	return false;
}

const IntegerLiteralExprNode* getIntegerConstantExpression(const ExpressionNode* expr)
{
	const ExpressionNode* ic = expr->getConstantValue();
	if (ic) {
		const IntegerLiteralExprNode* lit = dynamic_cast<const IntegerLiteralExprNode*>(ic);
		if (lit)
			return lit;
	}

	return 0;
}

pair<bool, int> tryGetIntegerConstantValue(const ExpressionNode* expr)
{
	const ExpressionNode* ic = expr->getConstantValue();
	if (ic) {
		const IntegerLiteralExprNode* lit = dynamic_cast<const IntegerLiteralExprNode*>(ic);
		if (lit)
			return make_pair(true, lit->getIntValue());
	}

	return make_pair(false, 0);
}

const string BooleanLiteralExprNode::booleanTrue = "true";
const string BooleanLiteralExprNode::booleanFalse = "false";

void BooleanLiteralExprNode::setBooleanLiteral(const char* text)
{
	if (booleanTrue == text)
		value = true;
	else if (booleanFalse == text)
		value = false;
	else
		ASSERT(false);
}

static_assert(sizeof(long long) == 8, "type 'long long' must have 64 bits");

const string IntegerLiteralExprNode::integerMax = "9223372036854775807"; //64 bit signed max
const IntegerLiteralExprNode::IntegerType IntegerLiteralExprNode::intMax = std::numeric_limits<int>::max();
const IntegerLiteralExprNode::IntegerType IntegerLiteralExprNode::intMin = std::numeric_limits<int>::min();


int IntegerLiteralExprNode::getIntValue() const
{
	if (value > intMax)
		reportError(location, "Integer literal overflows signed int max limit.");
	else if (value < intMin)
		reportError(location, "Integer literal overflows signed int min limit.");
	else
		return static_cast<int>(value);

	return 0;
}

/* static */
IntegerLiteralExprNode::IntegerType IntegerLiteralExprNode::textToValue(const Location& loc, const string& textValue)
{
	return atoll(textValue.c_str());
}

/* static */
int IntegerLiteralExprNode::textToIntValue(const Location& loc, const string& textValue)
{
	long long integerValue = textToValue(loc, textValue);

	ASSERT(integerValue >= 0LL);

	if (integerValue > intMax) {
		reportError(loc, "Integer literal overflows int signed limit.");
		return 0;
	}

	return static_cast<int>(integerValue);

}

/* static */
FloatLiteralExprNode::FloatType FloatLiteralExprNode::textToValue(const Location& loc, const string& textValue)
{
	return atof(textValue.c_str());
}

