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

        string tags;
        for (auto it = node->tags.begin(); it != node->tags.end(); ++it) {
            if (it != node->tags.begin())
                tags += ",";
            tags += *it;
        }

        dbgWriteWithLocation(node->location, fmt::format("{} Structure name='{}' tags='{}'", kind, node->name, tags));

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

    static string dbgTypeToString(const DataType& dataType) {

        string result = "kind='";
        switch (dataType.typeKind) {
        case DataType::PLAIN:
            result += "PLAIN";
            break;
        case DataType::ENUM:
            result += "ENUM";
            break;
        case DataType::CLASS:
            result += "CLASS";
            break;
        case DataType::SEQUENCE:
            result += "SEQUENCE";
            break;
        case DataType::VECTOR:
            result += "VECTOR";
            break;
        default:
            HAREASSERT(false);
        }

        result += "' name='";
        result += dataType.name;
        result += "'";
        if (!dataType.arguments.empty()) {
            result += " arguments='";
            for (auto it = dataType.arguments.begin(); it != dataType.arguments.end(); ++it) {
                if (it != dataType.arguments.begin())
                    result += ",";
                result += fmt::format("{}", *it);
            }
            result += "'";
        }
        if (!dataType.enumValues.empty()) {
            result += " enumValues='";
            for (auto it = dataType.enumValues.begin(); it != dataType.enumValues.end(); ++it) {
                if (it != dataType.enumValues.begin())
                    result += ",";
                result += fmt::format("{}={}", it->first, it->second);
            }
            result += "'";
        }

        return result;
    }


    void dbgDumpDataMember(const DataMember* node) {

        string attr;
        if (node->extendTo)
            attr += "extendTo=true";
        if (node->defaulValue != 0)
            attr += fmt::format("defaultValue='{}'", node->defaulValue);

        string typeStr = dbgTypeToString(node->type);
        dbgWriteWithLocation(node->location, fmt::format("DataMember name='{}' {} {}", node->name, attr, typeStr));
    }

    static string dbgEncodingToString(const EncodingAttributes& encoding) {

        string result = "encodingAttr='";
        result += encoding.name;
        result += "'";
        if (!encoding.arguments.empty()) {
            result += " arguments='";
            for (auto it = encoding.arguments.begin(); it != encoding.arguments.end(); ++it) {
                if (it != encoding.arguments.begin())
                    result += ",";
                result += fmt::format("{}", *it);
            }
            result += "'";
        }

        return result;
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

