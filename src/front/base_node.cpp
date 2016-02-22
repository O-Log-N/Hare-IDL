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

#include "base_node.h"

#include <set>

//#include "declaration_node.h"
#include "error.h"
#include "debug.h"


using namespace std;

const bool enableLeakDetector = true;
set<YyBase*> leakDetector;

YyBase::YyBase()
{
	if (enableLeakDetector)
		leakDetector.insert(this);
}

YyBase::~YyBase()
{
	if (enableLeakDetector)
		leakDetector.erase(this);
}

size_t Node::nodeIdNext = 0;

void dumpLeaks(std::ostream& os)
{
	for (set<YyBase*>::const_iterator it = leakDetector.begin(); it != leakDetector.end(); ++it) {
		if (Node* n = dynamic_cast<Node*>(*it))
			dumpNode(os, n);
		else {
			(*it)->location.write(os);
			os << endl;
		}
	}
}


void setKeywordFlag(bool& flag, const Location& loc, const std::string& flagName)
{
	if (flag)
		reportWarning(loc, "Duplicated keyword '%s'.", flagName);
	else
		flag = true;
}


void ResolutionFlag::assertResolved() const
{
	if (resolutionState == ResolutionError)
		throw PreviousResolutionException();

	if (resolutionState != Resolved)
		ASSERT(false);

}

void ResolvingNow::throwResolutionCycleException(const Location& location, const std::string& message) const
{
	throw ResolutionCycleException(location, message);
}

void ResolvingNow::throwResolutionCycleException(const Location& location, const std::string& message, const std::string& arg) const
{
	throw ResolutionCycleException(location, formatMessage(message, arg));
}

struct ResolvedTypeVoid_t {} ResolvedTypeVoid;

void ResolvedType::setDefaultAndCheck(const Location& location, DefaultModifier defaultModifier)
{
	if ((defaultModifier != FunctionReturn) && isVoid)
		throw UnresolvedException(location, "Void only allowed as method return type.");
	if ((defaultModifier != NameDeclaration) && isConst && !isRef)
		throw UnresolvedException(location, "Non-reference const only allowed at declarations.");
}



std::string ResolvedType::toString() const
{
	if (isVoid)
		return "void";

	string s;

	if (isConst)
		s += "const ";

	s += declaration->getFullTypeName();

	if (isRef)
		s += "&";

	return s;
}


ResolvedType CalculatedType::Void(ResolvedTypeVoid);
ResolvedType CalculatedType::Null;
ResolvedType CalculatedType::Bool;
ResolvedType CalculatedType::Int;

//ResolvedType CalculatedType::IntegerLiteral;


void ResolvedType::initialize(const ResolvedType& rType)
{
	if (isVoid || declaration != 0 || isConst || isRef)
		ASSERT(false);


	isVoid = rType.isVoid;
	declaration = rType.declaration;
	isConst = rType.isConst; //
	isRef = rType.isRef;
	isPrimitive = rType.isPrimitive;
	typeCode = rType.typeCode;

	forceResolved();
}

//std::string CalculatedType::toString() const
//{
//	if(isVoid)
//		return "void";
//
//	//if (isNull())
//	//	return "null";
//
//	string s;
//	//if(isStaticConst)
//	//	s += "static const ";
//	if(isConst)
//		s += "const ";
//		
//
//	s += declaration->getFullTypeName().toString();
//	
//	return s;
//}


/* static */
void ExpressionNode::resolveExpression(std::unique_ptr<ExpressionNode>& expression)
{
	if (expression) {
		if (expression->isUnresolved()) {
			//ExpressionResolver resolver(expression);
			//{
			//	// in case we throw or cycle
			//	ResolvingNow rn(expression->cType, expression->location);
			//	expression->resolveE(resolver);
			//}

			//if (resolver.replaced) {
			//	resolveExpression(expression);
			//}
		}
	}
}

/* static */
void ExpressionNode::resolveExpressions(std::vector<std::unique_ptr<ExpressionNode> >& expressions)
{
	for (std::vector<std::unique_ptr<ExpressionNode> >::iterator it = expressions.begin(); it != expressions.end(); ++it) {
		if (*it)
			resolveExpression(*it);
	}
}


/* virtual */
void TypeNode::dump(std::ostream& os) const
{
	os << " type='" << toString() << "'";
	dumpResolved(os, cType.declaration); // May be NULL
}

std::string TypeNode::formatFlags(const std::string& baseName) const
{
	if (!isConst && !isRef)
		return baseName;
	else {
		string buffer;
		if (isConst)
			buffer.append("const ");
		buffer.append(baseName);
		if (isRef)
			buffer.append("&");

		return buffer;
	}
}

void TypeNode::addQualifier(const Location& loc, int token, const std::string& text)
{
	//switch (token) {
	//case KW_CONST:
	//	setKeywordFlag(isConst, loc, text);
	//	break;
	//case '&':
	//	setKeywordFlag(isRef, loc, text);
	//	break;
	//default:
	//	reportError(loc, "Keyword '%s' not allowed at primitive type.", text);
	//	break;
	//}
}

/* static */
//void TypeNode::resolveType(TypeNode* type, InitializerNode* initializer, ResolvedType::DefaultModifier defaultModifier)
//{
//	ASSERT(type);
//	type->resolveT(initializer);

//	type->cType.setDefaultAndCheck(type->location, defaultModifier);

//	if (initializer)
//		initializer->resolveInitializer(type->location, type->getType());
//}

/* virtual */
void TypeDeclNode::resolve()
{
	if (cType.isUnresolved()) {
		ResolvingNow rn(cType, location); // in case we throw or cycle

										  //access.setOwner(getNamedScope()->ownerTypeDecl);

		resolveType();
	}
}
