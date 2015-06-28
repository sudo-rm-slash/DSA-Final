#include "util.hpp"
#include "../trie.hpp"
#include <iostream>
#include <string>
#include <list>
#define N_TEST 2


char rand_strs[N_TEST][STR_MAX_LENGTH];

int main(){

	for( int i = 0 ; i < N_TEST ; ++i ){
		std::string str;
		std::cin >> str ;
		str_assign( rand_strs[i], str.c_str() );
	}
	

	dsa::trie tr;
	for( int i = 0 ; i < N_TEST  ; ++i ){
		std::cout << rand_strs[i] << std::endl;
		tr.insert( rand_strs[i], i );
	}
	
	std::cout << tr.find( "abde" ) << std::endl
		  << tr.find( "abcde" ) << std::endl;

	std::list<int> list = tr.wildcard( "ab.e" );

	std::cout << "==================== Ans ====================" << std::endl;
	for(const auto& item:list)
		std::cout << "data: " << item << std::endl;

}
