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

void dbgPrintExpression( vector<ExpressionElement>& expression );
void dbgPrintLineParts( vector<LinePart2>& parts )
{
	size_t i;
	for ( i=0; i<parts.size(); i++ )
	{
		if ( parts[i].isVerbatim )
			fmt::print( "{}", parts[i].verbatim.c_str() );
		else
		{
			fmt::print( "@" );
			dbgPrintExpression( parts[i].expr );
			fmt::print( "@" );
		}
	}
}

void dbgPrintExpression( vector<ExpressionElement>& expression )
{
	size_t i;
	for ( i=0; i<expression.size(); i++ )
	{
		if ( expression[i].oper == OPERATOR::PUSH )
		{
			switch ( expression[i].argtype )
			{
				case ARGTYPE::STRING: 
				{
					fmt::print( "\"" ); 
					dbgPrintLineParts( expression[i].lineParts );
					fmt::print( "\" " ); 
					break;
				}
				case ARGTYPE::NUMBER: fmt::print( "{} ", expression[i].numberValue ); break;
				case ARGTYPE::PLACEHOLDER:
				{
					string placeholderStr = standardNameToString( expression[i].ph );
					fmt::print( "{} ", placeholderStr.c_str() );
					break;
				}
				case ARGTYPE::NO_ARGTYPE: fmt::print( "\"\"" ); break;
				default: fmt::print( "[????[type={}]????] ", static_cast<int>(expression[i].argtype) ); break;
			}
		}
		else if ( expression[i].oper == OPERATOR::CALL_BUILTIN_FN )
		{
			fmt::print( "{}() ", functionNameToString( expression[i].fn.id ).c_str() );
		}
		else if ( expression[i].oper == OPERATOR::CALL_USERDEF_FN )
		{
			fmt::print( "{}() ", expression[i].userDefFunction.name.c_str() );
		}
		else
		{
			fmt::print( "{} ", operatorToString( expression[i].oper ).c_str() );
		}
	}
}

void dbgPrintAttributes( map<AttributeName, vector<ExpressionElement>>& attributes )
{
	for ( auto it:attributes )
	{
		fmt::print( "{}{}", attributeNameToString( it.first.id ).c_str(), it.first.ext );
		if ( it.second.size() )
		{
			fmt::print( "=" );
			dbgPrintExpression( it.second );
		}
		fmt::print( " " );
	}
}


void dbgPrintNode_( TemplateNode& node, int depth )
{
	dbgPrintIndent( depth );
	fmt::print( "[{}] {} ", node.srcLineNum, nodeTypesToString( node.type ) );
	if ( node.type == NODE_TYPE::CONTENT )
	{
		assert( node.attributes.size() == 1 );
		dbgPrintExpression( node.attributes.begin()->second );
	}
	else
	{
		dbgPrintExpression( node.expression );
		dbgPrintAttributes( node.attributes );
	}
	fmt::print( "\n" );
	for ( size_t i=0; i<node.childNodes.size(); i++ )
		dbgPrintNode_( node.childNodes[i], depth + 1 );
}

void dbgPrintRootNode( TemplateRootNode& node, int depth )
{
	dbgPrintIndent( depth );
	fmt::print( "[{}] {} ", node.srcLineNum, node.isFunction ? "FUNCTION-NODE" : "TEMPLATE-NODE" );
	fmt::print( "NAME= \"{}\" ", node.name );
	for ( auto p:node.params )
	{
		fmt::print( "{}{}", attributeNameToString( p.id ).c_str(), p.ext );
		fmt::print( " " );
	}
	fmt::print( "\n" );
	for ( size_t i=0; i<node.childNodes.size(); i++ )
		dbgPrintNode_( node.childNodes[i], depth + 1 );
}

void postProcessReturningTemplate( TemplateNode& node )
{
	assert( node.type != NODE_TYPE::CONTENT );
	node.isFunctionNode = true;
	for ( size_t i=0; i<node.childNodes.size(); i++ )
		postProcessReturningTemplate( node.childNodes[i] );
}

