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
#include <string.h> // for memmov()
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

/*
// data types
#define DATA_TYPE_
#define DATA_TYPE_
#define DATA_TYPE_STRING_ ""
#define DATA_TYPE_STRING_ ""
*/


class template_parser
{
	void print_indent( int depth )
	{
		for ( int i=0; i<depth; i++ )
			printf( " . " );
	}

	void print_line_parts( LINE_PARTS& parts )
	{
		unsigned int i;
		for ( i=0; i<parts.size(); i++ )
			switch ( parts[i].type )
			{
				case LINE_PART_VERBATIM: printf( parts[i].verbatim.c_str() ); break;
				case PLACEHOLDER_STRUCTNAME: printf( PLACEHOLDER_STRING_STRUCTNAME ); break;
				case PLACEHOLDER_MEMBER_TYPE: printf( PLACEHOLDER_STRING_MEMBER_TYPE ); break;
				case PLACEHOLDER_MEMBER_NAME: printf( PLACEHOLDER_STRING_MEMBER_NAME ); break;
				case PARAM_TYPE: printf( " %s", PARAM_STRING_TYPE ); break;
				case PARAM_BEGIN: printf( " %s", PARAM_STRING_BEGIN ); break;
				case PARAM_END: printf( " %s", PARAM_STRING_END ); break;
				case EXPRESSION_PART_EQ: printf( " == " ); break;
				case EXPRESSION_PART_NEQ: printf( " != " ); break;
				default:
				{
					printf( "Unknown line_part.type = %d found\n", parts[i].type );
					assert( 0 == "Error: Not Implemented" );
				}
			}
	}

	void print_node( TEMPLATE_NODE& node, int depth )
	{
		print_indent( depth );
		printf( "[%d] ", node.src_line_num );
		switch ( node.type )
		{
			case NODE_TYPE_CONTENT: break;
			case NODE_TYPE_BEGIN_TEMPLATE: printf( "BEGIN_TEMPLATE " ); break;
			case NODE_TYPE_END_TEMPLATE: printf( "END_TEMPLATE " ); break;
			case NODE_TYPE_IF: printf( "IF " ); break;
			case NODE_TYPE_ASSERT: printf( "ASSERT " ); break;
			case NODE_TYPE_FOR_EACH_OF_MEMBERS: printf( "FOR_EACH_OF_MEMBERS " ); break;
			case NODE_TYPE_INCLUDE: printf( "INCLUDE " ); break;
			case NODE_TYPE_IF_TRUE_BRANCHE: printf( "IF_TRUE" ); break;
			case NODE_TYPE_IF_FALSE_BRANCHE: printf( "IF_FALSE" ); break;
		}

		if ( node.line_parts.size() )
			print_line_parts( node.line_parts );
		printf( "\n" );
		for ( unsigned int i=0; i<node.child_nodes.size(); i++ )
			print_node( node.child_nodes[i], depth + 1 );
	}

	void validate_node( TEMPLATE_NODE& node )
	{
		switch ( node.type )
		{
			case NODE_TYPE_CONTENT: 
			{
				assert( node.child_nodes.size() == 0 );
				break;
			}
			case NODE_TYPE_BEGIN_TEMPLATE:
			{
				for ( unsigned int i=0; i<node.child_nodes.size(); i++ )
					validate_node( node.child_nodes[i] );
				break;
			}
			case NODE_TYPE_IF:
			{
				int child_cnt = node.child_nodes.size();
				assert( child_cnt == 1 || node.child_nodes.size() == 2 );
				if ( child_cnt == 1 )
				{
					assert( node.child_nodes[0].type == NODE_TYPE_IF_TRUE_BRANCHE || node.child_nodes[0].type == NODE_TYPE_IF_FALSE_BRANCHE );
				}
				else
				{
					assert( node.child_nodes[0].type == NODE_TYPE_IF_TRUE_BRANCHE );
					assert( node.child_nodes[1].type == NODE_TYPE_IF_FALSE_BRANCHE );
				}
				for ( unsigned int i=0; i<node.child_nodes.size(); i++ )
					validate_node( node.child_nodes[i] );
				break;
			}
			case NODE_TYPE_ASSERT:
			{
				int child_cnt = node.child_nodes.size();
				assert( child_cnt == 0 );
				break;
			}
			case NODE_TYPE_FOR_EACH_OF_MEMBERS:
			case NODE_TYPE_IF_TRUE_BRANCHE:
			case NODE_TYPE_IF_FALSE_BRANCHE:
			{
				for ( unsigned int i=0; i<node.child_nodes.size(); i++ )
					validate_node( node.child_nodes[i] );
				break;
			}
			case NODE_TYPE_INCLUDE:
			{
				assert( 0 == "ERROR: NOT IMPLEMENTED" );
				break;
			}
		}
	}

