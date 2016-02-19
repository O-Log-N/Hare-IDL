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

#include "grammar/parser_helper.h"

#include <vector>
#include <string>
#include <cassert>
#include <sstream>
#include <iomanip>

#include "base_node.h"
#include "idl_node.h"
//#include "declaration_node.h"
#include "parser.h"
#include "error.h"
#include "literal_node.h"

using namespace std;
using namespace hare;

FileNode* acceptFile = 0;
vector<string> fileNames;
const char* currentFileName = 0;
int returnState = 0;

bool allowAtIdentifier = false;

vector<int> stateStack;

template<class T>
struct YyList : public YyBase {
	std::vector<std::unique_ptr<T> > items;
	void addItem(T* t) {
		items.push_back(std::unique_ptr<T>(t));
	}
};

struct YyToken : public YyBase {
	int token;
	std::string text;
	YyToken() : token(0) {}
};
typedef YyList<YyToken> YyTokenList;

struct YyIdentifier : public YyBase {
	std::string text;
};
typedef YyIdentifier YyStringLiteral;
typedef YyIdentifier YyIntegerLiteral;

typedef YyList<YyIdentifier> YyIdentifierList;
typedef YyList<YyStringLiteral> YyStringLiteralList;
typedef YyList<ExpressionNode> YyExpressionList;
typedef YyList<EnumValueDeclNode> YyEnumValueList;

/*
	yystype_cast is used to cast YYSTYPE elements from the parser.
	The assert is to be sure the rule are assuming the correct type.
	The parser is not exception safe (plain C).
*/
template<typename T>
T yystype_cast(YYSTYPE yys)
{
	T t = dynamic_cast<T>(yys);
	if (!t)
		assert(false);
	return t;
}

void setLocation(Location& loc, int line)
{
	loc.fileName = currentFileName;
	loc.lineNumber = line;
}
void setLocationFromToken(Node* node, YyBase* token)
{
	YyToken* t = yystype_cast<YyToken*>(token);
	node->location = t->location;

	delete token;
}

std::string getNameFromYyIdentifier(YyBase* id)
{
	YyIdentifier* i = yystype_cast<YyIdentifier*>(id);
	std::string temp = i->text;

	delete id;
	return temp;
}

template<class T>
void setNameFromYyIdentifier(T* node, YyBase* id)
{
	YyIdentifier* i = yystype_cast<YyIdentifier*>(id);
	node->location = i->location;
	node->name = i->text;

	delete id;
}



//////////////////////////////////////////////////////////////////////////////
//					Lexer functions											//
//////////////////////////////////////////////////////////////////////////////
extern "C" int yylineno;

void pushState(int state)
{
	stateStack.push_back(state);
}

int popState()
{
	int s = stateStack.back();
	stateStack.pop_back();
	return s;
}


int yywrap()
{
	return 1;
}

void yyerror(const char* msg)
{
	Location l;
	setLocation(l, yylineno);

	reportError(l, msg);
}

void parserError(const char* msg, const char* text, int line)
{
	Location l;
	setLocation(l, line);

	reportError(l, msg, text);
}


void parserErrorUnknownChar(char text, int line)
{
	Location l;
	setLocation(l, line);

	stringstream ss;
	ss << "Unknown char ";
	unsigned int ui = static_cast<unsigned int>(text);
	if (ui >= 32) {
		ss.put('\'');
		ss.put(text);
		ss.put('\'');
		ss.put(' ');
	}

	ss << "0x" << hex << setfill('0') << setw(2) << ui;
	ss << " found.";

	reportError(l, ss.str());
}


void releaseYys(YYSTYPE yys)
{
	delete yys;
}

void releaseYys2(YYSTYPE yys0, YYSTYPE yys1)
{
	delete yys0;
	delete yys1;
}

void releaseYys3(YYSTYPE yys0, YYSTYPE yys1, YYSTYPE yys2)
{
	delete yys0;
	delete yys1;
	delete yys2;
}

void releaseYys4(YYSTYPE yys0, YYSTYPE yys1, YYSTYPE yys2, YYSTYPE yys3)
{
	delete yys0;
	delete yys1;
	delete yys2;
	delete yys3;
}

void releaseYys5(YYSTYPE yys0, YYSTYPE yys1, YYSTYPE yys2, YYSTYPE yys3, YYSTYPE yys4)
{
	delete yys0;
	delete yys1;
	delete yys2;
	delete yys3;
	delete yys4;
}

YYSTYPE createYyToken(const char* text, int line, int token)
{
	YyToken* yy = new YyToken();
	setLocation(yy->location, line);
	yy->token = token;
	yy->text = text;

	return yy;
	//	*yys = yy;
	//	return token;
}

