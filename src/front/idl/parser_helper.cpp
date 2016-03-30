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

#include "../../front-back/raiistdiofile.h"

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

//static const set<string> primitives = { "INT8", "INT16", "INT32", "UINT8", "UINT16", "UINT32" };

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

struct YyTypedef : public YyBase {
    Typedef data;
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

struct YyCharacterSet : public YyBase {
    CharacterSet charSet;
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
T* releasePointedFromYyPtr(YYSTYPE yys)
{
    HAREASSERT(yys);
    YyPtr<T>* t = dynamic_cast<YyPtr<T>*>(yys);
    HAREASSERT(t);
    return t->ptr.release();
}

static
void setLocation(Location& loc, int line)
{
    loc.fileName = currentFileName;
    loc.lineNumber = line;
}

static
string nameFromYyIdentifier(YyBase* id)
{
    return yystype_cast<YyIdentifier*>(id)->text;
}

static
Variant variantFromExpression(YYSTYPE expr)
{
    if (YyIntegerLiteral* intLit = dynamic_cast<YyIntegerLiteral*>(expr)) {
        Variant v;
        v.kind = Variant::NUMBER;
        v.numberValue = static_cast<double>(intLit->value);
        return v;
    }
    else if (YyFloatLiteral* floatLit = dynamic_cast<YyFloatLiteral*>(expr)) {
        Variant v;
        v.kind = Variant::NUMBER;
        v.numberValue = floatLit->value;
        return v;
    }
    else if (YyStringLiteral* strLit = dynamic_cast<YyStringLiteral*>(expr)) {
        Variant v;
        v.kind = Variant::STRING;
        v.stringValue = strLit->text;
        return v;
    }
    else {
        reportError(expr->location, "Unsuported value");
        return Variant();
    }
}

static
double floatLiteralFromExpression(YYSTYPE expr)
{
    if (YyIntegerLiteral* intLit = dynamic_cast<YyIntegerLiteral*>(expr)) {
        return static_cast<double>(intLit->value);
    }
    else if (YyFloatLiteral* floatLit = dynamic_cast<YyFloatLiteral*>(expr)) {
        return floatLit->value;
    }
    else {
        reportError(expr->location, "Unsuported value");
        return 0;
    }
}

static
long long integerLiteralFromExpression(YYSTYPE expr, long long min_value, long long max_value)
{
    if (YyIntegerLiteral* intLit = dynamic_cast<YyIntegerLiteral*>(expr)) {
        if (intLit->value >= min_value && intLit->value <= max_value) {
            return intLit->value;
        }
        else {
            reportError(expr->location, fmt::format("Value outside valid range [{},{}]", min_value, max_value));
            return min_value;
        }
    }
    else {
        reportError(expr->location, "Unsuported value");
        return min_value;
    }
}

static
map<string, Variant> argumentListFromYy(YYSTYPE arg_list)
{
    YyArgumentList* al = yystype_cast<YyArgumentList*>(arg_list);
    map<string, Variant> result = std::move(al->arguments);

    return result;
}

static
CharacterSet getNamedCharacterSet(const Location& loc, const string& name)
{
    if (name == "PRINTABLE-ASCII") {
        //PRINTABLE-ASCII-STRING is a typedef to CHARACTER-STRING {32-126}
        // see https://github.com/O-Log-N/Hare-IDL/issues/52
        CharacterSet cs;
        cs.ranges.emplace_back(32, 126);
        return cs;
    }
    else if (name == "UNICODE") {
        //UNICODE-STRING is a typedef to CHARACTER-STRING {1-1114111}
        // see https://github.com/O-Log-N/Hare-IDL/issues/52
        CharacterSet cs;
        cs.ranges.emplace_back(1, 0x10ffff);
        return cs;
    }
    else {
        reportError(loc, fmt::format("Unknown named character set '{}'", name));
        return CharacterSet();
    }
}

static
bool checkCharRangeValues(const Location& loc, const CharacterRange& range)
{
    if (range.from > range.to) {
        reportError(loc, fmt::format("Character range is inverted"));
        return false;
    }
    else if (range.from == 0) {
        reportError(loc, fmt::format("Character zero or null not allowed"));
        return false;
    }
    else if (range.from > 0x10ffff || range.to > 0x10ffff) {
        reportError(loc, fmt::format("Character range overflow"));
        return false;
    }
    else
        return true;
}

static
CharacterSet getCharacterSet(YYSTYPE charset)
{
    if (YyStringLiteral* strLit = dynamic_cast<YyStringLiteral*>(charset)) {
        return getNamedCharacterSet(strLit->location, strLit->text);
    }
    else if (YyCharacterSet* cs = dynamic_cast<YyCharacterSet*>(charset)) {

        HAREASSERT(!cs->charSet.ranges.empty());
        auto it = cs->charSet.ranges.begin();
        if(!checkCharRangeValues(charset->location, *it))
            return CharacterSet();

        auto prev = it;
        HAREASSERT(it != cs->charSet.ranges.end());
        ++it;
        while (it != cs->charSet.ranges.end()) {

            if (!checkCharRangeValues(charset->location, *it))
                return CharacterSet();
            else if (it->from <= prev->to) {
                reportError(charset->location, fmt::format("Character set ranges are overlapping"));
                return CharacterSet();
            }
            else if (it->from == prev->to + 1) {
                //need to merge with previous;
                prev->to = it->to;
                it = cs->charSet.ranges.erase(it);
            }
            else {
                prev = it;
                ++it;
            }
        }
        return std::move(cs->charSet);
    }
    else
        HAREASSERT(false);

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
    HAREASSERT(!file);
    unique_ptr<YyBase> d0(item);

    Structure* s = releasePointedFromYyPtr<Structure>(item);
    rootPtr->structures.push_back(unique_ptr<Structure>(s));

    return 0;
}

YYSTYPE addTypedefToFile(YYSTYPE file, YYSTYPE td)
{
    HAREASSERT(!file);
    unique_ptr<YyBase> d0(td);

    YyTypedef* dt = yystype_cast<YyTypedef*>(td);

    rootPtr->typedefs.emplace_back(dt->data);

    return 0;
}


YYSTYPE addToStruct(YYSTYPE decl, YYSTYPE attr)
{
    unique_ptr<YyBase> d0(decl);
    unique_ptr<YyBase> d1(attr);

    Structure* yy = getPointedFromYyPtr<Structure>(decl);

    EncodedOrMember* a = releasePointedFromYyPtr<EncodedOrMember>(attr);

    yy->members.push_back(unique_ptr<EncodedOrMember>(a));

    return d0.release();
}

static
DataMember* makeDataMember(YYSTYPE type, YYSTYPE id)
{
    DataMember* yy = new DataMember();
    yy->location = id->location;
    yy->name = nameFromYyIdentifier(id);
    yy->extendTo = false;

    YyDataType* dt = yystype_cast<YyDataType*>(type);
    yy->type = std::move(dt->dataType);

    return yy;
}

YYSTYPE createAttribute(YYSTYPE type, YYSTYPE id)
{
    unique_ptr<YyBase> d0(type);
    unique_ptr<YyBase> d1(id);

    DataMember* att = makeDataMember(type, id);

    return new YyPtr<EncodedOrMember>(att);
}

YYSTYPE createTypedef(YYSTYPE token, YYSTYPE type, YYSTYPE id)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(type);
    unique_ptr<YyBase> d2(id);

