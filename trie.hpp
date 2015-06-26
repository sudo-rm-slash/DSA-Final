#include <string.h>
#include <stdlib.h>
#include "char_map.hpp"

typedef unsigned int uint;
typedef void account;

//trie:

class trie{

public:
	
	struct trie_node{
		char_map<trie_node*>children;
		account* ptr_account = nullptr;
	};		
	account* find( char* str );
	void insert( char* str, account* ptr_account );
	void remove( char* str );

private:       
	trie_node root;       
};
