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
#define PARAM_STRING_BEGIN_TEMPLATE "BEGIN-TEMPLATE"
#define PARAM_STRING_END_TEMPLATE "END-TEMPLATE"
#define KEYWORD_STRING_FOR_EACH_OF_MEMBERS "FOR-EACH-OF-MEMBERS"
#define KEYWORD_STRING_IF "IF"
#define KEYWORD_STRING_ELSE "ELSE"
#define KEYWORD_STRING_ELIF "ELIF"
#define PARAM_STRING_ENDIF "ENDIF"
#define PARAM_STRING_ASSERT "ASSERT"

// parameters
#define PARAM_STRING_TYPE "TYPE"
#define PARAM_STRING_BEGIN "BEGIN"
#define PARAM_STRING_END "END"

// main keywords ( starting from '@@' )
#define PLACEHOLDER_STRING_STRUCTNAME "@STRUCT-NAME@"
#define PLACEHOLDER_STRING_MEMBER_TYPE "@MEMBER-TYPE@"
#define PLACEHOLDER_STRING_MEMBER_NAME "@MEMBER-NAME@"

struct KeyWord
{
	const char* kw;
	int size;
	NODE_TYPE id;
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

KeyWord keywords[] = 
{
	{PARAM_STRING_BEGIN_TEMPLATE, sizeof(PARAM_STRING_BEGIN_TEMPLATE)-1, NODE_TYPE::BEGIN_TEMPLATE},
	{PARAM_STRING_END_TEMPLATE, sizeof(PARAM_STRING_END_TEMPLATE)-1, NODE_TYPE::END_TEMPLATE},
	{KEYWORD_STRING_FOR_EACH_OF_MEMBERS, sizeof(KEYWORD_STRING_FOR_EACH_OF_MEMBERS)-1, NODE_TYPE::FOR_EACH_OF_MEMBERS},
	{KEYWORD_STRING_IF, sizeof(KEYWORD_STRING_IF)-1, NODE_TYPE::IF},
	{PARAM_STRING_ENDIF, sizeof(PARAM_STRING_ENDIF)-1, NODE_TYPE::ENDIF},
	{KEYWORD_STRING_ELIF, sizeof(KEYWORD_STRING_ELIF)-1, NODE_TYPE::ELIF},
	{KEYWORD_STRING_ELSE, sizeof(KEYWORD_STRING_ELSE)-1, NODE_TYPE::ELSE},
	{PARAM_STRING_ASSERT, sizeof(PARAM_STRING_ASSERT)-1, NODE_TYPE::ASSERT},
	{NULL, 0, NODE_TYPE::CONTENT}
};

PlaceholderWord placeholders[] = 
{
	{PLACEHOLDER_STRING_STRUCTNAME, sizeof(PLACEHOLDER_STRING_STRUCTNAME)-1, PLACEHOLDER::STRUCT_NAME},
	{PLACEHOLDER_STRING_MEMBER_TYPE, sizeof(PLACEHOLDER_STRING_MEMBER_TYPE)-1, PLACEHOLDER::MEMBER_TYPE},
	{PLACEHOLDER_STRING_MEMBER_NAME, sizeof(PLACEHOLDER_STRING_MEMBER_NAME)-1, PLACEHOLDER::MEMBER_NAME},
	{NULL, 0, PLACEHOLDER::VERBATIM},
};

ParameterWord params[] = 
{
	{PARAM_STRING_BEGIN, sizeof(PARAM_STRING_BEGIN)-1, PARAMETER::BEGIN},
	{PARAM_STRING_END, sizeof(PARAM_STRING_END)-1, PARAMETER::END},
	{PARAM_STRING_TYPE, sizeof(PARAM_STRING_TYPE)-1, PARAMETER::TYPE},
	{NULL, 0, PARAMETER::NONE},
};

class TemplateParser
{
	void dbgPrintIndent( int depth )
	{
		for ( int i=0; i<depth; i++ )
			printf( " . " );
	}

