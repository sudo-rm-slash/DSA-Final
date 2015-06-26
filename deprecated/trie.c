#include <string.h>
#include <stdlib.h>
#include "trie.hpp"
typedef unsigned int uint;


void* trie_find( trie* trie_obj, char* str ){
	
	trie_node* node_now = trie_obj -> root ;
	void* target_ptr = NULL;
	int depth = 0;
	while( node_now != NULL && depth < strlen( str ) ){
		node_now = map_find( node_now -> children, str[depth] );
		depth ++;
	}
	return target_ptr;
}

void trie_insert( trie* trie_obj, char* str, void* ptr ){
	trie_node* node_now = trie_obj -> root ;
	
	int depth = 0;
	while( depth < strlen( str ) ){
		node_now = map_find( trie_obj -> children , str[depth] );
		if( node_now == NULL ){
			node_now = malloc( sizeof( trie_node ) );
			map_insert( node_now -> children, str[depth], node_now );
		}
		depth ++;
	}
	node_now -> ptr_data = ptr;
}
	
		
void trie_remove( trie* trie_obj, char* str ){

	trie_node* node_stack[100];
	char char_stack[100];

	int depth = 0;
	while( depth < strlen( str ) && node_now != NULL ){

		node_stack[depth] = node_now;
		char_stack[depth] = str[depth];

		node_now = map_find( trie_obj -> children , str[depth] );		
		depth += 1;
	}

	node_now -> ptr_data = NULL;

	for( depth -= 1; depth > 0 ; --depth ){

		trie_node* node = node_stack[depth];		

		if( map_size( node -> children ) == 0 &&
		    node -> ptr_data == NULL ){

			free( node );

			trie_node* parent_node = node_stack[depth - 1];
			char node_index = char_stack[depth - 1];

			map_remove( parent_node -> children, node_index );
		}else{
			break;
		}
	}
			
}
