#include "trie.hpp"

#include <iostream>

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

#ifdef _DEBUG
	std::cout << "leaf: " << node << std::endl;
#endif
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
			node -> character = key;
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

// void dsa::trie::wildcard_print( char* str ){
// 	wildcard_print_node( &root, str );
// }

// void dsa::trie::wildcard_print_node( trie_node* node, char* str ){
// 	traveler tr_node = traveler( node );
// 	if( *str == '*' || *str == '.' ){
// 		for( traveler tr_child = tr_node.child_next();
// 		     tr_child.get_node() != nullptr;
// 		     tr_child = tr_node.child_next() ){
// 			wildcard_print_node( tr_child.get_node(), str + 1 );
// 		}

// 		if( *str == '*' ){
// 			for( traveler tr_child = tr_node.child_next();
// 			     tr_child.get_node() != nullptr;
// 			     tr_child = tr_node.child_next() ){
// 				wildcard_print_node( tr_child.get_node(), str );
// 			}
// 		}		
// 	}
// 	else if( *str == '\0' ){
// 	        storage[
// 	}
// 	else{
// 		traveler tr_child = tr_node.child( *str );
// 		trie_node* child_node  = tr_child.get_node();
// 		if( child_node != nullptr ){
// 			wildcard_print_node( child_node, str + 1 );
// 		}
// 	}
// }


std::list<int> dsa::trie::wildcard( char* str ){
	traveler tr_root = this -> get_traveler();
	return wildcard_node( tr_root , str );
}

std::list<int> dsa::trie::wildcard_node( traveler& node, char* str ){
	std::list<int> list;
	traveler tr_node = node;

	std::cerr << "data=" << node.get_char() << std::endl;
	
	if( *str == '*' || *str == '?' ){
		std::cerr << "...wildcard character found" << std::endl;
		

		for( traveler tr_child = tr_node.child_next();
		     tr_child.valid();
		     tr_child = tr_node.child_next() ){			
			list.merge( wildcard_node( tr_child, str + 1 ) );			
			if( *str == '*' ){
				std::cerr << "...* character found, continue" << std::endl;
				list.merge( wildcard_node( tr_node, str + 1 ) );
				list.merge( wildcard_node( tr_child, str ) );
			}		
		}

	}
	else if( *str == '\0' ){
<<<<<<< HEAD
		std::cerr << "...end of string" << std::endl;
		
		traveler leaf = tr_node.child('\0');		
		std::cerr << "current_data=" << leaf.get_data() << std::endl;
		
		if( leaf.valid() ){
			std::cerr << "...valid leaf" << std::endl;
			
			list.push_back( leaf.get_data() );
		}
=======
		//print_full_id();
>>>>>>> 7303eafeba9653394656282f67dd5aeaac1e247f
	}
	else{
		traveler tr_child = tr_node.child( *str );
		if( tr_child.valid() ){
			std::cerr << "...valid child" << std::endl;
			
			list.merge( wildcard_node( tr_child, str + 1 ) );
		}
	}

	return list;
}
	
dsa::trie::traveler::traveler(){
	node = nullptr ;
}
	
dsa::trie::traveler::traveler( trie_node*node )
	:map_iterator( node -> children.get_iterator() ){
	this -> node = node;
}

dsa::trie::traveler dsa::trie::traveler::child_next(){
	trie_node*node = map_iterator.get_data();
	map_iterator.next();
	if( node == nullptr ){
		return traveler();
	}
	return traveler( node );
}

dsa::trie::traveler dsa::trie::traveler::child( char index ){
	trie_node* next_node = node -> children.find( index );
	return traveler( next_node );
}

dsa::trie::trie_node* dsa::trie::traveler::get_node(){
	return node;
}

bool dsa::trie::traveler::valid(){
	 if( node == nullptr ){
		 return false;
	 }
	 else{
		 return true;
	 }
 }

 int dsa::trie::traveler::get_data(){
	 if( this -> valid() ){
		 return this -> node -> ptr_account;
	 }
	 else{
		 return -1;
	 }
 }


dsa::trie::traveler dsa::trie::traveler::parent(){
	return traveler( this -> get_node() -> parent );
 }

char dsa::trie::traveler::get_char(){
	return this -> get_node() -> character;
 }



dsa::trie::traveler dsa::trie::get_traveler(){
	return traveler( &root );
}
