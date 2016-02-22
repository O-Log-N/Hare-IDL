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

#ifndef BASE_NODE_H_INCLUDED
#define BASE_NODE_H_INCLUDED "include guard"

#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include <sstream>

#include "common.h"
#include "forward_decl.h"
#include "visitor.h"


struct YyBase {
	Location location;
	YyBase();
	virtual ~YyBase() = 0;
private:
	YyBase(const YyBase&);
	YyBase& operator=(const YyBase&);
};


void dumpLeaks(std::ostream& os);
void setKeywordFlag(bool& flag, const Location& loc, const std::string& flagName);

template<class T>
std::string integerToString(T t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

template<class T>
std::string pairToString(const std::pair<T, T>& t)
{
	std::stringstream ss;
	ss << "< " << t.first << " , " << t.second << ">";
	return ss.str();
}

class Node;
class NodeVisitor;
class NodeWalker;
class ExpressionResolver;
class SyntaxCheckStack;
class PostCheckHelper;
class ClassDeclNode;
class TypeDeclNode;


struct ResolutionFlag {
private:
	friend struct ResolvingNow;
	enum ResolutionStates { Unresolved, ResolvingNow, Resolved, ResolutionError } resolutionState;
public:
	ResolutionFlag() : resolutionState(Unresolved) {}

	bool isResolvedState() const {
		return resolutionState != Resolved;
	}

	bool isUnresolved() const {
		return resolutionState == Unresolved;
	}

	void assertResolved() const;

	void setResolved() {
		ASSERT(resolutionState == ResolvingNow);
		resolutionState = Resolved;
	}

protected:
	void forceResolved() {
		ASSERT(resolutionState == Unresolved || resolutionState == ResolvingNow);
		resolutionState = Resolved;
	}
};

/**
RIIA for resolution.
*/
struct ResolvingNow {
	ResolutionFlag& flag;

	ResolvingNow(ResolutionFlag& flag, const Location& location) :flag(flag) {
		if (flag.resolutionState == ResolutionFlag::ResolvingNow)
			throwResolutionCycleException(location, "Resolution cycle detected");

		ASSERT(flag.resolutionState == ResolutionFlag::Unresolved);
		flag.resolutionState = ResolutionFlag::ResolvingNow;
	}

	ResolvingNow(ResolutionFlag& flag, const Location& location, const std::string& name) :flag(flag) {
		if (flag.resolutionState == ResolutionFlag::ResolvingNow)
			throwResolutionCycleException(location, "Resolution cycle detected while resolving '%s'", name);

		ASSERT(flag.resolutionState == ResolutionFlag::Unresolved);
		flag.resolutionState = ResolutionFlag::ResolvingNow;
	}

	~ResolvingNow() {
		if (flag.resolutionState == ResolutionFlag::ResolvingNow)
			flag.resolutionState = ResolutionFlag::ResolutionError;
	}

private:
	/* ResolutionCycleException is unknown in this header */
	void throwResolutionCycleException(const Location& location, const std::string& message) const;
	void throwResolutionCycleException(const Location& location, const std::string& message, const std::string& arg) const;

	ResolvingNow(const ResolvingNow&);
	ResolvingNow& operator=(const ResolvingNow&);
};

/**
	ResolvedType is the reference of a type resolution,
	used in declarations and general type references, but not on expressions.
	Expressions have much more complex type resolution flags.
	Using separate structures for types and expressions allows better flag control.
*/
struct ResolvedTypeVoid_t;

struct ResolvedType :ResolutionFlag {

	TypeDeclNode* declaration;
	bool isVoid;

public:
	bool isPrimitive;
	bool isConst;
	bool isRef;

	enum TypeCodes {
		Unknown = 0,
		NullType,
		BoolType,
		IntegerLiteralType, //int
		IntegerType, //INT<n,m>
		BitVectorType,
		TritVectorType,
		TupleType, //Pair<,>, Triple<,,>, Four<,,,>
		ArrayType
	} typeCode;

	enum DefaultModifier {
		NoDefault,
		NameDeclaration,
		TemplateArgument,
		FunctionReturn,
		FunctionArgument
	};

	ResolvedType() : declaration(0), isVoid(false), isPrimitive(false), isConst(false), isRef(false), typeCode(Unknown) {}
	ResolvedType(const ResolvedTypeVoid_t& isVoid) : declaration(0), isVoid(true), isPrimitive(false), isConst(false), isRef(false), typeCode(Unknown) {
		forceResolved();
	}

	TypeDeclNode* get() const {
		ASSERT(declaration);
		return declaration;
	};

	void initialize(TypeDeclNode* typeDecl, bool primitiveFlag) {
		ASSERT(!isVoid);
		declaration = typeDecl;
		setResolved();
		isPrimitive = primitiveFlag;
	}
	void initialize(const ResolvedType& rType);

	void setDefaultAndCheck(const Location& location, DefaultModifier defaultModifier);

	void setFlags(const Location& location, bool constFlag, bool refFlag) {
		isConst = constFlag;
		isRef = refFlag;
	}

	void setConst() { isConst = true; }

	std::string toString() const;

	void assertCheck() const {
		ASSERT(isVoid || declaration != 0);
	}
};

typedef ResolvedType Rtype;

struct CalculatedType {
public:
	static ResolvedType Void;
	static ResolvedType Null;
	static ResolvedType Bool;
	static ResolvedType Int;

	CalculatedType() {}
};

typedef CalculatedType Ctype;

class Node : public YyBase
{
public:
	static size_t nodeIdNext;
	const size_t nodeId;
	Node* parent;
public:
	Node() : nodeId(++nodeIdNext), parent(0) { ASSERT(nodeIdNext != 0); }
	Node(const Node&) = default;
	virtual ~Node() {}
private:
	//	Node(const Node& other);
	Node& operator=(const Node&) = delete;

public:
	/* visitors */
	virtual void visit(NodeVisitor& visitor) = 0;
	virtual void walk(NodeWalker& walker) {} //non-child default
	virtual Node* clone() const { assert(false); return 0; } //not used

	/* before resolution, syntax and consistency checks */
	virtual void checkSyntax(SyntaxCheckStack& stack) const {}

	/* build lookup tables */
	virtual void buildLookupTables() {}

	/* resolve */
	virtual void resolve() {}

	/* after resolution typed checks */
	virtual void checkTypes() {} /* not const, since type casting and/or convertions may apply */

	virtual void postCheck(PostCheckHelper& helper) {}

	//virtual Scope* getScope() const {
	//	if (!parent)
	//		return 0;
	//	return parent->getScope();
	//}

	//virtual NamedScope* getNamedScope() const {
	//	if (!parent)
	//		ASSERT(false);
	//	return parent->getNamedScope();
	//}

	//virtual RootContext* getRootContext() const {
	//	ASSERT(parent);
	//	return parent->getRootContext();
	//}

	/* dump node specific data */
	virtual void dump(std::ostream& os) const {}
	virtual void dumpSymbols(const std::string& prefix, std::ostream& os) const {}


protected:
	/* Commmon tasks helpers */
	void dumpResolved(std::ostream& os, const Node* resolved) const {
		if (resolved)
			os << " resolved=>#" << resolved->nodeId;
	}

	template<class T>
	void dumpAttribute(std::ostream& os, const char* name, const T& value) const {
		os << " " << name << "='" << value << "'";
	}

	template<class T>
	void dumpAttribute(std::ostream& os, const char* name, const std::vector<T>& values) const {
		os << " " << name << "='";
		for (auto it = values.begin(); it != values.end(); ++it) {
			if (it != values.begin())
				os << "','";
			os << *it;
		}
		os << "'";
	}

public:
	const Node* getRoot() const {

		const Node* current = this;
		while (current->parent)
			current = current->parent;

		return current;
	}

};


/*
	Always use with inheritance, to allow ResolutionChecker verification.
*/
class HasResolutionFlag
{
protected:
	ResolutionFlag rFlag;

	HasResolutionFlag() : rFlag() {}

public:
	bool isUnresolved() const {
		return rFlag.isUnresolved();
	}
};

class HasResolvedType
{
protected:
	ResolvedType cType;

public:
	HasResolvedType() : cType() {}

	bool isUnresolved() const {
		return cType.isUnresolved();
	}

	void assertResolved() const {
		cType.assertResolved();
	}

	const ResolvedType& getType() const {
		cType.assertResolved();
		cType.assertCheck();
		return cType;
	};
};

template <class T>
const ResolvedType& resolveGetType(T* node) {
	node->resolve();
	return node->getType();
}

class ExpressionNode : public Node, public HasResolvedType
{
public:
	bool hasParenthesis;
	bool lValueFlag;

	ExpressionNode() : hasParenthesis(false), lValueFlag(false) {}

	virtual ExpressionNode* clone() const { assert(false); return 0; }

	// All expressions must be resolved by its owner, to allow insertion of automatic conversions.
	virtual void resolve() { cType.assertResolved(); }
	virtual void resolveE(ExpressionResolver& resolver) {}

	/* special case to evaluate integer literals arithmetics */
	virtual IntegerLiteralExprNode* getIntegerLiteral() { return 0; }
	virtual const ExpressionNode* getConstantValue() const { return 0; }

	//	virtual ThisExprNode* getThis() { return 0; }
	bool isLvalue() const { cType.assertResolved(); return lValueFlag; }

	static void resolveExpression(std::unique_ptr<ExpressionNode>& expression);
	static void resolveExpressions(std::vector<std::unique_ptr<ExpressionNode> >& expressions);
};


class StatementNode : public Node
{
public:
	virtual StatementNode* clone() const { assert(false); return 0; }
};


class DeclarationNode : public Node
{
public:
	virtual DeclarationNode* clone() const { assert(false); return 0; }
	virtual std::string toString() const { return "<unknown>"; }

};

class TypeNode : public Node, public HasResolvedType
{
public:
	bool isConst;
	bool isRef;
	//enum TypeContext {
	//	MethodReturnType,
	//	MethodArgumentType,
	//	VariableDeclarationType
	//};

	TypeNode() : isConst(false), isRef(false) {}

	virtual TypeNode* clone() const { assert(false); return 0; }

	virtual std::string toString() const = 0;
	virtual void dump(std::ostream& os) const;

	virtual void resolveT(const InitializerNode* initializer) {} // = 0;
	virtual void resolve() { assertResolved(); }

	//	virtual TypeNode* deepClone() const = 0;

	std::string formatFlags(const std::string& baseName) const;


	void copy(const TypeNode* other) {
		this->isConst = other->isConst;
		this->isRef = other->isRef;
	}

	void addQualifier(const Location& loc, int token, const std::string& text);

	//static void resolveType(TypeNode* type, ExpressionNode* initializer, ResolvedType::DefaultModifier defaultModifier);
	//static void resolveType(TypeNode* type, ResolvedType::DefaultModifier defaultModifier) {
	//	resolveType(type, 0, defaultModifier);
	//}
};

class TypeDeclNode : public DeclarationNode, public HasResolvedType
{
public:
	std::string fullTypeName;
	ResolvedType::TypeCodes typeCode;

	TypeDeclNode() :typeCode(ResolvedType::Unknown) {}

	virtual void resolveType() = 0;
	virtual void resolve();

	const std::string& getFullTypeName() const {
		return fullTypeName;
	}

	//		void setTypeCode(const Location& loc, int token, const std::string& text);

	//		static std::string getArgumentsName(const std::vector<ResolvedType>& argTypes, const std::vector<int>& argValues);
};

#endif // BASE_NODE_H_INCLUDED
