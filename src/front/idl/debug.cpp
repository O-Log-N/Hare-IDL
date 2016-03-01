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

#include "debug.h"
#include "../../front-back/idl_tree.h"
#include "parser.h" // string locationToString(const Location& loc)

using namespace std;


class DbgDumpWalker
{
public:
    FILE* file;
    bool printLocation;
    size_t offset;
    vector<string> offsets;

    DbgDumpWalker(FILE* file, bool printLocation) : file(file), printLocation(printLocation), offset(0)
    {
        offsets.push_back("");
    }

    void dbgDumpRoot(const Root* node) {
        dbgWrite("Root");
        ++offset;
        for (auto& it : node->structures)
            dbgDumpStructure(it.get());

        --offset;
    }

private:
    static string dbgAttributesToString(const vector<pair<string, Variant> >& v) {
        string tags = "( ";
        for (auto& it = v.begin(); it != v.end(); ++it) {
            if (it != v.begin())
                tags += ",";
            tags += fmt::format("{}={}", it->first, dbgVariantToString(it->second));
        }
        tags += " )";
        return tags;
    }


    static string dbgVariantToString(const Variant& v) {

        switch (v.kind) {
        case Variant::NUMBER:
            return fmt::format("( kind=NUMBER numberValue={} )", v.numberValue);
            break;
        case Variant::STRING:
            return fmt::format("( kind=STRING stringValue={} )", v.stringValue);
            break;
        default:
            HAREASSERT(false);
        }

    }
    static string dbgTypeToString(const DataType& dataType) {

        switch (dataType.kind) {
        case DataType::PRIMITIVE:
            return fmt::format("{{ kind=PRIMITIVE name={} }}", dataType.name);
            break;
        case DataType::LIMITED_PRIMITIVE:

            return fmt::format("{{ kind=LIMITED_PRIMITIVE name={} lowLimit={}:{} highLimit={}:{} }}",
                               dataType.name, dataType.lowLimit.inclusive, dataType.lowLimit.value,
                               dataType.highLimit.inclusive, dataType.highLimit.value);
            break;
        case DataType::ENUM:
        {
            string enumValues;
            for (auto it = dataType.enumValues.begin(); it != dataType.enumValues.end(); ++it) {
                if (it != dataType.enumValues.begin())
                    enumValues += ",";
                enumValues += fmt::format("{}={}", it->first, it->second);
            }

            return fmt::format("{{ kind=ENUM name={} enumValues={} }}", dataType.name, enumValues);
        }
        break;
        case DataType::NAMED_TYPE:
            return fmt::format("{{ kind=NAMED_TYPE name={} }}", dataType.name);
            break;
        case DataType::SEQUENCE:
        {
            HAREASSERT(dataType.paramType);
            string arg = dbgTypeToString(*dataType.paramType);
            return fmt::format("{{ kind=CLASS name={} paramType={} }}", dataType.name, arg);
        }
        break;
        case DataType::ENCODING_SPECIFIC:
        {
            string attrs = dbgAttributesToString(dataType.encodingAttributes);
            return fmt::format("{{ kind=ENCODING_SPECIFIC name={} encAttrs={} }}",
                               dataType.name, attrs);
        }
        break;
        case DataType::MAPPING_SPECIFIC:
        {
            string attrs = dbgAttributesToString(dataType.mappingAttributes);
            return fmt::format("{{ kind=MAPPING_SPECIFIC name={} encAttrs={} }}",
                               dataType.name, attrs);
        }
        break;
        default:
            HAREASSERT(false);
        }
    }


    void dbgDumpStructure(const Structure* node) {

        string kind = "";
        switch (node->declType) {
        case Structure::IDL:
            kind = "IDL";
            break;
        case Structure::MAPPING:
            kind = "MAPPING";
            break;
        case Structure::ENCODING:
            kind = "ENCODING";
            break;
        default:
            HAREASSERT(false);
        }

        string tags = dbgAttributesToString(node->encodingAttr.encodingAttributes);
        dbgWriteWithLocation(node->location, fmt::format("Structure kind={} name={} encAttrs={}", kind, node->name, tags));

        ++offset;
        for (auto& it : node->members) {
            const DataMember* data = dynamic_cast<const DataMember*>(it.get());
            if (data) {
                dbgDumpDataMember(data);
            }
            else {
                const EncodedMembers* group = dynamic_cast<const EncodedMembers*>(it.get());
                if (group) {
                    dbgDumpEncodedMember(group);
                }
                else
                    HAREASSERT(false);
            }
        }
        --offset;
    }


    void dbgDumpDataMember(const DataMember* node) {

        string attr;
        if (node->extendTo)
            attr += "extendTo=true";
        if (node->defaultValue.kind != Variant::NONE)
            attr += fmt::format("defaultValue='{}'", dbgVariantToString(node->defaultValue));

        string typeStr = dbgTypeToString(node->type);
        dbgWriteWithLocation(node->location, fmt::format("DataMember name='{}' {} {}", node->name, attr, typeStr));
    }

    static string dbgEncodingToString(const EncodingAttributes& encoding) {

        return fmt::format("encAttrName={}, encAttrArgs={}", encoding.name, dbgAttributesToString(encoding.encodingAttributes));
    }


    void dbgDumpEncodedMember(const EncodedMembers* node) {
        string attr = dbgEncodingToString(node->encodingAttr);
        dbgWriteWithLocation(node->location, fmt::format("EncodedMembers {}", attr));
        ++offset;
        for (auto& it : node->members) {
            const DataMember* data = dynamic_cast<const DataMember*>(it.get());
            if (data) {
                dbgDumpDataMember(data);
            }
            else {
                const EncodedMembers* group = dynamic_cast<const EncodedMembers*>(it.get());
                if (group) {
                    dbgDumpEncodedMember(group);
                }
                else
                    HAREASSERT(false);
            }
        }
        --offset;
    }

    void dbgWrite(const string& text) {
        fmt::print(file, "{}{}\n", getOffset(), text);
    }

    void dbgWriteWithLocation(const Location& location, const string& text) {
        if (printLocation) {
            string l = locationToString(location);
            fmt::print(file, "{}{} {}\n", getOffset(), text, l);
        }
        else
            dbgWrite(text);
    }

    void addOffset()
    {
        string r;
        for (size_t i = 0; i < offsets.size() - 1; ++i) {
            r.append("| ");
        }
        r.append("|-");
        offsets.push_back(r);
    }

    const string& getOffset()
    {
        while (offsets.size() <= offset)
            addOffset();

        return offsets[offset];
    }
};

void dbgDumpTree(FILE* file, const Root* root, bool printLocation)
{
    HAREASSERT(file);
    HAREASSERT(root);

    DbgDumpWalker walker(file, printLocation);
    walker.dbgDumpRoot(root);
}

