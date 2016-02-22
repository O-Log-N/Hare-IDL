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

#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED "include guard"

#include <string>
#include <ostream>
#include <exception>
#include <vector>
#include <list>

#include "common.h"

namespace hare
{

	class AssertException : public std::exception
	{
	public:
		const char* msg;
		const char* file;
		int line;

		AssertException() : msg(), file(0), line(0) {}
		AssertException(const char* msg, const char* file, int line) : msg(msg), file(file), line(line) {}
	};

	class AbortException : public std::exception
	{
	public:
		AbortException() {}
	};

	class UnresolvedException : public std::exception
	{
	public:
		Location location;
		std::string message;
		std::vector<std::string> extendedMessage;

		UnresolvedException(const Location& location, const std::string& message) :
			location(location), message(message) {}
		UnresolvedException(const Location& location, const std::string& message, const std::vector<std::string>& extendedMessage) :
			location(location), message(message), extendedMessage(extendedMessage) {}
		UnresolvedException(const Location& location, const std::string& message, const std::string& extraLine) :
			location(location), message(message), extendedMessage() {
			extendedMessage.push_back(extraLine);
		}

		~UnresolvedException() throw() {}
	};

	class ResolutionCycleException : public std::exception
	{
	public:
		Location location;
		std::string message;

		ResolutionCycleException(const Location& location, const std::string& message) :
			location(location), message(message) {}

		~ResolutionCycleException() throw() {}
	};

	class PreviousResolutionException : public std::exception
	{
	public:
		PreviousResolutionException() {}
		~PreviousResolutionException() throw() {}
	};

	std::string formatError(const Location& loc, const std::string& msg);

	std::string formatMessage(const std::string& msg, const std::string& arg);
	std::string formatMessage(const std::string& msg, size_t arg);
	std::string formatMessage(const std::string& msg, const std::string& arg0, const std::string& arg1);

	void reportWarning(const Location& loc, const std::string& msg);
	inline void reportWarning(const Location& loc, const std::string& msg, const std::string& arg)
	{
		reportWarning(loc, formatMessage(msg, arg));
	}


	void plainError(const std::string& msg);
	inline void plainError(const std::string& msg, const std::string& arg)
	{
		plainError(formatMessage(msg, arg));
	}
	inline void plainError(const std::string& msg, const std::string& arg0, const std::string& arg1)
	{
		plainError(formatMessage(msg, arg0, arg1));
	}

	void reportError(const Location& loc, const std::string& msg);
	inline void reportError(const Location& loc, const std::string& msg, const std::string& arg)
	{
		reportError(loc, formatMessage(msg, arg));
	}
	inline void reportError(const Location& loc, const std::string& msg, const std::string& arg0, const std::string& arg1)
	{
		reportError(loc, formatMessage(msg, arg0, arg1));
	}

	inline
		void reportPreviousDef(const Location& loc)
	{
		reportError(loc, "Previous definition here");
	}


	struct ResolvedType;
	void reportTypeError(const Location& loc, const std::string& msg, const ResolvedType& ctype);
	void reportTypePairError(const Location& loc, const std::string& msg, const ResolvedType& to, const ResolvedType& from);

	void reportAbortException(const AbortException& e);
	void reportAssertException(const AssertException& e);
	void reportUnresolvedException(const UnresolvedException& e);
	void reportResolutionCycleException(const ResolutionCycleException& e);
	void reportUnknownFatalException(const std::exception& e);
	void reportUnknownFatalException();

	void catchedException(const Location& loc, const std::exception& e);
	void setError();
	bool hasError();

}

#endif // ERROR_H_INCLUDED
