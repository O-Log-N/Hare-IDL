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

#include "template_processor.h"
#include <string.h> // for memmov()
#include <assert.h> // for assert()

#include <vector>
using namespace std;

#define NODE_TYPE_CONTENT 0
#define NODE_TYPE_BEGIN_TEMPLATE 1
#define NODE_TYPE_END_TEMPLATE 2
#define NODE_TYPE_IF 3
#define NODE_TYPE_ELSE 4
#define NODE_TYPE_ELIF 5
#define NODE_TYPE_ENDIF 6
#define NODE_TYPE_FOR_EACH_OF_MEMBERS 7
#define NODE_TYPE_INCLUDE 8
#define NODE_TYPE_ASSERT 9// derived types
//#define NODE_TYPE_TMP 20
#define NODE_TYPE_IF_TRUE_BRANCHE 21
#define NODE_TYPE_IF_FALSE_BRANCHE 22

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
#define PARAM_BEGIN_TEMPLATE 101
#define PARAM_END_TEMPLATE 102
#define KEYWORD_FOR_EACH_OF_MEMBERS 103
#define KEYWORD_IF 104
#define KEYWORD_ELSE 105
#define KEYWORD_ELIF 106
#define PARAM_ENDIF 107
#define PARAM_ASSERT 108

// PARAMETERS (following main keywords)
#define PARAM_NONE 120
#define PARAM_TYPE 121
#define PARAM_BEGIN 122
#define PARAM_END 123

// plaseholders (single-words between '@')
#define LINE_PART_VERBATIM 200
#define PLASEHOLDER_STRUCTNAME 201
#define PLASEHOLDER_MEMBER_TYPE 202
#define PLASEHOLDER_MEMBER_NAME 203

#define PLASEHOLDER_STRING_STRUCTNAME "@STRUCTNAME@"
#define PLASEHOLDER_STRING_MEMBER_TYPE "@MEMBER-TYPE@"
#define PLASEHOLDER_STRING_MEMBER_NAME "@MEMBER-NAME@"

// expression parts ( ==, !=, etc)
#define EXPRESSION_PART_EQ 301
#define EXPRESSION_PART_NEQ 302

/*
// data types
#define DATA_TYPE_
#define DATA_TYPE_
#define DATA_TYPE_STRING_ ""
#define DATA_TYPE_STRING_ ""
*/

typedef struct _LINE_PART
{
	int type;
	std:: string verbatim;
} LINE_PART;

typedef vector<LINE_PART> LINE_PARTS;

typedef struct _TEMPLATE_NODE
{
	int line_type;
//	std::string content;
	int src_line_num;
	LINE_PARTS line_parts;
	vector<_TEMPLATE_NODE> child_nodes;
} TEMPLATE_NODE;

typedef vector<TEMPLATE_NODE> TEMPLATE_NODES;
typedef vector<TEMPLATE_NODE>::iterator TEMPLATE_NODES_ITERATOR;