void postProcessReturningTemplate( TemplateRootNode& node )
{
	for ( size_t i=0; i<node.childNodes.size(); i++ )
		postProcessReturningTemplate( node.childNodes[i] );
}

bool getTemplateOrFunctionName( const TemplateLine& line, string& templateName)
{
	auto attrName = line.attributes.find( {ATTRIBUTE::NAME, ""} );
	bool nameOK = attrName != line.attributes.end();
	if ( nameOK )
	{
		auto& expr = attrName->second;
		nameOK = expr.size() == 1;
		if ( nameOK )
			nameOK = expr[0].lineParts.size() == 1;
		if ( nameOK )
			nameOK = expr[0].lineParts[0].isVerbatim;
		if ( nameOK )
			templateName = expr[0].lineParts[0].verbatim;
		if ( !nameOK )
		{
			fmt::print( "line {}: error: template/function has bad or no name\n", line.srcLineNum );
			assert( 0 );
			return false;
		}
	}
	return nameOK;
}

bool buildTemplateTree( TemplateNode& root, vector<TemplateLine>& lines, size_t& flidx, bool& isFunctionNode )
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
				if ( !buildTemplateTree( nodeTrueBranch, lines, flidx, isFunctionNode ) )
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
					if ( !buildTemplateTree( nodeFalseBranch, lines, flidx, isFunctionNode ) )
						return false;
					node.childNodes.push_back( nodeFalseBranch );
				}
				else if ( lines[flidx].type == TemplateLine::LINE_TYPE::ELSE )
				{
					TemplateNode nodeFalseBranch;
					nodeFalseBranch.type = NODE_TYPE::IF_FALSE_BRANCH;
					nodeFalseBranch.srcLineNum = lines[flidx].srcLineNum;
					++flidx;
					if ( !buildTemplateTree( nodeFalseBranch, lines, flidx, isFunctionNode ) )
						return false;
					node.childNodes.push_back( nodeFalseBranch );
				}
				if ( lines[flidx].type != TemplateLine::LINE_TYPE::ENDIF )
				{
					fmt::print( "line {}: error: ENDIF expected\n", lines[flidx].srcLineNum );
					assert( 0 );
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
				node.attributes = lines[flidx].attributes;
				root.childNodes.push_back( node );
				++flidx;
				break;
			}
			case TemplateLine::LINE_TYPE::DBG_PRINT:
			{
				TemplateNode node;
				node.type = NODE_TYPE::DBG_PRINT;
				node.srcLineNum = lines[flidx].srcLineNum;
				if ( lines[flidx].expression.size() == 0 )
				{
					fmt::print( "line {}: error: expression required\n", lines[flidx].srcLineNum );
					assert( 0 );
					return false;
				}
				if ( lines[flidx].attributes.size() )
				{
					fmt::print( "line {}: error: attributes are not expected\n", lines[flidx].srcLineNum );
					assert( 0 );
					return false;
				}
				node.expression = lines[flidx].expression;
				root.childNodes.push_back( node );
				++flidx;
				break;
			}
			case TemplateLine::LINE_TYPE::RETURN:
			{
				TemplateNode node;
				node.type = NODE_TYPE::RETURN;
				node.srcLineNum = lines[flidx].srcLineNum;
				node.expression = lines[flidx].expression;
				node.isFunctionNode = true;
				isFunctionNode = true;
				assert( lines[flidx].attributes.size() == 0 ); // TODO: proper error reporting
				root.childNodes.push_back( node );
				++flidx;
				break;
			}
			case TemplateLine::LINE_TYPE::LET:
			{
				TemplateNode node;
				node.type = NODE_TYPE::LET;
				node.srcLineNum = lines[flidx].srcLineNum;
				node.expression = lines[flidx].expression;
				node.attributes = lines[flidx].attributes;
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
				if ( !buildTemplateTree( node, lines, flidx, isFunctionNode ) )
					return false;
				if ( lines[flidx].type != TemplateLine::LINE_TYPE::CLOSE_OUTPUT_FILE )
				{
					fmt::print( "line {}: error: CLOSE-OUTPUT-FILE expected\n", lines[flidx].srcLineNum );
					assert( 0 );
					return false;
				}
				++flidx;
				root.childNodes.push_back( node );
				break;
			}
			case TemplateLine::LINE_TYPE::FOR_EACH:
			{
				bool isEnd = lines[flidx].attributes.find( {ATTRIBUTE::END, ""} ) != lines[flidx].attributes.end();
				if ( isEnd )
					return true; // it's upper level end or bullshit

				if ( lines[flidx].expression.size() == 0 )
				{
					fmt::print( "line {}: error: {} expression expected\n", lines[flidx].srcLineNum, mainKeywordToString( ltype ) );
					assert( 0 );
					return false;
				}

				TemplateNode node;
				node.type = NODE_TYPE::FOR_EACH;
				node.srcLineNum = lines[flidx].srcLineNum;
				node.expression = lines[flidx].expression;
				int varCnt = 0;
				for ( const auto it:lines[flidx].attributes )
				{
					if ( it.first.id == ATTRIBUTE::LOCAL )
					{
						if ( varCnt )
						{
							fmt::print( "line {}: error: {} assumes only a single iterator variable\n", lines[flidx].srcLineNum, mainKeywordToString( ltype ) );
							assert( 0 );
							return false;
						}
						node.attributes.insert( it );
						++varCnt;
					}
				}

				if ( varCnt == 0 )
				{
					fmt::print( "line {}: error: {} requires an iterator variable to be specified\n", lines[flidx].srcLineNum, mainKeywordToString( ltype ) );
					assert( 0 );
					return false;
				}

				++flidx;
				if ( !buildTemplateTree( node, lines, flidx, isFunctionNode ) )
					return false;

				bool isEnd1 = lines[flidx].attributes.find( {ATTRIBUTE::END, ""} ) != lines[flidx].attributes.end();
				if ( !isEnd1 )
				{
					fmt::print( "line {}: error: {} END expected\n", lines[flidx].srcLineNum, mainKeywordToString( ltype ) );
					assert( 0 );
					return false;
				}
				++flidx;
				root.childNodes.push_back( node );

				break;
			}
			case TemplateLine::LINE_TYPE::WHILE:
			{
				if ( lines[flidx].attributes.size() )
				{
					fmt::print( "line {}: error: {} does not have attributes\n", lines[flidx].srcLineNum, mainKeywordToString( ltype ) );
					assert( 0 );
					return false;
				}
				if ( lines[flidx].expression.size() == 0 )
				{
					fmt::print( "line {}: error: {} requires expression\n", lines[flidx].srcLineNum, mainKeywordToString( ltype ) );
					assert( 0 );
					return false;
				}

				TemplateNode node;
				node.type = NODE_TYPE::WHILE;
				node.srcLineNum = lines[flidx].srcLineNum;
				node.expression = lines[flidx].expression;

				++flidx;
				if ( !buildTemplateTree( node, lines, flidx, isFunctionNode ) )
					return false;
				if ( lines[flidx].type != TemplateLine::LINE_TYPE::ENDWHILE )
				{
					fmt::print( "line {}: error: {} expected\n", lines[flidx].srcLineNum, mainKeywordToString( TemplateLine::LINE_TYPE::ENDWHILE ) );
					assert( 0 );
					return false;
				}
				++flidx;
				root.childNodes.push_back( node );
				break;
			}
			default:
				return true;
		}
	}

	return true;
}

