#include "recommendation.hpp"

// □ : Slot that is the same as original character
// ✖ : Slot that is different from original character
// ○ : Empty slot

// recipe:
// { 
//     positions of extra slots
//     {x1,x2,x3...},
//     positions of in-place slots
//     {y1,y2,y3...},
//     positions of empty slots
//     {z1,z2,z3...} 
// },
recommendation::std::vector<recipe> score_1_recipes{ 

	//Recipe 1: □  □  □  ○  |
	{
		{},{},{0}
	}
	//Recipe 2: □  □  □  ✖  |
	{
		{},{0},{}
	},
	//Recipe 3: □  □  □  □  | ✖ 
	{ 
		{0},{},{} 
	},
};

recommendation::std::vector<recipe> score_2_recipes{

	//Recipe 1: □  □  ✖  □  |
	{ 
		{},{1},{} 
	},
	//Recipe 2: □  □  ✖  ○  | 
	{
		{},{0},{0}
	},
	//Recipe 3: □  □  □  ✖  | ✖ 
	{
		{0},{0},{}
	}

};

recommendation::std::vector<recipe> score_3_recipes{

	//Recipe 1: □  □  ○  ○  |
	{
		{},{},{0,1}
	},
	//Recipe 2: □  ✖  □  □  | 
	{
		{},{2},{}
	},
	//Recipe 3: □  □  ✖  ✖  |
	{
		{},{0,1},{}
	},
	//Recipe 4: □  □  □  □  | ✖  ✖
	{ 
		{0,1},{},{} 
	},
	//Recipe 5: □  □  ✖  □  | ✖
	{
		{0},{1},{}
	}

};

recommendation::recommendation()
{
	recommendation_count = 0;
}

void recommendation::enumerate_strings( )
{
	
}
void execute_recipe( std::vector<recipe>& recipes )
{
	std::vector<std::string> candidate_strings;
	
	for( auto current_recipe:recipes )
	{
		for( auto position: current_recipe[1] )
			enumerate_nodes( candidate_strings, APPEND( position ) )

	}
}
void recommendation::trim_string( 
void recommendation::enumerate_nodes( node* node, std::vector<std::string> candidate_strings , int position )
{
	char* candidates_characters_ptr = candidates_characters;
	child_node* child = node->children.start;

	while( child != nullptr )
	{
		while( *candidates_characters_ptr != child.data() )
		{
			undetermined_string[ position ] = *candidates_characters_ptr;
			recommendations.push_back( undetermined_string );
			++candidates_characters_ptr;
		}

		child = child->next;
		++candidates_characters_ptr;
	}

	
	while( candidates_characters_ptr )
	{
		undetermined_string[ position ] = *candidates_characters_ptr;
		recommendations.push_back( undetermined_string );
		++candidates_characters_ptr;
	}

}

































#include "trie.hpp"
#include <stack>
#include <queue>

#define RECOMMENDATION_NUMBER 10

char candidates[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

unsigned char_map<T>::key_to_ind( char key ){
	if( 'a' <= key && key <= 'z' ){
		return key - 'a';
	}
	if( 'A' <= key && key <= 'Z' ){
		return key - 'A' + 26;
	}
	if( '0' <= key && key <= '9' ){
		return key - '0' + 52;
	}
}

struct prefix_t {

	dsa::trie::node* node;
	char* str;

};

void current( 

std::pair<node*,char*> longest_prefix( char* username )
{
	trie_node* node = &root;

	do{
		node = node->children.find(*username);
		if (node == nullptr){
			return username;
		}

	}while (*username++ != '\0');
}

void append_nodes( std::vector<std::string> recommendations, std::string output, node* current_node )
{
	while( current_node->children.next() != -1 && recommendations.size() <= RECOMMENDATION_NUMBER )
	{
		output
	}
}
static void dsa::recommend_non_existing_accounts( const char* username )
{
	std::vector<std::string> recommendations;
	std::string output(username);

	append_nodes( recommendations, output, current_node->parent );
}

static void dsa::recommend_existing_accounts( const char* username )
{
	std::priority_queue<std::string> recommendations;
	std::string              output;
	std::stack<node*>        candidates;
	char* current_character = username;
	int dept = 0;

	candidates.push( root );

	while( recommendations.size() <= RECOMMENDATION_NUMBER && !candidates.empty() )
	{
		node* current_node = candidates.front();
		candidates.pop();

		while( next_node && current_character )
		{

			next_node = current_node->children.find( *current_character );
			if( next_node != node )
			{
				output_stack.push( *current_character );
				candidates.push( next_node );
			}

			next_node = current_node->child();
			while( next_node )
			{
				if( next_node->data() != *current_character )
				{
					candidates.push( next_node );
					next_node = current_node->child();
				}

				if( next_node->data() == '\0' )
			}

		}
	}


}
