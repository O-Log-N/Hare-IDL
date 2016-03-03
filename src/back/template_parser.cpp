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

#include "template_parser.h"
#include <assert.h> // for assert()


// main keywords
#define KEYWORD_STRING_BEGIN_TEMPLATE "BEGIN-TEMPLATE"
#define KEYWORD_STRING_END_TEMPLATE "END-TEMPLATE"
#define KEYWORD_STRING_FOR_EACH_OF_MEMBERS "FOR-EACH-OF-MEMBERS"
#define KEYWORD_STRING_IF "IF"
#define KEYWORD_STRING_ELSE "ELSE"
#define KEYWORD_STRING_ELIF "ELIF"
#define KEYWORD_STRING_ENDIF "ENDIF"
#define KEYWORD_STRING_ASSERT "ASSERT"

#define KEYWORD_STRING_OPEN_OUTPUT_FILE "OPEN-OUTPUT-FILE"
#define KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT "FOR-EACH-PUBLISHABLE-STRUCT"
#define KEYWORD_STRING_CLOSE_OUTPUT_FILE "CLOSE-OUTPUT-FILE"
#define KEYWORD_STRING_INCLUDE "INCLUDE"

// parameters
#define PARAM_STRING_TYPE "TYPE"
#define PARAM_STRING_BEGIN "BEGIN"
#define PARAM_STRING_END "END"
#define PARAM_STRING_TEMPLATE "TEMPLATE"

// main keywords ( starting from '@@' )
#define PLACEHOLDER_STRING_STRUCTNAME "@STRUCT-NAME@"
#define PLACEHOLDER_STRING_MEMBER_TYPE "@MEMBER-TYPE@"
#define PLACEHOLDER_STRING_MEMBER_NAME "@MEMBER-NAME@"

struct TemplateLine
{
	enum LINE_TYPE {
		CONTENT = 0,
		BEGIN_TEMPLATE,
		END_TEMPLATE,
		IF,
		ELSE,
		ELIF,
		ENDIF,
		INCLUDE,
		ASSERT,
		FOR_EACH_OF_MEMBERS, // used ONLY within STRUCT
		OPEN_OUTPUT_FILE,
		FOR_EACH_PUBLISHABLE_STRUCT,
		CLOSE_OUTPUT_FILE,
	};

	int type;
	int srcLineNum;
	vector<LinePart> lineParts;

	vector<ExpressionElement> expression; // used only for NODE_TYPE::IF and NODE_TYPE::ASSERT
	string templateName; // used only for NODE_TYPE::BEGIN_TEMPLATE
	string templateType; // used only for NODE_TYPE::BEGIN_TEMPLATE
	string outputFileName; // used only for NODE_TYPE::OPEN_OUTPUT_FILE

	enum FOREACH_PARAM_TYPE { BEGIN, END, TEMPLATE };
	FOREACH_PARAM_TYPE foreachParam; // used only for NODE_TYPE::FOR_EACH_OF_MEMBERS and NODE_TYPE::FOR_EACH_PUBLISHABLE_STRUCT
	string foreachTemplateName; // used only for NODE_TYPE::FOR_EACH_OF_MEMBERS and NODE_TYPE::FOR_EACH_PUBLISHABLE_STRUCT with foreachParam = TEMPLATE
};
typedef vector<TemplateLine>::iterator TEMPLATE_LINES_ITERATOR;

struct KeyWord
{
	const char* kw;
	int size;
	TemplateLine::LINE_TYPE id;
};

enum PARAMETER {
	NONE,
	BEGIN,
	END,
	TEMPLATE,
};

struct ParameterWord
{
	const char* kw;
	int size;
	PARAMETER id;
};

struct PlaceholderWord
{
	const char* kw;
	int size;
	PLACEHOLDER id;
};

const KeyWord keywords[] = 
{
	{KEYWORD_STRING_BEGIN_TEMPLATE, sizeof(KEYWORD_STRING_BEGIN_TEMPLATE)-1, TemplateLine::LINE_TYPE::BEGIN_TEMPLATE},
	{KEYWORD_STRING_END_TEMPLATE, sizeof(KEYWORD_STRING_END_TEMPLATE)-1, TemplateLine::LINE_TYPE::END_TEMPLATE},
	{KEYWORD_STRING_FOR_EACH_OF_MEMBERS, sizeof(KEYWORD_STRING_FOR_EACH_OF_MEMBERS)-1, TemplateLine::LINE_TYPE::FOR_EACH_OF_MEMBERS},
	{KEYWORD_STRING_IF, sizeof(KEYWORD_STRING_IF)-1, TemplateLine::LINE_TYPE::IF},
	{KEYWORD_STRING_ENDIF, sizeof(KEYWORD_STRING_ENDIF)-1, TemplateLine::LINE_TYPE::ENDIF},
	{KEYWORD_STRING_ELIF, sizeof(KEYWORD_STRING_ELIF)-1, TemplateLine::LINE_TYPE::ELIF},
	{KEYWORD_STRING_ELSE, sizeof(KEYWORD_STRING_ELSE)-1, TemplateLine::LINE_TYPE::ELSE},
	{KEYWORD_STRING_ASSERT, sizeof(KEYWORD_STRING_ASSERT)-1, TemplateLine::LINE_TYPE::ASSERT},
	{KEYWORD_STRING_OPEN_OUTPUT_FILE, sizeof(KEYWORD_STRING_OPEN_OUTPUT_FILE)-1, TemplateLine::LINE_TYPE::OPEN_OUTPUT_FILE},
	{KEYWORD_STRING_CLOSE_OUTPUT_FILE, sizeof(KEYWORD_STRING_CLOSE_OUTPUT_FILE)-1, TemplateLine::LINE_TYPE::CLOSE_OUTPUT_FILE},
	{KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT, sizeof(KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT)-1, TemplateLine::LINE_TYPE::FOR_EACH_PUBLISHABLE_STRUCT},
	{KEYWORD_STRING_INCLUDE, sizeof(KEYWORD_STRING_INCLUDE)-1, TemplateLine::LINE_TYPE::INCLUDE},
	{NULL, 0, TemplateLine::LINE_TYPE::CONTENT},
};

