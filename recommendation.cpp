#include "recommendation.hpp"

// Extra space reserved for candidate strings
#define EXTRA_SPACE 4

// Candidate has been confirmed and can be added into recommendation lists.
#define ADD_RECOMMENDATION( candidate_string, length ) \
	recommendations.push_back( std::string( candidate_string ) ); 

//#define ADD_RECOMMENDATION( candidate_string, length ) \
	recommendations.push_back( new char[ length+1 ] ); \
	strcpy( recommendations.back() , candidate_string ); 						

// Append '\0' to some position so that candidate_string ends there
#define APPEND_END_CHARACTER( candidate_string, position ) \
		candidate_string[ position ] = '\0';

// Recover the candidate_string to original text in convenience of later enumeration
#define RECOVER_STRING( candidate_string, position ) \
	candidate_string[ position ] = this->original_text[ position ];

// Check if we are going too far
#define CHECK_LENGTH( text_length, length ) \
	if(  text_length < length )return;

// Check if we have reached the required number of recommendations
#define CHECK_RETURN() \
	if( recommendations.size() > RECOMMENDATION_NUMBER )return; 

// Check if candidate_string exists in our target container
#define PROBE( candidate_string, length )             			\
	if(container.find(std::string(candidate_string)) == container.end())			\
	{                                           				\
		ADD_RECOMMENDATION( candidate_string, length ) 			\
		std::cout << " --> "<< candidate_string << std::endl;  \
	}

/* Front identifier for candidates_characters */
#define FRONT (char)0
/* End   identifier for candidates_characters */
#define END   '\0'

#define CANDIDATE_NUMBER 9
// const char dsa::recommendation::candidates_characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
 const char dsa::recommendation::candidates_characters[] = "012ABCabc";
/** 
 * @Function: map character to its corresponding index in static variable 'candidates_characters' 
 * 
 * @Param: ch	
 * 
 * @Return: index
 */
int dsa::recommendation::character_to_index( char ch )
{
	if( ch < 'A' )
		// ch is digit: ch - '0'
		return ch - '0';
	if( ch < 'a' )
		// ch is uppercase alphabet
		return ch - 'A' + 3;
	
	// ch is lowercase alphabet
	return ch - 'a' + 3 + 3;
}
// int dsa::recommendation::character_to_index( char ch )
// {
	// if( ch < 'A' )
		// // ch is digit: ch - '0'
		// return ch - '0';
	// if( ch < 'a' )
		// // ch is uppercase alphabet: ch - 'A' + 10 ( ch - 65 + 10 )
		// return ch - 55;
	
	// // ch is lowercase alphabet: ch - 'a' + 10 + 26 ( ch - 97 + 10 + 26 )
	// return ch - 61;
// }

/** 
 * @Function:  enumerate all possible characters of a single slot
 *             and probe them one by one into the hashmap.
 *             Note that there's an bounds to the enumeration. By doing so, we can preserve alphabetical order 
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

bool dsa::recommendation::enumerate_single_character( std::vector<std::string>& recommendations, int position, int length, bound_t bounds )
{
	if( position < 0 )
		return true;
	for( int i = bounds.first ? character_to_index(bounds.first)+1 : 0 ; candidates_characters[i] != bounds.second ; ++i )
	{
		candidate_string[ position ] = candidates_characters[i];
		PROBE( candidate_string, length )
		if( recommendations.size() > RECOMMENDATION_NUMBER )
			return false; 
	}

	RECOVER_STRING( candidate_string, position )

	return true;
}

/** 
 * @Function:  enumerate all possible characters of a pair of slots
 *             and probe them one by one into the hashmap
 * 
 * @Param:     candidate_string
 * @Param:     length
 * @Param:     positions
 * @Param:     bounds_pair
 * 
 * @Return:    
 */