    YyTypedef* yy = new YyTypedef();
    yy->data.location = id->location;
    yy->data.name = nameFromYyIdentifier(id);

    YyDataType* dt = yystype_cast<YyDataType*>(type);
    yy->data.type = std::move(dt->dataType);

    return yy;
}

YYSTYPE createPublishableStruct(YYSTYPE token, YYSTYPE id)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(id);

    Structure* yy = new Structure();

    yy->location = id->location;
    yy->name = nameFromYyIdentifier(id);
    yy->declType = Structure::IDL;
    yy->type = Structure::STRUCT;

    return new YyPtr<Structure>(yy);
}

YYSTYPE createMapping(YYSTYPE token, YYSTYPE arg_list, YYSTYPE id)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(arg_list);
    unique_ptr<YyBase> d2(id);

    Structure* yy = new Structure();

    yy->location = id->location;
    yy->name = nameFromYyIdentifier(id);
    yy->declType = Structure::MAPPING;
    yy->type = Structure::STRUCT;

    yy->encodingSpecifics.attrs = argumentListFromYy(arg_list);

    return new YyPtr<Structure>(yy);
}

YYSTYPE createEncoding(YYSTYPE token, YYSTYPE arg_list, YYSTYPE id)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(arg_list);
    unique_ptr<YyBase> d2(id);

    Structure* yy = new Structure();

    yy->location = id->location;
    yy->name = nameFromYyIdentifier(id);
    yy->declType = Structure::ENCODING;
    yy->type = Structure::STRUCT;

    yy->encodingSpecifics.attrs = argumentListFromYy(arg_list);

    EncodedMembers* g = new EncodedMembers();
    g->location = yy->location;
    yy->members.push_back(unique_ptr<EncodedOrMember>(g));

    return new YyPtr<Structure>(yy);
}

