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

#include "template_tree_builder.h"
#include "template_line_tokenizer.h"
#include "template_line_tokens.h" // for tree printing
#include <assert.h> // for assert()

void dbgPrintIndent( int depth )
{
	for ( int i=0; i<depth; i++ )
		fmt::print( " . " );
}

void dbgPrintLineParts( vector<LinePart>& parts )
{
	size_t i;
	for ( i=0; i<parts.size(); i++ )
	{
		if ( parts[i].type == PLACEHOLDER::VERBATIM )
			fmt::print( "{}", parts[i].verbatim.c_str() );
		else
			fmt::print( "{}", placeholderToString( parts[i].type ).c_str() );
	}
}

void dbgPrintExpression( vector<ExpressionElement>& expression )
{
	size_t i;
	for ( i=0; i<expression.size(); i++ )
		switch ( expression[i].oper )
		{
			case ExpressionElement::OPERATION::PUSH:
			{
				switch ( expression[i].argtype )
				{
					case ExpressionElement::ARGTYPE::STRING: fmt::print( "{}", expression[i].stringValue.c_str() ); break;
					case ExpressionElement::ARGTYPE::NUMBER: fmt::print( "{}", expression[i].numberValue ); break;
					case ExpressionElement::ARGTYPE::PLACEHOLDER: fmt::print( "{}", placeholderToString( expression[i].placeholder ).c_str() ); break;
					case ExpressionElement::ARGTYPE::NONE: fmt::print( "\"\"" ); break;
					default: fmt::print( "?????????" ); break;
				}
				break;
			}
			case ExpressionElement::OPERATION::EQ: fmt::print( " == " ); break;
			case ExpressionElement::OPERATION::NEQ: fmt::print( " != " ); break;
			default:
			{
				fmt::print( "Unknown expression.oper = {} found\n", expression[i].oper );
				assert( 0 == "Error: Not Implemented" );
			}
		}
}

void dbgPrintAttributes( map<AttributeName, vector<LinePart>>& attributes )
{
	for ( auto it:attributes )
	{
		fmt::print( "{}{}", attributeNameToString( it.first.id ).c_str(), it.first.ext );
		if ( it.second.size() )
		{
			fmt::print( "=" );
			dbgPrintLineParts( it.second );
		}
		fmt::print( " " );
	}
}


