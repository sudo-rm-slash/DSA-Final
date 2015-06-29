#include "recommendation.hpp"

// Extra space reserved for candidate strings
#define EXTRA_SPACE 4

// Recover the candidate to original text in convenience of later enumeration
#define RECOVER_STRING( candidate, position ) \
	candidate[ position ] = this->original_text[ position ];

/* Front identifier for candidate_characters */
#define FRONT (char)0
/* End   identifier for candidate_characters */
#define END   '\0'

const std::string candidate_characters("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

void dsa::recommendation::probe( std::string& candidate )
{
	if(container.find(candidate) == container.end())						
	{                                           							
		recommendations.push_back( candidate );
	}
#ifdef DEBUG_RECOMMENDATION
	std::cout << " --> " << candidate << std::endl;
#endif
}

/**
 * @Function: map character to its corresponding index in static variable 'candidate_characters'
 *
 * @Param: ch
 *
 * @Return: index
 */
std::string::const_iterator dsa::recommendation::character_to_index( char ch )
{
	if( ch < 'A' )
		// ch is digit: ch - '0'
		return candidate_characters.cbegin() + ch - '0';
	if( ch < 'a' )
		// ch is uppercase alphabet: ch - 'A' + 10 ( ch - 65 + 10 )
		return candidate_characters.cbegin() + ch - 55;

	// ch is lowercase alphabet: ch - 'a' + 10 + 26 ( ch - 97 + 10 + 26 )
	return candidate_characters.cbegin() + ch - 61;
}


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
 * @Param:     candidate
 * @Param:     position ( position of the character to be enumerated )
 * @Param:     length ( length of the resulting candidate string )
 * @Param:     upperbound ( upperbound to the enumeration )
 */

bool dsa::recommendation::enumerate_single_character( std::string::reverse_iterator position, bound_t bounds)
{
	char original_character = *position;
	for (auto it = std::get<1>(bounds) ; it != std::get<2>(bounds) ; ++it)
	{
		*position = *it;
		probe( candidate );
		if (recommendations.size() >= RECOMMENDATION_NUMBER)
		{
			return false;
		}
	}

	*position = original_character;

	return true;
}

/**
 * @Function:  enumerate all possible characters of a pair of slots
 *             and probe them one by one into the hashmap
 *
 * @Param:     candidate
 * @Param:     length
 * @Param:     positions
 * @Param:     bounds_pair
 *
 * @Return:
 */
bool dsa::recommendation::enumerate_double_character(
        std::pair<int, int> positions,
        std::pair<bound_t, bound_t>&& bounds_pair)
{

	*position = original_character;
	for (int i = bounds_pair.first.first ? character_to_index(bounds_pair.first.first) + 1 : 0; candidate_characters[i] != bounds_pair.first.second ; ++i)
	{
		candidate[ positions.first ] = candidate_characters[i];

		if (!enumerate_single_character(positions.second,  bounds_pair.second))
		{
			return false;
		}
	}

	RECOVER_STRING(candidate, positions.first)

	return true;
}

bool dsa::recommendation::enumerate_triple_character(
        std::vector<int>&& positions,
        std::vector<bound_t>&& bounds)
{
	for (int i = bounds[0].first ? character_to_index(bounds[0].first) + 1 : 0; candidate_characters[i] != bounds[0].second ; ++i)
	{
		candidate[ positions[0] ] = candidate_characters[i];

		if (!enumerate_single_character(positions[1],  bounds[1]))
		{
			return false;
		}
		if (!enumerate_single_character(positions[2],  bounds[2]))
		{
			return false;
		}
	}

	RECOVER_STRING(candidate, positions[0])

	return true;
}

std::vector<std::string>& dsa::recommendation::recommend( std::string& original_text )
{
	this->candidate = original_text;

	/*
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
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 1: □  □  □  ○  | \n";
#endif
	if (text_length > 1)
	{
		candidate.resize( original_text.size()-1 );
		probe( candidate );
		candidate.resize( original_text.size() );
	}
	/*----------------------------------------------------*/

//
//	Upper bound ( the character of the original text is chosen here ) on candidate character to preserve alphabetic order
//
//	Score 1: □  □  □  ✖  |
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 1: □  □  □  ✖  | \n";
#endif
	if (text_length > 0)
	{
		if (!enumerate_single_character(candidate.rbegin(), std::make_tuple(candidate_characters.cbegin(), original_text[ text_length - 1 ])))
		{
			return;
		}
	}
	/*----------------------------------------------------*/

//
//	Score 1: □  □  □  □  | ✖
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 1: □  □  □  □  | ✖  \n";
#endif
	candidate.resize( original_text.size()+1 );
	if (!enumerate_single_character( candidate.rbegin() , std::make_pair(FRONT, END)))
	{
		return;
	}
	candidate.resize( original_text.size() );
	/*----------------------------------------------------*/

//
//	Lower bound on candidate character to preserve alphabetic order
//
//	Score 1: □  □  □  ✖  |
//
	/*----------------------------------------------------*/

#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 1: □  □  □  ✖  \n";
#endif
	if (text_length > 0)
	{
		if (!enumerate_single_character(candidate.rbegin() , std::make_pair(original_text[ text_length - 1 ], END)))
		{
			return;
		}
	}
	/*----------------------------------------------------*/

//
//	Score 2: □  □  ✖  ○  |
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 2: □  □  ✖  ○  | \n";
#endif
	if (text_length > 1)
	{
		candidate.resize( original_text.size()-1 );
		if (!enumerate_single_character(candidate.rbegin(), std::make_pair(FRONT, original_text[text_length - 2])))
		{
			return;
		}
		candidate.resize( original_text.size() );
	}
	/*----------------------------------------------------*/

//
//	Score 2: □  □  ✖  □  |
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 2: □  □  ✖  □  |\n";
#endif
	if (text_length > 1)
	{
		if (!enumerate_single_character(candidate.rbegin()+1, std::make_pair(FRONT, original_text[text_length - 2])))
		{
			return;
		}
	}
	/*----------------------------------------------------*/


//
//	Score 2: □  □  □  ✖  | ✖
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 2: □  □  □  ✖  | ✖  \n";
#endif
	if (text_length > 0)
	{
		candidate.resize( original_text.size()+1 );
		if (!enumerate_double_character(recommendations, std::make_pair( candidate.rbegin()+1, candidate.rbegin() ),
		                                std::make_pair(
		                                    std::make_pair(FRONT, original_text[text_length - 1]),
		                                    std::make_pair(FRONT, END)
		                                )))
		{
			return;
		}
		if (!enumerate_double_character(recommendations, std::make_pair( candidate.rbegin()+1, candidate.rbegin() ),
		                                std::make_pair(
		                                    std::make_pair(original_text[text_length - 1], END),
		                                    std::make_pair(FRONT, END)
		                                )))
		{
			return;
		}
		candidate.resize( original_text.size() );
	}
	/*----------------------------------------------------*/

//
//	Score 2: □  □  ✖  ○  |
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 2: □  □  ✖  ○  | \n";
#endif
	if (text_length > 1)
	{
		candidate.resize( original_text.size()-1 );
		if (!enumerate_single_character(candidate.rbegin(), std::make_pair(original_text[text_length - 2], END)))
		{
			return;
		}
		candidate.resize( original_text.size() );
	}
//
//	Score 2: □  □  ✖  □  |
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 2: □  □  ✖  □  |\n";
#endif
	if (text_length > 1)
	{
		if (!enumerate_single_character(candidate.rbegin()+1, std::make_pair(original_text[text_length - 2], END)))
		{
			return;
		}
	}
	/*----------------------------------------------------*/

//
//	Score 3: □  ✖  □  □  |
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 3: □  ✖  □  □  | \n";
#endif
	if (text_length > 2)
	{
		if (!enumerate_single_character(candidate.rbegin()+2, std::make_pair(0, original_text[text_length - 3])))
		{
			return;
		}
	}


//
//	Score 3: □  □  ○  ○  |
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 3: □  □  ○  ○  |\n";
#endif
	if (text_length > 2)
	{
		candidate.resize( original_text.size() - 2 );
		probe( candidate );
		candidate.resize( original_text.size() );
	}

//
//	Score 3: □  □  ✖  ✖  |
//	Score 3: □  □  ✖  □   | ✖
//
	/*----------------------------------------------------*/

#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 3: □  □  ✖  ✖   + Score 3: □  □  ✖  □   | ✖  \n";
#endif
	if (text_length > 1)
	{
		RESIZE(candidate, text_length + 1);
		if (!enumerate_triple_character(recommendations,
	{text_length - 2, text_length - 1, text_length},
	{
		std::make_pair(FRONT, original_text[text_length - 2]),
			std::make_pair(FRONT, original_text[text_length - 1]),
			std::make_pair(FRONT, END)
		}))
		return;
		RECOVER_STRING(candidate, text_length + 1);
	}

//
//	Score 3: □  □  □  □   | ✖  ✖
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 3: □  □  □  □   | ✖  ✖  \n";
#endif
	RESIZE(candidate, text_length + 2);
	if (!enumerate_double_character(std::make_pair(text_length, text_length + 1),
	                                std::make_pair(
	                                    std::make_pair(FRONT, END),
	                                    std::make_pair(FRONT, END)
	                                )))
	{
		return;
	}

//
//	Score 3: □  ✖  □  □  |
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 3: □  ✖  □  □  | \n";
#endif
	if (text_length > 2)
	{
		if (!enumerate_single_character(text_length - 3, std::make_pair(original_text[text_length - 3], END)))
		{
			return;
		}
	}


//
//	Score 3: □  □  ✖  □   | ✖  +  Score 3:  □  □  ✖  ✖  |
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 3: □  □  ✖  ✖   + Score 3: □  □  ✖  □   | ✖  \n";
#endif
	if (text_length > 1)
	{
		RESIZE(candidate, text_length + 1);
		if (!enumerate_triple_character(recommendations,
	{text_length - 2, text_length - 1, text_length},
	{
		std::make_pair(original_text[text_length - 2], END),
			std::make_pair(FRONT, END),
			std::make_pair(original_text[text_length - 1], END)
		}))
		return;
		RECOVER_STRING(candidate, text_length + 1);
	}

}