YYSTYPE addToEncoding(YYSTYPE decl, YYSTYPE elem)
{
    unique_ptr<YyBase> d0(decl);
    unique_ptr<YyBase> d1(elem);

    Structure* yy = getPointedFromYyPtr<Structure>(decl);

    EncodedOrMember* g = releasePointedFromYyPtr<EncodedOrMember>(elem);
    EncodedMembers* em = dynamic_cast<EncodedMembers*>(yy->members.back().get());
    em->members.push_back(unique_ptr<EncodedOrMember>(g));

    return d0.release();
}

YYSTYPE addFenceToEncoding(YYSTYPE decl, YYSTYPE token)
{
    unique_ptr<YyBase> d0(decl);
    unique_ptr<YyBase> d1(token);

    Structure* yy = getPointedFromYyPtr<Structure>(decl);

    EncodedMembers* g = new EncodedMembers();
    g->location = token->location;
    yy->members.push_back(unique_ptr<EncodedOrMember>(g));

    return d0.release();
}

YYSTYPE createEncodingAttribute(YYSTYPE type, YYSTYPE id, YYSTYPE opt_expr)
{
    unique_ptr<YyBase> d0(type);
    unique_ptr<YyBase> d1(id);
    unique_ptr<YyBase> d2(opt_expr);

    DataMember* att = makeDataMember(type, id);

    if (opt_expr) {
        Variant v = variantFromExpression(opt_expr);
        att->defaultValue = v;
    }

    return new YyPtr<EncodedOrMember>(att);
}

YYSTYPE createExtendAttribute(YYSTYPE id, YYSTYPE type)
{
    unique_ptr<YyBase> d0(id);
    unique_ptr<YyBase> d1(type);

    DataMember* att = makeDataMember(type, id);
    att->extendTo = true;

    return new YyPtr<EncodedOrMember>(att);
}

static
EncodingSpecifics createEncodingAttributes(YYSTYPE id, YYSTYPE opt_arg_list)
{
    EncodingSpecifics att;
    att.name = nameFromYyIdentifier(id);

    if (opt_arg_list)
        att.attrs = argumentListFromYy(opt_arg_list);

    return att;
}

YYSTYPE createEncodingGroup(YYSTYPE id, YYSTYPE opt_arg_list, YYSTYPE opt_att)
{
    unique_ptr<YyBase> d0(id);
    unique_ptr<YyBase> d1(opt_arg_list);
    unique_ptr<YyBase> d2(opt_att);

    EncodedMembers* yy = new EncodedMembers();

    yy->location = id->location;
    yy->encodingSpecifics = createEncodingAttributes(id, opt_arg_list);

    if (opt_att) {
        EncodedOrMember* g = releasePointedFromYyPtr<EncodedOrMember>(opt_att);
        yy->members.push_back(unique_ptr<EncodedOrMember>(g));
    }

    return new YyPtr<EncodedOrMember>(yy);
}


YYSTYPE addToEncodingGroup(YYSTYPE group, YYSTYPE element)
{
    unique_ptr<YyBase> d0(group);
    unique_ptr<YyBase> d1(element);

    EncodedMembers* yy = getPointedFromYyPtr<EncodedMembers, EncodedOrMember>(group);

    EncodedOrMember* g = releasePointedFromYyPtr<EncodedOrMember>(element);
    yy->members.push_back(unique_ptr<EncodedOrMember>(g));

    return d0.release();
}

YYSTYPE createUnion(YYSTYPE token, YYSTYPE discr_id, YYSTYPE id)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(discr_id);
    unique_ptr<YyBase> d2(id);

    Structure* yy = new Structure();

    yy->location = id->location;
    yy->name = nameFromYyIdentifier(id);
    yy->declType = Structure::IDL;
    yy->type = Structure::DISCRIMINATED_UNION;
    yy->discriminant = nameFromYyIdentifier(discr_id);

    return new YyPtr<Structure>(yy);
}

