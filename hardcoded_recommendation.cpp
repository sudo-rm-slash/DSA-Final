#include "hardcoded_recommendation.hpp"

#define ADD_RECOMMENDATION( candidate_string, length ) \
	recommendations.push_back( new char[ length+1 ] ); \
	strcpy( recommendations.last() , candidate_string ); 						

#define PROBE( candidate_string ) 				\
	if(hashmap[ candidate_string ]) 			\
	{											\
		ADD_RECOMMENDATION( candidate_string )  \
		CHECK_RETURN()						    \
	}
	
#define RECOVER_STRING( candidate_string, position ) \
	candidate_string[ position ] = original_text[ position ];

#define CHECK_LENGTH( text_length, length ) \
	if(  text_length < length )return;

#define CHECK_RETURN() \
	if( recommendations.size() > RECOMMENDATION_NUMBER )return; 

void dsa::hardcoded_recommendation::character_to_index( char ch )
{
	if( ch < 'A' )
		// ch is digit: ch - '0'
		return ch - '0';
	if( ch < 'a' )
		// ch is uppercase alphabet: ch - 'A' + 10 ( ch - 65 + 10 )
		return ch - 55;
	
	// ch is lowercase alphabet: ch - 'a' + 10 + 26 ( ch - 97 + 10 + 26 )
	return ch - 61;
}

void dsa::hardcoded_recommendation::enumerate_single_character_with_upperbound( char* candidate_string, int position, char upperbound = '\0')
{
	for( int i = 0; candidates_characters[i] != upperbound ; ++i )
	{
		candidate_string[ position ] = candidates_characters[i];
		PROBE( candidate_string )
	}
}

void dsa::hardcoded_recommendation::enumerate_single_character_with_lowerbound( char* candidate_string, int position, char lowerbound)
{
	for( int i = character_to_index(lowerbound) ; i < CANDIDATES_SIZE ; ++i )
	{
		candidate_string[ position ] = candidates_characters[i];
		PROBE( candidate_string )
	}
}

void dsa::hardcoded_recommendation::enumerate_double_character( char* candidate_string, int first, int second )
{
	for( int i = 0; i < CANDIDATES_SIZE ; ++i )
	{
		candidate_string[ first ] = candidates_characters[i];
		for( int j = 0; i < CANDIDATES_SIZE ; ++j )
		{
			candidate_string[ second ] = candidates_characters[j];
			PROBE( candidate_string )
		}			
	}
}

void dsa::hardcoded_recommendation::recommenend(const char* original_text)
{

	std::vector<char*> recommendations;
	int  text_length = std::strlen( original_text );
	auto candidate_string 	  = new char[ +1 ];
	std::strcpy( candidate_string, original_text );

//
//	Hardcoded spagetti
//
//	Score 1: □  □  □  ○  |
//
/*----------------------------------------------------*/
	candidate_string[ text_length-1 ] = '\0';
	PROBE( candidate_string )
	RECOVER_STRING( candidate_string , text_length-1 )
/*----------------------------------------------------*/

//
//	Hardcoded spagetti
//	Upper bound on candidate character to preserver alphabetic order
//
//	Score 1: □  □  □  ✖  |
//
/*----------------------------------------------------*/
	enumerate_single_character_with_upperbound( candidate_string, text_length-1, original_text[ text_length-1 ] );
	CHECK_RETURN()
	RECOVER_STRING( candidate_string , text_length-1 )
/*----------------------------------------------------*/

//
//	Hardcoded spagetti
//
//	Score 1: □  □  □  □  | ✖ 
//
/*----------------------------------------------------*/
	enumerate_single_character_with_upperbound( candidate_string, text_length );
	CHECK_RETURN()
	RECOVER_STRING( candidate_string , text_length )
/*----------------------------------------------------*/

//
//	Hardcoded spagetti
//	Lower bound on candidate character to preserver alphabetic order
//
//	Score 1: □  □  □  ✖  |
//
/*----------------------------------------------------*/
	enumerate_single_character_with_lowerbound( candidate_string, text_length-1, original_text[ text_length-1 ] );
	CHECK_RETURN()
	RECOVER_STRING( candidate_string , text_length-1 )
/*----------------------------------------------------*/

//
//	Hardcoded spagetti
//
//	Score 2: □  □  ✖  ○  | 
//
/*----------------------------------------------------*/
	CHECK_LENGTH( text_length, 2 )
	candidate_string[ text_length-1 ] = '\0';
	enumerate_single_character_with_upperbound( candidate_string, text_length-2, original_text[text_length-2] );
	CHECK_RETURN()
	RECOVER_STRING( candidate_string , text_length-2 )
	RECOVER_STRING( candidate_string , text_length-1 )
/*----------------------------------------------------*/

//
//	Hardcoded spagetti
//
//	Score 2: □  □  ✖  □  |
//
/*----------------------------------------------------*/
	enumerate_single_character_with_upperbound( candidate_string, text_length-2, original_text[text_length-2] );
	CHECK_RETURN()
	RECOVER_STRING( candidate_string , text_length-2 )
/*----------------------------------------------------*/


//
//	Hardcoded spagetti
//
//	Score 2: □  □  □  ✖  | ✖ 
//
/*----------------------------------------------------*/
	// enumerate_double_character( candidate_string, text_length-1, text_length );
	// CHECK_RETURN()
	// RECOVER_STRING( candidate_string , text_length-1 )
	// RECOVER_STRING( candidate_string , text_length )
/*----------------------------------------------------*/


	//Score 3: □  □  ○  ○  |
	//CHECK_LENGTH( text_length, 2 )
	
	//Score 3: □  ✖  □  □  | 

	//Score 3: □  □  ✖  ✖  |
	
	//Score 3: □  □  □  □  | ✖  ✖
	
	//Score 3: □  □  ✖  □  | ✖
}


void dsa::hardcoded_recommendation::print_recommendation()
{
	for( auto recommendation:recommendations )
	{
		std::cout << recommendation << " ";
	}
}