bool dsa::recommendation::enumerate_double_character( std::vector<std::string>& recommendations, 
														 int length, 
														 std::pair<int,int> positions, 
														 std::pair<bound_t,bound_t>&& bounds_pair )
{
	if( positions.first < 0 || positions.second < 0 )
		return true;

	for( int i = character_to_index(bounds_pair.first.first)+1; candidates_characters[i] != bounds_pair.first.second ; ++i )
	{
		candidate_string[ positions.first ] = candidates_characters[i];

		if(!enumerate_single_character( recommendations , length, positions.second, bounds_pair.second ))
			return false;
	}

	RECOVER_STRING( candidate_string, positions.first )
	RECOVER_STRING( candidate_string, positions.second )

	return true;
}

void dsa::recommendation::recommend(std::vector<std::string>& recommendations, const char* _original_text)
{
	int  text_length = std::strlen( _original_text );

	this->original_text = _original_text;
	this->candidate_string = new char[ text_length + EXTRA_SPACE + 1 ];
	std::strcpy( candidate_string, _original_text );

/*
 * 
 *
 *	□ : Slot whose character is the same as original text
 *
 *  ✖ : Slot whose character is different from the original text
 *
 *	○ : Empty slot
 *
 **/

//
//	Score 1: □  □  □  ○  |
//
/*----------------------------------------------------*/
	if( text_length > 1 )
	{
		APPEND_END_CHARACTER( candidate_string, text_length-1 )
		PROBE( candidate_string, text_length-1 )
		RECOVER_STRING( candidate_string , text_length-1 )
	}
/*----------------------------------------------------*/

//
//	Upper bound ( the character of the original text is chosen here ) on candidate character to preserve alphabetic order
//
//	Score 1: □  □  □  ✖  |
//
/*----------------------------------------------------*/
	if( text_length > 1 )
	{
		if(!enumerate_single_character( recommendations , text_length-1 , text_length, std::make_pair( FRONT,original_text[ text_length-1 ]) ))
			return;
	}
/*----------------------------------------------------*/

//
//	Score 1: □  □  □  □  | ✖ 
//
/*----------------------------------------------------*/
	std::cout<<" Score 1:  □  □  □  □  | ✖  \n";
	APPEND_END_CHARACTER( candidate_string, text_length+1 )
	if(!enumerate_single_character( recommendations , text_length , text_length , std::make_pair(FRONT,END)  ))
		return;
/*----------------------------------------------------*/

//
//	Lower bound on candidate character to preserve alphabetic order
//
//	Score 1: □  □  □  ✖  |
//
/*----------------------------------------------------*/

	std::cout<<" Score 1: □  □  □  ✖  \n";
	if( text_length > 0 )
	{
		if(!enumerate_single_character( recommendations , text_length-1 , text_length , std::make_pair(original_text[ text_length-1 ],END) ))
			return;
	}
/*----------------------------------------------------*/

//
//	Score 2: □  □  ✖  ○  | 
//
/*----------------------------------------------------*/
	std::cout<<" Score 2: □  □  ✖  ○  | \n";
	if( text_length > 1 )
	{
		APPEND_END_CHARACTER( candidate_string, text_length-1 )
		if(!enumerate_single_character( recommendations , text_length-2 , text_length-1, std::make_pair(FRONT, original_text[text_length-2]) ))
			return;
	}
/*----------------------------------------------------*/

//
//	Score 2: □  □  ✖  □  |
//
/*----------------------------------------------------*/
	if( text_length > 1 )
	{
		if(!enumerate_single_character( recommendations , text_length-2 , text_length, std::make_pair(FRONT,original_text[text_length-2]) ))
			return;
	}
/*----------------------------------------------------*/


//
//	Score 2: □  □  □  ✖  | ✖ 
//
/*----------------------------------------------------*/
	if( text_length > 0 )
	{
		APPEND_END_CHARACTER( candidate_string, text_length+1 ) 
		if(!enumerate_double_character( recommendations , text_length+1, std::make_pair(text_length-1, text_length+1), 
					std::make_pair(
							std::make_pair( FRONT, original_text[text_length-1] ),
							std::make_pair( FRONT,END )
						)))
			return;
		if(!enumerate_double_character( recommendations , text_length+1, std::make_pair(text_length-1, text_length+1), 
					std::make_pair(
							std::make_pair(original_text[text_length-1],END ),
							std::make_pair( FRONT,END )
						)))
			return;
	}
	//RECOVER_STRING( candidate_string , text_length ) /* recover '\0' */
/*----------------------------------------------------*/

//
//	Score 2: □  □  ✖  ○  | 
//
/*----------------------------------------------------*/
	if( text_length > 1 )
	{
		APPEND_END_CHARACTER( candidate_string, text_length-1 )
		if(!enumerate_single_character( recommendations , text_length-2 , text_length-1, std::make_pair(original_text[text_length-2],END ) ))
			return;
	}
//
//	Score 2: □  □  ✖  □  |
//
/*----------------------------------------------------*/
	if( text_length > 1 )
	{
		if(!enumerate_single_character( recommendations , text_length-2 , text_length, std::make_pair(original_text[text_length-2],END) ))
			return;
	}
/*----------------------------------------------------*/

//
//	Score 3: □  ✖  □  □  | 
//
/*----------------------------------------------------*/
	if( text_length > 2 )
	{
		if(!enumerate_single_character( recommendations , text_length-3, text_length, std::make_pair(0,original_text[text_length-3]) ))
			return;
	}


//
//	Score 3: □  □  ○  ○  |
//
/*----------------------------------------------------*/
	if( text_length > 3 )
	{
		APPEND_END_CHARACTER( candidate_string, text_length-2 );
		PROBE( candidate_string, text_length-2 )
		RECOVER_STRING( candidate_string , text_length-2 )
	}

//
//	Score 3: □  □  ✖  ✖  |
//
/*----------------------------------------------------*/
	if( text_length > 1 )
	{
		if(!enumerate_double_character( recommendations , text_length, std::make_pair(text_length-2, text_length-1), 
					std::make_pair(
							std::make_pair(FRONT, original_text[text_length-2] ),
							std::make_pair(FRONT, original_text[text_length-1] )
						)))
			return;
	}
	
//
//	Score 3: □  □  ✖  □   | ✖
//
/*----------------------------------------------------*/
	if( text_length > 1 )
	{
		APPEND_END_CHARACTER( candidate_string, text_length+1 );
		if(!enumerate_double_character( recommendations , text_length+1, std::make_pair(text_length-2, text_length), 
					std::make_pair(
							std::make_pair(FRONT, original_text[text_length-2] ),
							std::make_pair(FRONT, END )
						)))
			return;
	}
//
//	Score 3: □  □  □  □   | ✖  ✖ 
//
/*----------------------------------------------------*/
	APPEND_END_CHARACTER( candidate_string, text_length+1 );
	if(!enumerate_double_character( recommendations , text_length+2, std::make_pair(text_length, text_length+1), 
				std::make_pair(
						std::make_pair(FRONT, END ),
						std::make_pair(FRONT, END )
					)))
		return;
	
//
//	Score 3: □  ✖  □  □  | 
//
/*----------------------------------------------------*/
	if( text_length > 2 )
	{
		if(!enumerate_single_character( recommendations , text_length-3, text_length, std::make_pair(original_text[text_length-3],END) ))
			return;
	}



	
//
//	Score 3: □  □  ✖  □   | ✖
//
/*----------------------------------------------------*/
	if( text_length > 1 )
	{
		APPEND_END_CHARACTER( candidate_string, text_length+1 );
		if(!enumerate_double_character( recommendations , text_length+1, std::make_pair(text_length-2, text_length), 
					std::make_pair(
							std::make_pair( original_text[text_length-2], END ),
							std::make_pair(FRONT, END )
						)))
			return;
	}

//
//	Score 3: □  □  ✖  ✖  |
//
/*----------------------------------------------------*/
	if( text_length > 1 )
	{
		if(!enumerate_double_character( recommendations , text_length, std::make_pair(text_length-2, text_length-1), 
					std::make_pair(
							std::make_pair( original_text[text_length-2], END ),
							std::make_pair( original_text[text_length-1], END )
						)))
			return;
	}

}


