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

#include "error.h"

#include <cstdio>
#include <sstream>
#include <iostream>

#include "base_node.h"


using namespace std;

static bool errorFlag = false;

std::string formatError(const Location& loc, const std::string& msg)
{
	string str;
	str.append(loc.toString());
	str.append(" - ");
	str.append(msg);
	str.append(" -");
	return str;
}

#pragma warning( push )
#pragma warning( disable : 4996 )

std::string formatMessage(const std::string& msg, const std::string& arg)
{
	ASSERT(msg.size() < 160); //arbitrary limit
	char buffer[1100];
	const char* a = arg.size() < 1000 ? arg.c_str() : "<...message too long...>";
	sprintf(buffer, msg.c_str(), a);
	return buffer;
}
std::string formatMessage(const std::string& msg, size_t arg)
{
	ASSERT(msg.size() < 80); //arbitrary limit
	char buffer[100];
	sprintf(buffer, msg.c_str(), arg);
	return buffer;
}
std::string formatMessage(const std::string& msg, const std::string& arg0, const std::string& arg1)
{
	ASSERT(msg.size() < 80); //arbitrary limit
	char buffer[2100];
	const char* a0 = arg0.size() < 1000 ? arg0.c_str() : "<...message too long...>";
	const char* a1 = arg1.size() < 1000 ? arg1.c_str() : "<...message too long...>";
	sprintf(buffer, msg.c_str(), a0, a1);
	return buffer;
}

#pragma warning( pop )

void reportWarning(const Location& loc, const string& msg)
{
	cerr << "warning: " << loc.toString() << " - " << msg << " -" << endl;
}

void plainError(const std::string& msg)
{
	setError();
	cerr << "error: - " << msg << " -" << endl;
}

void reportError(const Location& loc, const std::string& msg)
{
	setError();
	cerr << "error: " << loc.toString() << " - " << msg << " -" << endl;
}

void reportTypeError(const Location& loc, const std::string& msg, const ResolvedType& ctype)
{
	setError();
	cerr << "error: " << loc.toString() << " - " << msg << " <" << ctype.toString() << "> -" << endl;
}

void reportTypePairError(const Location& loc, const std::string& msg, const ResolvedType& to, const ResolvedType& from)
{
	setError();
	cerr << "error: " << loc.toString() << " - " << msg << " <" << to.toString() << ", " << from.toString() << "> -" << endl;
}

void reportAssertException(const AssertException& e)
{
	cerr << "assert: @" << e.file << ":" << e.line << " - " << e.what() << " -" << endl;
}

void reportAbortException(const AbortException& e)
{
	cerr << "fatal: - Aborting due to previous errors -" << endl;
}

void reportUnresolvedException(const UnresolvedException& e)
{
	reportError(e.location, e.message);

	for (vector<string>::const_iterator it = e.extendedMessage.begin(); it != e.extendedMessage.end(); ++it)
		cerr << (*it) << endl;
}
void reportResolutionCycleException(const ResolutionCycleException& e)
{
	reportError(e.location, e.message);
}

void reportUnknownFatalException(const std::exception& e)
{
	cerr << "fatal: - Unknown fatal failure";
	cerr << " type = '" << typeid(e).name() << "'";
	if (e.what())
		cerr << " what = '" << e.what() << "'";

	cerr << " -" << endl;
}

void reportUnknownFatalException()
{
	cerr << "fatal: - Unknown fatal failure -" << endl;
}

void catchedException(const Location& loc, const std::exception& e)
{
	if (hasError())
		return;


	reportError(loc, formatMessage("Internal Error. Unknown '%s' exception caught.", typeid(e).name()));
}


void setError()
{
	errorFlag = true;
}

bool hasError()
{
	return errorFlag;
}
