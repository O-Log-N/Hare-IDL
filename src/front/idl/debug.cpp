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
	size_t offset;
	vector<string> offsets;

	DbgDumpWalker(FILE* file) : file(file), offset(0)
	{
		offsets.push_back("");
	}

public:
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

	void dbgWrite(const string& text) {
		fmt::print(file, "{}{}\n", getOffset(), text);
	}

	void dbgWriteWithLocation(const Location& location, const string& text) {
		string l = locationToString(location);
		fmt::print(file, "{}{} {}\n", getOffset(), text, l);
	}

	void dbgDumpRoot(const Root* node) {
		dbgWrite("Root");
		++offset;
		for (auto& it : node->structures)
			dbgDumpStructure(it.get());

		--offset;

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
		dbgWriteWithLocation(node->location, fmt::format("{} Structure '{}'", kind, node->name));

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
		dbgWriteWithLocation(node->location, fmt::format("DataMember name='{}' type='{}'", node->name, node->type.name));
	}

	void dbgDumpEncodedMember(const EncodedMembers* node) {
		dbgWriteWithLocation(node->location, fmt::format("EncodedMembers encodingAttr='{}'", node->encodingAttr.name));
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

};

void dbgDumpTree(FILE* file, const Root* root)
{
	HAREASSERT(file);
	HAREASSERT(root);

	DbgDumpWalker walker(file);
	walker.dbgDumpRoot(root);
}

