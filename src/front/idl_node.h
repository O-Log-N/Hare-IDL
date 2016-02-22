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

#ifndef IDL_NODE_H_INCLUDED
#define IDL_NODE_H_INCLUDED "include guard"

#include "common.h"
#include "base_node.h"


class FileNode : public Node
{
public:
	const std::string fileName; // must be const, so we can use c_str() pointer in Location
	ChildList<Node> items;
	bool isInternalFile;

	FileNode(const std::string& fileName) : fileName(fileName), items(this), isInternalFile(false) {}
	FileNode(const FileNode&) = delete;

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		Node::walk(walker);
		walker.walkChild(this, items);
	}

};

class RootNode : public Node
{
public:
	ChildList<FileNode> files;

	RootNode() :files(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		Node::walk(walker);
		walker.walkChild(this, files);
	}

};

class PublishableStructDeclNode : public DeclarationNode
{
public:
	std::string name;
	ChildList<AttributeDeclNode> attributes;

	PublishableStructDeclNode() :attributes(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		DeclarationNode::walk(walker);
		walker.walkChild(this, attributes);
	}

	virtual void dbgDump(std::ostream& os) const {
		dbgDumpAttribute(os, "name", name);
	}
};

class AttributeDeclNode : public DeclarationNode
{
public:
	std::string name;

	Child<TypeNode> type;

	AttributeDeclNode() : type(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		DeclarationNode::walk(walker);
		walker.walkChild(this, type);
	}

	virtual void dbgDump(std::ostream& os) const {
		dbgDumpAttribute(os, "name", name);
	}
};


class FencedAttributeDeclNode : public AttributeDeclNode
{
public:
	Child<TypeNode> extended_type;
	Child<ExpressionNode> default_value;

	FencedAttributeDeclNode() :extended_type(this), default_value(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		AttributeDeclNode::walk(walker);
		walker.walkChild(this, extended_type);
		walker.walkChild(this, default_value);
	}
};


class FenceDeclNode : public DeclarationNode
{
public:
	ChildList<FencedAttributeDeclNode> attributes;

	FenceDeclNode() :attributes(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		DeclarationNode::walk(walker);
		walker.walkChild(this, attributes);
	}
};

class EncodingDeclNode : public DeclarationNode
{
public:
	std::string name;
	std::string encoding;
	ChildList<AttributeDeclNode> attributes;
	ChildList<FenceDeclNode> fences;

	EncodingDeclNode() :attributes(this), fences(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		DeclarationNode::walk(walker);
		walker.walkChild(this, attributes);
		walker.walkChild(this, fences);
	}

	virtual void dbgDump(std::ostream& os) const {
		dbgDumpAttribute(os, "name", name);
		dbgDumpAttribute(os, "encoding", encoding);
	}
};

class MappingDeclNode : public DeclarationNode
{
public:
	std::string name;
	std::vector<std::string> tags;
	ChildList<AttributeDeclNode> attributes;

	MappingDeclNode() :attributes(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		DeclarationNode::walk(walker);
		walker.walkChild(this, attributes);
	}

	virtual void dbgDump(std::ostream& os) const {
		dbgDumpAttribute(os, "name", name);
		dbgDumpAttribute(os, "tags", tags);
	}
};




class NameTypeNode : public TypeNode
{
public:
	std::string name;

	NameTypeNode() {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }

	virtual std::string toString() const {
		return name;
	}
};


class NumericTypeNode : public TypeNode
{
public:
	bool low_open;
	bool high_open;
	double low_value;
	double high_value;
	ChildList<ExpressionNode> arguments;

	NumericTypeNode() : low_open(false), high_open(false),
		low_value(0), high_value(0), arguments(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		TypeNode::walk(walker);
		walker.walkChild(this, arguments);
	}
	virtual std::string toString() const { return "NUMERIC"; }

};

class IntTypeNode : public TypeNode
{
public:
	bool low_open;
	bool high_open;
	long long low_value;
	long long high_value;
	ChildList<ExpressionNode> arguments;

	IntTypeNode() : low_open(false), high_open(false),
		low_value(0), high_value(0), arguments(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		TypeNode::walk(walker);
		walker.walkChild(this, arguments);
	}

	virtual std::string toString() const { return "INT"; }
};

class FixedPointTypeNode : public TypeNode
{
public:
	double value;
	ChildList<ExpressionNode> arguments;

	FixedPointTypeNode() : value(0), arguments(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		TypeNode::walk(walker);
		walker.walkChild(this, arguments);
	}

	virtual std::string toString() const { return "FIXED_POINT"; }
};

class BitTypeNode : public TypeNode
{
public:
	long long value;
	ChildList<ExpressionNode> arguments;

	BitTypeNode() : value(0), arguments(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		TypeNode::walk(walker);
		walker.walkChild(this, arguments);
	}

	virtual std::string toString() const { return "BIT"; }
};

class SequenceOfTypeNode : public TypeNode
{
public:
	Child<TypeNode> type;

	SequenceOfTypeNode() :type(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		TypeNode::walk(walker);
		walker.walkChild(this, type);
	}

	virtual std::string toString() const {
		return "SEQUENCE< " + type->toString() + " >";
	}

};

class ClassRefTypeNode : public TypeNode
{
public:
	std::string name;

	ClassRefTypeNode() {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }

	virtual std::string toString() const {
		return "class " + name;
	}

};

class InlineEnumTypeNode : public TypeNode
{
public:
	std::string name;
	ChildList<EnumValueDeclNode> values;

	InlineEnumTypeNode() :values(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		TypeNode::walk(walker);
		walker.walkChild(this, values);
	}

	virtual std::string toString() const { return "enum " + name; }
};

class EnumValueDeclNode : public DeclarationNode
{
public:
	std::string name;
	Child<ExpressionNode> value;

	EnumValueDeclNode() :value(this) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
	virtual void walk(NodeWalker& walker) {
		DeclarationNode::walk(walker);
		walker.walkChild(this, value);
	}

	virtual std::string toString() const { return "enum " + name; }

};

class IdentifierExprNode : public ExpressionNode
{
public:
	std::string name;

	Node* resolved;

	IdentifierExprNode() : resolved(0) {}

	virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }

	virtual void dbgDump(std::ostream& os) const {
		dbgDumpAttribute(os, "name", name);
		dbgDumpResolved(os, resolved);
	}
};

#endif // IDL_NODE_H_INCLUDED