YYSTYPE createUnionAttribute(YYSTYPE type, YYSTYPE id, YYSTYPE id_list)
{
    unique_ptr<YyBase> d0(type);
    unique_ptr<YyBase> d1(id);
    unique_ptr<YyBase> d2(id_list);

    DataMember* att = makeDataMember(type, id);

    YyIdentifierList* al = yystype_cast<YyIdentifierList*>(id_list);
    att->whenDiscriminant = al->ids;

    return new YyPtr<EncodedOrMember>(att);
}

YYSTYPE createIdType(YYSTYPE id)
{
    unique_ptr<YyBase> d0(id);

    YyDataType* yy = new YyDataType();

    string name = nameFromYyIdentifier(id);
    if (name == "INT8") {
        yy->dataType.kind = DataType::INTEGER;
        yy->dataType.lowLimit.inclusive = true;
        yy->dataType.lowLimit.value = INT8_MIN;
        yy->dataType.highLimit.inclusive = true;
        yy->dataType.highLimit.value = INT8_MAX;
    }
    else if (name == "INT16") {
        yy->dataType.kind = DataType::INTEGER;
        yy->dataType.lowLimit.inclusive = true;
        yy->dataType.lowLimit.value = INT16_MIN;
        yy->dataType.highLimit.inclusive = true;
        yy->dataType.highLimit.value = INT16_MAX;
    }
    else if (name == "INT32") {
        yy->dataType.kind = DataType::INTEGER;
        yy->dataType.lowLimit.inclusive = true;
        yy->dataType.lowLimit.value = INT32_MIN;
        yy->dataType.highLimit.inclusive = true;
        yy->dataType.highLimit.value = INT32_MAX;
    }
    else if (name == "UINT8") {
        yy->dataType.kind = DataType::INTEGER;
        yy->dataType.lowLimit.inclusive = true;
        yy->dataType.lowLimit.value = 0;
        yy->dataType.highLimit.inclusive = true;
        yy->dataType.highLimit.value = UINT8_MAX;
    }
    else if (name == "UINT16") {
        yy->dataType.kind = DataType::INTEGER;
        yy->dataType.lowLimit.inclusive = true;
        yy->dataType.lowLimit.value = 0;
        yy->dataType.highLimit.inclusive = true;
        yy->dataType.highLimit.value = UINT16_MAX;
    }
    else if (name == "UINT32") {
        yy->dataType.kind = DataType::INTEGER;
        yy->dataType.lowLimit.inclusive = true;
        yy->dataType.lowLimit.value = 0;
        yy->dataType.highLimit.inclusive = true;
        yy->dataType.highLimit.value = UINT32_MAX;
    }
    else if (name == "DOUBLE") {
        yy->dataType.kind = DataType::FLOATING_POINT;
        yy->dataType.floatingSignificandBits = 53;
        yy->dataType.floatingExponentBits = 11;
    }
    else if (name == "DOUBLE80") {
        yy->dataType.kind = DataType::FLOATING_POINT;
        yy->dataType.floatingSignificandBits = 65;
        yy->dataType.floatingExponentBits = 15;
    }
    else {
        yy->dataType.name = name;
        yy->dataType.kind = DataType::NAMED_TYPE;
    }

    return yy;
}

YYSTYPE createEncodingType(YYSTYPE id, YYSTYPE arg_list)
{
    unique_ptr<YyBase> d0(id);
    unique_ptr<YyBase> d1(arg_list);

    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::ENCODING_SPECIFIC;
    yy->dataType.name = nameFromYyIdentifier(id);
    yy->dataType.encodingAttrs = argumentListFromYy(arg_list);

    return yy;
}

YYSTYPE createIntegerType(YYSTYPE token, bool low_flag, YYSTYPE low_expr, YYSTYPE high_expr, bool high_flag)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(low_expr);
    unique_ptr<YyBase> d2(high_expr);

    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::INTEGER;

    double l = floatLiteralFromExpression(low_expr);
    yy->dataType.lowLimit.inclusive = low_flag;
    yy->dataType.lowLimit.value = l;

    double h = floatLiteralFromExpression(high_expr);
    yy->dataType.highLimit.inclusive = high_flag;
    yy->dataType.highLimit.value = h;

    if (!(yy->dataType.lowLimit.value < yy->dataType.highLimit.value))
        reportError(token->location, "Low limit must be less than high limit");

    return yy;
}

