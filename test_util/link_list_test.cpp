#include "../link_list.hpp"
#include <iostream>

link_list<int> test( int depth ){
	link_list<int> list ;
	if( depth == 100 ) return list;
	list.insert( depth );
	list.append( test( depth + 1 ) );
	return list;
}
	

int main(){
	link_list<int> list;
	//list = test(0);
	for( int i = 0 ; i < 100 ; ++i ){
		list.insert( i );
	}
						
	link_list<int>::node*node = list.head -> next;
	while( node != 0 ){
		std::cout << node -> data << std::endl;
		node = node -> next;
	}
}
