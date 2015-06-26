#include "../trie.hpp"
#include <iostream>
#include <map>
//#include "char_map.hpp"
#include <ctime>
#include <cstdlib>
#include <map>
#include <utility>
#include <cstring>
using namespace std;

typedef char* key;
typedef int data;

#define N_CHAR 62
#define STR_MAX_LENGTH 100
#define N_TEST 10000
#define N_OPERATION 3

using namespace dsa;

enum operations{ INSERT, REMOVE, FIND };

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

char get_random_string(char* str){
	int length = ( rand() % (STR_MAX_LENGTH - 1) ) + 1;
	for( int i = 0 ; i < length ; ++i ){
		str[i] = get_random_char();
	}
	str[STR_MAX_LENGTH] = '\0';
}

char get_random_opration(){
	return rand() % N_OPERATION;
}


data trie_find( trie&t, key k ){
	return t.find( k );
}

data std_map_find( map<key,data>& m, key k ){
	if( m.count( k ) == 0 ){
		return -1;
	}
	return m.at( k );
}


data trie_insert( trie& t, key k, data d ){
	t.insert( k, d );
	return trie_find( t, k );
}

data std_map_insert( std::map<key,data>& m, key k, data d ){
	m.insert( pair<key,data>( k , d) );
	return std_map_find( m, k );
}

data trie_remove( trie& t, key k ){
	t.remove( k );
	return trie_find( t, k );
}

data std_map_remove( std::map<key,data>& m, key k ){
	m.erase( k );
	return std_map_find( m, k );
}

char rand_strs[N_TEST][STR_MAX_LENGTH];

unsigned int get_rand_number( unsigned int upper , unsigned int lower = 0 ){
	return ( rand() % ( upper - lower + 1 ) ) + lower;
}

void str_assign( char* str1, char* str2 ){
	for( int i = 0 ; i <= strlen( str2 ) ; ++i ){
		str1[i] = str2[i];
	}
}
		     
int main(){

	init_char_table();	
	srand( time(NULL) );

	for( int i = 0 ; i < N_TEST ; ++i ){
		get_random_string( rand_strs[i] );
	}
	unsigned int index_used = 0;

	str_assign( rand_strs[0], "123" );
	
	map<key,data>std_map;
	trie my_trie;
	

	std_map_insert( std_map, rand_strs[0], -1 );
	trie_insert( my_trie, rand_strs[0],  -1 );

	char str[N_CHAR];
	for( unsigned long long int i = 1 ; i < N_TEST ; ++i ){
		int operation = get_random_opration();

		switch( operation ){
		case INSERT:{
			char* str = rand_strs[index_used++];
			cout << i << "-th Insert " << str << endl;
			data result1 = std_map_insert( std_map, str, i );
			data result2 = trie_insert( my_trie, str,  i );
			if( result1 != result2 ){				
				cerr << "Error: " << i << "-th Insert " << str << endl
				     << "      std = " <<  result1 
				     << " char = " <<  result2 << endl;
			}
			break;
		}

		case REMOVE:{
			int index = get_rand_number( index_used );
			char* str = rand_strs[index];
			cout << i << "-th Remove " << str << endl;
			data result1 = std_map_remove( std_map, str );
			data result2 = trie_remove( my_trie , str );
			if( result1 != result2 ){				
				cerr << "Error: " << i << "-th Remove " << str << endl
				     << "      std = " <<  result1
				     << " char = " <<   result2 << endl;
			}
			break;
		}

		case FIND:{
			int index = get_rand_number( index_used );
			char* str = rand_strs[index];
			cout << i << "-th At " << str << endl;
			data result1 = std_map_find( std_map, str );
			data result2 = trie_find( my_trie, str );
			if( result1 != result2 ){				
				cerr << "Error: " << i << "-th Find " << str << endl
				     << "      std = " <<   result1 
				     << " char = " << result2 << endl;
			}
			break;
		}
		}
	}
}