YYSTYPE createFixedPointType(YYSTYPE token, bool low_flag, YYSTYPE low_expr, YYSTYPE precision_expr, YYSTYPE high_expr, bool high_flag)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(low_expr);
    unique_ptr<YyBase> d2(precision_expr);
    unique_ptr<YyBase> d3(high_expr);

    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::FIXED_POINT;

    yy->dataType.lowLimit.inclusive = low_flag;
    yy->dataType.lowLimit.value = floatLiteralFromExpression(low_expr);

    yy->dataType.highLimit.inclusive = high_flag;
    yy->dataType.highLimit.value = floatLiteralFromExpression(high_expr);

    yy->dataType.fixedPrecision = floatLiteralFromExpression(precision_expr);

    if (!(yy->dataType.lowLimit.value < yy->dataType.highLimit.value))
        reportError(token->location, "Low limit must be less than high limit");

    return yy;
}

YYSTYPE createFloatingPointType(YYSTYPE token, YYSTYPE significand_expr, YYSTYPE exponent_expr)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(significand_expr);
    unique_ptr<YyBase> d2(exponent_expr);

    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::FLOATING_POINT;

    yy->dataType.floatingSignificandBits = static_cast<int>(
            integerLiteralFromExpression(significand_expr, 1, 65));
    yy->dataType.floatingExponentBits = static_cast<int>(
                                            integerLiteralFromExpression(exponent_expr, 1, 15));

    return yy;
}

YYSTYPE createCharacterType(YYSTYPE token, YYSTYPE charset)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(charset);

    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::CHARACTER;
    yy->dataType.characterSet = getCharacterSet(charset);

    return yy;
}

YYSTYPE createCharacterStringType(YYSTYPE token, YYSTYPE charset, YYSTYPE min_expr, YYSTYPE max_expr)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(charset);
    unique_ptr<YyBase> d2(min_expr);
    unique_ptr<YyBase> d3(max_expr);

    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::CHARACTER_STRING;
    yy->dataType.characterSet = getCharacterSet(charset);

    if (min_expr) {
        yy->dataType.stringMinSize = static_cast<int>(
                                         integerLiteralFromExpression(min_expr, 0, INT_MAX));

        yy->dataType.stringMaxSize = static_cast<int>(
                                         integerLiteralFromExpression(max_expr, yy->dataType.stringMinSize, INT_MAX));
    }

    return yy;
}

YYSTYPE createBitStringType(YYSTYPE token, YYSTYPE min_expr, YYSTYPE max_expr)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(min_expr);
    unique_ptr<YyBase> d2(max_expr);

    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::BIT_STRING;

    if (min_expr) {
        yy->dataType.stringMinSize = static_cast<int>(
                                         integerLiteralFromExpression(min_expr, 0, INT_MAX));

        yy->dataType.stringMaxSize = static_cast<int>(
                                         integerLiteralFromExpression(max_expr, yy->dataType.stringMinSize, INT_MAX));
    }

    return yy;
}


YYSTYPE createSequence(YYSTYPE opt_id, YYSTYPE type)
{
    unique_ptr<YyBase> d0(opt_id);
    unique_ptr<YyBase> d1(type);

    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::SEQUENCE;
    if (opt_id)
        yy->dataType.name = nameFromYyIdentifier(opt_id);

    YyDataType* t = yystype_cast<YyDataType*>(type);
    yy->dataType.paramType.reset(new DataType(t->dataType));

    return yy;
}

YYSTYPE createDictionaryType(YYSTYPE token, YYSTYPE key_type, YYSTYPE value_type)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(key_type);
    unique_ptr<YyBase> d2(value_type);

    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::DICTIONARY;

    YyDataType* kt = yystype_cast<YyDataType*>(key_type);
    yy->dataType.keyType.reset(new DataType(kt->dataType));

    YyDataType* vt = yystype_cast<YyDataType*>(value_type);
    yy->dataType.paramType.reset(new DataType(vt->dataType));

    return yy;
}


YYSTYPE createClassReference(YYSTYPE token, YYSTYPE id_type)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(id_type);

    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::MAPPING_SPECIFIC;
    yy->dataType.name = "class";

    Variant value = variantFromExpression(id_type);
    yy->dataType.mappingAttrs.emplace("className", value);

    return yy;
}

YYSTYPE createInlineEnum(YYSTYPE token, YYSTYPE opt_id, YYSTYPE values)
{
    unique_ptr<YyBase> d0(token);
    unique_ptr<YyBase> d1(opt_id);
    unique_ptr<YyBase> d2(values);

    YyDataType* yy = new YyDataType();

    yy->dataType.kind = DataType::ENUM;
    if(opt_id)
        yy->dataType.name = nameFromYyIdentifier(opt_id);

    YyEnumValues* v = yystype_cast<YyEnumValues*>(values);
    yy->dataType.enumValues = v->enumValues;

    return yy;
}

