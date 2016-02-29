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

#include "../../idlc_include.h"

#include <set>

#include "parser_helper.h"
#include "parser.h"

using namespace std;

static const bool dbgEnableLeakDetector = true;
static const bool NotImplementedYet = false;

static Root* rootPtr = 0;
static string currentFileName;

static vector<int> stateStack;

static set<YyBase*> dbgLeakDetector;

static bool errorFlag = false;



string locationToString(const Location& loc)
{
    if (!loc.fileName.empty()) {
        if (loc.lineNumber != 0)
            return fmt::format("@{}:{}", loc.fileName, loc.lineNumber);
        else
            return string("@") + loc.fileName;
    }
    else
        return "";
}


YyBase::YyBase()
{
    if (dbgEnableLeakDetector)
        dbgLeakDetector.insert(this);
}

YyBase::~YyBase()
{
    if (dbgEnableLeakDetector)
        dbgLeakDetector.erase(this);
}

void dbgDumpLeaks()
{
    if (!dbgLeakDetector.empty()) {
        plainError("Parser nodes leaked:");
        for (set<YyBase*>::const_iterator it = dbgLeakDetector.begin(); it != dbgLeakDetector.end(); ++it) {
            reportError((*it)->location, typeid(**it).name());
        }
    }
}

void reportError(const Location& loc, const std::string& msg)
{
    errorFlag = true;
    fmt::print(stderr, "{} - {}\n", locationToString(loc), msg);
}

void plainError(const std::string& msg)
{
    errorFlag = true;
    fmt::print(stderr, "{}\n", msg);
}



template<class T>
struct YyList : public YyBase {
    std::vector<std::unique_ptr<T> > items;
    void addItem(T* t) {
        items.push_back(std::unique_ptr<T>(t));
    }
};

template<class T>
struct YyPtr : public YyBase {
    unique_ptr<T> ptr;
    YyPtr(T* ptr) : ptr(ptr) {}
    T* operator->() const {
        return ptr.get();
    }
};

struct YyDataType : public YyBase {
    DataType dataType;
};

struct YyEnumValues : public YyBase {
    vector<pair<string, int> > enumValues;
};

struct YyStringLiteralList : public YyBase {
    vector<string> textValues;
};

struct YyToken : public YyBase {
    int token;
    std::string text;
    YyToken() : token(0) {}
};

struct YyIdentifier : public YyBase {
    std::string text;
};

struct YyIntegerLiteral : public YyBase {
    long long value;
};

struct YyFloatLiteral : public YyBase {
    double value;
};

struct YyArgumentList : public YyBase {
    vector<pair<string, Variant> > arguments;
};

typedef YyIdentifier YyStringLiteral;

typedef YyList<YyIdentifier> YyIdentifierList;

/*
	yystype_cast is used to cast YYSTYPE elements from the parser.
	The assert is to be sure the rule are assuming the correct type.
	The parser is not exception safe (plain C).
*/
template<typename T>
T yystype_cast(YYSTYPE yys)
{
    HAREASSERT(yys);
    T t = dynamic_cast<T>(yys);
    HAREASSERT(t);
    return t;
}

template<typename T, typename U = T>
T* yystype_ptr_cast(YYSTYPE yys)
{
    HAREASSERT(yys);
    YyPtr<U>* t = dynamic_cast<YyPtr<U>*>(yys);
    HAREASSERT(t);
    T* t2 = dynamic_cast<T*>(t->ptr.get());
    HAREASSERT(t2);
    return t2;
}

template<typename T>
T* yystype_ptr_release(YYSTYPE yys)
{
    HAREASSERT(yys);
    YyPtr<T>* t = dynamic_cast<YyPtr<T>*>(yys);
    HAREASSERT(t);
    T* ptr = t->ptr.release();
    delete yys;
    return ptr;
}


void setLocation(Location& loc, int line)
{
    loc.fileName = currentFileName;
    loc.lineNumber = line;
}

