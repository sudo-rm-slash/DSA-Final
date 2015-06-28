#include "util.hpp"
#include <cstring>

char char_table[N_CHAR];


char get_random_char(){
	int rand_number = rand() % N_CHAR;	
	return char_table[rand_number];
}

void get_random_string(char* str){
	int length = ( rand() % (STR_MAX_LENGTH - 1) ) + 1;
	for( int i = 0 ; i < length ; ++i ){
		str[i] = get_random_char();
	}
	str[length] = '\0';
}

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


void str_assign( char* str1, const char* str2 ){
	for( int i = 0 ; i <= strlen( str2 ) ; ++i ){
		str1[i] = str2[i];
	}
}
