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

#pragma once

#include "common.h"
#include "base_node.h"
//#include "declaration_node.h"


namespace hare
{


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

		//std::unique_ptr<NamedScope> named;
		//std::unique_ptr<RootContext> rootContext;

		//		std::unique_ptr<VerilogMapper> mapper;


		RootNode() :files(this) {}
		RootNode(const RootNode&) = delete;

		virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
		virtual void walk(NodeWalker& walker) {
			Node::walk(walker);
			walker.walkChild(this, files);
		}

		//virtual void buildLookupTables() {
			//ASSERT(!named);
			//named.reset(new NamedScope());

			//ASSERT(!rootContext);
			//rootContext.reset(new RootContext(this));

			//ASSERT(!mapper);
			//mapper.reset(new VerilogMapper());
		//}


		//virtual Scope* getScope() const { return 0; }

		//virtual NamedScope* getNamedScope() const {
		//	ASSERT(named);
		//	return named.get();
		//}

		//virtual RootContext* getRootContext() const {
		//	ASSERT(rootContext);
		//	return rootContext.get();
		//}

		//virtual void dumpSymbols(const std::string& prefix, std::ostream& os) const {
		//	//if (named)
		//	//	named->dump(prefix, os);
		//}
	};

	class PublishableStructDeclNode : public DeclarationNode
	{
	public:
		std::string name;
		ChildList<AttributeDeclNode> attributes;

		//std::unique_ptr<NamedScope> classScope;

		PublishableStructDeclNode() :attributes(this) {}

		virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
		virtual void walk(NodeWalker& walker) {
			DeclarationNode::walk(walker);
			walker.walkChild(this, attributes);
		}

		//virtual void checkSyntax(SyntaxCheckStack& stack) const;
		//virtual void buildLookupTables();
		//virtual void resolveType() {
		//	cType.initialize(this, false);
		//	cType.typeCode = typeCode;
		//}


		//virtual Scope* getScope() const {
		//	ASSERT(classScope);
		//	return 0;
		//}

		//virtual NamedScope* getNamedScope() const {
		//	ASSERT(classScope);
		//	return classScope.get();
		//}

		virtual void dump(std::ostream& os) const {
			dumpAttribute(os, "name", name);
		}

		//virtual void dumpSymbols(const std::string& prefix, std::ostream& os) const {
		//	//		if(classScope)
		//	//			classScope->dump(prefix, os);
		//}
		//virtual std::string toString() const {
		//	return name;
		//}

	};

	class AttributeDeclNode : public DeclarationNode, public HasResolutionFlag
	{
	public:
		std::string name;

		Child<TypeNode> type;
		//		std::unique_ptr<InitializerNode> initializer;

		//bool isStatic;
		//bool isMember;

		//bool useBuffered; //TODO improve

		AttributeDeclNode() : type(this) {}

		virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
		virtual void walk(NodeWalker& walker) {
			DeclarationNode::walk(walker);
			walker.walkChild(this, type);
			//			walker.walkChild(this, initializer);
		}
		//	virtual void checkSyntax(SyntaxCheckStack& stack) const;
		//virtual void buildLookupTables();
		//virtual void resolve();

		//virtual void checkTypes() {
		//	if (initializer)
		//		initializer->checkInitializer(location, getType());
		//}

		virtual void dump(std::ostream& os) const {
			dumpAttribute(os, "name", name);
		}
		//virtual std::string toString() const {
		//	return name;
		//}

		//AttributeDeclNode
		//virtual void checkVisibility(const Location& loc, const NamedScope* context, bool isSet) const;

		//const ResolvedType& getType() const {
		//	return type->getType();
		//}

		//const ExpressionNode* getConstantValue() const;


		//void setType(TypeNode* node) {
		//	setNodeParent(node);
		//	type.reset(node);
		//}
		//void setInitializer(InitializerNode* node) {
		//	setNodeParent(node);
		//	initializer.reset(node);
		//}

		//void addQualifier(const Location& loc, int token, const std::string& text);

		//void setMember() { isMember = true; }

		//AttributeDeclNode* templateClone() const {

		//	ASSERT(!initializer);
		//	std::unique_ptr<AttributeDeclNode> clone(new AttributeDeclNode());
		//	clone->location = this->location;
		//	//		clone->access = this->access;
		//	clone->name = this->name;
		//	clone->isStatic = this->isStatic;
		//	clone->isMember = this->isMember;

		//	//		clone->setType(this->type->deepClone());

		//	return clone.release();
		//}
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
		//	virtual void checkSyntax(SyntaxCheckStack& stack) const;
		//virtual void buildLookupTables();
		//virtual void resolve();

		//virtual void checkTypes() {
		//	if (initializer)
		//		initializer->checkInitializer(location, getType());
		//}

		//virtual void dump(std::ostream& os) const {
		//	dumpAttribute(os, "name", name);
		//}
		//virtual std::string toString() const {
		//	return name;
		//}

		//AttributeDeclNode
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

		//std::unique_ptr<NamedScope> classScope;

		EncodingDeclNode() :attributes(this), fences(this) {}

		virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
		virtual void walk(NodeWalker& walker) {
			DeclarationNode::walk(walker);
			walker.walkChild(this, attributes);
			walker.walkChild(this, fences);
		}

		//virtual void checkSyntax(SyntaxCheckStack& stack) const;
		//virtual void buildLookupTables();
		//virtual void resolveType() {
		//	cType.initialize(this, false);
		//	cType.typeCode = typeCode;
		//}


		//virtual Scope* getScope() const {
		//	ASSERT(classScope);
		//	return 0;
		//}

		//virtual NamedScope* getNamedScope() const {
		//	ASSERT(classScope);
		//	return classScope.get();
		//}

		virtual void dump(std::ostream& os) const {
			dumpAttribute(os, "name", name);
			dumpAttribute(os, "encoding", encoding);
		}

		//virtual void dumpSymbols(const std::string& prefix, std::ostream& os) const {
		//	//		if(classScope)
		//	//			classScope->dump(prefix, os);
		//}
		//virtual std::string toString() const {
		//	return name;
		//}
	};

	class MappingDeclNode : public DeclarationNode
	{
	public:
		std::string name;
		std::vector<std::string> tags;
		ChildList<AttributeDeclNode> attributes;

		//std::unique_ptr<NamedScope> classScope;

		MappingDeclNode() :attributes(this) {}

		virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
		virtual void walk(NodeWalker& walker) {
			DeclarationNode::walk(walker);
			walker.walkChild(this, attributes);
		}

		//virtual void checkSyntax(SyntaxCheckStack& stack) const;
		//virtual void buildLookupTables();
		//virtual void resolveType() {
		//	cType.initialize(this, false);
		//	cType.typeCode = typeCode;
		//}


		//virtual Scope* getScope() const {
		//	ASSERT(classScope);
		//	return 0;
		//}

		//virtual NamedScope* getNamedScope() const {
		//	ASSERT(classScope);
		//	return classScope.get();
		//}

		virtual void dump(std::ostream& os) const {
			dumpAttribute(os, "name", name);
			dumpAttribute(os, "tags", tags);
		}

		//virtual void dumpSymbols(const std::string& prefix, std::ostream& os) const {
		//	//		if(classScope)
		//	//			classScope->dump(prefix, os);
		//}
		//virtual std::string toString() const {
		//	return name;
		//}
	};




	class NameTypeNode : public TypeNode
	{
	public:
		std::string name;

		NameTypeNode() {}

		virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
		//virtual void walk(NodeWalker& walker) {
		//	TypeNode::walk(walker);
		//}

//		virtual void resolveT(const InitializerNode* initializer);
		virtual std::string toString() const {
			return name;
		}

		//virtual NameTypeNode* deepClone() const {
		//	NameTypeNode* node = new NameTypeNode();

		//	node->typeNodeClone(this);
		//	node->name = this->name;

		//	return node;
		//}
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
		//virtual NumberTypeNode* clone() const {
		//	return new NumberTypeNode(*this);
		//}

		//virtual void checkSyntax(SyntaxCheckStack& stack) const;
		//virtual void resolveT(const InitializerNode* initializer);
		virtual std::string toString() const { return "NUMERIC"; }

		//virtual NumberTypeNode* deepClone() const {
		//	NumberTypeNode* node = new NumberTypeNode();

		//	node->typeNodeClone(this);
		//	ASSERT(false);

		//	return node;
		//}
		//void setType(const Location& loc, int token, const std::string& text);
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
		//virtual NumberTypeNode* clone() const {
		//	return new NumberTypeNode(*this);
		//}

		//virtual void checkSyntax(SyntaxCheckStack& stack) const;
		//virtual void resolveT(const InitializerNode* initializer);
		virtual std::string toString() const { return "INT"; }

		//virtual NumberTypeNode* deepClone() const {
		//	NumberTypeNode* node = new NumberTypeNode();

		//	node->typeNodeClone(this);
		//	ASSERT(false);

		//	return node;
		//}
		//void setType(const Location& loc, int token, const std::string& text);
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
		//virtual NumberTypeNode* clone() const {
		//	return new NumberTypeNode(*this);
		//}

		//virtual void checkSyntax(SyntaxCheckStack& stack) const;
		//virtual void resolveT(const InitializerNode* initializer);
		virtual std::string toString() const { return "FIXED_POINT"; }

		//virtual NumberTypeNode* deepClone() const {
		//	NumberTypeNode* node = new NumberTypeNode();

		//	node->typeNodeClone(this);
		//	ASSERT(false);

		//	return node;
		//}
		//void setType(const Location& loc, int token, const std::string& text);
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
		//std::string name;
		Child<TypeNode> type;

		SequenceOfTypeNode() :type(this) {}

		virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
		virtual void walk(NodeWalker& walker) {
			TypeNode::walk(walker);
			walker.walkChild(this, type);
		}

		//virtual void checkSyntax(SyntaxCheckStack& stack) const;
		//virtual void resolveT(const InitializerNode* initializer);
		virtual std::string toString() const {
			return "SEQUENCE< " + type->toString() + " >";
		}

	};

	class ClassRefTypeNode : public TypeNode
	{
	public:
		//std::string name;
		Child<TypeNode> type;

		ClassRefTypeNode() :type(this) {}

		virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }
		virtual void walk(NodeWalker& walker) {
			TypeNode::walk(walker);
			walker.walkChild(this, type);
		}

		//virtual void checkSyntax(SyntaxCheckStack& stack) const;
		//virtual void resolveT(const InitializerNode* initializer);
		virtual std::string toString() const {
			return "class " + type->toString();
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

		//virtual void checkSyntax(SyntaxCheckStack& stack) const;
		//virtual void resolveT(const InitializerNode* initializer);
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

		//virtual void checkSyntax(SyntaxCheckStack& stack) const;
		//virtual void resolveT(const InitializerNode* initializer);
		virtual std::string toString() const { return "enum " + name; }

	};

	class IdentifierExprNode : public ExpressionNode
	{
	public:
		std::string name;

		Node* resolved;

		IdentifierExprNode() : resolved(0) {}

		virtual void visit(NodeVisitor& visitor) { visitor.visitMe(this); }

		virtual void dump(std::ostream& os) const {
			dumpAttribute(os, "name", name);
			dumpResolved(os, resolved);
		}

//		static VariableExprNode* createVariable(const Location& location, VariableDeclNode* decl);
	};

}