Location getLocationFromYyIdentifier(YyBase* id)
{
    YyIdentifier* t = yystype_cast<YyIdentifier*>(id);
    return t->location;
}

string getNameFromYyIdentifier(YyBase* id)
{
    YyIdentifier* i = yystype_cast<YyIdentifier*>(id);
    std::string temp = i->text;

    delete id;
    return temp;
}

Variant getExpressionVariant(YYSTYPE expr)
{
    if (YyIntegerLiteral* intLit = dynamic_cast<YyIntegerLiteral*>(expr)) {
        double value = static_cast<double>(intLit->value);
        delete expr;

        Variant v;
        v.kind = Variant::NUMBER;
        v.numberValue = value;
        return v;
    }
    else if(YyFloatLiteral* floatLit = dynamic_cast<YyFloatLiteral*>(expr)) {
        double value = floatLit->value;
        delete expr;

        Variant v;
        v.kind = Variant::NUMBER;
        v.numberValue = value;
        return v;
    }
    else if (YyStringLiteral* strLit = dynamic_cast<YyStringLiteral*>(expr)) {
        string text = strLit->text;
        delete expr;

        Variant v;
        v.kind = Variant::STRING;
        v.stringValue = text;
        return v;
    }
    else {
        reportError(expr->location, "Unsuported value");

        return Variant();
    }
}

double getFloatLiteral(YYSTYPE expr)
{
    if (YyIntegerLiteral* intLit = dynamic_cast<YyIntegerLiteral*>(expr)) {
        double value = static_cast<double>(intLit->value);
        delete expr;

        return value;
    }
    else if (YyFloatLiteral* floatLit = dynamic_cast<YyFloatLiteral*>(expr)) {
        double value = floatLit->value;
        delete expr;

        return value;
    }
    else {
        reportError(expr->location, "Unsuported value");

        return 0;
    }
}

long long getIntegerLiteral(YYSTYPE expr)
{
    if (YyIntegerLiteral* intLit = dynamic_cast<YyIntegerLiteral*>(expr)) {
        long long value = intLit->value;
        delete expr;

        return value;
    }
    else {
        reportError(expr->location, "Unsuported value");

        return 0;
    }
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

    reportError(l, fmt::format(msg, text));
}


void parserErrorUnknownChar(char text, int line)
{
    Location l;
    setLocation(l, line);

    reportError(l, fmt::format("Unknown char '0x{:x}'", static_cast<unsigned char>(text)));
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
}

YYSTYPE createIdentifier(const char* text, int line)
{
    YyIdentifier* yy = new YyIdentifier();
    setLocation(yy->location, line);
    yy->text = text;
    return yy;
}

YYSTYPE createIntegerLiteral(const char* text, int line)
{
    YyIntegerLiteral* yy = new YyIntegerLiteral();

    setLocation(yy->location, line);
    yy->value =  atoll(text);

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
    string t = text;
    if(t.size() >= 2)
        t = t.substr(1, t.size() - 2);

    YyStringLiteral* yy = new YyStringLiteral();
    setLocation(yy->location, line);
    yy->text = t;
    return yy;
}

YYSTYPE createCharLiteral(const char* text, int line)
{
    //HAREASSERT(text);
    //string t = text;
    //HAREASSERT(t.size() >= 2);
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
    YyStringLiteral* yy = new YyStringLiteral();
    setLocation(yy->location, line);
    yy->text = text;

    return yy;
}

YYSTYPE createFloatLiteral(const char* text, int line)
{
    YyFloatLiteral* yy = new YyFloatLiteral();

    setLocation(yy->location, line);
    yy->value = atof(text);

    return yy;
}


//////////////////////////////////////////////////////////////////////////////

YYSTYPE addToFile(YYSTYPE file, YYSTYPE item)
{
    Structure* s = yystype_ptr_release<Structure>(item);
    rootPtr->structures.push_back(unique_ptr<Structure>(s));

    return 0;
}