class idl_generation_template
{
	std::string name;
	std::string type;
	TEMPLATE_NODE _root_node;
	TEMPLATE_NODES nodes;

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
				case PLASEHOLDER_STRUCTNAME: printf( PLASEHOLDER_STRING_STRUCTNAME ); break;
				case PLASEHOLDER_MEMBER_TYPE: printf( PLASEHOLDER_STRING_MEMBER_TYPE ); break;
				case PLASEHOLDER_MEMBER_NAME: printf( PLASEHOLDER_STRING_MEMBER_NAME ); break;
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
		switch ( node.line_type )
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
		switch ( node.line_type )
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
					assert( node.child_nodes[0].line_type == NODE_TYPE_IF_TRUE_BRANCHE || node.child_nodes[0].line_type == NODE_TYPE_IF_FALSE_BRANCHE );
				}
				else
				{
					assert( node.child_nodes[0].line_type == NODE_TYPE_IF_TRUE_BRANCHE );
					assert( node.child_nodes[1].line_type == NODE_TYPE_IF_FALSE_BRANCHE );
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

	bool calc_condition_of_if_node( TEMPLATE_NODE& if_node, void* idlmap, int context )
	{
		// NOTE: here we have a quite quick and dirty solution just for a couple of immediately necessary cases
		// TODO: full implementation

		assert( if_node.line_type == NODE_TYPE_IF || if_node.line_type == NODE_TYPE_ASSERT );
		bool ret;

		unsigned int i, j;
		vector<std::string> argstack;
		vector<int> commands;
		for ( i=0; i<if_node.line_parts.size(); i++ )
		{
			switch ( if_node.line_parts[i].type )
			{
				case LINE_PART_VERBATIM: argstack.push_back( if_node.line_parts[i].verbatim ); break;
				case EXPRESSION_PART_EQ:
				case EXPRESSION_PART_NEQ:
				{
					commands.push_back( if_node.line_parts[i].type );
					break;
				}
				case PLASEHOLDER_MEMBER_TYPE:
				{
					assert( context == CONTEXT_STRUCT_MEMBER );
					AttributeDeclNode* attr = (AttributeDeclNode*)idlmap;
					argstack.push_back( attr->type->toString() ); 
					break;
				}
				default:
				{
					printf( "Type %d is unexpected or unsupported\n", if_node.line_parts[i].type );
					assert( 0 == "Error: not supported" );
				}
			}
		}

		unsigned int command_cnt = commands.size();
		unsigned int stacksz = argstack.size();

		assert( ( command_cnt == 1 && stacksz == 2 ) || command_cnt == 0 && stacksz == 1 ); // limitation of a current version; TODO: further development

		if ( command_cnt == 1 )
		{
			for ( j=command_cnt; j; j-- )
			{
				switch ( commands[j-1] )
				{
					case EXPRESSION_PART_EQ:
					{
						ret = argstack[0] == argstack[1];
						break;
					}
					case EXPRESSION_PART_NEQ:
					{
						ret = !(argstack[0] == argstack[1]);
						break;
					}
					default:
					{
						printf( "Type %d is unexpected or unsupported\n", commands[j-1] );
						assert( 0 == "Error: not supported" );
					}
				}
			}
		}
		else
		{
			ret = !( argstack[0] == "0" || argstack[0] == "FALSE" );
		}
		return ret;
		/*
#define LINE_PART_VERBATIM 200
#define PLASEHOLDER_STRUCTNAME 201
#define PLASEHOLDER_MEMBER_TYPE 202
#define PLASEHOLDER_MEMBER_NAME 203

#define PLASEHOLDER_STRING_STRUCTNAME "@STRUCTNAME@"
#define PLASEHOLDER_STRING_MEMBER_TYPE "@MEMBER-TYPE@"
#define PLASEHOLDER_STRING_MEMBER_NAME "@MEMBER-NAME@"

// expression parts ( ==, !=, etc)
#define EXPRESSION_PART_EQ 301
#define EXPRESSION_PART_NEQ 302
		*/
	}

	void apply_node( TEMPLATE_NODE& node, void* idlmap, int context )
	{
		switch ( node.line_type )
		{
			case NODE_TYPE_CONTENT:
			{
				// we have to go char by char; if '@' is found, make sure it's not a placeholder, or replace it accordingly
/*				unsigned int pos = 0;
				unsigned int sz = node.content.size();
				do
				{
					if ( node.content[ pos ] != '@' )
					{
						printf( "%c", node.content[ pos ] );
						pos ++;
					}
					else
					{
						int placehldr = parse_placeholder( node.content, pos );
						switch ( placehldr )
						{
							case LINE_PART_VERBATIM: printf( "%c", node.content[ pos ] ); pos ++; break;
							case PLASEHOLDER_STRUCTNAME: printf( "<structname>" ); break;
							case PLASEHOLDER_MEMBER_TYPE: printf( "<mem_type>" ); break;
							case PLASEHOLDER_MEMBER_NAME: printf( "<mem_name>" ); break;
							default:
							{
								break;
								assert( 0 == "NOT IMPLEMENTED" );
							}
						}
					}
				}
				while ( pos < sz );*/
				for ( unsigned int i=0; i<node.line_parts.size(); i++ )
					switch ( node.line_parts[i].type )
					{
						case LINE_PART_VERBATIM:
						{
							printf( node.line_parts[i].verbatim.c_str() ); 
							break;
						}
						case PLASEHOLDER_STRUCTNAME: 
						{
//							if ( context == CONTEXT_STRUCT )
							assert( context == CONTEXT_STRUCT );
								printf( ((MappingDeclNode*)idlmap)->name.c_str() ); 
							break;
						}
						case PLASEHOLDER_MEMBER_TYPE: 
						{
							assert( context == CONTEXT_STRUCT_MEMBER );
//							printf( PLASEHOLDER_STRING_MEMBER_TYPE ); 
							AttributeDeclNode* attr = (AttributeDeclNode*)idlmap;
							printf( attr->type->toString().c_str() ); 
							break;
						}
						case PLASEHOLDER_MEMBER_NAME: 
						{
							assert( context == CONTEXT_STRUCT_MEMBER );
							AttributeDeclNode* attr = (AttributeDeclNode*)idlmap;
							printf( attr->name.c_str() ); 
							break;
						}
						default:
						{
							printf( "Unknown line_part.type = %d found", node.line_parts[i].type );
							assert( 0 == "Error: Not Implemented" );
						}
					}
				printf( "\n" ); 
				break;
			}
			case NODE_TYPE_BEGIN_TEMPLATE:
			case NODE_TYPE_IF_TRUE_BRANCHE:
			case NODE_TYPE_IF_FALSE_BRANCHE:
			{
				for ( unsigned int k=0; k<node.child_nodes.size(); k++ )
					apply_node( node.child_nodes[k], idlmap, context );
				break;
			}
			case NODE_TYPE_FOR_EACH_OF_MEMBERS:
			{
				assert( context == CONTEXT_STRUCT );
				int member_cnt = ((MappingDeclNode*)idlmap)->attributes.size();
				for ( int j=0; j<member_cnt; j++ )
				{
					for ( unsigned int k=0; k<node.child_nodes.size(); k++ )
						apply_node( node.child_nodes[k], &(*(((MappingDeclNode*)idlmap)->attributes[j])), CONTEXT_STRUCT_MEMBER );
				}
				break;
			}
			case NODE_TYPE_IF:
			{
				bool cond = calc_condition_of_if_node( node, idlmap, context );
				if ( cond )					
				{
					if ( node.child_nodes[0].line_type == NODE_TYPE_IF_TRUE_BRANCHE )
						apply_node( node.child_nodes[0], idlmap, context );
				}
				else
				{
					if ( node.child_nodes[0].line_type == NODE_TYPE_IF_FALSE_BRANCHE )
						apply_node( node.child_nodes[0], idlmap, context );
					else if ( node.child_nodes[1].line_type == NODE_TYPE_IF_FALSE_BRANCHE )
						apply_node( node.child_nodes[1], idlmap, context );
				}
				break;
			}
			case NODE_TYPE_ASSERT:
			{
				bool cond = calc_condition_of_if_node( node, idlmap, context );
				if ( !cond )					
				{
					printf( "Instantiation Error: Assertion failed: Line %d\n", node.src_line_num );
				}
				break;
			}
			case NODE_TYPE_INCLUDE:
			{
				assert( 0 == "ERROR: NOT IMPLEMENTED" );
				break;
			}
			default:
			{
				printf( "Unexpected node type %d found\n", node.line_type );
				assert( 0 == "ERROR: UNEXPECTED" );
			}
		}
	}

	bool make_node_tree( TEMPLATE_NODE& root_node, TEMPLATE_NODES_ITERATOR node_begin, TEMPLATE_NODES_ITERATOR node_end )
	{
		TEMPLATE_NODES_ITERATOR it = node_begin;
		while ( it != node_end )
		{
			switch ( it->line_type )
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
						do { ++node_block_end; } while ( node_block_end != node_end && node_block_end->line_type != NODE_TYPE_FOR_EACH_OF_MEMBERS );
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
						if ( node_block_end->line_type == NODE_TYPE_IF )
							ifendif_balance ++;
						if ( node_block_end->line_type == NODE_TYPE_ENDIF )
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
					assert( node_block_end->line_type == NODE_TYPE_ENDIF );

					// VALID CASE
					// we need to separate its TRUE branche from the rest if IF/ENDIF body which is it FALSE branch
					// posive branch ends up (up to inner IF/ENDIF blocks) with one of NODE_TYPE_ELSE, NODE_TYPE_ELIF, or NODE_TYPE_ENDIF (the latter is already processed out)
					// if none of NODE_TYPE_ELSE or NODE_TYPE_ELIF found, IF block has only its TRUE branch
					ifendif_balance = 0;
					TEMPLATE_NODES_ITERATOR true_branch_end = it;
					do 
					{ 
						++true_branch_end; 
						if ( true_branch_end->line_type == NODE_TYPE_IF )
							ifendif_balance ++;
						if ( true_branch_end->line_type == NODE_TYPE_ENDIF )
							ifendif_balance --;
						if ( ifendif_balance == 0 && (true_branch_end->line_type == NODE_TYPE_ELSE || true_branch_end->line_type == NODE_TYPE_ELIF ) )
						{
							break;
						}
					}
					while ( true_branch_end != node_block_end );

					TEMPLATE_NODE if_true, if_false;
					if_true.line_type = NODE_TYPE_IF_TRUE_BRANCHE;
					if_true.src_line_num = true_branch_end == it + 1 ? -1 : it->src_line_num + 1;
					make_node_tree( if_true, it + 1, true_branch_end );

					if ( true_branch_end->line_type == NODE_TYPE_ELSE )
					{
						if_false.line_type = NODE_TYPE_IF_FALSE_BRANCHE;
						if_false.src_line_num = true_branch_end != node_block_end ? true_branch_end->src_line_num + 1 : -1;
						make_node_tree( if_false, true_branch_end + 1, node_block_end );
					}
					else
					{
						assert( true_branch_end->line_type == NODE_TYPE_ELIF );
						if_false.line_type = NODE_TYPE_IF_FALSE_BRANCHE;
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
					if ( root_node.line_type != NODE_TYPE_IF_FALSE_BRANCHE )
					{
						printf( "line %d: error: \"%s\" without matching \"%s\"\n", it->src_line_num, KEYWORD_STRING_ELIF, KEYWORD_STRING_IF );
						return false;
					}
					assert( node_end->line_type == NODE_TYPE_ENDIF );
					++node_end; // that is, we will re-use it
					it->line_type = NODE_TYPE_IF;
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
		if ( line.compare( content_start, sizeof(PARAM_STRING_BEGIN_TEMPLATE)-1, PARAM_STRING_BEGIN_TEMPLATE ) == 0 )
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
		}
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
		if ( line.compare( content_start, sizeof(PARAM_STRING_BEGIN)-1, PARAM_STRING_BEGIN ) == 0 )
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
		}
//		while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
		return ret;
	}

	int parse_placeholder( std::string& line, unsigned int& content_start )
	{
		int ret = LINE_PART_VERBATIM;
		while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
		if ( line.compare( content_start, sizeof(PLASEHOLDER_STRING_STRUCTNAME)-1, PLASEHOLDER_STRING_STRUCTNAME ) == 0 )
		{
			content_start += sizeof(PLASEHOLDER_STRING_STRUCTNAME)-1;
			ret = PLASEHOLDER_STRUCTNAME;
		}
		else if ( line.compare( content_start, sizeof(PLASEHOLDER_STRING_MEMBER_TYPE)-1, PLASEHOLDER_STRING_MEMBER_TYPE ) == 0 )
		{
			content_start += sizeof(PLASEHOLDER_STRING_MEMBER_TYPE)-1;
			ret = PLASEHOLDER_MEMBER_TYPE;
		}
		else if ( line.compare( content_start, sizeof(PLASEHOLDER_STRING_MEMBER_NAME)-1, PLASEHOLDER_STRING_MEMBER_NAME ) == 0 )
		{
			content_start += sizeof(PLASEHOLDER_STRING_MEMBER_NAME)-1;
			ret = PLASEHOLDER_MEMBER_NAME;
		}
//		while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
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
							case PLASEHOLDER_STRUCTNAME:
							case PLASEHOLDER_MEMBER_TYPE:
							case PLASEHOLDER_MEMBER_NAME:
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
							case PLASEHOLDER_MEMBER_TYPE:
							case PLASEHOLDER_MEMBER_NAME:
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
	idl_generation_template() {}
	bool load_template( FILE* ft, int* current_line_num )
	{
		if ( ft == NULL )
		{
			printf( "error: no input file\n" );
			return false;
		}
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
					while ( content_start < line.size() && (!(line[content_start] == ' ' || line[content_start] == '\t'))) name.push_back( line[content_start++] );
					while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
					if ( line.compare( content_start, sizeof(PARAM_STRING_TYPE)-1, PARAM_STRING_TYPE ) != 0 )
					{
						printf( "line %d: error: no \"%s\" after \"%s\"\n", *current_line_num, PARAM_STRING_TYPE, PARAM_STRING_BEGIN_TEMPLATE );
						return false; // TODO: make sure the decision is correct in all cases + error analysis and reporting
					}
					content_start += sizeof(PARAM_STRING_TYPE)-1;
					while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
					if ( content_start < line.size() && line[content_start] != '=' )
					{
						printf( "line %d: error: no \"%s\" after \"%s\"\n", *current_line_num, "=", PARAM_STRING_TYPE );
						return false; // TODO: make sure the decision is correct in all cases + error analysis and reporting
					}
					content_start++;
					while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
					// read type
					while ( content_start < line.size() && (!(line[content_start] == ' ' || line[content_start] == '\t'))) type.push_back( line[content_start++] );
					while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
					if ( !( content_start == line.size() ) )
					{
						printf( "line %d: error: unexpected tokens\n", *current_line_num );
						return false; // TODO: make sure the decision is correct in all cases + error analysis and reporting
					}

					start_found = true;
					break;
				}
			}
			// at this point a template has started...
		}

		if ( !start_found )
		{
			printf( "line %d: error: no no template has been found\n", *current_line_num );
			return false; // TODO: make sure the decision is correct in all cases + error analysis and reporting
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
				tl.line_type = NODE_TYPE_CONTENT;
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
				return false;
			}

			// is template end?
			if ( kwd == NODE_TYPE_END_TEMPLATE )
			{
				// read name
				std::string end_name;
				while ( content_start < line.size() && (!(line[content_start] == ' ' || line[content_start] == '\t'))) end_name.push_back( line[content_start++] );
				if ( end_name != name )
				{
					printf( "line %d: error: name does not match that at template beginning\n", *current_line_num );
					return false;
				}
				while ( content_start < line.size() && (line[content_start] == ' ' || line[content_start] == '\t')) content_start++;
				if ( !( content_start == line.size() || ( content_start + 1 == line.size() || line[content_start] == '\r' ) ) )
				{
					printf( "line %d: error: unexpected tokens\n", *current_line_num );
					return false; // TODO: make sure the decision is correct in all cases + error analysis and reporting
				}

				end_found = true;
				break;
			}

			// other control nodes
			tl.src_line_num = *current_line_num;
			tl.line_type = kwd;
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
						return false;
					}
					LINE_PART part;
					part.type = param;
					tl.line_parts.push_back( part );
					skip_spaces( remaining, content_start );
					if ( content_start < remaining.size() )
					{
						printf( "line %d: error: unexpected token(s) \"%s\"\n", *current_line_num, std::string( remaining.begin() + content_start, remaining.end() ) );
						return false;
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
			return false; // TODO: make sure the decision is correct in all cases + error analysis and reporting
		}

		_root_node.line_type = NODE_TYPE_BEGIN_TEMPLATE;
		bool tree_ok = make_node_tree( _root_node, nodes.begin(), nodes.end() );
		if ( !tree_ok )
		{
			printf( "line %d: error: building tree failed\n", _root_node.src_line_num );
			return false; // TODO: make sure the decision is correct in all cases + error analysis and reporting
		}

		validate_node( _root_node );

		return true;
	}

	void print_template_basics()
	{
		printf( "Template name = \"%s\", type = \"%s\", size: %d nodes\n", name.c_str(), type.c_str(), nodes.size() );
		for ( unsigned int i=0; i<nodes.size(); i++ )
		{
			printf( "%d: %s%d", nodes[i].src_line_num, nodes[i].line_type == NODE_TYPE_CONTENT ? "    " : "ctr ", nodes[i].line_type );
			if ( nodes[i].line_parts.size() )
			{
				printf( ", \"" );
				print_line_parts( nodes[i].line_parts );
				printf( "\"\n" );
			}
			else
				printf( "\n" );
		}
	}

	void print_tree()
	{
		print_node( _root_node, 0 );
	}

	void apply( void* idlmap, int context )
	{
		apply_node( _root_node, idlmap, context );
	}
};

idl_generation_template gt;

bool load_template( FILE* ft, int* current_line_num )
{
	return gt.load_template( ft, current_line_num );
}

void print_template_basics()
{
	gt.print_template_basics();
}

void print_tree()
{
	gt.print_tree();
}

void apply( void* idlmap, int context )
{
	gt.apply( idlmap, context );
}