	void dbgPrintLineParts( vector<LinePart>& parts )
	{
		unsigned int i;
		for ( i=0; i<parts.size(); i++ )
			switch ( parts[i].type )
			{
				case PLACEHOLDER::VERBATIM: printf( parts[i].verbatim.c_str() ); break;
				case PLACEHOLDER::STRUCT_NAME: printf( PLACEHOLDER_STRING_STRUCTNAME ); break;
				case PLACEHOLDER::MEMBER_TYPE: printf( PLACEHOLDER_STRING_MEMBER_TYPE ); break;
				case PLACEHOLDER::MEMBER_NAME: printf( PLACEHOLDER_STRING_MEMBER_NAME ); break;
				case PARAMETER::TYPE: printf( " %s", PARAM_STRING_TYPE ); break;
				case PARAMETER::BEGIN: printf( " %s", PARAM_STRING_BEGIN ); break;
				case PARAMETER::END: printf( " %s", PARAM_STRING_END ); break;
				case OPERATOR::EQ: printf( " == " ); break;
				case OPERATOR::NEQ: printf( " != " ); break;
				default:
				{
					printf( "Unknown line_part.type = %d found\n", parts[i].type );
					assert( 0 == "Error: Not Implemented" );
				}
			}
	}

	void dbgPrintNode( TemplateNode& node, int depth )
	{
		dbgPrintIndent( depth );
		printf( "[%d] ", node.srcLineNum );
		switch ( node.type )
		{
			case NODE_TYPE::CONTENT: break;
			case NODE_TYPE::BEGIN_TEMPLATE: printf( "BEGIN_TEMPLATE " ); break;
			case NODE_TYPE::END_TEMPLATE: printf( "END_TEMPLATE " ); break;
			case NODE_TYPE::IF: printf( "IF " ); break;
			case NODE_TYPE::ASSERT: printf( "ASSERT " ); break;
			case NODE_TYPE::FOR_EACH_OF_MEMBERS: printf( "FOR_EACH_OF_MEMBERS " ); break;
			case NODE_TYPE::INCLUDE: printf( "INCLUDE " ); break;
			case NODE_TYPE::IF_TRUE_BRANCHE: printf( "IF_TRUE" ); break;
			case NODE_TYPE::IF_FALSE_BRANCHE: printf( "IF_FALSE" ); break;
		}

		if ( node.lineParts.size() )
			dbgPrintLineParts( node.lineParts );
		printf( "\n" );
		for ( unsigned int i=0; i<node.childNodes.size(); i++ )
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
			case NODE_TYPE::BEGIN_TEMPLATE:
			{
				for ( unsigned int i=0; i<node.childNodes.size(); i++ )
					dbgValidateNode( node.childNodes[i] );
				break;
			}
			case NODE_TYPE::IF:
			{
				int childCnt = node.childNodes.size();
				assert( childCnt == 1 || node.childNodes.size() == 2 );
				if ( childCnt == 1 )
				{
					assert( node.childNodes[0].type == NODE_TYPE::IF_TRUE_BRANCHE || node.childNodes[0].type == NODE_TYPE::IF_FALSE_BRANCHE );
				}
				else
				{
					assert( node.childNodes[0].type == NODE_TYPE::IF_TRUE_BRANCHE );
					assert( node.childNodes[1].type == NODE_TYPE::IF_FALSE_BRANCHE );
				}
				for ( unsigned int i=0; i<node.childNodes.size(); i++ )
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
			case NODE_TYPE::IF_TRUE_BRANCHE:
			case NODE_TYPE::IF_FALSE_BRANCHE:
			{
				for ( unsigned int i=0; i<node.childNodes.size(); i++ )
					dbgValidateNode( node.childNodes[i] );
				break;
			}
			case NODE_TYPE::INCLUDE:
			{
				assert( 0 == "ERROR: NOT IMPLEMENTED" );
				break;
			}
		}
	}

