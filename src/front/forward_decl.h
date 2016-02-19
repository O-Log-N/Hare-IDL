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

namespace hare
{

	class Node;
	class ExpressionNode;
	class StatementNode;
	class TypeNode;
	class InitializerNode;


	class RootNode;
	class FileNode;

	class BooleanLiteralExprNode;
	class IntegerLiteralExprNode;
	class IntegerCastExprNode;

	class AttributeDeclNode;

	class PublishableStructDeclNode;
	class FenceDeclNode;
	class FencedAttributeDeclNode;
	class EncodingDeclNode;
	class MappingDeclNode;

	class NameTypeNode;
	class NumericTypeNode;
	class IntTypeNode;
	class FixedPointTypeNode;
	class BitTypeNode;
	class SequenceOfTypeNode;
	class ClassRefTypeNode;
	class InlineEnumTypeNode;
	class EnumValueDeclNode;

	class FloatLiteralExprNode;
	class IdentifierExprNode;
}