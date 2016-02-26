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

#ifndef HARE_H
#define HARE_H

#include <exception>
#include "../../3rdparty/cppformat/cppformat/format.h"

namespace hare {
    class AssertException : public std::exception {
        const char* cond;
        const char* msg;
        const char* file;
        int line;
        
        public:
        AssertException(const char* cond_, const char* file_, int line_)
        : cond(cond_), msg(nullptr), file(file_), line(line_) {
        }
        AssertException(const char* cond_, const char* msg_, const char* file_, int line_)
        : cond(cond_), msg(msg_), file(file_), line(line_) {
        }
    }
}

//#defining things within namespace is misleading,
//  so they go outside

//Unlike usual assert(), HAREASSERT():
//  * is ALWAYS on
//  * instead of calling abort(), throws hare::AssertException()
//
//NB: if changing HAREASSERT()/HAREASSERTM(),
//  make sure to consult with http://cnicholson.net/2009/02/stupid-c-tricks-adventures-in-assert/
#define HAREASSERT(cond) \
    do { \
        if(!(cond)) { \
            throw hare::AssertException(#cond,__FILE__,__LINE__); \
        } \
    } while(0);

//HAREASSERTM() stands for "HAREASSERT with Message"
#define HAREASSERTM(cond,msg) \
    do { \
        if(!(cond)) { \
            throw hare::AssertException(#cond,msg,__FILE__,__LINE__); \
        } \
    } while(0);

#endif // HARE_H