	bool makeNodeTree( TemplateNode& rootNode, TEMPLATE_NODES_ITERATOR nodeBegin, TEMPLATE_NODES_ITERATOR nodeEnd )
	{
		TEMPLATE_NODES_ITERATOR it = nodeBegin;
		while ( it != nodeEnd )
		{
			switch ( it->type )
			{
				case NODE_TYPE::CONTENT:
				{
					 rootNode.childNodes.push_back( *it );
					 ++it;
					 break;
				}
				case NODE_TYPE::FOR_EACH_OF_MEMBERS:
				{
					assert( it->lineParts.size() == 1 && ( it->lineParts[0].type == PARAMETER::BEGIN || it->lineParts[0].type == PARAMETER::END ) );
					unsigned int param = it->lineParts[0].type;
					unsigned int contentStart = 0;
					if ( param == PARAMETER::END )
					{
						printf( "line %d: error: \"%s %s\" without matching \"%s %s\"\n", it->srcLineNum, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_END, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_BEGIN );
						return false;
					}
					else if ( param == PARAMETER::BEGIN )
					{
						// next NODE_TYPE::FOR_EACH_OF_MEMBERS must be somewhere down, and it must be terminating (so far inner blocks of this type are not expected)
						TEMPLATE_NODES_ITERATOR nodeBlockEnd = it;
						do { ++nodeBlockEnd; } while ( nodeBlockEnd != nodeEnd && nodeBlockEnd->type != NODE_TYPE::FOR_EACH_OF_MEMBERS );
						if ( nodeBlockEnd == nodeEnd )
						{
							printf( "line %d: error: \"%s %s\" without matching \"%s %s\"\n", it->srcLineNum, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_BEGIN, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_END );
							return false;
						}
						// at least, now we are at NODE_TYPE::FOR_EACH_OF_MEMBERS node...
						contentStart = 0;
						assert( nodeBlockEnd->lineParts.size() == 1 && ( nodeBlockEnd->lineParts[0].type == PARAMETER::BEGIN || nodeBlockEnd->lineParts[0].type == PARAMETER::END ) );
						param = nodeBlockEnd->lineParts[0].type;
						if ( param == PARAMETER::END )
						{
							// VALID CASE
							makeNodeTree( *it, it + 1, nodeBlockEnd );
							rootNode.childNodes.push_back( *it );
							it = nodeBlockEnd;
							it++;
							break;
						}
						else if ( param == PARAMETER::BEGIN )
						{
							printf( "line %d: error: \"%s %s\" without matching \"%s %s\" (see also line %d)\n", it->srcLineNum, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_BEGIN, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_END, nodeBlockEnd->srcLineNum );
							return false;
						}
						else
						{
							assert( 0 );
							return false;
						}
					}
					else
					{
						assert( 0 );
						return false;
					}

					assert( 0 ); // we should not be here!
				}
				case NODE_TYPE::IF:
				{
					// each NODE_TYPE::IF eventually ends up with a matching NODE_TYPE::ENDIF; inner IF/ENDIF pairs are allowed, too
					int ifendifBalance = 1;
					TEMPLATE_NODES_ITERATOR nodeBlockEnd = it;
					bool endifFound = false;
					do 
					{ 
						++nodeBlockEnd; 
						if ( nodeBlockEnd->type == NODE_TYPE::IF )
							ifendifBalance ++;
						if ( nodeBlockEnd->type == NODE_TYPE::ENDIF )
							ifendifBalance --;
						if ( ifendifBalance == 0 )
						{
							endifFound = true;
							break;
						}
					}
					while ( nodeBlockEnd != nodeEnd );

					if ( !endifFound )
					{
						printf( "line %d: error: \"%s\" without matching \"%s\"\n", it->srcLineNum, KEYWORD_STRING_IF, PARAM_STRING_ENDIF );
						return false;
					}
					assert( nodeBlockEnd->type == NODE_TYPE::ENDIF );

					// VALID CASE
					// we need to separate its TRUE branche from the rest if IF/ENDIF body which is it FALSE branch
					// posive branch ends up (up to inner IF/ENDIF blocks) with one of NODE_TYPE::ELSE, NODE_TYPE::ELIF, or NODE_TYPE::ENDIF (the latter is already processed out)
					// if none of NODE_TYPE::ELSE or NODE_TYPE::ELIF found, IF block has only its TRUE branch
					ifendifBalance = 0;
					TEMPLATE_NODES_ITERATOR trueBranchEnd = it;
					do 
					{ 
						++trueBranchEnd; 
						if ( trueBranchEnd->type == NODE_TYPE::IF )
							ifendifBalance ++;
						if ( trueBranchEnd->type == NODE_TYPE::ENDIF )
							ifendifBalance --;
						if ( ifendifBalance == 0 && (trueBranchEnd->type == NODE_TYPE::ELSE || trueBranchEnd->type == NODE_TYPE::ELIF ) )
						{
							break;
						}
					}
					while ( trueBranchEnd != nodeBlockEnd );

					TemplateNode ifTrue, ifFalse;
					ifTrue.type = NODE_TYPE::IF_TRUE_BRANCHE;
					ifTrue.srcLineNum = trueBranchEnd == it + 1 ? -1 : it->srcLineNum + 1;
					makeNodeTree( ifTrue, it + 1, trueBranchEnd );

					if ( trueBranchEnd->type == NODE_TYPE::ELSE )
					{
						ifFalse.type = NODE_TYPE::IF_FALSE_BRANCHE;
						ifFalse.srcLineNum = trueBranchEnd != nodeBlockEnd ? trueBranchEnd->srcLineNum + 1 : -1;
						makeNodeTree( ifFalse, trueBranchEnd + 1, nodeBlockEnd );
					}
					else
					{
						assert( trueBranchEnd->type == NODE_TYPE::ELIF );
						ifFalse.type = NODE_TYPE::IF_FALSE_BRANCHE;
						ifFalse.srcLineNum = trueBranchEnd != nodeBlockEnd ? trueBranchEnd->srcLineNum : -1;
						makeNodeTree( ifFalse, trueBranchEnd, nodeBlockEnd );
					}

					it->childNodes.push_back( ifTrue );
					it->childNodes.push_back( ifFalse );

					rootNode.childNodes.push_back( *it );
					it = nodeBlockEnd;
					++it;
					break;
				}
				case NODE_TYPE::ASSERT:
				{
					rootNode.childNodes.push_back( *it );
					++it;
					break;
				}
				case NODE_TYPE::ENDIF: // processed out while processing a respective NODE_TYPE::IF
				{
					printf( "line %d: error: \"%s\" without matching \"%s\"\n", it->srcLineNum, PARAM_STRING_ENDIF, KEYWORD_STRING_IF );
					return false;
				}
				case NODE_TYPE::ELIF:
				{
					if ( rootNode.type != NODE_TYPE::IF_FALSE_BRANCHE )
					{
						printf( "line %d: error: \"%s\" without matching \"%s\"\n", it->srcLineNum, KEYWORD_STRING_ELIF, KEYWORD_STRING_IF );
						return false;
					}
					assert( nodeEnd->type == NODE_TYPE::ENDIF );
					++nodeEnd; // that is, we will re-use it
					it->type = NODE_TYPE::IF;
					break; // re-process it as NODE_TYPE::IF
				}
				case NODE_TYPE::ELSE: // processed out while processing a respective NODE_TYPE::IF
				{
					printf( "line %d: error: \"%s\" without matching \"%s\"\n", it->srcLineNum, KEYWORD_STRING_ELSE, KEYWORD_STRING_IF );
					return false;
				}
				default:
				{
					printf( "line %d: error: unexpected token(s)\n", it->srcLineNum );
					break;
				}
			} // end of switch
		}

		return true;
	}