YYSTYPE createPublishableStruct(YYSTYPE token, YYSTYPE id)
{
    Structure* yy = new Structure();

    delete token;
    yy->location = getLocationFromYyIdentifier(id);
    yy->name = getNameFromYyIdentifier(id);
    yy->declType = Structure::IDL;
    yy->type = Structure::STRUCT;

    return new YyPtr<Structure>(yy);
}

DataMember* makeDataMember(YYSTYPE type, YYSTYPE id)
{
    DataMember* yy = new DataMember();
    yy->location = getLocationFromYyIdentifier(id);
    yy->name = getNameFromYyIdentifier(id);
    yy->extendTo = false;

    YyDataType* dt = yystype_cast<YyDataType*>(type);
    yy->type = std::move(dt->dataType);
    delete type;

    return yy;
}

YYSTYPE addToPublishableStruct(YYSTYPE decl, YYSTYPE type, YYSTYPE id)
{
    Structure* yy = yystype_ptr_cast<Structure>(decl);

    DataMember* att = makeDataMember(type, id);
    yy->members.push_back(unique_ptr<EncodedOrMember>(att));

    return decl;
}

YYSTYPE createMapping(YYSTYPE token, YYSTYPE str_list, YYSTYPE id)
{
    Structure* yy = new Structure();

    delete token;
    yy->location = getLocationFromYyIdentifier(id);
    yy->name = getNameFromYyIdentifier(id);
    yy->declType = Structure::MAPPING;
    yy->type = Structure::STRUCT;

    YyStringLiteralList* l = yystype_cast<YyStringLiteralList*>(str_list);
    yy->tags = l->textValues;
    delete str_list;

    return new YyPtr<Structure>(yy);
}

YYSTYPE addToMapping(YYSTYPE decl, YYSTYPE type, YYSTYPE id)
{
    Structure* yy = yystype_ptr_cast<Structure>(decl);

    DataMember* att = makeDataMember(type, id);
    yy->members.push_back(unique_ptr<EncodedOrMember>(att));

    return decl;
}


YYSTYPE createEncoding(YYSTYPE token, YYSTYPE str_list, YYSTYPE id)
{
    Structure* yy = new Structure();

    delete token;
    yy->location = getLocationFromYyIdentifier(id);
    yy->name = getNameFromYyIdentifier(id);
    yy->declType = Structure::ENCODING;
    yy->type = Structure::STRUCT;

    YyStringLiteralList* l = yystype_cast<YyStringLiteralList*>(str_list);
    yy->tags = l->textValues;
    delete str_list;

    EncodedMembers* g = new EncodedMembers();
    g->location = yy->location;
    yy->members.push_back(unique_ptr<EncodedOrMember>(g));

    return new YyPtr<Structure>(yy);
}

YYSTYPE addToEncoding(YYSTYPE decl, YYSTYPE elem)
{
    Structure* yy = yystype_ptr_cast<Structure>(decl);

    EncodedOrMember* g = yystype_ptr_release<EncodedOrMember>(elem);
    EncodedMembers* em = dynamic_cast<EncodedMembers*>(yy->members.back().get());
    em->members.push_back(unique_ptr<EncodedOrMember>(g));

    return decl;
}

YYSTYPE addFenceToEncoding(YYSTYPE decl, YYSTYPE token)
{
    Structure* yy = yystype_ptr_cast<Structure>(decl);

    EncodedMembers* g = new EncodedMembers();
    g->location = token->location;
    delete token;
    yy->members.push_back(unique_ptr<EncodedOrMember>(g));

    return decl;
}

YYSTYPE createEncodingAttribute(YYSTYPE type, YYSTYPE id, YYSTYPE opt_expr)
{
    DataMember* att = makeDataMember(type, id);

    if (opt_expr) {
        Variant v = getExpressionVariant(opt_expr);
        att->defaultValue = v;
    }

    return new YyPtr<EncodedOrMember>(att);
}

YYSTYPE createExtendAttribute(YYSTYPE id, YYSTYPE type)
{
    DataMember* att = makeDataMember(type, id);
    att->extendTo = true;

    return new YyPtr<EncodedOrMember>(att);
}

