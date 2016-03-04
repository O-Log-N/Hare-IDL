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

#include "parser_helper.h"
#include "parser.h"
#include "lex.h"

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

struct YyBase {
    Location location;
    YyBase() {
        if (dbgEnableLeakDetector)
            dbgLeakDetector.insert(this);
    }
    virtual ~YyBase() {
        if (dbgEnableLeakDetector)
            dbgLeakDetector.erase(this);
    }
    YyBase(const YyBase&) = delete;
    YyBase& operator=(const YyBase&) = delete;
};


static
void reportError(const Location& loc, const std::string& msg)
{
    errorFlag = true;
    fmt::print(stderr, "{} - {}\n", locationToString(loc), msg);
}

void dbgDumpLeaks()
{
    if (!dbgLeakDetector.empty()) {
        fmt::print(stderr, "Parser nodes leaked\n");
        for (set<YyBase*>::const_iterator it = dbgLeakDetector.begin(); it != dbgLeakDetector.end(); ++it) {
            reportError((*it)->location, typeid(**it).name());
        }
    }
}

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
    map<string, int> enumValues;
};

struct YyIdentifierList : public YyBase {
    vector<string> ids;
};

struct YyToken : public YyBase {
    int token;
    std::string text;
    YyToken() : token(0) {}
};

struct YyIdentifier : public YyBase {
    Location location;
    std::string text;
};

struct YyIntegerLiteral : public YyBase {
    long long value;
};

struct YyFloatLiteral : public YyBase {
    double value;
};

struct YyArgumentList : public YyBase {
    map<string, Variant> arguments;
};

typedef YyIdentifier YyStringLiteral;

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
T* getPointedFromYyPtr(YYSTYPE yys)
{
    HAREASSERT(yys);
    YyPtr<U>* t = dynamic_cast<YyPtr<U>*>(yys);
    HAREASSERT(t);
    T* t2 = dynamic_cast<T*>(t->ptr.get());
    HAREASSERT(t2);
    return t2;
}

template<typename T>
T* releasePointedFromYyPtrAndDelete(YYSTYPE yys)
{
    HAREASSERT(yys);
    YyPtr<T>* t = dynamic_cast<YyPtr<T>*>(yys);
    HAREASSERT(t);
    T* ptr = t->ptr.release();
    delete yys;
    return ptr;
}

static
void setLocation(Location& loc, int line)
{
    loc.fileName = currentFileName;
    loc.lineNumber = line;
}

static
Location getLocationFromYyIdentifier(YyBase* id)
{
    YyIdentifier* t = yystype_cast<YyIdentifier*>(id);
    return t->location;
}

static
string nameFromYyIdentifierAndDelete(YyBase* id)
{
    YyIdentifier* i = yystype_cast<YyIdentifier*>(id);
    std::string temp = i->text;

    delete id;
    return temp;
}

static
Variant variantFromExpressionAndDelete(YYSTYPE expr)
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

static
double floatLiteralFromExpressionAndDelete(YYSTYPE expr)
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

static
map<string, Variant> argumentListFromYyAndDelete(YYSTYPE arg_list)
{
    YyArgumentList* al = yystype_cast<YyArgumentList*>(arg_list);
    map<string, Variant> result = std::move(al->arguments);
    delete arg_list;

    return result;
}

//////////////////////////////////////////////////////////////////////////////
//					Lexer functions											//
//////////////////////////////////////////////////////////////////////////////


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
    Structure* s = releasePointedFromYyPtrAndDelete<Structure>(item);
    rootPtr->structures.push_back(unique_ptr<Structure>(s));

    return 0;
}

YYSTYPE addToStruct(YYSTYPE decl, YYSTYPE attr)
{
    Structure* yy = getPointedFromYyPtr<Structure>(decl);

    EncodedOrMember* a = releasePointedFromYyPtrAndDelete<EncodedOrMember>(attr);

    yy->members.push_back(unique_ptr<EncodedOrMember>(a));

    return decl;
}

static
DataMember* makeDataMemberAndDelete(YYSTYPE type, YYSTYPE id)
{
    DataMember* yy = new DataMember();
    yy->location = getLocationFromYyIdentifier(id);
    yy->name = nameFromYyIdentifierAndDelete(id);
    yy->extendTo = false;

    YyDataType* dt = yystype_cast<YyDataType*>(type);
    yy->type = std::move(dt->dataType);
    delete type;

    return yy;
}

YYSTYPE createAttribute(YYSTYPE type, YYSTYPE id)
{
    DataMember* att = makeDataMemberAndDelete(type, id);

    return new YyPtr<EncodedOrMember>(att);
}

YYSTYPE createPublishableStruct(YYSTYPE token, YYSTYPE id)
{
    Structure* yy = new Structure();

    delete token;
    yy->location = getLocationFromYyIdentifier(id);
    yy->name = nameFromYyIdentifierAndDelete(id);
    yy->declType = Structure::IDL;
    yy->type = Structure::STRUCT;

    return new YyPtr<Structure>(yy);
}

