#include <iostream>
#include <map>
#include "char_map.hpp"
#include <ctime>
#include <cstdlib>
#include <map>
#include <utility>

using namespace std;

typedef char key;
typedef int data;

#define N_CHAR 62
#define STR_MAX_LENGTH 100
#define N_TEST 10000
#define N_OPERATION 3

enum operations{ INSERT, REMOVE, AT };

char char_table[N_CHAR];


void init_char_table(){
	int index = 0;
	for( int i = 0; i < 26 ; ++i ){
		char_table[index] = 'a' + i;
		index += 1;
	}
	for( int i = 0; i < 26 ; ++i ){
		char_table[index] = 'A' + i;
		index += 1;
	}
	for( int i = 0 ; i < 10 ; ++i ){
		char_table[index] = '0' + i;
		index += 1;
	}
}

char get_random_char(){
	int rand_number = rand() % N_CHAR;	
	return char_table[rand_number];
}

char get_random_opration(){
	return rand() % N_OPERATION;
}


data char_map_find( char_map<data>& m, key k ){
	return m.find( k );
}

data std_map_find( map<key,data>& m, key k ){
	if( m.count( k ) == 0 ){
		return 0;
	}
	return m.at( k );
}


data char_map_insert( char_map<data>& m, key k, data d ){
	m.insert( k, d );
	return char_map_find( m, k );
}

data std_map_insert( std::map<key,data>& m, key k, data d ){
	m.insert( pair<key,data>( k , d) );
	return std_map_find( m, k );
}

data char_map_remove( char_map<data>& m, key k ){
	m.remove( k );
	return char_map_find( m, k );
}

data std_map_remove( std::map<key,data>& m, key k ){
	m.erase( k );
	return std_map_find( m, k );
}
		     
int main(){

	srand( time(NULL) );
	
	char_map<data>c_map;
	map<key,data>std_map;
	
	init_char_table();

	for( int i = 1 ; i < N_TEST ; ++i ){
		int operation = get_random_opration();

		switch( operation ){
		case INSERT:{
			char rand_char = get_random_char();
			cout << i << "-th Insert " << rand_char << endl;
			data result1 = std_map_insert( std_map, rand_char, i );
			data result2 = char_map_insert( c_map, rand_char, i );
			if( result1 != result2 ){				
				cerr << "Error: " << i << "-th operation" << endl
				     << "      std = " << result1 << " char = " << result2 << endl;
			}
			break;
		}

		case REMOVE:{
			char rand_char = get_random_char();
			cout << i << "-th Remove " << rand_char << endl;
			data result1 = std_map_remove( std_map, rand_char );
			data result2 = char_map_remove( c_map, rand_char );
			if( result1 != result2 ){				
				cerr << "Error: " << i << "-th operation" << endl
				     << "      std = " << result1 << " char = " << result2 << endl;
			}
			break;
		}

		case AT:{
			char rand_char = get_random_char();
			cout << i << "-th At " << rand_char << endl;
			data result1 = std_map_find( std_map, rand_char );
			data result2 = char_map_find( c_map, rand_char );
			if( result1 != result2 ){				
				cerr << "Error: " << i << "-th operation" << endl
				     << "      std = " << result1 << " char = " << result2 << endl;
			}
			break;
		}
		}
	}
}
