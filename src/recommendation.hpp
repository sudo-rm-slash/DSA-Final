#ifndef __RECOMMENDATION_HPP__
#define __RECOMMENDATION_HPP__

#include <unordered_map>	// std::unordered_map
#include <string>			// std::string
#include <tuple>			// std::tuple
#include <array> 			// std::array
#include <vector> 			// std::vector

#define TARGET_AMOUNT 10

#ifdef DEBUG_RECOMMENDATION

#define SIZE_OF_CANDIDATE_CHARACTER 6

#else

#define SIZE_OF_CANDIDATE_CHARACTER 62

#endif


namespace dsa
{
	class recommendation
	{
	private:

	#ifdef DEBUG_RECOMMENDATION
		const char candidate_chars[SIZE_OF_CANDIDATE_CHARACTER+1] = "012345";
	#else
		const char candidate_chars[SIZE_OF_CANDIDATE_CHARACTER+1] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	#endif

		std::string candidate_str;		// Buffer storage for candidate string during the enumeration.

		struct boundary
		{
			char upper;
			char lower;
		};
		std::array<std::string::reverse_iterator, 3> positions;	// Local storage for the positions.
		std::array<boundary, 3> boundaries;				// Local storage for the boundaries.


	public:
		/**
		 * Recommend a series of candidate strings that aren't occupied.
		 * @arg hashtable The container that stores existed accounts.
		 * @arg original The original string to act as the template.
		 * @arg results The container to store the results.
		 */
		void recommend(const std::unordered_map<std::string, unsigned int>& hashtable,
		               const std::string& original_str,
		               std::vector<std::string>& results);


	private:
		/**
		 * Enumerate all possible characters of a single slot and probe them one by one into the hashmap.
		 * Note that there's an bounds to the enumeration. By doing so, we can preserve alphabetical order.
		 * For an example, take 'abcd' as original text:
		 *      ....
		 *      ....
		 *      abcc
		 *      abcd
		 *      abce
		 *      abcf
		 *      ....
		 *      ....
		 *      abcda
		 *      abcdb
		 *
		 *      'abcda' has higher alphabetical order than 'abcf' but is being enumerated later
		 * @arg hashtable
		 * @arg results
		 * @arg level ( default to level 0 )
		 * @return Whether the requirement is satisfied.
		 */
		bool enumerate_single_character(const std::unordered_map<std::string, unsigned int>& hashtable, std::vector<std::string>& results, int level = 0);

		/**
		 * @Function:  Enumerate all possible pairs of character
		 *
		 * @Param:     hashtable
		 * @Param:     results
		 *
		 * @Return:    Whether the requirement is satisfied.
		 */
		bool enumerate_double_character(const std::unordered_map<std::string, unsigned int>& hashtable, std::vector<std::string>& results);

		/**
		 * @Function:  Enumerate all possible triples in alphabetical order
		 *
		 * @Param:     hashtable
		 * @Param:     results
		 *
		 * @Return:    Whether the requirement is satisfied.
		 */
		bool enumerate_triple_character(const std::unordered_map<std::string, unsigned int>& hashtable, std::vector<std::string>& results);

		/**
		 * @Function:  Doggling the last character of a candidate string
		 *
		 * @Param:     hashtable
		 * @Param:     results
		 * @Param:     toggle_character
		 *
		 * @Return:
		 */
		bool enumerate_toggle_single_character(const std::unordered_map<std::string, unsigned int>& hashtable, std::vector<std::string>& results, char toggle_character);

		/**
		 * Map character to its corresponding index in static variable 'candidate_chars'.
		 * @arg ch
		 * @return: index
		 */
		char char_to_candidate(const char c);
	};
}

#endif