YYSTYPE addEnumValue(YYSTYPE list, YYSTYPE id, YYSTYPE int_lit)
{
    unique_ptr<YyBase> d0(list);
    unique_ptr<YyBase> d1(id);
    unique_ptr<YyBase> d2(int_lit);

    YyEnumValues* yy = 0;
    if (list)
        yy = yystype_cast<YyEnumValues*>(list);
    else {
        yy = new YyEnumValues();
        d0.reset(yy);
    }

    string name = nameFromYyIdentifier(id);
    int value = static_cast<int>(integerLiteralFromExpression(int_lit, 0, INT_MAX));

    yy->enumValues.emplace(name, value);

    return d0.release();
}

YYSTYPE createPrintableAsciiStringType(YYSTYPE token)
{
    unique_ptr<YyBase> d0(token);

    YyDataType* yy = new YyDataType();

    //PRINTABLE-ASCII-STRING is a typedef to CHARACTER-STRING {32-126}
    // see https://github.com/O-Log-N/Hare-IDL/issues/52
    yy->dataType.kind = DataType::CHARACTER_STRING;
    yy->dataType.characterSet = getNamedCharacterSet(token->location, "PRINTABLE-ASCII");

    return yy;
}

YYSTYPE createUnicodeStringType(YYSTYPE token)
{
    unique_ptr<YyBase> d0(token);

    YyDataType* yy = new YyDataType();

    //UNICODE-STRING is a typedef to CHARACTER-STRING {1-1114111}
    // see https://github.com/O-Log-N/Hare-IDL/issues/52
    yy->dataType.kind = DataType::CHARACTER_STRING;
    yy->dataType.characterSet = getNamedCharacterSet(token->location, "UNICODE");

    return yy;
}


YYSTYPE addIdentifier(YYSTYPE list, YYSTYPE id)
{
    unique_ptr<YyBase> d0(list ? list : new YyIdentifierList());
    unique_ptr<YyBase> d1(id);

    YyIdentifierList* yy = yystype_cast<YyIdentifierList*>(d0.get());

    string value = nameFromYyIdentifier(id);
    yy->ids.push_back(value);

    return d0.release();
}


YYSTYPE addExpression(YYSTYPE list, YYSTYPE id, YYSTYPE expr)
{
    unique_ptr<YyBase> d0(list ? list : new YyArgumentList());
    unique_ptr<YyBase> d1(id);
    unique_ptr<YyBase> d2(expr);

    YyArgumentList* yy = yystype_cast<YyArgumentList*>(d0.get());

    string name = nameFromYyIdentifier(id);
    Variant value = variantFromExpression(expr);
    yy->arguments.emplace(name, value);

    return d0.release();
}

YYSTYPE makeMinusIntLit(YYSTYPE int_lit)
{
    YyIntegerLiteral* yy = yystype_cast<YyIntegerLiteral*>(int_lit);

    yy->value = -(yy->value);

    return yy;
}

YYSTYPE makeMinusFloatLit(YYSTYPE float_lit)
{
    YyFloatLiteral* yy = yystype_cast<YyFloatLiteral*>(float_lit);

    yy->value = -(yy->value);

    return yy;
}

YYSTYPE addToCharSet(YYSTYPE list, YYSTYPE from, YYSTYPE to)
{
    unique_ptr<YyBase> d0(list ? list : new YyCharacterSet());
    unique_ptr<YyBase> d1(from);
    unique_ptr<YyBase> d2(to);

    YyCharacterSet* yy = yystype_cast<YyCharacterSet*>(d0.get());

    uint32_t from_32 = static_cast<uint32_t>(integerLiteralFromExpression(from, 0, UINT32_MAX));
    uint32_t to_32 = from_32;
    if (to)
        to_32 = static_cast<uint32_t>(integerLiteralFromExpression(to, 0, UINT32_MAX));

    yy->charSet.ranges.emplace_back(from_32, to_32);

    return d0.release();
}



//////////////////////////////////////////////////////////////////////////////

Root* parseSourceFile(const string& fileName, bool debugDump)
{
    if (fileName.empty())
        throw ParserException("Missing input file name");

    RaiiStdioFile file(fopen(fileName.c_str(), "r"));

    if (!file)
        throw ParserException(fmt::format("Failed to open file '{}'.", fileName));

    unique_ptr<Root> root(new Root());

    yyin = file;
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
