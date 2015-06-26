#include "trie.hpp"

int dsa::trie::find(char* str)
{
	
	unsigned int depth = 0;
	char key;
	trie_node* node = &root;

	do{
		key = str[depth++];
		node = node->children.find(key);
		if (node == nullptr){
			return -1;
		}

	}while (key != '\0');

	return node->ptr_account;
}

void dsa::trie::insert(char* str, int ptr_account)
{

	unsigned int depth = 0;
	char key;
	trie_node* parent;
	trie_node* node = &root;
	do{
			key = str[depth++];
			parent = node;
			node = node->children.find(key);
			if (node == nullptr)
				{
					dsa::trie::trie_node* new_node = new dsa::trie::trie_node;
					parent->children.insert(key, new_node);
					node = new_node;
					node->parent = parent;
					//cerr << "Trie 35: " << new_node
					//Can do compression here.
				}
		}
	while (key != '\0');

	if (node->ptr_account == -1)
		{
			node->ptr_account = ptr_account;
		}

}

#define MAX_LENGTH 100
void dsa::trie::remove(char* str)
{

	trie_node* node_stack[MAX_LENGTH];
	unsigned int depth = 0;
	char key;
	trie_node* node = &root;

	do{
		node_stack[depth] = node;
		key = str[depth];
		depth += 1;
		node = node->children.find(key);

		if (node == nullptr){
			return;
		}

	}while (key != '\0');

	node->ptr_account = -1;

	depth --;

	node = node_stack[depth];

	while (depth > 0 && node->children.get_size() == 0)
		{
			depth -= 1;
			node = node_stack[depth];
			trie_node* empty_node = node->children.remove(str[depth]);
			delete empty_node;
		}
}

void dsa::trie::wildcard_print( char* str ){
	wildcard_print_node( &root, str );
}

void dsa::trie::wildcard_print_node( trie_node* node, char* str ){
	traveler tr_node = traveler( node );
	if( *str == '*' || *str == '.' ){
		for( traveler tr_child = tr_node.child_next();
		     tr_child.get_node() != nullptr;
		     tr_child = tr_node.child_next() ){
			wildcard_print_node( tr_child.get_node(), str + 1 );
		}

		if( *str == '.' ){
			for( traveler tr_child = tr_node.child_next();
			     tr_child.get_node() != nullptr;
			     tr_child = tr_node.child_next() ){
				wildcard_print_node( tr_child.get_node(), str );
			}
		}		
	}
	else if( *str == '\0' ){
		//print_full_id();
	}
	else{
		traveler tr_child = tr_node.child( *str );
		trie_node* child_node  = tr_child.get_node();
		if( child_node != nullptr ){
			wildcard_print_node( child_node, str + 1 );
		}
	}
}
	
	
dsa::trie::traveler::traveler( trie_node*node )
	:map_iterator( node -> children.get_iterator() ){
	this -> node = node;
}

dsa::trie::traveler dsa::trie::traveler::child_next(){
	map_iterator.next();
	return traveler( map_iterator.get_data() );
}

dsa::trie::traveler dsa::trie::traveler::child( char index ){
	trie_node* next_node = node -> children.find( index );
	return traveler( next_node );
}

dsa::trie::trie_node* dsa::trie::traveler::get_node(){
	return node;
}