YYSTYPE createIdentifier(const char* text, int line)
{
	YyIdentifier* yy = new YyIdentifier();
	setLocation(yy->location, line);
	yy->text = text;
	return yy;
}

YYSTYPE createAtIdentifier(const char* text, int line)
{
	if (!allowAtIdentifier)
		parserError("Unknown keyword", text, line);

	return createIdentifier(text, line);
}

YYSTYPE createIntegerLiteral(const char* text, int line)
{
	IntegerLiteralExprNode* yy = new IntegerLiteralExprNode();

	setLocation(yy->location, line);
	yy->setIntegerLiteral(text);

	return yy;
}

YYSTYPE createHexIntegerLiteral(const char* text, int line)
{
	parserError("Hex integer literal not implemente yet!", text, line);

	return 0;
}


YYSTYPE createZeroLiteral(const char* text, int line)
{
	return createIntegerLiteral(text, line);
}


YYSTYPE createStringLiteral(const char* text, int line)
{
	ASSERT(text);
	string t = text;
	ASSERT(t.size() >= 2);
	t = t.substr(1, t.size() - 2);

	YyStringLiteral* yy = new YyStringLiteral();
	setLocation(yy->location, line);
	yy->text = t;
	return yy;
}

YYSTYPE createCharLiteral(const char* text, int line)
{
	//ASSERT(text);
	//string t = text;
	//ASSERT(t.size() >= 2);
	//t = t.substr(1, t.size() - 2);

	//CharLiteralExprNode* yy = new CharLiteralExprNode();
	//setLocation(yy->location, line);
	//yy->text = t;
	//return yy;
	parserError("Char literal not implemente yet!", text, line);

	return 0;
}

YYSTYPE createBooleanLiteral(const char* text, int line)
{
	BooleanLiteralExprNode* yy = new BooleanLiteralExprNode();
	setLocation(yy->location, line);
	yy->setBooleanLiteral(text);

	return yy;
}

YYSTYPE createFloatLiteral(const char* text, int line)
{
	FloatLiteralExprNode* yy = new FloatLiteralExprNode();

	setLocation(yy->location, line);
	yy->setFloatLiteral(text);

	return yy;
}


//////////////////////////////////////////////////////////////////////////////

YYSTYPE createPublishableStruct(YYSTYPE token, YYSTYPE id)
{
	PublishableStructDeclNode* yy = new PublishableStructDeclNode();

	setLocationFromToken(yy, token);
	yy->name = getNameFromYyIdentifier(id);

	return yy;
}

YYSTYPE addToPublishableStruct(YYSTYPE decl, YYSTYPE elem)
{
	PublishableStructDeclNode* yy = yystype_cast<PublishableStructDeclNode*>(decl);

	AttributeDeclNode* e = yystype_cast<AttributeDeclNode*>(elem);
	yy->attributes.push_back(e);

	return decl;
}

YYSTYPE createMapping(YYSTYPE token, YYSTYPE str_list, YYSTYPE id)
{
	MappingDeclNode* yy = new MappingDeclNode();

	setLocationFromToken(yy, token);
	yy->name = getNameFromYyIdentifier(id);

	YyStringLiteralList* l = yystype_cast<YyStringLiteralList*>(str_list);
	for (const std::unique_ptr<YyStringLiteral>& each : l->items)
		yy->tags.push_back(each->text);

	delete str_list;

	return yy;
}

YYSTYPE addToMapping(YYSTYPE decl, YYSTYPE elem)
{
	MappingDeclNode* yy = yystype_cast<MappingDeclNode*>(decl);

	AttributeDeclNode* e = yystype_cast<AttributeDeclNode*>(elem);
	yy->attributes.push_back(e);

	return decl;
}


YYSTYPE createEncoding(YYSTYPE token, YYSTYPE str_lit, YYSTYPE id)
{
	EncodingDeclNode* yy = new EncodingDeclNode();

	setLocationFromToken(yy, token);
	yy->name = getNameFromYyIdentifier(id);
	yy->encoding = getNameFromYyIdentifier(str_lit);
	
	return yy;
}

YYSTYPE addToEncoding(YYSTYPE decl, YYSTYPE elem)
{
	EncodingDeclNode* yy = yystype_cast<EncodingDeclNode*>(decl);

	AttributeDeclNode* e = yystype_cast<AttributeDeclNode*>(elem);
	yy->attributes.push_back(e);

	return decl;
}