static
EncodingAttributes createEncodingAttributes(YYSTYPE id, YYSTYPE opt_arg_list)
{
    EncodingAttributes att;
    att.name = getNameFromYyIdentifier(id);

    if (opt_arg_list) {
        YyArgumentList* al = yystype_cast<YyArgumentList*>(opt_arg_list);
        att.arguments = al->arguments;
        delete opt_arg_list;
    }

    return att;
}

YYSTYPE createEncodingGroup(YYSTYPE id, YYSTYPE opt_arg_list, YYSTYPE opt_att)
{
    EncodedMembers* yy = new EncodedMembers();

    yy->location = getLocationFromYyIdentifier(id);
    yy->encodingAttr = createEncodingAttributes(id, opt_arg_list);

    if (opt_att) {
        EncodedOrMember* g = yystype_ptr_release<EncodedOrMember>(opt_att);
        yy->members.push_back(unique_ptr<EncodedOrMember>(g));
    }

    return new YyPtr<EncodedOrMember>(yy);
}


YYSTYPE addToEncodingGroup(YYSTYPE group, YYSTYPE element)
{
    EncodedMembers* yy = yystype_ptr_cast<EncodedMembers, EncodedOrMember>(group);

    EncodedOrMember* g = yystype_ptr_release<EncodedOrMember>(element);
    yy->members.push_back(unique_ptr<EncodedOrMember>(g));

    return group;
}


YYSTYPE addEncodingOption(YYSTYPE id, YYSTYPE opt_arg_list, YYSTYPE group)
{
    return createEncodingGroup(id, opt_arg_list, group);
}


YYSTYPE createIdType(YYSTYPE id)
{
    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::PRIMITIVE;
    yy->dataType.name = getNameFromYyIdentifier(id);

    return yy;
}


YYSTYPE createNumeric(YYSTYPE token, bool low_flag, YYSTYPE low_expr, YYSTYPE high_expr, bool high_flag)
{
    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::LIMITED_PRIMITIVE;
    yy->dataType.name = "NUMERIC";

    double l = getFloatLiteral(low_expr);
    yy->dataType.lowLimit.inclusive = low_flag;
    yy->dataType.lowLimit.value = l;

    double h = getFloatLiteral(high_expr);
    yy->dataType.highLimit.inclusive = high_flag;
    yy->dataType.highLimit.value = h;

    delete token;

    return yy;
}

YYSTYPE createInt(YYSTYPE token, bool low_flag, YYSTYPE low_expr, YYSTYPE high_expr, bool high_flag)
{
    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::LIMITED_PRIMITIVE;
    yy->dataType.name = "INT";

    double l = getFloatLiteral(low_expr);
    yy->dataType.lowLimit.inclusive = low_flag;
    yy->dataType.lowLimit.value = l;

    double h = getFloatLiteral(high_expr);
    yy->dataType.highLimit.inclusive = high_flag;
    yy->dataType.highLimit.value = h;

    delete token;

    return yy;
}

YYSTYPE createFixedPoint(YYSTYPE token, YYSTYPE expr)
{
    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::FIXED_POINT;
    yy->dataType.name = "FIXED_POINT";

    double v = getFloatLiteral(expr);
    yy->dataType.fixedPointPrecision = v;

    delete token;

    return yy;
}

YYSTYPE createBit(YYSTYPE token, YYSTYPE expr)
{
    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::BIT;
    yy->dataType.name = "BIT";

    long long v = getIntegerLiteral(expr);
    //TODO check limits?
    yy->dataType.bitSize = static_cast<int>(v);

    delete token;

    return yy;
}

YYSTYPE createSequence(YYSTYPE token, YYSTYPE id_type)
{
    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::SEQUENCE;
    yy->dataType.name = "SEQUENCE";

    //TODO support more generic types
    yy->dataType.paramType.reset(new DataType());
    yy->dataType.paramType->kind = DataType::PRIMITIVE;
    yy->dataType.paramType->name = getNameFromYyIdentifier(id_type);

    delete token;

    return yy;
}