const PlaceholderWord placeholders[] = 
{
	{PLACEHOLDER_STRING_STRUCTNAME, sizeof(PLACEHOLDER_STRING_STRUCTNAME)-1, PLACEHOLDER::STRUCT_NAME},
	{PLACEHOLDER_STRING_MEMBER_TYPE, sizeof(PLACEHOLDER_STRING_MEMBER_TYPE)-1, PLACEHOLDER::MEMBER_TYPE},
	{PLACEHOLDER_STRING_MEMBER_NAME, sizeof(PLACEHOLDER_STRING_MEMBER_NAME)-1, PLACEHOLDER::MEMBER_NAME},
	{NULL, 0, PLACEHOLDER::VERBATIM},
};

const ParameterWord params[] = 
{
	{PARAM_STRING_BEGIN, sizeof(PARAM_STRING_BEGIN)-1, PARAMETER::BEGIN},
	{PARAM_STRING_END, sizeof(PARAM_STRING_END)-1, PARAMETER::END},
	{PARAM_STRING_TEMPLATE, sizeof(PARAM_STRING_TEMPLATE)-1, PARAMETER::TEMPLATE},
	{NULL, 0, PARAMETER::NONE},
};

class TemplateParser
{
	void dbgPrintIndent( int depth )
	{
		for ( int i=0; i<depth; i++ )
			fmt::print( " . " );
	}

	void dbgPrintLineParts( vector<LinePart>& parts )
	{
		size_t i;
		for ( i=0; i<parts.size(); i++ )
			switch ( parts[i].type )
			{
				case PLACEHOLDER::VERBATIM: fmt::print( "{}", parts[i].verbatim.c_str() ); break;
				case PLACEHOLDER::STRUCT_NAME: fmt::print( PLACEHOLDER_STRING_STRUCTNAME ); break;
				case PLACEHOLDER::MEMBER_TYPE: fmt::print( PLACEHOLDER_STRING_MEMBER_TYPE ); break;
				case PLACEHOLDER::MEMBER_NAME: fmt::print( PLACEHOLDER_STRING_MEMBER_NAME ); break;
				default:
				{
					fmt::print( "Unknown line_part.type = {} found\n", parts[i].type );
					assert( 0 == "Error: Not Implemented" );
				}
			}
	}