YYSTYPE addGroupToEncoding(YYSTYPE decl, YYSTYPE group)
{
	ASSERT(NotImplementedYet);

	return decl;
}


YYSTYPE createAttribute(YYSTYPE type, YYSTYPE id)
{
	AttributeDeclNode* yy = new AttributeDeclNode();
	
	setNameFromYyIdentifier(yy, id);

	TypeNode* t = yystype_cast<TypeNode*>(type);
	yy->type.set(t);

	return yy;
}

YYSTYPE createIdentifierAttribute(YYSTYPE id_type, YYSTYPE id)
{
	AttributeDeclNode* yy = new AttributeDeclNode();

	setNameFromYyIdentifier(yy, id);

	NameTypeNode* t = new NameTypeNode();
	setNameFromYyIdentifier(yy, id_type);
	yy->type.set(t);

	return yy;
}

YYSTYPE addTagToAttribute(YYSTYPE id, YYSTYPE arg_list, YYSTYPE element)
{
	ASSERT(NotImplementedYet);

	return 0;
}


YYSTYPE createTagGroup(YYSTYPE id, YYSTYPE arg_list)
{
	ASSERT(NotImplementedYet);

	return 0;
}

YYSTYPE addToTagGroup(YYSTYPE group, YYSTYPE element)
{
	ASSERT(NotImplementedYet);

	return 0;
}


YYSTYPE createNumeric(YYSTYPE token, bool low_flag, YYSTYPE low_literal, YYSTYPE high_literal, bool high_flag)
{
	NumericTypeNode* yy = new NumericTypeNode();

	setLocationFromToken(yy, token);

	yy->low_open = low_flag;
	yy->high_open = high_flag;

	ExpressionNode* l = yystype_cast<ExpressionNode*>(low_literal);
	yy->arguments.push_back(l);

	ExpressionNode* h = yystype_cast<ExpressionNode*>(high_literal);
	yy->arguments.push_back(h);

	return yy;
}

YYSTYPE createInt(YYSTYPE token, bool low_flag, YYSTYPE low_literal, YYSTYPE high_literal, bool high_flag)
{
	IntTypeNode* yy = new IntTypeNode();

	setLocationFromToken(yy, token);

	yy->low_open = low_flag;
	yy->high_open = high_flag;

	ExpressionNode* l = yystype_cast<ExpressionNode*>(low_literal);
	yy->arguments.push_back(l);

	ExpressionNode* h = yystype_cast<ExpressionNode*>(high_literal);
	yy->arguments.push_back(h);

	return yy;
}

YYSTYPE createFixedPoint(YYSTYPE token, YYSTYPE float_lit)
{
	FixedPointTypeNode* yy = new FixedPointTypeNode();

	setLocationFromToken(yy, token);

	ExpressionNode* e = yystype_cast<ExpressionNode*>(float_lit);
	yy->arguments.push_back(e);

	return yy;
}

YYSTYPE createBit(YYSTYPE token, YYSTYPE int_lit)
{
	FixedPointTypeNode* yy = new FixedPointTypeNode();

	setLocationFromToken(yy, token);

	ExpressionNode* e = yystype_cast<ExpressionNode*>(int_lit);
	yy->arguments.push_back(e);

	return yy;
}

YYSTYPE createSequence(YYSTYPE token, YYSTYPE id_type)
{
	SequenceOfTypeNode* yy = new SequenceOfTypeNode();

	setLocationFromToken(yy, token);

	NameTypeNode* t = new NameTypeNode();
	setNameFromYyIdentifier(t, id_type);
	yy->type.set(t);

	return yy;
}

YYSTYPE createClassReference(YYSTYPE token, YYSTYPE id_type)
{
	ClassRefTypeNode* yy = new ClassRefTypeNode();

	setLocationFromToken(yy, token);

	NameTypeNode* t = new NameTypeNode();
	setNameFromYyIdentifier(t, id_type);
	yy->type.set(t);

	return yy;
}

YYSTYPE createInlineEnum(YYSTYPE token, YYSTYPE id, YYSTYPE values)
{
	InlineEnumTypeNode* yy = new InlineEnumTypeNode();

	setLocationFromToken(yy, token);
	yy->name = getNameFromYyIdentifier(id);

	YyEnumValueList* l = yystype_cast<YyEnumValueList*>(values);
	for (std::unique_ptr<EnumValueDeclNode>& each : l->items)
		yy->values.push_back(each.release());

	delete values;

	return yy;
}