YYSTYPE createClassReference(YYSTYPE token, YYSTYPE id_type)
{
    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::CLASS;
    yy->dataType.name = getNameFromYyIdentifier(id_type);

    delete token;

    return yy;
}

YYSTYPE createInlineEnum(YYSTYPE token, YYSTYPE id, YYSTYPE values)
{
    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::ENUM;
    yy->dataType.name = getNameFromYyIdentifier(id);

    YyEnumValues* v = yystype_cast<YyEnumValues*>(values);
    yy->dataType.enumValues = v->enumValues;
    delete token;
    delete values;

    return yy;
}

YYSTYPE addEnumValue(YYSTYPE list, YYSTYPE id, YYSTYPE int_lit)
{

    YyEnumValues* yy = 0;
    if (list)
        yy = yystype_cast<YyEnumValues*>(list);
    else
        yy = new YyEnumValues();


    string name = getNameFromYyIdentifier(id);
    YyIntegerLiteral* l = yystype_cast<YyIntegerLiteral*>(int_lit);

    yy->enumValues.push_back(make_pair(name, static_cast<int>(l->value)));
    delete int_lit;

    return yy;
}


YYSTYPE addString(YYSTYPE list, YYSTYPE str)
{
    YyStringLiteralList* yy = 0;
    if (list)
        yy = yystype_cast<YyStringLiteralList*>(list);
    else
        yy = new YyStringLiteralList();

    string value = getNameFromYyIdentifier(str);
    yy->textValues.push_back(value);

    return yy;
}

YYSTYPE addExpression(YYSTYPE list, YYSTYPE expr)
{
    YyArgumentList* yy = 0;
    if (list)
        yy = yystype_cast<YyArgumentList*>(list);
    else
        yy = new YyArgumentList();


    string name = "!TODO!";
    Variant value = getExpressionVariant(expr);
    yy->arguments.push_back(make_pair(name, value));

    return yy;
}

YYSTYPE createIdentifierExpression(YYSTYPE id)
{
    return id;
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


static
Root* parseInternal(const std::string& fileName, bool debugDump)
{
    HAREASSERT(!rootPtr);
    try {
        unique_ptr<Root> root(new Root());

        rootPtr = root.get();
        currentFileName = fileName;
        yydebug = static_cast<int>(debugDump);

        int err = yyparse();

        rootPtr = 0;
        currentFileName.erase();
        yydebug = 0;

        if (err != 0)
            plainError(fmt::format("Errors found while parsing file '%s'.", fileName));

        return root.release();
    }
    catch (...) {
        plainError(fmt::format("Exception thrown while parsing file '%s'.", fileName));

        rootPtr = 0;
        currentFileName.erase();
        yydebug = 0;
        throw;
    }
}


Root* parseCode(const char* code, const std::string& pseudoFileName, bool debugDump)
{
    HAREASSERT(code);

    unique_ptr<yy_buffer_state, void(*)(yy_buffer_state*)> buff(yy_scan_string(code), &yy_delete_buffer);

    yylineno = 0;
    return parseInternal(pseudoFileName, debugDump);
}


Root* parseSourceFile(const string& fileName, bool debugDump)
{
    HAREASSERT(!fileName.empty());

#pragma warning( push )
#pragma warning( disable : 4996 )
    unique_ptr<FILE, int(*)(FILE*)> file(fopen(fileName.c_str(), "r"), &fclose);
#pragma warning( pop )
    if (!file) {
        plainError(fmt::format("Failed to open file '%s'.", fileName));
        return 0;
    }

    unique_ptr<yy_buffer_state, void(*)(yy_buffer_state*)> buff(yy_create_buffer(file.get(), 16000), &yy_delete_buffer);

    if (!buff) {
        plainError(fmt::format("Failed to allocate read buffer for file '%s'.", fileName));
        return 0;
    }

    yy_switch_to_buffer(buff.get());
    yylineno = 1;
    return parseInternal(fileName, debugDump);
}

//////////////////////////////////////////////////////////////////////////////