bool buildTemplateTree( TemplateRootNode& root, vector<TemplateLine>& lines, size_t& flidx, bool& isFunctionNode )
{
	for ( ; flidx<lines.size(); )
	{
		TemplateLine::LINE_TYPE ltype = lines[flidx].type;
		switch ( ltype )
		{
			case TemplateLine::LINE_TYPE::BEGIN_TEMPLATE:
			case TemplateLine::LINE_TYPE::BEGIN_FUNCTION:
			{
				int lnStart = lines[flidx].srcLineNum;
				string templateName;
				bool nameOK = getTemplateOrFunctionName( lines[flidx], templateName);

				// Function names are of a special form: FUNCTION-XXX. Let's check it
				if ( ltype == TemplateLine::LINE_TYPE::BEGIN_FUNCTION )
				{
					size_t contentStart = 0;
					SpecialName sn = parseStandardName( templateName, contentStart );
					if ( sn.id != PLACEHOLDER::FUNCTION_MINUS )
					{
						fmt::print( "line {}: error: name of a user-defined function must be of a form FUNCTION-XXX\n", lines[flidx].srcLineNum );
						assert( 0 );
						return false;
					}
				}

				root.srcLineNum = lines[flidx].srcLineNum;
				for (auto& p:lines[flidx].args)
					root.params.push_back( p );
				++flidx;
				TemplateNode node;
				if ( !buildTemplateTree( node, lines, flidx, isFunctionNode ) )
					return false;
				root.childNodes = std::move( node.childNodes );
//				root.params = std::move( lines[flidx].args );
				root.isFunction = ltype == TemplateLine::LINE_TYPE::BEGIN_FUNCTION || isFunctionNode; // TODO: revise as soon as functions are in effect
				isFunctionNode = root.isFunction;
				auto terminator = ltype == TemplateLine::LINE_TYPE::BEGIN_FUNCTION ? TemplateLine::LINE_TYPE::END_FUNCTION : TemplateLine::LINE_TYPE::END_TEMPLATE;
				if ( lines[flidx].type != terminator )
				{
					fmt::print( "line {}: error: {} expected\n", lines[flidx].srcLineNum, mainKeywordToString( terminator ) );
					assert( 0 );
					return false;
				}

				string closingTemplateName;
				nameOK = getTemplateOrFunctionName( lines[flidx], closingTemplateName);
				if ( nameOK )
				{
					if ( templateName != closingTemplateName )
					{
						fmt::print( "line {}: error: template/function name at template begin (see line {}) does not coincide with that at template/function end\n", lines[flidx].srcLineNum, lnStart );
						assert( 0 );
						return false;
					}
				}
				else
				{
					fmt::print( "line {}: error: template has bad or no name\n", lines[flidx].srcLineNum );
					assert( 0 );
					return false;
				}
				root.name = templateName;
				++flidx;
				break;
			}
			default:
				return true;
		}
	}

	return true;
}


bool loadTemplates( FILE* tf, TemplateNodeSpace& nodeSpace, int& currentLineNum )
{
	for (;;)
	{
		TemplateRootNode rootNode;
		vector<TemplateLine> templateLines;
		bool ret = tokenizeTemplateLines( tf, templateLines, currentLineNum );
		if ( !ret )
			break;
		size_t flidx = 0;
		bool isFunctionNode = false;
		ret = buildTemplateTree( rootNode, templateLines, flidx, isFunctionNode );
		fmt::print( "line {}: {}: {}\n", currentLineNum, rootNode.name, rootNode.isFunction ? "FUNCTION" : "TEMPLATE" );
		if ( isFunctionNode )
			postProcessReturningTemplate( rootNode );
		nodeSpace.templates.push_back( rootNode );
	}
	return true;
}

void dbgPrintTemplateTrees( TemplateNodeSpace& nodeSpace )
{
	for ( auto tt:nodeSpace.templates)
	{
		dbgPrintRootNode( tt, 0 );
		fmt::print( "\n" );
	}
}