YYSTYPE addEnumValue(YYSTYPE list, YYSTYPE id, YYSTYPE int_lit)
{
	YyEnumValueList* yy = 0;
	if (list)
		yy = yystype_cast<YyEnumValueList*>(list);
	else
		yy = new YyEnumValueList();

	EnumValueDeclNode* ev = new EnumValueDeclNode();

	setNameFromYyIdentifier(ev, id);

	ExpressionNode* e = yystype_cast<ExpressionNode*>(int_lit);
	ev->value.set(e);

	yy->addItem(ev);

	return yy;
}


YYSTYPE addString(YYSTYPE list, YYSTYPE str)
{
	YyStringLiteralList* yy = 0;
	if (list)
		yy = yystype_cast<YyStringLiteralList*>(list);
	else
		yy = new YyStringLiteralList();

	YyStringLiteral* s = yystype_cast<YyStringLiteral*>(str);
	yy->addItem(s);

	return yy;
}

YYSTYPE addExpression(YYSTYPE list, YYSTYPE expr)
{
	YyExpressionList* yy = 0;
	if (list)
		yy = yystype_cast<YyExpressionList*>(list);
	else
		yy = new YyExpressionList();

	ExpressionNode* e = yystype_cast<ExpressionNode*>(expr);
	yy->addItem(e);

	return yy;
}

YYSTYPE createIdentifierExpression(YYSTYPE id)
{
	IdentifierExprNode* yy = new IdentifierExprNode();

	setNameFromYyIdentifier(yy, id);

	return yy;
}



YYSTYPE addToFile(YYSTYPE file, YYSTYPE item);


YYSTYPE addToFile(YYSTYPE file, YYSTYPE item)
{
	ASSERT(acceptFile);

	Node* d = yystype_cast<Node*>(item);
	acceptFile->items.push_back(d);

	return 0;
}


//////////////////////////////////////////////////////////////////////////////

extern "C" int yyparse();
extern "C" int yydebug;
struct yy_buffer_state; //forward
extern "C" yy_buffer_state* yy_create_buffer(FILE* file, int size);
extern "C" void yy_switch_to_buffer(yy_buffer_state* new_buffer);
extern "C" yy_buffer_state* yy_scan_buffer(char* buffer, unsigned int size);
extern "C" yy_buffer_state* yy_scan_string(const char* yy_str);
extern "C" yy_buffer_state* yy_scan_bytes(const char* bytes, int len);
extern "C" void yy_delete_buffer(yy_buffer_state*);

namespace hare
{


	static FileNode* parseInternal(const std::string& fileName, bool debugDump, bool internalFile)
	{
		ASSERT(!acceptFile);
		try {
			unique_ptr<FileNode> file(new FileNode(fileName));
			file->isInternalFile = internalFile;
			acceptFile = file.get();
			currentFileName = file->fileName.c_str();
			allowAtIdentifier = internalFile;
			yydebug = static_cast<int>(debugDump);

			int err = yyparse();

			acceptFile = 0;
			currentFileName = 0;
			allowAtIdentifier = 0;
			yydebug = 0;

			if (err != 0) {
				plainError("Errors found while parsing file '%s'.", fileName);
			}

			return file.release();
		}
		catch (...) {
			plainError("Exception thrown while parsing file '%s'.", fileName);

			acceptFile = 0;
			currentFileName = 0;
			allowAtIdentifier = 0;
			yydebug = 0;
			throw;
		}
	}


	FileNode* parseCode(const char* code, const std::string& pseudoFileName, bool debugDump, bool internalFile)
	{
		ASSERT(code);

		unique_ptr<yy_buffer_state, void(*)(yy_buffer_state*)> buff(yy_scan_string(code), &yy_delete_buffer);

		yylineno = 0;
		return parseInternal(pseudoFileName, debugDump, internalFile);
	}


	FileNode* parseSourceFile(const string& fileName, bool debugDump, bool internalFile)
	{
		ASSERT(!fileName.empty());

#pragma warning( push )
#pragma warning( disable : 4996 )
		unique_ptr<FILE, int(*)(FILE*)> file(fopen(fileName.c_str(), "r"), &fclose);
#pragma warning( pop )
		if (!file) {
			plainError("Failed to open file '%s'.", fileName);
			return 0;
		}

		unique_ptr<yy_buffer_state, void(*)(yy_buffer_state*)> buff(yy_create_buffer(file.get(), 16000), &yy_delete_buffer);

		if (!buff) {
			plainError("Failed to allocate read buffer for file '%s'.", fileName);
			return 0;
		}

		yy_switch_to_buffer(buff.get());
		yylineno = 1;
		return parseInternal(fileName, debugDump, internalFile);
	}

} // namespace kpm

//////////////////////////////////////////////////////////////////////////////
