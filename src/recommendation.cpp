#include "recommendation.hpp"

#define PROBE( candidate ) 									\
	if(container.find(candidate) == container.end()) 		\
	{                                           			\
		recommendations.push_back( candidate );				\
	}														\
	std::cout << " --> " << candidate << std::endl;

/* Front identifier for candidate_characters */
#define FRONT candidate_characters.cbegin()
/* End   identifier for candidate_characters */
#define END   candidate_characters.cend()
/* Boundary for candidate_characters */
#define BOUNDARY(offset) get_iterator(*(candidate.rbegin()+offset))+1
/* Get iterator for the last character of the current candidate */
#define BACK (get_iterator(candidate.back())+1)

#ifdef DEBUG
const std::string candidate_characters("01234");
#else
const std::string candidate_characters("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
#endif


/**
 * @Function: map character to its corresponding index in static variable 'candidate_characters'
 *
 * @Param: ch
 *
 * @Return: index
 */
std::string::const_iterator dsa::recommendation::get_iterator(char ch)
{
	if (ch < 'A')
		// ch is digit: ch - '0'
	{
		return candidate_characters.cbegin() + ch - '0';
	}
	if (ch < 'a')
		// ch is uppercase alphabet: ch - 'A' + 10 ( ch - 65 + 10 )
	{
		return candidate_characters.cbegin() + ch - 55;
	}

	// ch is lowercase alphabet: ch - 'a' + 10 + 26 ( ch - 97 + 10 + 26 )
	return candidate_characters.cbegin() + ch - 61;
}


/**
 * @Function:  enumerate all possible characters of a single slot
 *             and PROBE them one by one into the hashmap.
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

bool dsa::recommendation::enumerate_single_character(std::vector<std::string>& recommendations, std::string::reverse_iterator position, bound_t bounds)
{
	char original_character = *position;
	for (auto it = bounds.first ; it != bounds.second ; ++it)
	{
		*position = *it;
		PROBE(candidate);
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
 *             and PROBE them one by one into the hashmap
 *
 * @Param:     candidate
 * @Param:     length
 * @Param:     positions
 * @Param:     bounds_pair
 *
 * @Return:
 */
bool dsa::recommendation::enumerate_double_character(
    std::vector<std::string>& recommendations,
    std::pair<std::string::reverse_iterator, std::string::reverse_iterator> positions,
    std::pair<bound_t, bound_t>&& bounds_pair)
{
	char original_character = *(positions.first);
	for (auto it = bounds_pair.first.first ; it != bounds_pair.first.second ; ++it)
	{
		*(positions.first) = *it;
		if (!enumerate_single_character(recommendations, positions.second,  bounds_pair.second))
		{
			return false;
		}
	}
	*(positions.first) = original_character;

	return true;
}

bool dsa::recommendation::enumerate_triple_character(
    std::vector<std::string>& recommendations,
    std::vector<std::string::reverse_iterator>&& positions,
    std::vector<bound_t>&& bounds)
{
	char original_character = *(positions[0]);
	for (auto it = bounds[0].first ; it != bounds[0].second ; ++it)
	{
		*(positions[0]) = *it;
		if (!enumerate_single_character(recommendations, positions[1],  bounds[1]))
		{
			return false;
		}
		if (!enumerate_single_character(recommendations, positions[2],  bounds[2]))
		{
			return false;
		}
	}
	*(positions[0]) = original_character;

	return true;
}

void dsa::recommendation::recommend(std::vector<std::string>& recommendations, const std::string & original_text)
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
	if (original_text.size() > 1)
	{
		candidate.resize(original_text.size() - 1);
		PROBE(candidate);
		candidate.resize(original_text.size());
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
	if (original_text.size() > 0)
	{
		if (!enumerate_single_character(recommendations, candidate.rbegin(), std::make_pair(FRONT, BACK)))
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
	candidate.resize(original_text.size() + 1);
	if (!enumerate_single_character(recommendations, candidate.rbegin() , std::make_pair(FRONT, END)))
	{
		return;
	}
	candidate.resize(original_text.size());
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
	if (original_text.size() > 0)
	{
		if (!enumerate_single_character(recommendations, candidate.rbegin() , std::make_pair(BACK, END)))
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
	if (original_text.size() > 1)
	{
		candidate.resize(original_text.size() - 1);
		if (!enumerate_single_character(recommendations, candidate.rbegin(), std::make_pair(FRONT, END)))
		{
			return;
		}
		candidate.resize(original_text.size());
	}
	/*----------------------------------------------------*/

//
//	Score 2: □  □  ✖  □  |
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 2: □  □  ✖  □  |\n";
#endif
	if (original_text.size() > 1)
	{
		if (!enumerate_single_character(recommendations, candidate.rbegin() + 1, std::make_pair(FRONT, BOUNDARY(1))))
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
	if (original_text.size() > 0)
	{
		candidate.resize(original_text.size() + 1);
		if (!enumerate_double_character(recommendations, std::make_pair(candidate.rbegin() + 1, candidate.rbegin()),
		                                std::make_pair(
		                                    std::make_pair(FRONT, BOUNDARY(1)),
		                                    std::make_pair(FRONT, END)
		                                )))
		{
			return;
		}
		if (!enumerate_double_character(recommendations, std::make_pair(candidate.rbegin() + 1, candidate.rbegin()),
		                                std::make_pair(
		                                    std::make_pair(BOUNDARY(1), END),
		                                    std::make_pair(FRONT, END)
		                                )))
		{
			return;
		}
		candidate.resize(original_text.size());
	}
	/*----------------------------------------------------*/

//
//	Score 2: □  □  ✖  ○  |
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 2: □  □  ✖  ○  | \n";
#endif
	if (original_text.size() > 1)
	{
		candidate.resize(original_text.size() - 1);
		if (!enumerate_single_character(recommendations, candidate.rbegin(), std::make_pair(BACK, END)))
		{
			return;
		}
		candidate.resize(original_text.size());
	}
//
//	Score 2: □  □  ✖  □  |
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 2: □  □  ✖  □  |\n";
#endif
	if (original_text.size() > 1)
	{
		if (!enumerate_single_character(recommendations, candidate.rbegin() + 1, std::make_pair(BOUNDARY(1), END)))
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
	if (original_text.size() > 2)
	{
		if (!enumerate_single_character(recommendations, candidate.rbegin() + 2, std::make_pair(FRONT, BOUNDARY(2))))
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
	if (original_text.size() > 2)
	{
		candidate.resize(original_text.size() - 2);
		PROBE(candidate);
		candidate.resize(original_text.size());
	}

//
//	Score 3: □  □  ✖  ✖  |
//	Score 3: □  □  ✖  □   | ✖
//
	/*----------------------------------------------------*/

#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 3: □  □  ✖  ✖   + Score 3: □  □  ✖  □   | ✖  \n";
#endif
	if (original_text.size() > 1)
	{
		candidate.resize(original_text.size() + 1);
		if (!enumerate_triple_character(recommendations,
	{ candidate.rbegin() + 2, candidate.rbegin() + 1, candidate.rbegin()},
		{
			std::make_pair(FRONT, BOUNDARY(2)) ,
			std::make_pair(FRONT, BOUNDARY(1)) ,
			std::make_pair(FRONT, END)
		}))
		{
			return;
		}
		candidate.resize(original_text.size());
	}

//
//	Score 3: □  □  □  □   | ✖  ✖
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 3: □  □  □  □   | ✖  ✖  \n";
#endif
	candidate.resize(original_text.size() + 2);
	if (!enumerate_double_character(
	            recommendations,
	            std::make_pair(candidate.rbegin() + 1, candidate.rbegin()),
	            std::make_pair(
	                std::make_pair(FRONT, END),
	                std::make_pair(FRONT, END)
	            )))
	{
		return;
	}
	candidate.resize(original_text.size());

//
//	Score 3: □  ✖  □  □  |
//
	/*----------------------------------------------------*/
#ifdef DEBUG_RECOMMENDATION
	std::cout << "Score 3: □  ✖  □  □  | \n";
#endif
	if (original_text.size() > 2)
	{
		if (!enumerate_single_character(recommendations, candidate.rbegin() + 2, std::make_pair(BOUNDARY(2), END)))
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
	if (original_text.size() > 1)
	{
<<<<<<< HEAD
		candidate.resize( original_text.size()+2 );
		if (!enumerate_triple_character(
			recommendations,
			{ candidate.rbegin()+2, candidate.rbegin()+1, candidate.rbegin()},
			{
				std::make_pair( BOUNDARY(2), END),
				std::make_pair( FRONT, END),
				std::make_pair( BOUNDARY(1), END),
			}))
		{
			return;
		}
		candidate.resize( original_text.size() );
	}
}


