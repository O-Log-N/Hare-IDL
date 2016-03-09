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

#ifndef RAIISTDIOFILE_H_INCLUDED
#define RAIISTDIOFILE_H_INCLUDED

#include <stdio.h>

class RaiiStdioFile {
  FILE* f;
  
  public:
  RaiiStdioFile(FILE* f_)
  : f(f_) {
  }
  ~RaiiStdioFile() {
    if(f)
      fclose(f);
  }
  
  RaiiStdioFile(const RaiiStdioFile&) = delete;
  RaiiStdioFile& operator =(const RaiiStdioFile&) = delete;
  
  operator FILE*() {
    return f;
  }
};

#endif //RAIISTDIOFILE_H_INCLUDED