void dbgPrintNode_( TemplateNode& node, int depth )
{
	dbgPrintIndent( depth );
	if ( node.type == NODE_TYPE::CONTENT )
	{
		assert( node.attributes.size() == 1 );
		dbgPrintLineParts( node.attributes.begin()->second );
	}
	else
	{
		fmt::print( "[{}] {} ", node.srcLineNum, nodeTypesToString( node.type ) );
		dbgPrintExpression( node.expression );
		dbgPrintAttributes( node.attributes );
	}
	fmt::print( "\n" );
	for ( size_t i=0; i<node.childNodes.size(); i++ )
		dbgPrintNode_( node.childNodes[i], depth + 1 );
}

	
bool buildTemplateTree( TemplateNode& root, vector<TemplateLine>& lines, size_t& flidx )
{
	for ( ; flidx<lines.size(); )
	{
		TemplateLine::LINE_TYPE ltype = lines[flidx].type;
		switch ( ltype )
		{
			case TemplateLine::LINE_TYPE::CONTENT:
			{
				TemplateNode node;
				node.type = NODE_TYPE::CONTENT;
				node.srcLineNum = lines[flidx].srcLineNum;
				node.attributes = lines[flidx].attributes;
				root.childNodes.push_back( node );
				++flidx;
				break;
			}
			case TemplateLine::LINE_TYPE::IF:
			case TemplateLine::LINE_TYPE::ELIF_TO_IF:
			{
				TemplateNode node;
				node.type = NODE_TYPE::IF;
				node.srcLineNum = lines[flidx].srcLineNum;
				node.expression = lines[flidx].expression;
				++flidx;
				TemplateNode nodeTrueBranch;
				nodeTrueBranch.type = NODE_TYPE::IF_TRUE_BRANCH;
				nodeTrueBranch.srcLineNum = lines[flidx].srcLineNum;
				if ( !buildTemplateTree( nodeTrueBranch, lines, flidx ) )
					return false;
				node.childNodes.push_back( nodeTrueBranch );
				// TODO: think about internal while( ELIF )
				if ( lines[flidx].type == TemplateLine::LINE_TYPE::ELIF ) // this is not that ELIF with which we've entered; it's a nested one!
				{
					lines[flidx].type = TemplateLine::LINE_TYPE::ELIF_TO_IF;
					TemplateNode nodeFalseBranch;
					nodeFalseBranch.type = NODE_TYPE::IF_FALSE_BRANCH;
					nodeFalseBranch.srcLineNum = lines[flidx].srcLineNum;
					// no changes to flidx; we will repeat processing on the next level
					if ( !buildTemplateTree( nodeFalseBranch, lines, flidx ) )
						return false;
					node.childNodes.push_back( nodeFalseBranch );
				}
				else if ( lines[flidx].type == TemplateLine::LINE_TYPE::ELSE )
				{
					TemplateNode nodeFalseBranch;
					nodeFalseBranch.type = NODE_TYPE::IF_FALSE_BRANCH;
					nodeFalseBranch.srcLineNum = lines[flidx].srcLineNum;
					++flidx;
					if ( !buildTemplateTree( nodeFalseBranch, lines, flidx ) )
						return false;
					node.childNodes.push_back( nodeFalseBranch );
				}
				if ( lines[flidx].type != TemplateLine::LINE_TYPE::ENDIF )
				{
					fmt::print( "line {}: error: ENDIF expected\n", lines[flidx].srcLineNum );
					return false;
				}
				if ( ltype == TemplateLine::LINE_TYPE::IF )
				{
					++flidx;
				}
				root.childNodes.push_back( node );
				break;
			}
			case TemplateLine::LINE_TYPE::INCLUDE:
			{
				TemplateNode node;
				node.type = NODE_TYPE::INCLUDE;
				node.srcLineNum = lines[flidx].srcLineNum;
				node.attributes = lines[flidx].attributes;
				root.childNodes.push_back( node );
				++flidx;
				break;
			}
			case TemplateLine::LINE_TYPE::ASSERT:
			{
				TemplateNode node;
				node.type = NODE_TYPE::ASSERT;
				node.srcLineNum = lines[flidx].srcLineNum;
				node.expression = lines[flidx].expression;
				root.childNodes.push_back( node );
				++flidx;
				break;
			}
			case TemplateLine::LINE_TYPE::OPEN_OUTPUT_FILE:
			{
				TemplateNode node;
				node.type = NODE_TYPE::OPEN_OUTPUT_FILE;
				node.srcLineNum = lines[flidx].srcLineNum;
				node.attributes = lines[flidx].attributes;
				++flidx;
				if ( !buildTemplateTree( node, lines, flidx ) )
					return false;
				if ( lines[flidx].type != TemplateLine::LINE_TYPE::CLOSE_OUTPUT_FILE )
				{
					fmt::print( "line {}: error: CLOSE-OUTPUT-FILE expected\n", lines[flidx].srcLineNum );
					return false;
				}
				++flidx;
				root.childNodes.push_back( node );
				break;
			}
			case TemplateLine::LINE_TYPE::FOR_EACH_OF_MEMBERS:
			{
				bool isEnd = lines[flidx].attributes.find( {ATTRIBUTE::END, ""} ) != lines[flidx].attributes.end();
				if ( isEnd )
					return true; // it's upper level end or bullshit
				TemplateNode node;
				node.type = NODE_TYPE::FOR_EACH_OF_MEMBERS;
				node.srcLineNum = lines[flidx].srcLineNum;
				// we may have include statement here, let's check
				auto includeTemplate = lines[flidx].attributes.find( {ATTRIBUTE::TEMPLATE, ""} );
				if ( includeTemplate != lines[flidx].attributes.end() )
				{
					TemplateNode nodeIncludeTemplate;
					nodeIncludeTemplate.type = NODE_TYPE::INCLUDE;
					nodeIncludeTemplate.srcLineNum = lines[flidx].srcLineNum;
					nodeIncludeTemplate.attributes.insert( make_pair(AttributeName(ATTRIBUTE::TEMPLATE, ""), includeTemplate->second ) );
					node.childNodes.push_back( nodeIncludeTemplate );
					++flidx;
				}
				else
				{
					bool isBegin = lines[flidx].attributes.find( {ATTRIBUTE::BEGIN, ""} ) != lines[flidx].attributes.end();
					if ( !isBegin )
					{
						fmt::print( "line {}: error: FOR_EACH_OF_MEMBERS has unexpected parameter set\n", lines[flidx].srcLineNum );
						assert( isBegin );
						return false;
					}
					++flidx;
					if ( !buildTemplateTree( node, lines, flidx ) )
						return false;
					bool isBegin1 = lines[flidx].attributes.find( {ATTRIBUTE::BEGIN, ""} ) != lines[flidx].attributes.end();
					bool isEnd1 = lines[flidx].attributes.find( {ATTRIBUTE::END, ""} ) != lines[flidx].attributes.end();
					if ( !isEnd1 )
					{
						fmt::print( "line {}: error: FOR_EACH_OF_MEMBERS END expected\n", lines[flidx].srcLineNum );
						assert( isBegin1 );
						return false;
					}
					++flidx;
				}
				root.childNodes.push_back( node );
				break;
			}
			case TemplateLine::LINE_TYPE::FOR_EACH_PUBLISHABLE_STRUCT:
			{
				bool isEnd = lines[flidx].attributes.find( {ATTRIBUTE::END, ""} ) != lines[flidx].attributes.end();
				if ( isEnd )
					return true; // it's upper level end or bullshit
				TemplateNode node;
				node.type = NODE_TYPE::FOR_EACH_PUBLISHABLE_STRUCT;
				node.srcLineNum = lines[flidx].srcLineNum;
				// we may have include statement here, let's check
				auto includeTemplate = lines[flidx].attributes.find( {ATTRIBUTE::TEMPLATE, ""} );
				if ( includeTemplate != lines[flidx].attributes.end() )
				{
					TemplateNode nodeIncludeTemplate;
					nodeIncludeTemplate.type = NODE_TYPE::INCLUDE;
					nodeIncludeTemplate.srcLineNum = lines[flidx].srcLineNum;
					nodeIncludeTemplate.attributes.insert( make_pair(AttributeName(ATTRIBUTE::TEMPLATE, ""), includeTemplate->second ) );
					node.childNodes.push_back( nodeIncludeTemplate );
					++flidx;
				}
				else
				{
					bool isBegin = lines[flidx].attributes.find( {ATTRIBUTE::BEGIN, ""} ) != lines[flidx].attributes.end();
					if ( !isBegin )
					{
						fmt::print( "line {}: error: FOR_EACH_PUBLISHABLE_STRUCT has unexpected parameter set\n", lines[flidx].srcLineNum );
						assert( isBegin );
						return false;
					}
					++flidx;
					if ( !buildTemplateTree( node, lines, flidx ) )
						return false;
					bool isBegin1 = lines[flidx].attributes.find( {ATTRIBUTE::BEGIN, ""} ) != lines[flidx].attributes.end();
					bool isEnd1 = lines[flidx].attributes.find( {ATTRIBUTE::END, ""} ) != lines[flidx].attributes.end();
					if ( !isEnd1 )
					{
						fmt::print( "line {}: error: FOR_EACH_PUBLISHABLE_STRUCT END expected\n", lines[flidx].srcLineNum );
						assert( isBegin1 );
						return false;
					}
					++flidx;
				}
				root.childNodes.push_back( node );
				break;
			}
			case TemplateLine::LINE_TYPE::BEGIN_TEMPLATE:
			{
				int lnStart = lines[flidx].srcLineNum;
				string templateName;
				auto attrName = lines[flidx].attributes.find( {ATTRIBUTE::NAME, ""} );
				bool nameOK = attrName != lines[flidx].attributes.end();
				if ( nameOK )
				{
					auto& lineParts = attrName->second;
					nameOK = lineParts.size() == 1;
					if ( nameOK )
						templateName = lineParts[0].verbatim;
					else
					{
						fmt::print( "line {}: error: template has bad or no name\n", lines[flidx].srcLineNum );
						return false;
					}
				}

				TemplateNode node;
				node.type = NODE_TYPE::FULL_TEMPLATE;
				node.srcLineNum = lines[flidx].srcLineNum;
				node.attributes = lines[flidx].attributes;
				++flidx;
				if ( !buildTemplateTree( node, lines, flidx ) )
					return false;
				root.childNodes.push_back( node );
				if ( lines[flidx].type != TemplateLine::LINE_TYPE::END_TEMPLATE )
				{
					fmt::print( "line {}: error: END-TEMPLATE expected\n", lines[flidx].srcLineNum );
					return false;
				}
				string closingTemplateName;
				attrName = lines[flidx].attributes.find( {ATTRIBUTE::NAME, ""} );
				nameOK = attrName != lines[flidx].attributes.end();
				if ( nameOK )
				{
					auto& lineParts = attrName->second;
					nameOK = lineParts.size() == 1;
					if ( nameOK )
					{
						closingTemplateName = lineParts[0].verbatim;
						if ( templateName != closingTemplateName )
						{
							fmt::print( "line {}: error: template name at template begin (see line {}) does not coincide with that at template end\n", lines[flidx].srcLineNum, lnStart );
							return false;
						}
					}
					else
					{
						fmt::print( "line {}: error: template has bad or no name\n", lines[flidx].srcLineNum );
						return false;
					}
				}
				++flidx;
				break;
			}
			default:
				return true;
		}
	}

	return true;
}


bool loadTemplates( istream& tf, TemplateNodeSpace& nodeSpace, int& currentLineNum )
{
	for (;;)
	{
		TemplateNode rootNode;
		vector<TemplateLine> templateLines;
		bool ret = tokenizeTemplateLines( tf, templateLines, currentLineNum );
		if ( !ret )
			break;
		size_t flidx = 0;
		ret = buildTemplateTree( rootNode, templateLines, flidx );
		nodeSpace.templates.push_back( rootNode.childNodes[0] );
	}
	return true;
}

void dbgPrintTemplateTrees( TemplateNodeSpace& nodeSpace )
{
	for ( auto tt:nodeSpace.templates)
	{
		dbgPrintNode_( tt, 0 );
		fmt::print( "\n" );
	}
}