	string dbgPlaceholderIdToString( PLACEHOLDER placeholder )
	{
		return placeholders[ placeholder - PLACEHOLDER::VERBATIM ].kw; // TODO: revise implementation!!!
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
						case ExpressionElement::ARGTYPE::PLACEHOLDER: fmt::print( "{}", dbgPlaceholderIdToString( expression[i].placeholder ).c_str() ); break;
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

	void dbgPrintNode( TemplateNode& node, int depth )
	{
		dbgPrintIndent( depth );
		fmt::print( "[{}] ", node.srcLineNum );
		switch ( node.type )
		{
			case NODE_TYPE::FULL_TEMPLATE: fmt::print( "FULL_TEMPLATE {} TYPE = {}", node.templateName, node.templateType ); break;
			case NODE_TYPE::CONTENT: dbgPrintLineParts( node.lineParts ); break;
			case NODE_TYPE::IF: fmt::print( "IF " ); dbgPrintExpression( node.expression ); break;
			case NODE_TYPE::ASSERT: fmt::print( "ASSERT " ); dbgPrintExpression( node.expression ); break;
			case NODE_TYPE::FOR_EACH_OF_MEMBERS: fmt::print( "FOR_EACH_OF_MEMBERS " ); break;
			case NODE_TYPE::INCLUDE: fmt::print( "INCLUDE {}", node.templateName ); break;
			case NODE_TYPE::IF_TRUE_BRANCH: fmt::print( "IF_TRUE" ); break;
			case NODE_TYPE::IF_FALSE_BRANCH: fmt::print( "IF_FALSE" ); break;
			case NODE_TYPE::FOR_EACH_PUBLISHABLE_STRUCT: fmt::print( "FOR-EACH-PUBLISHABLE-STRUCT" ); break;
			case NODE_TYPE::OPEN_OUTPUT_FILE: fmt::print( "OPEN-OUTPUT-FILE {}", node.outputFileName ); break;
			default: fmt::print( "?????????" ); break;
		}

		if ( node.lineParts.size() )
		{
			assert( !(node.type == NODE_TYPE::IF || node.type == NODE_TYPE::ASSERT) );
			assert( node.type == NODE_TYPE::CONTENT );
		}
		fmt::print( "\n" );
		for ( size_t i=0; i<node.childNodes.size(); i++ )
			dbgPrintNode( node.childNodes[i], depth + 1 );
	}

	void dbgValidateNode( TemplateNode& node )
	{
		switch ( node.type )
		{
			case NODE_TYPE::CONTENT: 
			{
				assert( node.childNodes.size() == 0 );
				break;
			}
			case NODE_TYPE::FULL_TEMPLATE:
			{
				for ( size_t i=0; i<node.childNodes.size(); i++ )
					dbgValidateNode( node.childNodes[i] );
				break;
			}
			case NODE_TYPE::IF:
			{
				int childCnt = node.childNodes.size();
				assert( childCnt == 1 || node.childNodes.size() == 2 );
				if ( childCnt == 1 )
				{
					assert( node.childNodes[0].type == NODE_TYPE::IF_TRUE_BRANCH || node.childNodes[0].type == NODE_TYPE::IF_FALSE_BRANCH );
				}
				else
				{
					assert( node.childNodes[0].type == NODE_TYPE::IF_TRUE_BRANCH );
					assert( node.childNodes[1].type == NODE_TYPE::IF_FALSE_BRANCH );
				}
				for ( size_t i=0; i<node.childNodes.size(); i++ )
					dbgValidateNode( node.childNodes[i] );
				break;
			}
			case NODE_TYPE::ASSERT:
			{
				int childCnt = node.childNodes.size();
				assert( childCnt == 0 );
				break;
			}
			case NODE_TYPE::FOR_EACH_OF_MEMBERS:
			case NODE_TYPE::IF_TRUE_BRANCH:
			case NODE_TYPE::IF_FALSE_BRANCH:
			{
				for ( size_t i=0; i<node.childNodes.size(); i++ )
					dbgValidateNode( node.childNodes[i] );
				break;
			}
			case NODE_TYPE::INCLUDE:
			{
//				assert( 0 == "ERROR: NOT IMPLEMENTED" );
				break;
			}
		}
	}

	bool makeNodeTree( TemplateNode& rootNode, TEMPLATE_LINES_ITERATOR lnBegin, TEMPLATE_LINES_ITERATOR lnEnd )
	{
		auto it = lnBegin;
		while ( it != lnEnd )
		{
			switch ( it->type )
			{
				case TemplateLine::LINE_TYPE::BEGIN_TEMPLATE:
				{
					rootNode.type = NODE_TYPE::FULL_TEMPLATE;
					rootNode.templateName = it->templateName;
					rootNode.templateType = it->templateType;
					rootNode.srcLineNum = it->srcLineNum;
					++it;
					break;
				}
				case TemplateLine::LINE_TYPE::END_TEMPLATE:
				{
					++it;
					break;
				}
				case TemplateLine::LINE_TYPE::CONTENT:
				{
					TemplateNode node;
					node.type = NODE_TYPE::CONTENT;
					node.srcLineNum = it->srcLineNum;
					node.lineParts = it->lineParts;
					rootNode.childNodes.push_back( node );
					++it;
					break;
				}
				case TemplateLine::LINE_TYPE::FOR_EACH_OF_MEMBERS:
				{
					assert( it->lineParts.size() == 0 );
					TemplateNode node;
					node.srcLineNum = it->srcLineNum;
					node.type = NODE_TYPE::FOR_EACH_OF_MEMBERS;
					if ( it->foreachParam == TemplateLine::FOREACH_PARAM_TYPE::END )
					{
						fmt::print( "line {}: error: \"{} {}\" without matching \"{} {}\"\n", it->srcLineNum, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_END, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_BEGIN );
						return false;
					}
					else
					{
						// next TemplateLine::LINE_TYPE::FOR_EACH_OF_MEMBERS must be somewhere down, and it must be terminating (so far inner blocks of this type are not expected)
						if ( it->foreachParam == TemplateLine::FOREACH_PARAM_TYPE::TEMPLATE )
						{
							TemplateNode inclNode;
							inclNode.type = NODE_TYPE::INCLUDE;
							inclNode.srcLineNum = it->srcLineNum;
							inclNode.templateName = it->templateName;
							node.childNodes.push_back( inclNode );
							rootNode.childNodes.push_back( node );
							it++;
							break;
						}
						assert( it->foreachParam == TemplateLine::FOREACH_PARAM_TYPE::BEGIN );
						// next TemplateLine::LINE_TYPE::FOR_EACH_OF_MEMBERS must be somewhere down, and it must be terminating (so far inner blocks of this type are not expected)
						auto blockEnd = it;
						do { ++blockEnd; } while ( blockEnd != lnEnd && blockEnd->type != TemplateLine::LINE_TYPE::FOR_EACH_OF_MEMBERS );
						if ( blockEnd == lnEnd )
						{
							fmt::print( "line {}: error: \"{} {}\" without matching \"{} {}\"\n", it->srcLineNum, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_BEGIN, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_END );
							return false;
						}
						// at least, now we are at TemplateLine::LINE_TYPE::FOR_EACH_OF_MEMBERS node...
						if ( blockEnd->foreachParam == TemplateLine::FOREACH_PARAM_TYPE::END )
						{
							// VALID CASE
							makeNodeTree( node, it + 1, blockEnd );
							assert( node.lineParts.size() == 0 );
							rootNode.childNodes.push_back( node );
							it = blockEnd;
							it++;
							break;
						}
						else
						{
							fmt::print( "line {}: error: \"{} {}\" without matching \"{} {}\" (see also line {})\n", it->srcLineNum, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_BEGIN, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_END, blockEnd->srcLineNum );
							return false;
						}
					}

					assert( 0 ); // we should not be here!
				}
				case TemplateLine::LINE_TYPE::FOR_EACH_PUBLISHABLE_STRUCT:
				{
					assert( it->lineParts.size() == 0 );
					TemplateNode node;
					node.srcLineNum = it->srcLineNum;
					node.type = NODE_TYPE::FOR_EACH_PUBLISHABLE_STRUCT;
					if ( it->foreachParam == TemplateLine::FOREACH_PARAM_TYPE::END )
					{
						fmt::print( "line {}: error: \"{} {}\" without matching \"{} ...\"\n", it->srcLineNum, KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT, PARAM_STRING_END, KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT );
						return false;
					}
					else
					{
						if ( it->foreachParam == TemplateLine::FOREACH_PARAM_TYPE::TEMPLATE )
						{
							TemplateNode inclNode;
							inclNode.type = NODE_TYPE::INCLUDE;
							inclNode.srcLineNum = it->srcLineNum;
							inclNode.templateName = it->templateName;
							node.childNodes.push_back( inclNode );
							rootNode.childNodes.push_back( node );
							it++;
							break;
						}
						assert( it->foreachParam == TemplateLine::FOREACH_PARAM_TYPE::BEGIN );
						// next TemplateLine::LINE_TYPE::FOR_EACH_OF_MEMBERS must be somewhere down, and it must be terminating (so far inner blocks of this type are not expected)
						auto blockEnd = it;
						do { ++blockEnd; } while ( blockEnd != lnEnd && blockEnd->type != TemplateLine::LINE_TYPE::FOR_EACH_PUBLISHABLE_STRUCT );
						if ( blockEnd == lnEnd )
						{
							fmt::print( "line {}: error: \"{} {}\" without matching \"{} {}\"\n", it->srcLineNum, KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT, PARAM_STRING_BEGIN, KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT, PARAM_STRING_END );
							return false;
						}
						// at least, now we are at TemplateLine::LINE_TYPE::FOR_EACH_OF_MEMBERS node...
						if ( blockEnd->foreachParam == TemplateLine::FOREACH_PARAM_TYPE::END )
						{
							// VALID CASE
							makeNodeTree( node, it + 1, blockEnd );
							assert( node.lineParts.size() == 0 );
							rootNode.childNodes.push_back( node );
							it = blockEnd;
							it++;
							break;
						}
						else
						{
							fmt::print( "line {}: error: \"{} {}\" without matching \"{} {}\" (see also line {})\n", it->srcLineNum, KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT, PARAM_STRING_BEGIN, KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT, PARAM_STRING_END, blockEnd->srcLineNum );
							return false;
						}
					}

					assert( 0 ); // we should not be here!
				}
				case TemplateLine::LINE_TYPE::INCLUDE:
				{
					TemplateNode node;
					node.srcLineNum = it->srcLineNum;
					node.type = NODE_TYPE::INCLUDE;
					node.templateName = it->templateName;
					rootNode.childNodes.push_back( node );
					it++;
					break;
				}
				case TemplateLine::LINE_TYPE::OPEN_OUTPUT_FILE:
				{
					assert( it->lineParts.size() == 0 );
					TemplateNode node;
					node.srcLineNum = it->srcLineNum;
					node.type = NODE_TYPE::OPEN_OUTPUT_FILE;
					node.outputFileName = it->outputFileName;
					// next TemplateLine::LINE_TYPE::FOR_EACH_OF_MEMBERS must be somewhere down, and it must be terminating (so far inner blocks of this type are not expected)
					auto blockEnd = it;
					do { ++blockEnd; } while ( blockEnd != lnEnd && !( blockEnd->type == TemplateLine::LINE_TYPE::OPEN_OUTPUT_FILE || blockEnd->type == TemplateLine::LINE_TYPE::CLOSE_OUTPUT_FILE ) );
					if ( blockEnd == lnEnd )
					{
						fmt::print( "line {}: error: \"{}\" without matching \"{}\"\n", it->srcLineNum, KEYWORD_STRING_OPEN_OUTPUT_FILE, KEYWORD_STRING_CLOSE_OUTPUT_FILE );
						return false;
					}
					// at least, now we are at TemplateLine::LINE_TYPE::XXX_OUTPUT_FILE node...
					if ( blockEnd->type == TemplateLine::LINE_TYPE::CLOSE_OUTPUT_FILE )
					{
						// VALID CASE
						makeNodeTree( node, it + 1, blockEnd );
						assert( node.lineParts.size() == 0 );
						rootNode.childNodes.push_back( node );
						it = blockEnd;
						it++;
						break;
					}
					else
					{
						assert( blockEnd->type == TemplateLine::LINE_TYPE::OPEN_OUTPUT_FILE );
						fmt::print( "line {}: error: \"{}\" without matching \"{}\" (see also line {})\n", it->srcLineNum, KEYWORD_STRING_OPEN_OUTPUT_FILE, KEYWORD_STRING_CLOSE_OUTPUT_FILE, blockEnd->srcLineNum );
						return false;
					}
				}
				case TemplateLine::LINE_TYPE::CLOSE_OUTPUT_FILE: // processed out while processing a respective TemplateLine::LINE_TYPE::IF
				{
					fmt::print( "line {}: error: \"{}\" without matching \"{}\"\n", it->srcLineNum, KEYWORD_STRING_CLOSE_OUTPUT_FILE, KEYWORD_STRING_OPEN_OUTPUT_FILE );
					return false;
				}
				case TemplateLine::LINE_TYPE::IF:
				{
					// each NODE_TYPE::IF eventually ends up with a matching NODE_TYPE::ENDIF; inner IF/ENDIF pairs are allowed, too
					TemplateNode node;
					node.type = NODE_TYPE::IF;
					node.srcLineNum = it->srcLineNum;
					node.expression = it->expression;
					int ifendifBalance = 1;
					auto blockEnd = it;
					++blockEnd; 
					bool endifFound = false;
					do 
					{ 
						if ( blockEnd->type == TemplateLine::LINE_TYPE::IF )
							ifendifBalance ++;
						if ( blockEnd->type == TemplateLine::LINE_TYPE::ENDIF )
							ifendifBalance --;
						if ( ifendifBalance == 0 )
						{
							endifFound = true;
							break;
						}
						++blockEnd; 
					}
					while ( blockEnd != lnEnd );

					if ( !endifFound )
					{
						fmt::print( "line {}: error: \"{}\" without matching \"{}\"\n", it->srcLineNum, KEYWORD_STRING_IF, KEYWORD_STRING_ENDIF );
						return false;
					}
					assert( blockEnd->type == TemplateLine::LINE_TYPE::ENDIF );

					// VALID CASE
					// we need to separate its TRUE branche from the rest if IF/ENDIF body which is it FALSE branch
					// posive branch ends up (up to inner IF/ENDIF blocks) with one of TemplateLine::LINE_TYPE::ELSE, TemplateLine::LINE_TYPE::ELIF, or TemplateLine::LINE_TYPE::ENDIF (the latter is already processed out)
					// if none of TemplateLine::LINE_TYPE::ELSE or TemplateLine::LINE_TYPE::ELIF found, IF block has only its TRUE branch
					ifendifBalance = 0;
					auto trueBranchEnd = it;
					do 
					{ 
						++trueBranchEnd; 
						if ( trueBranchEnd->type == TemplateLine::LINE_TYPE::IF )
							ifendifBalance ++;
						if ( trueBranchEnd->type == TemplateLine::LINE_TYPE::ENDIF )
							ifendifBalance --;
						if ( ifendifBalance == 0 && (trueBranchEnd->type == TemplateLine::LINE_TYPE::ELSE || trueBranchEnd->type == TemplateLine::LINE_TYPE::ELIF ) )
						{
							break;
						}
					}
					while ( trueBranchEnd != blockEnd );

					TemplateNode ifTrue, ifFalse;
					ifTrue.type = NODE_TYPE::IF_TRUE_BRANCH;
					ifFalse.type = NODE_TYPE::IF_FALSE_BRANCH;
					ifTrue.srcLineNum = trueBranchEnd == it + 1 ? -1 : it->srcLineNum + 1;
					makeNodeTree( ifTrue, it + 1, trueBranchEnd );

					if ( trueBranchEnd->type == TemplateLine::LINE_TYPE::ELSE )
					{
						ifFalse.srcLineNum = trueBranchEnd != blockEnd ? trueBranchEnd->srcLineNum + 1 : -1;
						makeNodeTree( ifFalse, trueBranchEnd + 1, blockEnd );
					}
					else
					{
						assert( trueBranchEnd->type == TemplateLine::LINE_TYPE::ELIF );
						trueBranchEnd->type = TemplateLine::LINE_TYPE::IF;
						ifFalse.srcLineNum = trueBranchEnd != blockEnd ? trueBranchEnd->srcLineNum : -1;
						makeNodeTree( ifFalse, trueBranchEnd, blockEnd+1 );
					}

					node.childNodes.push_back( ifTrue );
					node.childNodes.push_back( ifFalse );

					rootNode.childNodes.push_back( node );
					it = blockEnd;
					++it;
					break;
				}
				case TemplateLine::LINE_TYPE::ASSERT:
				{
					TemplateNode node;
					node.type = NODE_TYPE::ASSERT;
					node.srcLineNum = it->srcLineNum;
					node.expression = it->expression;
					rootNode.childNodes.push_back( node );
					++it;
					break;
				}
				case TemplateLine::LINE_TYPE::ENDIF: // processed out while processing a respective TemplateLine::LINE_TYPE::IF
				{
					fmt::print( "line {}: error: \"{}\" without matching \"{}\"\n", it->srcLineNum, KEYWORD_STRING_ENDIF, KEYWORD_STRING_IF );
					return false;
				}
				case TemplateLine::LINE_TYPE::ELIF: // processed out while processing a respective TemplateLine::LINE_TYPE::IF
				{
					fmt::print( "line {}: error: \"{}\" without matching \"{}\"\n", it->srcLineNum, KEYWORD_STRING_ELIF, KEYWORD_STRING_IF );
					return false;
					break; // re-process it as TemplateLine::LINE_TYPE::IF
				}
				case TemplateLine::LINE_TYPE::ELSE: // processed out while processing a respective TemplateLine::LINE_TYPE::IF
				{
					fmt::print( "line {}: error: \"{}\" without matching \"{}\"\n", it->srcLineNum, KEYWORD_STRING_ELSE, KEYWORD_STRING_IF );
					return false;
				}
				default:
				{
					fmt::print( "line {}: error: unexpected line type {}\n", it->srcLineNum, it->type );
					++it;
					break;
				}
			} // end of switch
		}

		return true;
	}

	bool readLine( istream& tf, string& line, unsigned int& contentStart, int& currentLineNum )
	{
		contentStart = 0;
		bool somethingFound = false;
		bool startFound = false;
		for(;;) // through all chars - just read the line
		{
			char ch;
			tf.read( &ch, 1);
			if ( !tf )
				break;
			somethingFound = true;
			if ( ch == '\n' )
			{
				++currentLineNum;
				break;
			}
			line.push_back( ch );
			if ( !startFound && (ch == ' ' || ch == '\t') )
				contentStart++;
			else
				startFound = true;
		}
		while ( line.size() && *(line.end()-1) == '\r' )
			line.pop_back();
		return somethingFound;
	}

	template<class T> auto  parseSpecialWord( string& line, unsigned int& contentStart, T* words ) -> decltype( words->id )
	{
		int i;
		for ( i=0; ; i++ )
		{
			if ( words[i].size == 0 )
			{
				return words[i].id;
			}
			else if ( line.compare( contentStart, words[i].size, words[i].kw ) == 0 )
			{
				contentStart += words[i].size;
				return words[i].id;
			}
		}
	}

	TemplateLine::LINE_TYPE parseMainKeyword( string& line, unsigned int& contentStart )
	{
		assert( line.compare( contentStart, 2, "@@" ) == 0 );
		contentStart += 2;
		while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
		TemplateLine::LINE_TYPE ret = parseSpecialWord( line, contentStart, keywords );
		while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
		return ret;
	}

	PARAMETER parseParam( string& line, unsigned int& contentStart )
	{
		while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
		PARAMETER ret = parseSpecialWord( line, contentStart, params );
		return ret;
	}

	PLACEHOLDER parsePlaceholder( string& line, unsigned int& contentStart )
	{
		while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
		PLACEHOLDER ret = parseSpecialWord( line, contentStart, placeholders );
		return ret;
	}

	void skipSpaces( string& line, unsigned int& contentStart )
	{
		while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
	}

	void parseLineContent( string& lc, vector<LinePart>& parts )
	{
		// we have to go char by char; if '@' is found, make sure it's not a placeholder, or replace it accordingly
		unsigned int pos = 0;
		size_t sz = lc.size();
		LinePart part;
		part.type = PLACEHOLDER::VERBATIM;
		do
		{
			if ( lc[ pos ] != '@' )
			{
				part.verbatim.push_back( lc[ pos ] );
				pos ++;
			}
			else
			{
				int placehldr = parsePlaceholder( lc, pos );
				switch ( placehldr )
				{
					case PLACEHOLDER::VERBATIM: 
					{
						part.verbatim.push_back( lc[ pos ] ); 
						pos ++; 
						break;
					}
					case PLACEHOLDER::STRUCT_NAME:
					case PLACEHOLDER::MEMBER_TYPE:
					case PLACEHOLDER::MEMBER_NAME:
					{
						parts.push_back( part ); 
						part.verbatim.clear(); 
						part.type = placehldr; 
						parts.push_back( part ); 
						part.type = PLACEHOLDER::VERBATIM; 
						break;
					}
					default:
					{
						assert( 0 == "NOT IMPLEMENTED" );
						break;
					}
				}
			}
		}
		while ( pos < sz );

		if ( part.verbatim.size() )
		{
			assert( part.type == PLACEHOLDER::VERBATIM );
			parts.push_back( part ); 
		}
	}

	void parseIfCondition( string& lc, vector<ExpressionElement>& expression )
	{
		// we have to go char by char; if '@' is found, make sure it's not a placeholder, or replace it accordingly
		unsigned int pos = 0;
		size_t sz = lc.size();
		ExpressionElement element;
		element.oper = ExpressionElement::OPERATION::PUSH;
		element.argtype = ExpressionElement::ARGTYPE::STRING;
		do
		{
			if ( lc[ pos ] == '@' )
			{
				PLACEHOLDER placehldr = parsePlaceholder( lc, pos );
				switch ( placehldr )
				{
					case PLACEHOLDER::VERBATIM: 
					{
						element.stringValue.push_back( lc[ pos ] ); 
						pos ++; 
						break;
					}
					case PLACEHOLDER::MEMBER_TYPE:
					case PLACEHOLDER::MEMBER_NAME:
					{
						assert( element.oper == ExpressionElement::OPERATION::PUSH );
						assert( element.argtype == ExpressionElement::ARGTYPE::STRING );
						if ( element.stringValue.size() )
							expression.push_back( element ); 
						element.stringValue.clear(); 
						element.argtype = ExpressionElement::ARGTYPE::PLACEHOLDER; 
						element.placeholder = placehldr;
						expression.push_back( element ); 
						element.argtype = ExpressionElement::ARGTYPE::STRING; 
						break;
					}
					default:
					{
						assert( 0 == "NOT IMPLEMENTED" );
						break;
					}
				}
			}
			else
			{
				if ( lc[ pos ] == ' ' || lc[ pos ] == '\t')
				{
					if ( element.stringValue.size() )
					{
						assert( element.oper == ExpressionElement::OPERATION::PUSH );
						assert( element.argtype == ExpressionElement::ARGTYPE::STRING );
						expression.push_back( element );
						element.stringValue.clear();
					}
					pos ++;
				}
				else if ( lc.compare( pos, 2, "==" ) == 0 )
				{
					if ( element.stringValue.size() )
					{
						assert( element.oper == ExpressionElement::OPERATION::PUSH );
						assert( element.argtype == ExpressionElement::ARGTYPE::STRING );
						expression.push_back( element );
						element.stringValue.clear();
					}
					element.stringValue.clear();
					element.oper = ExpressionElement::OPERATION::EQ;
					element.argtype = ExpressionElement::ARGTYPE::NONE;
					expression.push_back( element );
					element.oper = ExpressionElement::OPERATION::PUSH;
					element.argtype = ExpressionElement::ARGTYPE::STRING;
					pos += 2;
				}
				else if ( lc.compare( pos, 2, "!=" ) == 0 )
				{
					if ( element.stringValue.size() )
					{
						assert( element.oper == ExpressionElement::OPERATION::PUSH );
						assert( element.argtype == ExpressionElement::ARGTYPE::STRING );
						expression.push_back( element );
						element.stringValue.clear();
					}
					element.stringValue.clear();
					element.oper = ExpressionElement::OPERATION::NEQ;
					element.argtype = ExpressionElement::ARGTYPE::NONE;
					expression.push_back( element );
					element.oper = ExpressionElement::OPERATION::PUSH;
					element.argtype = ExpressionElement::ARGTYPE::STRING;
					pos += 2;
				}
				else
				{
					element.stringValue.push_back( lc[ pos ] );
					pos ++;
				}
			}
		}
		while ( pos < sz );

		if ( element.stringValue.size() )
		{
			assert( element.oper == ExpressionElement::OPERATION::PUSH );
			assert( element.argtype == ExpressionElement::ARGTYPE::STRING );
			expression.push_back( element ); 
		}
	}

public:
	enum PROCESSING_RESULT {OK = 0, NO_MORE_TEMPLATES = 1, FAILED_ERROR = 2, FAILED_BUID_TREE_ERROR = 3,	FAILED_INTERNAL = 4};

	PROCESSING_RESULT tokenize( istream& tf, vector<TemplateLine>& templateLines, int& currentLineNum )
	{
		// it is assumed here that starting from a current position in a file any content other than the beginning and the rest of template can be safely ignored
		bool startFound = false;
		unsigned int contentStart = 0;
		bool endFound = false;

		string templateName;

		for( ;;) // through all nodes, find template beginning
		{
			string line;
			if ( !readLine( tf, line, contentStart, currentLineNum ) )
				break;
			if ( contentStart == line.size() )
				continue; // no content
			if ( line[contentStart] == '@' && contentStart + 1 < line.size() && line[contentStart+1] == '@' ) // this is only what we expect at the beginning of any service line
			{
				contentStart += 2;
				while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
				if ( line.compare( contentStart, sizeof(KEYWORD_STRING_BEGIN_TEMPLATE)-1, KEYWORD_STRING_BEGIN_TEMPLATE ) == 0 )
				{
					TemplateLine thisLine;
					thisLine.srcLineNum = currentLineNum;
					thisLine.type = TemplateLine::LINE_TYPE::BEGIN_TEMPLATE;

					contentStart += sizeof(KEYWORD_STRING_BEGIN_TEMPLATE)-1;
					while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;

					// read name
					while ( contentStart < line.size() && (!(line[contentStart] == ' ' || line[contentStart] == '\t'))) templateName.push_back( line[contentStart++] );
					thisLine.templateName = templateName;

					while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
					if ( line.compare( contentStart, sizeof(PARAM_STRING_TYPE)-1, PARAM_STRING_TYPE ) != 0 )
					{
						fmt::print( "line {}: error: no \"{}\" after \"{}\"\n", currentLineNum, PARAM_STRING_TYPE, KEYWORD_STRING_BEGIN_TEMPLATE );
						return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
					}
					contentStart += sizeof(PARAM_STRING_TYPE)-1;
					while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
					if ( contentStart < line.size() && line[contentStart] != '=' )
					{
						fmt::print( "line {}: error: no \"{}\" after \"{}\"\n", currentLineNum, "=", PARAM_STRING_TYPE );
						return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
					}
					contentStart++;
					while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;

					// read type
					while ( contentStart < line.size() && (!(line[contentStart] == ' ' || line[contentStart] == '\t'))) thisLine.templateType.push_back( line[contentStart++] );

					while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
					if ( !( contentStart == line.size() ) )
					{
						fmt::print( "line {}: error: unexpected tokens\n", currentLineNum );
						return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
					}

					templateLines.push_back( thisLine );

					startFound = true;
					break;
				}
			}
			// at this point a template has started...
		}

		if ( !startFound )
		{
			if ( templateLines.size() )
			{
				fmt::print( "line {}: error: no no template has been found\n", currentLineNum );
				return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
			}
			else
			{
				return NO_MORE_TEMPLATES;
			}
		}

		// go through other lines
		for( ;;) // through all nodes, find template beginning
		{
			TemplateLine thisLine;
			thisLine.srcLineNum = currentLineNum;

			string line;
			if ( !readLine( tf, line, contentStart, currentLineNum ) )
				break;
			bool isContent = line.compare( contentStart, 2, "@@" ) != 0;
			if ( isContent ) // an empty line => not ctr line => content line => keep "as is"
			{
				thisLine.type = TemplateLine::LINE_TYPE::CONTENT;
				parseLineContent( line, thisLine.lineParts );
				templateLines.push_back( thisLine );
				continue;
			}

			TemplateLine::LINE_TYPE kwd = parseMainKeyword( line, contentStart );

			// unexpected template start
			if ( kwd == TemplateLine::LINE_TYPE::BEGIN_TEMPLATE )
			{
				fmt::print( "line {}: error: \"{}\" is unexpected\n", currentLineNum, KEYWORD_STRING_BEGIN_TEMPLATE );
				return FAILED_ERROR;
			}

			// is template end?
			if ( kwd == TemplateLine::LINE_TYPE::END_TEMPLATE )
			{
				TemplateLine thisLine;
				thisLine.srcLineNum = currentLineNum;
				thisLine.type = TemplateLine::LINE_TYPE::END_TEMPLATE;

				// read name
				string endName;
				while ( contentStart < line.size() && (!(line[contentStart] == ' ' || line[contentStart] == '\t'))) endName.push_back( line[contentStart++] );
				if ( endName != templateName )
				{
					fmt::print( "line {}: error: name does not match that at template beginning\n", currentLineNum );
					return FAILED_ERROR;
				}
				while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
				if ( !( contentStart == line.size() || ( contentStart + 1 == line.size() || line[contentStart] == '\r' ) ) )
				{
					fmt::print( "line {}: error: unexpected tokens\n", currentLineNum );
					return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
				}

				templateLines.push_back( thisLine );

				endFound = true;
				break;
			}

			// other control nodes
			thisLine.type = kwd;
			switch ( kwd )
			{
				case TemplateLine::LINE_TYPE::IF:
				case TemplateLine::LINE_TYPE::ELIF:
				case TemplateLine::LINE_TYPE::ASSERT:
				{
					parseIfCondition( string( line.begin() + contentStart, line.end() ), thisLine.expression );
					break;
				}
				case TemplateLine::LINE_TYPE::FOR_EACH_OF_MEMBERS:
				{
					unsigned int contentStart_1 = 0;
					string remaining = string( line.begin() + contentStart, line.end() );
					PARAMETER param = parseParam( remaining, contentStart_1 );
					bool goodParam = param == PARAMETER::BEGIN || param == PARAMETER::END || param == PARAMETER::TEMPLATE;
					if ( !goodParam )
					{
						fmt::print( "line {}: error: \"{}\", \"{}\" or \"{}\" is expected after \"{}\"\n", currentLineNum, PARAM_STRING_BEGIN, PARAM_STRING_END, PARAM_STRING_TEMPLATE, KEYWORD_STRING_FOR_EACH_OF_MEMBERS );
						return FAILED_ERROR;
					}
					skipSpaces( remaining, contentStart );
					if ( param == PARAMETER::TEMPLATE )
					{
						thisLine.foreachParam = TemplateLine::FOREACH_PARAM_TYPE::TEMPLATE;
						thisLine.templateName = string( remaining.begin() + contentStart_1, remaining.end() );
					}
					else
					{
						if ( contentStart_1 < remaining.size() )
						{
							fmt::print( "line {}: error: unexpected token(s) \"{}\"\n", currentLineNum, string( remaining.begin() + contentStart_1, remaining.end() ) );
							return FAILED_ERROR;
						}
						thisLine.foreachParam = param == PARAMETER::BEGIN ? TemplateLine::FOREACH_PARAM_TYPE::BEGIN : TemplateLine::FOREACH_PARAM_TYPE::END;
					}
					break;
				}
				case TemplateLine::LINE_TYPE::FOR_EACH_PUBLISHABLE_STRUCT:
				{
					unsigned int contentStart_1 = 0;
					string remaining = string( line.begin() + contentStart, line.end() );
					PARAMETER param = parseParam( remaining, contentStart_1 );
					bool goodParam = param == PARAMETER::BEGIN || param == PARAMETER::END || param == PARAMETER::TEMPLATE;
					if ( !goodParam )
					{
						fmt::print( "line {}: error: \"{}\", \"{}\" or \"{}\" is expected after \"{}\"\n", currentLineNum, PARAM_STRING_BEGIN, PARAM_STRING_END, PARAM_STRING_TEMPLATE, KEYWORD_STRING_FOR_EACH_PUBLISHABLE_STRUCT );
						return FAILED_ERROR;
					}
					skipSpaces( remaining, contentStart_1 );
					if ( param == PARAMETER::TEMPLATE )
					{
						thisLine.foreachParam = TemplateLine::FOREACH_PARAM_TYPE::TEMPLATE;
						thisLine.templateName = string( remaining.begin() + contentStart_1, remaining.end() );
					}
					else
					{
						if ( contentStart_1 < remaining.size() )
						{
							fmt::print( "line {}: error: unexpected token(s) \"{}\"\n", currentLineNum, string( remaining.begin() + contentStart_1, remaining.end() ) );
							return FAILED_ERROR;
						}
						thisLine.foreachParam = param == PARAMETER::BEGIN ? TemplateLine::FOREACH_PARAM_TYPE::BEGIN : TemplateLine::FOREACH_PARAM_TYPE::END;
					}
					break;
				}
				case TemplateLine::LINE_TYPE::INCLUDE:
				{
					unsigned int contentStart_1 = 0;
					string remaining = string( line.begin() + contentStart, line.end() );
					PARAMETER param = parseParam( remaining, contentStart_1 );
					bool goodParam = param == PARAMETER::TEMPLATE;
					if ( !goodParam )
					{
						fmt::print( "line {}: error: \"{}\" is expected after \"{}\"\n", currentLineNum, PARAM_STRING_TEMPLATE, KEYWORD_STRING_INCLUDE );
						return FAILED_ERROR;
					}
					skipSpaces( remaining, contentStart_1 );
					thisLine.templateName = string( remaining.begin() + contentStart_1, remaining.end() );
					break;
				}
				case TemplateLine::LINE_TYPE::OPEN_OUTPUT_FILE:
				{
					skipSpaces( line, contentStart );
					thisLine.outputFileName = string( line.begin() + contentStart, line.end() );
					if ( thisLine.outputFileName.size() && thisLine.outputFileName[0] == '\"' )
					{
						size_t pos = 1; while ( pos < thisLine.outputFileName.size() && thisLine.outputFileName[pos] != '\"' ) pos++;
						if ( pos == thisLine.outputFileName.size() )
						{
							fmt::print( "line {}: error: file name string runs away\n", currentLineNum );
							return FAILED_ERROR;
						}
						thisLine.outputFileName = string( thisLine.outputFileName.begin() + 1, thisLine.outputFileName.begin() + pos );
					}
					break;
				}
				case TemplateLine::LINE_TYPE::CLOSE_OUTPUT_FILE:
				{
					skipSpaces( line, contentStart );
					if ( contentStart < line.size() )
					{
						fmt::print( "line {}: error: unexpected token(s) \"{}\"\n", currentLineNum, string( line.begin() + contentStart, line.end() ) );
						return FAILED_ERROR;
					}
					break;
				}
				default:
				{
					LinePart part;
					part.type = PLACEHOLDER::VERBATIM;
					part.verbatim = string( line.begin() + contentStart, line.end() );
					thisLine.lineParts.push_back( part );
				}
			}
			templateLines.push_back( thisLine );
		}

		if ( !endFound )
		{
			fmt::print( "line {}: error: \"{}\" not found\n", currentLineNum, KEYWORD_STRING_END_TEMPLATE );
			return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
		}

		return OK;
	}

	PROCESSING_RESULT loadTemplate( istream& tf, TemplateNode& rootNode, int& currentLineNum )
	{
		vector<TemplateLine> templateLines;
		PROCESSING_RESULT ret = tokenize( tf, templateLines, currentLineNum );
		if ( ret != PROCESSING_RESULT::OK )
			return ret;
		rootNode.type = NODE_TYPE::FULL_TEMPLATE;
		bool treeOK = makeNodeTree( rootNode, templateLines.begin(), templateLines.end() );
		if ( !treeOK )
		{
			fmt::print( "line {}: error: building tree failed\n", rootNode.srcLineNum );
			return FAILED_BUID_TREE_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
		}
		dbgValidateNode( rootNode );

		return OK;
	}

	void dbgPrintTree( TemplateNode& rootNode )
	{
		dbgPrintNode( rootNode, 0 );
	}
};


bool loadTemplate( istream& tf, TemplateNode& rootNode, int& currentLineNum )
{
	TemplateParser tp;
	return tp.loadTemplate( tf, rootNode, currentLineNum ) == TemplateParser::PROCESSING_RESULT::OK;
}

void dbgPrintTree( TemplateNode& rootNode )
{
	TemplateParser tp;
	tp.dbgPrintTree( rootNode );
}

bool loadTemplates( istream& tf, TemplateNodeSpace& nodeSpace, int& currentLineNum )
{
	TemplateParser::PROCESSING_RESULT ret;
	for (;;)
	{
		TemplateParser tp;
		TemplateNode rootNode;
		ret = tp.loadTemplate( tf, rootNode, currentLineNum );
		if ( ret == TemplateParser::PROCESSING_RESULT::OK )
			nodeSpace.templates.push_back( rootNode );
		else
			break;
	}
	return ret == TemplateParser::PROCESSING_RESULT::NO_MORE_TEMPLATES;
}

void dbgPrintTemplateTrees( TemplateNodeSpace& nodeSpace )
{
	for ( auto tt:nodeSpace.templates)
	{
		dbgPrintTree( tt );
		fmt::print( "\n" );
	}
}
