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

#include <memory>
#include <vector>
#include <map>

#include "forward_decl.h"
#include "common.h"

namespace hare
{

class NodeWalker
{
public:
	virtual void walkChildNode(Node* parent, Node* child) = 0;
	//virtual void walkChildExpression(Node* parent, Child<ExpressionNode>& child) {
	//	walkChildNode(parent, reinterpret_cast<Node*>(child.get()));
	//}

	template<typename T>
	void walkChild(Node* parent, Child<T>& child) {
		walkChildNode(parent, child.get());
	}

	//void walkChild(Node* parent, Child<ExpressionNode>& child) {
	//	walkChildExpression(parent, child);
	//}

	template<typename T>
	void walkChild(Node* parent, ChildList<T>& child_list) {
		for (Child<T>& each : child_list)
			walkChild(parent, each);
	}
};


template<class T>
T* replaceTemplate(std::unique_ptr<T>& current, T* replacement)
{
	ASSERT(current);
	if (replacement)
		replacement->parent = current->parent;

	T* replaced = current.release();
	current.reset(replacement);

	//let the old parent there, just in case.
	//if(replaced)
	//	replaced->parent = 0;

	return replaced;
}

template<typename T>
class SequenceManipulationHelper
{
public:
	std::vector<std::unique_ptr<T> >& container;
	typename std::vector<std::unique_ptr<T> >::iterator it;
	std::unique_ptr<T> old;
	bool removed;

	SequenceManipulationHelper(std::vector<std::unique_ptr<T> >& container) : container(container), it(container.begin()), removed(false) {}

	// this method should be call last in the resolveE, since throwing after this may cause problem.
	void removeThis() {
		ASSERT(!removed);
		ASSERT(it != container.end());

		old.reset(replaceDeclaration(*it, 0));
		removed = true;
		it = container.erase(it);
	}

	void replaceThis(T* node) {
		ASSERT(!removed);
		ASSERT(it != container.end());

		old.reset(replaceTemplate(*it, node));
		removed = true;
	}

	void insertBeforeThis(T* node) {
		ASSERT(node);
		ASSERT(!removed);
		ASSERT(it != container.end());

		node->parent = (*it)->parent;
		it = container.insert(it, std::unique_ptr<T>(node));
		ASSERT(it != container.end());
		++it;
		ASSERT(it != container.end());
	}

	void insertAfterThis(T* node) {
		ASSERT(node);
		ASSERT(!removed);
		ASSERT(it != container.end());

		node->parent = (*it)->parent;
		++it;
		it = container.insert(it, std::unique_ptr<T>(node));
		ASSERT(it != container.end());
	}

	T* releaseRemoved() {
		ASSERT(removed);
		return old.release();
	}
};

class NodeVisitor
{
public:
	virtual void visitMe(RootNode* node) { ASSERT(false); }

	virtual void visitMe(FileNode* node) { /*do nothing*/ }

	virtual void visitMe(BooleanLiteralExprNode* node) { ASSERT(false); }
	virtual void visitMe(IntegerLiteralExprNode* node) { ASSERT(false); }
	virtual void visitMe(IntegerCastExprNode* node) { ASSERT(false); }

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

}


