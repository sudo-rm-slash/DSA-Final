#include "util.hpp"
#include "../trie.hpp"
#include <iostream>
#include <string>

#define N_TEST 10


char rand_strs[N_TEST][STR_MAX_LENGTH];


void int_to_string( int val, char* str, int n_digit ){
	for( int i = n_digit - 1 ; i >= 0 ; i-- ){
		str[i] = '0' + val % 10;
		val /= 10;
	}
	str[ n_digit ] = '\0';
}

char str[STR_MAX_LENGTH];


int main(){

	dsa::trie tr;

	for( int i = 0 ; i < 10000 ; ++i ){
		int_to_string( i, str, 6 );
		std::cout << str << std::endl;
		tr.insert( str, i );
	}


	dsa::trie::traveler traveler = tr.get_traveler();

	tr.find( "001000" );
	
	std::string cmd;
	while( std::cin >> cmd ){
		if( cmd == "p" ){
			traveler = traveler.parent();
			std::cout << traveler.get_char() << std::endl;
		}else if( cmd == "n" ){
			dsa::trie::traveler child = traveler.child_next();
			if( child.valid() ){
				std::cout << child.get_char() << std::endl;
			}else{
				std::cout << "Not a valid child." << std::endl;
			}
		}else if( cmd == "c" ){
			char ind;
			std::cin >> ind;
			traveler = traveler.child( ind );
			std::cout << traveler.get_char() << std::endl;
		}else{
			std::cout << "Wrong cmd." << std::endl;
		}
	}
		
			
}