	bool make_node_tree( TEMPLATE_NODE& root_node, TEMPLATE_NODES_ITERATOR node_begin, TEMPLATE_NODES_ITERATOR node_end )
	{
		TEMPLATE_NODES_ITERATOR it = node_begin;
		while ( it != node_end )
		{
			switch ( it->type )
			{
				case NODE_TYPE_CONTENT:
				{
					 root_node.child_nodes.push_back( *it );
					 ++it;
					 break;
				}
				case NODE_TYPE_FOR_EACH_OF_MEMBERS:
				{
					assert( it->line_parts.size() == 1 && ( it->line_parts[0].type == PARAM_BEGIN || it->line_parts[0].type == PARAM_END ) );
					unsigned int param = it->line_parts[0].type;
					unsigned int content_start = 0;
					if ( param == PARAM_END )
					{
						printf( "line %d: error: \"%s %s\" without matching \"%s %s\"\n", it->src_line_num, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_END, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_BEGIN );
						return false;
					}
					else if ( param == PARAM_BEGIN )
					{
						// next NODE_TYPE_FOR_EACH_OF_MEMBERS must be somewhere down, and it must be terminating (so far inner blocks of this type are not expected)
						TEMPLATE_NODES_ITERATOR node_block_end = it;
						do { ++node_block_end; } while ( node_block_end != node_end && node_block_end->type != NODE_TYPE_FOR_EACH_OF_MEMBERS );
						if ( node_block_end == node_end )
						{
							printf( "line %d: error: \"%s %s\" without matching \"%s %s\"\n", it->src_line_num, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_BEGIN, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_END );
							return false;
						}
						// at least, now we are at NODE_TYPE_FOR_EACH_OF_MEMBERS node...
						content_start = 0;
						assert( node_block_end->line_parts.size() == 1 && ( node_block_end->line_parts[0].type == PARAM_BEGIN || node_block_end->line_parts[0].type == PARAM_END ) );
						param = node_block_end->line_parts[0].type;
						if ( param == PARAM_END )
						{
							// VALID CASE
							make_node_tree( *it, it + 1, node_block_end );
							root_node.child_nodes.push_back( *it );
							it = node_block_end;
							it++;
							break;
						}
						else if ( param == PARAM_BEGIN )
						{
							printf( "line %d: error: \"%s %s\" without matching \"%s %s\" (see also line %d)\n", it->src_line_num, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_BEGIN, KEYWORD_STRING_FOR_EACH_OF_MEMBERS, PARAM_STRING_END, node_block_end->src_line_num );
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
				case NODE_TYPE_IF:
				{
					// each NODE_TYPE_IF eventually ends up with a matching NODE_TYPE_ENDIF; inner IF/ENDIF pairs are allowed, too
					int ifendif_balance = 1;
					TEMPLATE_NODES_ITERATOR node_block_end = it;
					bool endif_found = false;
					do 
					{ 
						++node_block_end; 
						if ( node_block_end->type == NODE_TYPE_IF )
							ifendif_balance ++;
						if ( node_block_end->type == NODE_TYPE_ENDIF )
							ifendif_balance --;
						if ( ifendif_balance == 0 )
						{
							endif_found = true;
							break;
						}
					}
					while ( node_block_end != node_end );

					if ( !endif_found )
					{
						printf( "line %d: error: \"%s\" without matching \"%s\"\n", it->src_line_num, KEYWORD_STRING_IF, PARAM_STRING_ENDIF );
						return false;
					}
					assert( node_block_end->type == NODE_TYPE_ENDIF );

					// VALID CASE
					// we need to separate its TRUE branche from the rest if IF/ENDIF body which is it FALSE branch
					// posive branch ends up (up to inner IF/ENDIF blocks) with one of NODE_TYPE_ELSE, NODE_TYPE_ELIF, or NODE_TYPE_ENDIF (the latter is already processed out)
					// if none of NODE_TYPE_ELSE or NODE_TYPE_ELIF found, IF block has only its TRUE branch
					ifendif_balance = 0;
					TEMPLATE_NODES_ITERATOR true_branch_end = it;
					do 
					{ 
						++true_branch_end; 
						if ( true_branch_end->type == NODE_TYPE_IF )
							ifendif_balance ++;
						if ( true_branch_end->type == NODE_TYPE_ENDIF )
							ifendif_balance --;
						if ( ifendif_balance == 0 && (true_branch_end->type == NODE_TYPE_ELSE || true_branch_end->type == NODE_TYPE_ELIF ) )
						{
							break;
						}
					}
					while ( true_branch_end != node_block_end );

					TEMPLATE_NODE if_true, if_false;
					if_true.type = NODE_TYPE_IF_TRUE_BRANCHE;
					if_true.src_line_num = true_branch_end == it + 1 ? -1 : it->src_line_num + 1;
					make_node_tree( if_true, it + 1, true_branch_end );

					if ( true_branch_end->type == NODE_TYPE_ELSE )
					{
						if_false.type = NODE_TYPE_IF_FALSE_BRANCHE;
						if_false.src_line_num = true_branch_end != node_block_end ? true_branch_end->src_line_num + 1 : -1;
						make_node_tree( if_false, true_branch_end + 1, node_block_end );
					}
					else
					{
						assert( true_branch_end->type == NODE_TYPE_ELIF );
						if_false.type = NODE_TYPE_IF_FALSE_BRANCHE;
						if_false.src_line_num = true_branch_end != node_block_end ? true_branch_end->src_line_num : -1;
						make_node_tree( if_false, true_branch_end, node_block_end );
					}

					it->child_nodes.push_back( if_true );
					it->child_nodes.push_back( if_false );

					root_node.child_nodes.push_back( *it );
					it = node_block_end;
					++it;
					break;
				}
				case NODE_TYPE_ASSERT:
				{
					root_node.child_nodes.push_back( *it );
					++it;
					break;
				}
				case NODE_TYPE_ENDIF: // processed out while processing a respective NODE_TYPE_IF
				{
					printf( "line %d: error: \"%s\" without matching \"%s\"\n", it->src_line_num, PARAM_STRING_ENDIF, KEYWORD_STRING_IF );
					return false;
				}
				case NODE_TYPE_ELIF:
				{
					if ( root_node.type != NODE_TYPE_IF_FALSE_BRANCHE )
					{
						printf( "line %d: error: \"%s\" without matching \"%s\"\n", it->src_line_num, KEYWORD_STRING_ELIF, KEYWORD_STRING_IF );
						return false;
					}
					assert( node_end->type == NODE_TYPE_ENDIF );
					++node_end; // that is, we will re-use it
					it->type = NODE_TYPE_IF;
					break; // re-process it as NODE_TYPE_IF
				}
				case NODE_TYPE_ELSE: // processed out while processing a respective NODE_TYPE_IF
				{
					printf( "line %d: error: \"%s\" without matching \"%s\"\n", it->src_line_num, KEYWORD_STRING_ELSE, KEYWORD_STRING_IF );
					return false;
				}
				default:
				{
					printf( "line %d: error: unexpected token(s)\n", it->src_line_num );
					break;
				}
			} // end of switch
		}

		return true;
	}

	bool read_line( FILE* ft, std::string& line, unsigned int& content_start, int* current_line_num )
	{
		content_start = 0;
		bool something_found = false;
		bool start_found = false;
		for(;;) // through all chars - just read the line
		{
			char ch;
			int res = fread( &ch, 1, 1, ft );
			if ( res != 1 )
				break;
			something_found = true;
			if ( ch == '\n' )
			{
				(*current_line_num) ++;
				break;
			}
			line.push_back( ch );
			if ( !start_found && (ch == ' ' || ch == '\t') )
				content_start++;
			else
				start_found = true;
		}
		while ( line.size() && *(line.end()-1) == '\r' )
			line.pop_back();
		return something_found;
	}

	int parse_main_keyword( std::string& line, unsigned int& content_start )
	{
		int ret = NODE_TYPE_CONTENT;
		assert( line.compare( content_start, 2, "@@" ) == 0 );
		content_start += 2;
		while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
		struct keyword
		{
			const char* kw;
			int size;
			int id;
		};
		keyword keywords[8] = 
		{
			{PARAM_STRING_BEGIN_TEMPLATE, sizeof(PARAM_STRING_BEGIN_TEMPLATE)-1, NODE_TYPE_BEGIN_TEMPLATE},
			{PARAM_STRING_END_TEMPLATE, sizeof(PARAM_STRING_END_TEMPLATE)-1, NODE_TYPE_END_TEMPLATE},
			{KEYWORD_STRING_FOR_EACH_OF_MEMBERS, sizeof(KEYWORD_STRING_FOR_EACH_OF_MEMBERS)-1, NODE_TYPE_FOR_EACH_OF_MEMBERS},
			{KEYWORD_STRING_IF, sizeof(KEYWORD_STRING_IF)-1, NODE_TYPE_IF},
			{PARAM_STRING_ENDIF, sizeof(PARAM_STRING_ENDIF)-1, NODE_TYPE_ENDIF},
			{KEYWORD_STRING_ELIF, sizeof(KEYWORD_STRING_ELIF)-1, NODE_TYPE_ELIF},
			{KEYWORD_STRING_ELSE, sizeof(KEYWORD_STRING_ELSE)-1, NODE_TYPE_ELSE},
			{PARAM_STRING_ASSERT, sizeof(PARAM_STRING_ASSERT)-1, NODE_TYPE_ASSERT},
		};
		int i;
		for ( i=0; i<8; i++ )
		{
			if ( line.compare( content_start, keywords[i].size, keywords[i].kw ) == 0 )
			{
				content_start += keywords[i].size;
				ret = keywords[i].id;
			}
		}
/*		if ( line.compare( content_start, sizeof(PARAM_STRING_BEGIN_TEMPLATE)-1, PARAM_STRING_BEGIN_TEMPLATE ) == 0 )
		{
			content_start += sizeof(PARAM_STRING_BEGIN_TEMPLATE)-1;
			ret = NODE_TYPE_BEGIN_TEMPLATE;
		}
		if ( line.compare( content_start, sizeof(PARAM_STRING_END_TEMPLATE)-1, PARAM_STRING_END_TEMPLATE ) == 0 )
		{
			content_start += sizeof(PARAM_STRING_END_TEMPLATE)-1;
			ret = NODE_TYPE_END_TEMPLATE;
		}
		else if ( line.compare( content_start, sizeof(KEYWORD_STRING_FOR_EACH_OF_MEMBERS)-1, KEYWORD_STRING_FOR_EACH_OF_MEMBERS ) == 0 )
		{
			content_start += sizeof(KEYWORD_STRING_FOR_EACH_OF_MEMBERS)-1;
			ret = NODE_TYPE_FOR_EACH_OF_MEMBERS;
		}
		else if ( line.compare( content_start, sizeof(KEYWORD_STRING_IF)-1, KEYWORD_STRING_IF ) == 0 )
		{
			content_start += sizeof(KEYWORD_STRING_IF)-1;
			ret = NODE_TYPE_IF;
		}
		else if ( line.compare( content_start, sizeof(KEYWORD_STRING_ELSE)-1, KEYWORD_STRING_ELSE ) == 0 )
		{
			content_start += sizeof(KEYWORD_STRING_ELSE)-1;
			ret = NODE_TYPE_ELSE;
		}
		else if ( line.compare( content_start, sizeof(KEYWORD_STRING_ELIF)-1, KEYWORD_STRING_ELIF ) == 0 )
		{
			content_start += sizeof(KEYWORD_STRING_ELIF)-1;
			ret = NODE_TYPE_ELIF;
		}
		else if ( line.compare( content_start, sizeof(PARAM_STRING_ENDIF)-1, PARAM_STRING_ENDIF ) == 0 )
		{
			content_start += sizeof(PARAM_STRING_ENDIF)-1;
			ret = NODE_TYPE_ENDIF;
		}
		else if ( line.compare( content_start, sizeof(PARAM_STRING_ASSERT)-1, PARAM_STRING_ASSERT ) == 0 )
		{
			content_start += sizeof(PARAM_STRING_ASSERT)-1;
			ret = NODE_TYPE_ASSERT;
		}*/
		while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
		return ret;
	}

	void skip_spaces( std::string& line, unsigned int& content_start )
	{
		while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
	}

	int parse_param( std::string& line, unsigned int& content_start )
	{
		int ret = PARAM_NONE;
		while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
		struct param
		{
			const char* word;
			int size;
			int id;
		};
		param params[3] = 
		{
			{PARAM_STRING_BEGIN, sizeof(PARAM_STRING_BEGIN)-1, PARAM_BEGIN},
			{PARAM_STRING_END, sizeof(PARAM_STRING_END)-1, PARAM_END},
			{PARAM_STRING_TYPE, sizeof(PARAM_STRING_TYPE)-1, PARAM_TYPE},
		};
		int i;
		for ( i=0; i<3; i++ )
		{
			if ( line.compare( content_start, params[i].size, params[i].word ) == 0 )
			{
				content_start += params[i].size;
				ret = params[i].id;
			}
		}
/*		if ( line.compare( content_start, sizeof(PARAM_STRING_BEGIN)-1, PARAM_STRING_BEGIN ) == 0 )
		{
			content_start += sizeof(PARAM_STRING_BEGIN)-1;
			ret = PARAM_BEGIN;
		}
		if ( line.compare( content_start, sizeof(PARAM_STRING_END)-1, PARAM_STRING_END ) == 0 )
		{
			content_start += sizeof(PARAM_STRING_END)-1;
			ret = PARAM_END;
		}
		else if ( line.compare( content_start, sizeof(PARAM_STRING_TYPE)-1, PARAM_STRING_TYPE ) == 0 )
		{
			content_start += sizeof(PARAM_STRING_TYPE)-1;
			ret = PARAM_TYPE;
		}*/
//		while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
		return ret;
	}

	int parse_placeholder( std::string& line, unsigned int& content_start )
	{
		int ret = LINE_PART_VERBATIM;
		while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
		struct param
		{
			const char* word;
			int size;
			int id;
		};
		param params[3] = 
		{
			{PLACEHOLDER_STRING_STRUCTNAME, sizeof(PLACEHOLDER_STRING_STRUCTNAME)-1, PLACEHOLDER_STRUCTNAME},
			{PLACEHOLDER_STRING_MEMBER_TYPE, sizeof(PLACEHOLDER_STRING_MEMBER_TYPE)-1, PLACEHOLDER_MEMBER_TYPE},
			{PLACEHOLDER_STRING_MEMBER_NAME, sizeof(PLACEHOLDER_STRING_MEMBER_NAME)-1, PLACEHOLDER_MEMBER_NAME},
		};
		int i;
		for ( i=0; i<3; i++ )
		{
			if ( line.compare( content_start, params[i].size, params[i].word ) == 0 )
			{
				content_start += params[i].size;
				ret = params[i].id;
			}
		}
/*		if ( line.compare( content_start, sizeof(PLACEHOLDER_STRING_STRUCTNAME)-1, PLACEHOLDER_STRING_STRUCTNAME ) == 0 )
		{
			content_start += sizeof(PLACEHOLDER_STRING_STRUCTNAME)-1;
			ret = PLACEHOLDER_STRUCTNAME;
		}
		else if ( line.compare( content_start, sizeof(PLACEHOLDER_STRING_MEMBER_TYPE)-1, PLACEHOLDER_STRING_MEMBER_TYPE ) == 0 )
		{
			content_start += sizeof(PLACEHOLDER_STRING_MEMBER_TYPE)-1;
			ret = PLACEHOLDER_MEMBER_TYPE;
		}
		else if ( line.compare( content_start, sizeof(PLACEHOLDER_STRING_MEMBER_NAME)-1, PLACEHOLDER_STRING_MEMBER_NAME ) == 0 )
		{
			content_start += sizeof(PLACEHOLDER_STRING_MEMBER_NAME)-1;
			ret = PLACEHOLDER_MEMBER_NAME;
		}*/

		return ret;
	}

	void parse_line_content( std::string& lc, LINE_PARTS& parts, int line_type, int context )
	{
				// we have to go char by char; if '@' is found, make sure it's not a placeholder, or replace it accordingly
				unsigned int pos = 0;
				unsigned int sz = lc.size();
				LINE_PART part;
				part.type = LINE_PART_VERBATIM;
				do
				{
					if ( lc[ pos ] != '@' )
					{
						part.verbatim.push_back( lc[ pos ] );
						pos ++;
					}
					else
					{
						int placehldr = parse_placeholder( lc, pos );
						switch ( placehldr )
						{
							case LINE_PART_VERBATIM: 
							{
								part.verbatim.push_back( lc[ pos ] ); 
								pos ++; 
								break;
							}
							case PLACEHOLDER_STRUCTNAME:
							case PLACEHOLDER_MEMBER_TYPE:
							case PLACEHOLDER_MEMBER_NAME:
							{
								parts.push_back( part ); 
								part.verbatim.clear(); 
								part.type = placehldr; 
								parts.push_back( part ); 
								part.type = LINE_PART_VERBATIM; 
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
					assert( part.type == LINE_PART_VERBATIM );
					parts.push_back( part ); 
				}
	}

	void parse_if_condition( std::string& lc, LINE_PARTS& parts, int line_type, int context )
	{
				// we have to go char by char; if '@' is found, make sure it's not a placeholder, or replace it accordingly
				unsigned int pos = 0;
				unsigned int sz = lc.size();
				LINE_PART part;
				part.type = LINE_PART_VERBATIM;
				do
				{
					if ( lc[ pos ] == '@' )
					{
						int placehldr = parse_placeholder( lc, pos );
						switch ( placehldr )
						{
							case LINE_PART_VERBATIM: 
							{
								part.verbatim.push_back( lc[ pos ] ); 
								pos ++; 
								break;
							}
							case PLACEHOLDER_MEMBER_TYPE:
							case PLACEHOLDER_MEMBER_NAME:
							{
								assert( part.type == LINE_PART_VERBATIM );
								if ( part.verbatim.size() )
									parts.push_back( part ); 
								part.verbatim.clear(); 
								part.type = placehldr; 
								parts.push_back( part ); 
								part.type = LINE_PART_VERBATIM; 
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
								assert( part.type == LINE_PART_VERBATIM );
								parts.push_back( part );
								part.verbatim.clear();
							}
							pos ++;
						}
						else if ( lc.compare( pos, 2, "==" ) == 0 )
						{
							if ( part.verbatim.size() )
							{
								assert( part.type == LINE_PART_VERBATIM );
								parts.push_back( part );
								part.verbatim.clear();
							}
							part.verbatim.clear();
							part.type = EXPRESSION_PART_EQ;
							parts.push_back( part );
							part.type = LINE_PART_VERBATIM;
							pos += 2;
						}
						else if ( lc.compare( pos, 2, "!=" ) == 0 )
						{
							if ( part.verbatim.size() )
							{
								assert( part.type == LINE_PART_VERBATIM );
								parts.push_back( part );
								part.verbatim.clear();
							}
							part.verbatim.clear();
							part.type = EXPRESSION_PART_NEQ;
							parts.push_back( part );
							part.type = LINE_PART_VERBATIM;
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
					assert( part.type == LINE_PART_VERBATIM );
					parts.push_back( part ); 
				}
	}

public:
	enum {OK = 0, NO_MORE_TEMPLATES = 1, FAILED_ERROR = 2, FAILED_BUID_TREE_ERROR = 3,	FAILED_INTERNAL = 4};
	int load_template( FILE* ft, ANY_TEMPLATE_ROOT& _root_node, int* current_line_num )
	{
		if ( ft == NULL )
		{
			printf( "error: no input file\n" );
			return FAILED_INTERNAL;
		}

		TEMPLATE_NODES nodes;

		// it is assumed here that starting from a current position in a file any content other than the beginning and the rest of template can be safely ignored
		bool start_found = false;
		unsigned int content_start = 0;
		bool end_found = false;

		for( ;;) // through all nodes, find template beginning
		{
			std::string line;
			if ( !read_line( ft, line, content_start, current_line_num ) )
				break;
			if ( content_start == line.size() )
				continue; // no content
			if ( line[content_start] == '@' && content_start + 1 < line.size() && line[content_start+1] == '@' ) // this is only what we expect at the beginning of any service line
			{
				content_start += 2;
				while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
				if ( line.compare( content_start, sizeof(PARAM_STRING_BEGIN_TEMPLATE)-1, PARAM_STRING_BEGIN_TEMPLATE ) == 0 )
				{
					content_start += sizeof(PARAM_STRING_BEGIN_TEMPLATE)-1;
					while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
					// read name
					while ( content_start < line.size() && (!(line[content_start] == ' ' || line[content_start] == '\t'))) _root_node.name.push_back( line[content_start++] );
					while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
					if ( line.compare( content_start, sizeof(PARAM_STRING_TYPE)-1, PARAM_STRING_TYPE ) != 0 )
					{
						printf( "line %d: error: no \"%s\" after \"%s\"\n", *current_line_num, PARAM_STRING_TYPE, PARAM_STRING_BEGIN_TEMPLATE );
						return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
					}
					content_start += sizeof(PARAM_STRING_TYPE)-1;
					while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
					if ( content_start < line.size() && line[content_start] != '=' )
					{
						printf( "line %d: error: no \"%s\" after \"%s\"\n", *current_line_num, "=", PARAM_STRING_TYPE );
						return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
					}
					content_start++;
					while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
					// read type
					while ( content_start < line.size() && (!(line[content_start] == ' ' || line[content_start] == '\t'))) _root_node.type.push_back( line[content_start++] );
					while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
					if ( !( content_start == line.size() ) )
					{
						printf( "line %d: error: unexpected tokens\n", *current_line_num );
						return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
					}

					start_found = true;
					break;
				}
			}
			// at this point a template has started...
		}

		if ( !start_found )
		{
			if ( nodes.size() )
			{
				printf( "line %d: error: no no template has been found\n", *current_line_num );
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
			TEMPLATE_NODE tl;
			std::string line;
			if ( !read_line( ft, line, content_start, current_line_num ) )
				break;
			bool is_content = line.compare( content_start, 2, "@@" ) != 0;
			if ( is_content ) // an empty line => not ctr line => content line => keep "as is"
			{
				tl.src_line_num = *current_line_num;
				tl.type = NODE_TYPE_CONTENT;
				parse_line_content( line, tl.line_parts, NODE_TYPE_CONTENT, 0 );
//				tl.content = line;
				nodes.push_back( tl );
				continue;
			}

			int kwd = parse_main_keyword( line, content_start );

			// unexpected template start
			if ( kwd == NODE_TYPE_BEGIN_TEMPLATE )
			{
				printf( "line %d: error: \"%s\" is unexpected\n", *current_line_num, PARAM_STRING_BEGIN_TEMPLATE );
				return FAILED_ERROR;
			}

			// is template end?
			if ( kwd == NODE_TYPE_END_TEMPLATE )
			{
				// read name
				std::string end_name;
				while ( content_start < line.size() && (!(line[content_start] == ' ' || line[content_start] == '\t'))) end_name.push_back( line[content_start++] );
				if ( end_name != _root_node.name )
				{
					printf( "line %d: error: name does not match that at template beginning\n", *current_line_num );
					return FAILED_ERROR;
				}
				while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
				if ( !( content_start == line.size() || ( content_start + 1 == line.size() || line[content_start] == '\r' ) ) )
				{
					printf( "line %d: error: unexpected tokens\n", *current_line_num );
					return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
				}

				end_found = true;
				break;
			}

			// other control nodes
			tl.src_line_num = *current_line_num;
			tl.type = kwd;
			switch ( kwd )
			{
				case NODE_TYPE_IF:
				case NODE_TYPE_ELIF:
				case NODE_TYPE_ASSERT:
				{
					parse_if_condition( std::string( line.begin() + content_start, line.end() ), tl.line_parts, NODE_TYPE_CONTENT, 0 );
					break;
				}
				case NODE_TYPE_FOR_EACH_OF_MEMBERS:
				{
					unsigned int content_start_1 = 0;
					std::string remaining = std::string( line.begin() + content_start, line.end() );
					int param = parse_param( remaining, content_start_1 );
					bool good_param = param == PARAM_BEGIN || param == PARAM_END;
					if ( !good_param )
					{
						printf( "line %d: error: \"%s\" or \"%s\" is expected after \"%s\"\n", *current_line_num, PARAM_STRING_BEGIN, PARAM_STRING_END, KEYWORD_STRING_FOR_EACH_OF_MEMBERS );
						return FAILED_ERROR;
					}
					LINE_PART part;
					part.type = param;
					tl.line_parts.push_back( part );
					skip_spaces( remaining, content_start );
					if ( content_start < remaining.size() )
					{
						printf( "line %d: error: unexpected token(s) \"%s\"\n", *current_line_num, std::string( remaining.begin() + content_start, remaining.end() ) );
						return FAILED_ERROR;
					}
					break;
				}
				default:
				{
					LINE_PART part;
					part.type = LINE_PART_VERBATIM;
					part.verbatim = std::string( line.begin() + content_start, line.end() );
					tl.line_parts.push_back( part );
				}
			}
			nodes.push_back( tl );
		}

		if ( !end_found )
		{
			printf( "line %d: error: \"%s\" not found\n", *current_line_num, PARAM_STRING_END_TEMPLATE );
			return FAILED_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
		}

		_root_node.type = NODE_TYPE_BEGIN_TEMPLATE;
		_root_node.root.type = NODE_TYPE_TEMPLATE_ROOT;
		bool tree_ok = make_node_tree( _root_node.root, nodes.begin(), nodes.end() );
		if ( !tree_ok )
		{
			printf( "line %d: error: building tree failed\n", _root_node.src_line_num );
			return FAILED_BUID_TREE_ERROR; // TODO: make sure the decision is correct in all cases + error analysis and reporting
		}

		validate_node( _root_node.root );

		return OK;
	}

/*	void print_template_basics( ANY_TEMPLATE_ROOT& _root_node )
	{
		printf( "Template name = \"%s\", type = \"%s\", size: %d nodes\n", _root_node.name.c_str(), _root_node.type.c_str(), nodes.size() );
		for ( unsigned int i=0; i<nodes.size(); i++ )
		{
			printf( "%d: %s%d", nodes[i].src_line_num, nodes[i].type == NODE_TYPE_CONTENT ? "    " : "ctr ", nodes[i].type );
			if ( nodes[i].line_parts.size() )
			{
				printf( ", \"" );
				print_line_parts( nodes[i].line_parts );
				printf( "\"\n" );
			}
			else
				printf( "\n" );
		}
	}*/

	void print_tree( ANY_TEMPLATE_ROOT& _root_node )
	{
		print_node( _root_node.root, 0 );
	}
};

template_parser tp;

bool load_template( FILE* ft, ANY_TEMPLATE_ROOT& _root_node, int* current_line_num )
{
	return tp.load_template( ft, _root_node, current_line_num );
}

void print_tree( ANY_TEMPLATE_ROOT& _root_node )
{
	tp.print_tree( _root_node );
}
