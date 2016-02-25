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

#ifndef TEMPLATE_INSTANTIATOR_H
#define TEMPLATE_INSTANTIATOR_H

#include "../idlc_include.h"
#include "template_parser.h"
#include "back_idl_tree.h"

#define CONTEXT_STRUCT 1
#define CONTEXT_STRUCT_MEMBER 2

class TemplateInstantiator
{
protected:
	bool calcConditionOfIfNode( TemplateNode& ifNode );
	virtual void applyNode( TemplateNode& node );

public:
	TemplateInstantiator() {}

	virtual string placeholder( int placeholderId );
};


#endif // TEMPLATE_INSTANTIATOR_H
