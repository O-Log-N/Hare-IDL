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
	YyBase(const YyBase&) = delete;
	YyBase& operator=(const YyBase&) = delete;
};


void dbgDumpLeaks(std::ostream& os);

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

class Node : public YyBase
{
public:
	static size_t nodeIdNext;
	const size_t nodeId;
	Node* parent;
public:
	Node() : nodeId(++nodeIdNext), parent(0) { HAREASSERT(nodeIdNext != 0); }
	virtual ~Node() {}

public:
	/* visitors */
	virtual void visit(NodeVisitor& visitor) = 0;
	virtual void walk(NodeWalker& walker) {} //non-child default

	/* before resolution, syntax and consistency checks */
//	virtual void checkSyntax(SyntaxCheckStack& stack) const {}

	/* build lookup tables */
	virtual void buildLookupTables() {}

	/* resolve */
	virtual void resolve() {}

	/* dbgDump node specific data */
	virtual void dbgDump(std::ostream& os) const {}

	const Node* getRoot() const {

		const Node* current = this;
		while (current->parent)
			current = current->parent;

		return current;
	}


protected:
	/* Commmon tasks helpers */
	void dbgDumpResolved(std::ostream& os, const Node* resolved) const {
		if (resolved)
			os << " resolved=>#" << resolved->nodeId;
	}

	template<class T>
	void dbgDumpAttribute(std::ostream& os, const char* name, const T& value) const {
		os << " " << name << "='" << value << "'";
	}

	template<class T>
	void dbgDumpAttribute(std::ostream& os, const char* name, const std::vector<T>& values) const {
		os << " " << name << "='";
		for (auto it = values.begin(); it != values.end(); ++it) {
			if (it != values.begin())
				os << "','";
			os << *it;
		}
		os << "'";
	}

};



class ExpressionNode : public Node
{
public:
	bool hasParenthesis;

	ExpressionNode() : hasParenthesis(false) {}

	/* special case to evaluate integer literals arithmetics */
	virtual IntegerLiteralExprNode* getIntegerLiteral() { return 0; }
	virtual const ExpressionNode* getConstantValue() const { return 0; }

};


class DeclarationNode : public Node
{
};

class TypeNode : public Node
{
public:
	TypeNode() {}

	virtual std::string toString() const = 0;
	virtual void dbgDump(std::ostream& os) const {
		os << " type='" << toString() << "'";
	}
};

#endif // BASE_NODE_H_INCLUDED