YYSTYPE createMapping(YYSTYPE token, YYSTYPE arg_list, YYSTYPE id)
{
    Structure* yy = new Structure();

    delete token;
    yy->location = getLocationFromYyIdentifier(id);
    yy->name = nameFromYyIdentifierAndDelete(id);
    yy->declType = Structure::MAPPING;
    yy->type = Structure::STRUCT;

    yy->encodingSpecifics.attrs = argumentListFromYyAndDelete(arg_list);

    return new YyPtr<Structure>(yy);
}

YYSTYPE createEncoding(YYSTYPE token, YYSTYPE arg_list, YYSTYPE id)
{
    Structure* yy = new Structure();

    delete token;
    yy->location = getLocationFromYyIdentifier(id);
    yy->name = nameFromYyIdentifierAndDelete(id);
    yy->declType = Structure::ENCODING;
    yy->type = Structure::STRUCT;

    yy->encodingSpecifics.attrs = argumentListFromYyAndDelete(arg_list);

    EncodedMembers* g = new EncodedMembers();
    g->location = yy->location;
    yy->members.push_back(unique_ptr<EncodedOrMember>(g));

    return new YyPtr<Structure>(yy);
}

YYSTYPE addToEncoding(YYSTYPE decl, YYSTYPE elem)
{
    Structure* yy = getPointedFromYyPtr<Structure>(decl);

    EncodedOrMember* g = releasePointedFromYyPtrAndDelete<EncodedOrMember>(elem);
    EncodedMembers* em = dynamic_cast<EncodedMembers*>(yy->members.back().get());
    em->members.push_back(unique_ptr<EncodedOrMember>(g));

    return decl;
}

YYSTYPE addFenceToEncoding(YYSTYPE decl, YYSTYPE token)
{
    Structure* yy = getPointedFromYyPtr<Structure>(decl);

    EncodedMembers* g = new EncodedMembers();
    g->location = token->location;
    delete token;
    yy->members.push_back(unique_ptr<EncodedOrMember>(g));

    return decl;
}

YYSTYPE createEncodingAttribute(YYSTYPE type, YYSTYPE id, YYSTYPE opt_expr)
{
    DataMember* att = makeDataMemberAndDelete(type, id);

    if (opt_expr) {
        Variant v = variantFromExpressionAndDelete(opt_expr);
        att->defaultValue = v;
    }

    return new YyPtr<EncodedOrMember>(att);
}

YYSTYPE createExtendAttribute(YYSTYPE id, YYSTYPE type)
{
    DataMember* att = makeDataMemberAndDelete(type, id);
    att->extendTo = true;

    return new YyPtr<EncodedOrMember>(att);
}

static
EncodingSpecifics createEncodingAttributes(YYSTYPE id, YYSTYPE opt_arg_list)
{
    EncodingSpecifics att;
    att.name = nameFromYyIdentifierAndDelete(id);

    if (opt_arg_list)
        att.attrs = argumentListFromYyAndDelete(opt_arg_list);

    return att;
}

YYSTYPE createEncodingGroup(YYSTYPE id, YYSTYPE opt_arg_list, YYSTYPE opt_att)
{
    EncodedMembers* yy = new EncodedMembers();

    yy->location = getLocationFromYyIdentifier(id);
    yy->encodingSpecifics = createEncodingAttributes(id, opt_arg_list);

    if (opt_att) {
        EncodedOrMember* g = releasePointedFromYyPtrAndDelete<EncodedOrMember>(opt_att);
        yy->members.push_back(unique_ptr<EncodedOrMember>(g));
    }

    return new YyPtr<EncodedOrMember>(yy);
}


YYSTYPE addToEncodingGroup(YYSTYPE group, YYSTYPE element)
{
    EncodedMembers* yy = getPointedFromYyPtr<EncodedMembers, EncodedOrMember>(group);

    EncodedOrMember* g = releasePointedFromYyPtrAndDelete<EncodedOrMember>(element);
    yy->members.push_back(unique_ptr<EncodedOrMember>(g));

    return group;
}


YYSTYPE addEncodingOption(YYSTYPE id, YYSTYPE opt_arg_list, YYSTYPE group)
{
    return createEncodingGroup(id, opt_arg_list, group);
}

YYSTYPE createUnion(YYSTYPE token, YYSTYPE discr_id, YYSTYPE id)
{
    Structure* yy = new Structure();

    delete token;
    yy->location = getLocationFromYyIdentifier(id);
    yy->name = nameFromYyIdentifierAndDelete(id);
    yy->declType = Structure::IDL;
    yy->type = Structure::DISCRIMINATED_UNION;
    yy->discriminant = nameFromYyIdentifierAndDelete(discr_id);

    return new YyPtr<Structure>(yy);
}

YYSTYPE createUnionAttribute(YYSTYPE type, YYSTYPE id, YYSTYPE id_list)
{
    DataMember* att = makeDataMemberAndDelete(type, id);

    YyIdentifierList* al = yystype_cast<YyIdentifierList*>(id_list);
    att->whenDiscriminant = al->ids;
    delete id_list;

    return new YyPtr<EncodedOrMember>(att);
}

