#include "recommendation.hpp"

// Candidate has been confirmed and can be added into recommendation lists.
#define ADD_RECOMMENDATION( candidate_string, length ) \
	recommendations.push_back( new char[ length+1 ] ); \
	strcpy( recommendations.back() , candidate_string ); 						

// Recover the candidate_string to original text in convenience of later enumeration
#define RECOVER_STRING( candidate_string, position ) \
	candidate_string[ position ] = original_text[ position ];

// Check if we are going too far
#define CHECK_LENGTH( text_length, length ) \
	if(  text_length < length )return;

// Check if we have reached the required number of recommendations
#define CHECK_RETURN() \
	if( recommendations.size() > RECOMMENDATION_NUMBER )return; 

// Check if candidate_string exists in our target container
#define PROBE( candidate_string, length )             			\
	if(container.exist(std::string(candidate_string)))			\
	{                                           				\
		ADD_RECOMMENDATION( candidate_string, length ) 			\
		CHECK_RETURN()                          				\
	}

	

template<class T>
const char dsa::recommendation<T>::candidates_characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

/** 
 * @Function: map character to its corresponding index in static variable 'candidates_characters' 
 * 
 * @Param: ch	
 * 
 * @Return: index
 */
template<class T>
int dsa::recommendation<T>::character_to_index( char ch )
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

/** 
 * @Function:  enumerate all possible characters of a single slot
 *             and probe them one by one into the hashmap.
 *             Note that there's an upperbound to the enumeration. By doing so, we can preserve alphabetical order 
 *             For example, take 'abcd' as original text:
 *             ....
 *             ....
 *             abcc
 *             abcd
 *             abce
 *             abcf
 *             ....
 *             ....
 *             abcda
 *             abcdb
 *
 *             'abcda' has higher alphabetical order than 'abcf' but is being enumerated later
 *
 * 
 * @Param:     candidate_string
 * @Param:     position ( position of the character to be enumerated )
 * @Param:     length ( length of the resulting candidate string )
 * @Param:     upperbound ( upperbound to the enumeration )
 */
template<class T>
void dsa::recommendation<T>::enumerate_single_character_with_upperbound( char* candidate_string, int position, int length, char upperbound)
{
	for( int i = 0; candidates_characters[i] != upperbound ; ++i )
	{
		candidate_string[ position ] = candidates_characters[i];
		PROBE( candidate_string, length )
	}
}

/** 
 * @Function:  enumerate all possible characters of a single slot
 *             and probe them one by one into the hashmap
 * 
 * @Param:     candidate_string
 * @Param:     position ( position of the character to be enumerated )
 * @Param:     length ( length of the resulting candidate string )
 * @Param:     lowerbound
 */
template<class T>
void dsa::recommendation<T>::enumerate_single_character_with_lowerbound( char* candidate_string, int position, int length, char lowerbound)
{
	for( int i = character_to_index(lowerbound) ; i < CANDIDATES_SIZE ; ++i )
	{
		candidate_string[ position ] = candidates_characters[i];
		PROBE( candidate_string, length )
	}
}

/** 
 * @Function:  enumerate all possible characters of a pair of slots
 *             and probe them one by one into the hashmap
 * 
 * @Param:     length
 * @Param:     first ( first slot to be enumerated )
 * @Param:     second ( second slot to be enumerated )
 */
template<class T>
void dsa::recommendation<T>::enumerate_double_character( char* candidate_string, int length, int first, int second )
{
	// TODO 
	// WARNING: this function will not work!
	// Does that take alphabetic order into account!
	for( int i = 0; i < CANDIDATES_SIZE ; ++i )
	{
		candidate_string[ first ] = candidates_characters[i];
		for( int j = 0; i < CANDIDATES_SIZE ; ++j )
		{
			candidate_string[ second ] = candidates_characters[j];
			PROBE( candidate_string, length )
		}			
	}
}

template<class T>
void dsa::recommendation<T>::recommend(const char* original_text)
{

	std::vector<char*> recommendations;
	int  text_length = std::strlen( original_text );
	auto candidate_string = new char[ text_length+1 ];
	std::strcpy( candidate_string, original_text );


/*
 * 
 *
 *	□ : Slot whose character is the same as original text
 *
 *  ✖ : Slot whose character is different from the original text
 *
 *	○ : Empty slot
 *
 *
*/
//
//	Hardcoded spagetti
//
//	Score 1: □  □  □  ○  |
//
/*----------------------------------------------------*/
	candidate_string[ text_length-1 ] = '\0';
	PROBE( candidate_string, text_length-1 )
	RECOVER_STRING( candidate_string , text_length-1 )
/*----------------------------------------------------*/

//
//	Hardcoded spagetti
//	Upper bound ( the character of the original text is chosen here ) on candidate character to preserve alphabetic order
//
//	Score 1: □  □  □  ✖  |
//
/*----------------------------------------------------*/
	enumerate_single_character_with_upperbound( candidate_string, text_length-1, text_length, original_text[ text_length-1 ] );
	CHECK_RETURN()
	RECOVER_STRING( candidate_string , text_length-1 )
/*----------------------------------------------------*/

//
//	Hardcoded spagetti
//
//	Score 1: □  □  □  □  | ✖ 
//
/*----------------------------------------------------*/
	enumerate_single_character_with_upperbound( candidate_string, text_length+1, text_length );
	CHECK_RETURN()
	RECOVER_STRING( candidate_string , text_length )
/*----------------------------------------------------*/

//
//	Hardcoded spagetti
//	Lower bound on candidate character to preserve alphabetic order
//
//	Score 1: □  □  □  ✖  |
//
/*----------------------------------------------------*/
	enumerate_single_character_with_lowerbound( candidate_string, text_length-1, text_length, original_text[ text_length-1 ] );
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
	enumerate_single_character_with_upperbound( candidate_string, text_length-2, text_length-1, original_text[text_length-2] );
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
	enumerate_single_character_with_upperbound( candidate_string, text_length-2, text_length, original_text[text_length-2] );
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


// Print the recommendations
template<class T>
void dsa::recommendation<T>::print_recommendation()
{
	for( auto recommendation:recommendations )
	{
		std::cout << recommendation << " ";
	}
}

// Clean the recommendation list
template<class T>
void dsa::recommendation<T>::flush()
{
	recommendations.clear();
}