	bool readLine( FILE* ft, string& line, unsigned int& contentStart, int* currentLineNum )
	{
		contentStart = 0;
		bool somethingFound = false;
		bool startFound = false;
		for(;;) // through all chars - just read the line
		{
			char ch;
			int res = fread( &ch, 1, 1, ft );
			if ( res != 1 )
				break;
			somethingFound = true;
			if ( ch == '\n' )
			{
				(*currentLineNum) ++;
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

	int parseMainKeyword( string& line, unsigned int& contentStart )
	{
		assert( line.compare( contentStart, 2, "@@" ) == 0 );
		contentStart += 2;
		while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
		int ret = parseSpecialWord( line, contentStart, keywords );
		while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
		return ret;
	}

	int parseParam( string& line, unsigned int& contentStart )
	{
		while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
		int ret = parseSpecialWord( line, contentStart, params );
		return ret;
	}

	int parsePlaceholder( string& line, unsigned int& contentStart )
	{
		while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
		int ret = parseSpecialWord( line, contentStart, placeholders );
		return ret;
	}

	void skipSpaces( string& line, unsigned int& contentStart )
	{
		while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
	}

	void parseLineContent( string& lc, vector<LinePart>& parts, int lineType, int context )
	{
		// we have to go char by char; if '@' is found, make sure it's not a placeholder, or replace it accordingly
		unsigned int pos = 0;
		unsigned int sz = lc.size();
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

	void parseIfCondition( string& lc, vector<LinePart>& parts, int lineType, int context )
	{
				// we have to go char by char; if '@' is found, make sure it's not a placeholder, or replace it accordingly
				unsigned int pos = 0;
				unsigned int sz = lc.size();
				LinePart part;
				part.type = PLACEHOLDER::VERBATIM;
				do
				{
					if ( lc[ pos ] == '@' )
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
							case PLACEHOLDER::MEMBER_TYPE:
							case PLACEHOLDER::MEMBER_NAME:
							{
								assert( part.type == PLACEHOLDER::VERBATIM );
								if ( part.verbatim.size() )
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
					else
					{
						if ( lc[ pos ] == ' ' || lc[ pos ] == '\t')
						{
							if ( part.verbatim.size() )
							{
								assert( part.type == PLACEHOLDER::VERBATIM );
								parts.push_back( part );
								part.verbatim.clear();
							}
							pos ++;
						}
						else if ( lc.compare( pos, 2, "==" ) == 0 )
						{
							if ( part.verbatim.size() )
							{
								assert( part.type == PLACEHOLDER::VERBATIM );
								parts.push_back( part );
								part.verbatim.clear();
							}
							part.verbatim.clear();
							part.type = OPERATOR::EQ;
							parts.push_back( part );
							part.type = PLACEHOLDER::VERBATIM;
							pos += 2;
						}
						else if ( lc.compare( pos, 2, "!=" ) == 0 )
						{
							if ( part.verbatim.size() )
							{
								assert( part.type == PLACEHOLDER::VERBATIM );
								parts.push_back( part );
								part.verbatim.clear();
							}
							part.verbatim.clear();
							part.type = OPERATOR::NEQ;
							parts.push_back( part );
							part.type = PLACEHOLDER::VERBATIM;
							pos += 2;
						}
						else
						{
							part.verbatim.push_back( lc[ pos ] );
							pos ++;
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

public:
	enum {OK = 0, NO_MORE_TEMPLATES = 1, FAILED_ERROR = 2, FAILED_BUID_TREE_ERROR = 3,	FAILED_INTERNAL = 4};
	int loadTemplate( FILE* ft, AnyTemplateRoot& rootNode, int* currentLineNum )
	{
		if ( ft == NULL )
		{
			printf( "error: no input file\n" );
			return FAILED_INTERNAL;
		}

		TEMPLATE_NODES nodes;

		// it is assumed here that starting from a current position in a file any content other than the beginning and the rest of template can be safely ignored
		bool startFound = false;
		unsigned int contentStart = 0;
		bool endFound = false;

		for( ;;) // through all nodes, find template beginning
		{
			string line;
			if ( !readLine( ft, line, contentStart, currentLineNum ) )
				break;
			if ( contentStart == line.size() )
				continue; // no content
			if ( line[contentStart] == '@' && contentStart + 1 < line.size() && line[contentStart+1] == '@' ) // this is only what we expect at the beginning of any service line
			{
				contentStart += 2;
				while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
				if ( line.compare( contentStart, sizeof(PARAM_STRING_BEGIN_TEMPLATE)-1, PARAM_STRING_BEGIN_TEMPLATE ) == 0 )
				{
					contentStart += sizeof(PARAM_STRING_BEGIN_TEMPLATE)-1;
					while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
					// read name
					while ( contentStart < line.size() && (!(line[contentStart] == ' ' || line[contentStart] == '\t'))) rootNode.name.push_back( line[contentStart++] );
					while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
					if ( line.compare( contentStart, sizeof(PARAM_STRING_TYPE)-1, PARAM_STRING_TYPE ) != 0 )
					{
						printf( "line %d: error: no \"%s\" after \"%s\"\n", *currentLineNum, PARAM_STRING_TYPE, PARAM_STRING_BEGIN_TEMPLATE );
						return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
					}
					contentStart += sizeof(PARAM_STRING_TYPE)-1;
					while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
					if ( contentStart < line.size() && line[contentStart] != '=' )
					{
						printf( "line %d: error: no \"%s\" after \"%s\"\n", *currentLineNum, "=", PARAM_STRING_TYPE );
						return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
					}
					contentStart++;
					while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
					// read type
					while ( contentStart < line.size() && (!(line[contentStart] == ' ' || line[contentStart] == '\t'))) rootNode.type.push_back( line[contentStart++] );
					while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
					if ( !( contentStart == line.size() ) )
					{
						printf( "line %d: error: unexpected tokens\n", *currentLineNum );
						return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
					}

					startFound = true;
					break;
				}
			}
			// at this point a template has started...
		}

		if ( !startFound )
		{
			if ( nodes.size() )
			{
				printf( "line %d: error: no no template has been found\n", *currentLineNum );
				return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
			}
			else
			{
				return NO_MORE_TEMPLATES;
			}
		}

		// go through other nodes
		for( ;;) // through all nodes, find template beginning
		{
			TemplateNode tl;
			string line;
			if ( !readLine( ft, line, contentStart, currentLineNum ) )
				break;
			bool isContent = line.compare( contentStart, 2, "@@" ) != 0;
			if ( isContent ) // an empty line => not ctr line => content line => keep "as is"
			{
				tl.srcLineNum = *currentLineNum;
				tl.type = NODE_TYPE::CONTENT;
				parseLineContent( line, tl.lineParts, NODE_TYPE::CONTENT, 0 );
//				tl.content = line;
				nodes.push_back( tl );
				continue;
			}

			int kwd = parseMainKeyword( line, contentStart );

			// unexpected template start
			if ( kwd == NODE_TYPE::BEGIN_TEMPLATE )
			{
				printf( "line %d: error: \"%s\" is unexpected\n", *currentLineNum, PARAM_STRING_BEGIN_TEMPLATE );
				return FAILED_ERROR;
			}

			// is template end?
			if ( kwd == NODE_TYPE::END_TEMPLATE )
			{
				// read name
				string endName;
				while ( contentStart < line.size() && (!(line[contentStart] == ' ' || line[contentStart] == '\t'))) endName.push_back( line[contentStart++] );
				if ( endName != rootNode.name )
				{
					printf( "line %d: error: name does not match that at template beginning\n", *currentLineNum );
					return FAILED_ERROR;
				}
				while ( contentStart < line.size() && (line[contentStart] == ' ' || line[contentStart] == '\t')) contentStart++;
				if ( !( contentStart == line.size() || ( contentStart + 1 == line.size() || line[contentStart] == '\r' ) ) )
				{
					printf( "line %d: error: unexpected tokens\n", *currentLineNum );
					return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
				}

				endFound = true;
				break;
			}

			// other control nodes
			tl.srcLineNum = *currentLineNum;
			tl.type = kwd;
			switch ( kwd )
			{
				case NODE_TYPE::IF:
				case NODE_TYPE::ELIF:
				case NODE_TYPE::ASSERT:
				{
					parseIfCondition( string( line.begin() + contentStart, line.end() ), tl.lineParts, NODE_TYPE::CONTENT, 0 );
					break;
				}
				case NODE_TYPE::FOR_EACH_OF_MEMBERS:
				{
					unsigned int contentStart_1 = 0;
					string remaining = string( line.begin() + contentStart, line.end() );
					int param = parseParam( remaining, contentStart_1 );
					bool goodParam = param == PARAMETER::BEGIN || param == PARAMETER::END;
					if ( !goodParam )
					{
						printf( "line %d: error: \"%s\" or \"%s\" is expected after \"%s\"\n", *currentLineNum, PARAM_STRING_BEGIN, PARAM_STRING_END, KEYWORD_STRING_FOR_EACH_OF_MEMBERS );
						return FAILED_ERROR;
					}
					LinePart part;
					part.type = param;
					tl.lineParts.push_back( part );
					skipSpaces( remaining, contentStart );
					if ( contentStart < remaining.size() )
					{
						printf( "line %d: error: unexpected token(s) \"%s\"\n", *currentLineNum, string( remaining.begin() + contentStart, remaining.end() ) );
						return FAILED_ERROR;
					}
					break;
				}
				default:
				{
					LinePart part;
					part.type = PLACEHOLDER::VERBATIM;
					part.verbatim = string( line.begin() + contentStart, line.end() );
					tl.lineParts.push_back( part );
				}
			}
			nodes.push_back( tl );
		}

		if ( !endFound )
		{
			printf( "line %d: error: \"%s\" not found\n", *currentLineNum, PARAM_STRING_END_TEMPLATE );
			return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
		}

		rootNode.type = NODE_TYPE::BEGIN_TEMPLATE;
		rootNode.root.type = NODE_TYPE::FULL_TEMPLATE;
		bool treeOK = makeNodeTree( rootNode.root, nodes.begin(), nodes.end() );
		if ( !treeOK )
		{
			printf( "line %d: error: building tree failed\n", rootNode.srcLineNum );
			return FAILED_BUID_TREE_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
		}

		dbgValidateNode( rootNode.root );

		return OK;
	}

	void dbgPrintTree( AnyTemplateRoot& rootNode )
	{
		dbgPrintNode( rootNode.root, 0 );
	}
};

TemplateParser tp;

bool loadTemplate( FILE* ft, AnyTemplateRoot& rootNode, int* currentLineNum )
{
	return tp.loadTemplate( ft, rootNode, currentLineNum );
}

void dbgPrintTree( AnyTemplateRoot& rootNode )
{
	tp.dbgPrintTree( rootNode );
}