YYSTYPE createIdType(YYSTYPE id, YYSTYPE opt_arg_list)
{
    YyDataType* yy = new YyDataType();

    if (opt_arg_list) {
        yy->dataType.kind = DataType::ENCODING_SPECIFIC;
        yy->dataType.name = nameFromYyIdentifierAndDelete(id);
        yy->dataType.encodingAttrs = argumentListFromYyAndDelete(opt_arg_list);
    }
    else {
        yy->dataType.kind = DataType::PRIMITIVE;
        yy->dataType.name = nameFromYyIdentifierAndDelete(id);
    }

    return yy;
}


YYSTYPE createNumeric(YYSTYPE token, bool low_flag, YYSTYPE low_expr, YYSTYPE high_expr, bool high_flag)
{
    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::LIMITED_PRIMITIVE;
    yy->dataType.name = "NUMERIC";

    double l = floatLiteralFromExpressionAndDelete(low_expr);
    yy->dataType.lowLimit.inclusive = low_flag;
    yy->dataType.lowLimit.value = l;

    double h = floatLiteralFromExpressionAndDelete(high_expr);
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

    double l = floatLiteralFromExpressionAndDelete(low_expr);
    yy->dataType.lowLimit.inclusive = low_flag;
    yy->dataType.lowLimit.value = l;

    double h = floatLiteralFromExpressionAndDelete(high_expr);
    yy->dataType.highLimit.inclusive = high_flag;
    yy->dataType.highLimit.value = h;

    delete token;

    return yy;
}

YYSTYPE createSequence(YYSTYPE opt_id, YYSTYPE type)
{
    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::SEQUENCE;
    if (opt_id)
        yy->dataType.name = nameFromYyIdentifierAndDelete(opt_id);
    else
        yy->dataType.name = "SEQUENCE";

    YyDataType* t = yystype_cast<YyDataType*>(type);
    yy->dataType.paramType.reset(new DataType());
    *(yy->dataType.paramType) = std::move(t->dataType);
    delete type;

    return yy;
}

YYSTYPE createClassReference(YYSTYPE token, YYSTYPE id_type)
{
    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::MAPPING_SPECIFIC;
    yy->dataType.name = "class";

    Variant value = variantFromExpressionAndDelete(id_type);
    yy->dataType.mappingAttrs.insert(make_pair(string("className"), value));

    delete token;

    return yy;
}

YYSTYPE createInlineEnum(YYSTYPE token, YYSTYPE opt_id, YYSTYPE values)
{
    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::ENUM;
    if(opt_id)
        yy->dataType.name = nameFromYyIdentifierAndDelete(opt_id);

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


    string name = nameFromYyIdentifierAndDelete(id);
    YyIntegerLiteral* l = yystype_cast<YyIntegerLiteral*>(int_lit);

    yy->enumValues.insert(make_pair(name, static_cast<int>(l->value)));
    delete int_lit;

    return yy;
}


YYSTYPE addIdentifier(YYSTYPE list, YYSTYPE id)
{
    YyIdentifierList* yy = 0;
    if (list)
        yy = yystype_cast<YyIdentifierList*>(list);
    else
        yy = new YyIdentifierList();

    string value = nameFromYyIdentifierAndDelete(id);
    yy->ids.push_back(value);

    return yy;
}


YYSTYPE addExpression(YYSTYPE list, YYSTYPE id, YYSTYPE expr)
{
    YyArgumentList* yy = 0;
    if (list)
        yy = yystype_cast<YyArgumentList*>(list);
    else
        yy = new YyArgumentList();


    string name = nameFromYyIdentifierAndDelete(id);
    Variant value = variantFromExpressionAndDelete(expr);
    yy->arguments.insert(make_pair(name, value));

    return yy;
}

YYSTYPE createIdentifierExpression(YYSTYPE id)
{
    return id;
}






//////////////////////////////////////////////////////////////////////////////

Root* parseSourceFile(const string& fileName, bool debugDump)
{
    if (fileName.empty())
        throw ParserException("Missing input file name");
 
#pragma warning( push )
#pragma warning( disable : 4996 )
    unique_ptr<FILE, int(*)(FILE*)> file(fopen(fileName.c_str(), "r"), &fclose);
#pragma warning( pop )

    if (!file)
        throw ParserException(fmt::format("Failed to open file '{}'.", fileName));

    unique_ptr<Root> root(new Root());

    yyin = file.get();
    yyout = stderr;
    yylineno = 1;
    rootPtr = root.get();
    currentFileName = fileName;
    yydebug = static_cast<int>(debugDump);
 
    int err = yyparse();

    if (errorFlag | (err != 0) )
        throw ParserException(fmt::format("Errors found while parsing file '{}'.", fileName));

    return root.release();
}

//////////////////////////////////////////////////////////////////////////////
