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

#ifndef VISITOR_H_INCLUDED
#define VISITOR_H_INCLUDED "include guard"

#include <memory>
#include <vector>
#include <map>

#include "forward_decl.h"
#include "common.h"


class NodeWalker
{
public:
	virtual void walkChildNode(Node* parent, Node* child) = 0;

	template<typename T>
	void walkChild(Node* parent, Child<T>& child) {
		walkChildNode(parent, child.get());
	}

	template<typename T>
	void walkChild(Node* parent, ChildList<T>& child_list) {
		for (Child<T>& each : child_list)
			walkChild(parent, each);
	}
};

class NodeVisitor
{
public:
	virtual void visitMe(RootNode* node) { ASSERT(false); }

	virtual void visitMe(FileNode* node) { /*do nothing*/ }

	virtual void visitMe(BooleanLiteralExprNode* node) { ASSERT(false); }
	virtual void visitMe(IntegerLiteralExprNode* node) { ASSERT(false); }

	virtual void visitMe(AttributeDeclNode* node) { ASSERT(false); }

	virtual void visitMe(PublishableStructDeclNode* node) { ASSERT(false); }
	virtual void visitMe(FenceDeclNode* node) { ASSERT(false); }
	virtual void visitMe(FencedAttributeDeclNode* node) { ASSERT(false); }
	virtual void visitMe(EncodingDeclNode* node) { ASSERT(false); }
	virtual void visitMe(MappingDeclNode* node) { ASSERT(false); }

	virtual void visitMe(NameTypeNode* node) { ASSERT(false); }
	virtual void visitMe(NumericTypeNode* node) { ASSERT(false); }
	virtual void visitMe(IntTypeNode* node) { ASSERT(false); }
	virtual void visitMe(FixedPointTypeNode* node) { ASSERT(false); }
	virtual void visitMe(BitTypeNode* node) { ASSERT(false); }
	virtual void visitMe(SequenceOfTypeNode* node) { ASSERT(false); }
	virtual void visitMe(ClassRefTypeNode* node) { ASSERT(false); }
	virtual void visitMe(InlineEnumTypeNode* node) { ASSERT(false); }
	virtual void visitMe(EnumValueDeclNode* node) { ASSERT(false); }


	virtual void visitMe(FloatLiteralExprNode* node) { ASSERT(false); }
	virtual void visitMe(IdentifierExprNode* node) { ASSERT(false); }


};

#endif // VISITOR_H_INCLUDED
