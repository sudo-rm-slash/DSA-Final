#include "recommendation2.hpp"

#ifdef DEBUG

#include <iostream>
#define PRINT_CANDIDATE() std::cout << "--> " << this->candidate_str << std::endl;
#define DEBUG_MESG(mesg) std::cout << mesg << std::endl;

#else

#define PRINT_CANDIDATE()
#define DEBUG_MESG(mesg)

#endif

/**
 * Mnemonics
 *      S -> Slot whose character is the same as original text
 *      D -> Slot whose character is different from the original text
 *      E -> Empty slot
 */
void dsa::recommendation::recommend(const std::unordered_map<std::string, unsigned int>& hashtable, 
									const std::string& original_str, 
									std::vector<std::string>& results)
{
	// Start from the original string.
	this->candidate_str = original_str;


#define NOT_FOUND(S) hashtable.find(S) == std::end(hashtable)
#define SET_BOUNDARY(lvl, L, H) \
			this->boundaries[lvl].lower = L; \
			this->boundaries[lvl].upper = H;
#define SET_POSITOIN(lvl, P) \
			this->positions[lvl] = P;
#define FIRST_CANDIDATE 0
#define LAST_CANDIDATE SIZE_OF_CANDIDATE_CHARACTER
#define BOUNDARY(offset) char_to_candidate(*(original_str.rbegin()+offset))

	/**
	 * Score = 1
	 *      S S S E|
	 */
	DEBUG_MESG( "S S S E|" )

	// Remove the last character.
	this->candidate_str.pop_back();

	// Test for the case.
	if (NOT_FOUND(this->candidate_str))
	{
		results.push_back(this->candidate_str);
		PRINT_CANDIDATE()
	}

	// Restore the last character.
	this->candidate_str.push_back(original_str.back());


	/**
	 * Score = 1
	 *      S S S D|
	 *      Setup upper bound to restrain the candidate character, to preserve the alphabetic order.
	 */
	DEBUG_MESG( "Score = 1: S S S D|" )

	SET_BOUNDARY(0, FIRST_CANDIDATE, char_to_candidate(original_str.back()))
	SET_POSITOIN(0, this->candidate_str.rbegin())

	// Enumerate the lower bounded portion.
	if (enumerate_single_character(hashtable, results))
	{
		return;
	}


	/**
	 * Score = 1
	 *      S S S S|D
	 */

	DEBUG_MESG( "Score = 1: S S S S|D" )

	// Push back a dummy character to extend the length of the string.
	this->candidate_str.push_back('0');

	// Enumerate the entire character map.
	SET_BOUNDARY(0, FIRST_CANDIDATE, LAST_CANDIDATE)
	SET_POSITOIN(0, this->candidate_str.rbegin())

	// Enumerate the lower bounded portion.
	if (enumerate_single_character(hashtable, results))
	{
		return;
	}

	this->candidate_str.pop_back();

	/**
	 * Score = 1
	 *      S S S D|
	 *      Setup lower bound to restrain the candidate character, to preserve the alphabetic order.
	 */
	DEBUG_MESG( "Score = 1: S S S D|" )

	SET_BOUNDARY(0, char_to_candidate(original_str.back())+1, LAST_CANDIDATE)
	SET_POSITOIN(0, this->candidate_str.rbegin());

	// Enumerate the lower bounded portion.
	if (enumerate_single_character(hashtable, results))
	{
		return;
	}

	/**
	 * Score = 2
	 *      S S D E|
	 */

	DEBUG_MESG( "Score = 2: S S D E| + S S D S|" )

	if( original_str.size() > 1 )
	{
		SET_BOUNDARY(0, FIRST_CANDIDATE, BOUNDARY(1))

		// Enumerate the lower bounded portion.
		if (enumerate_toggle_single_character(hashtable, results,original_str.back()))
		{
			return;
		}

	}

	/**
	 * Score = 2
	 *      S S S D|D
	 */

	DEBUG_MESG( "Score = 2: S S S D|D" )

	// Push back a dummy character to extend the length of the string.
	this->candidate_str.push_back('0');

	// Enumerate the entire character map.
	SET_BOUNDARY(0, FIRST_CANDIDATE, char_to_candidate(original_str.back()))
	SET_POSITOIN(0, this->candidate_str.rbegin()+1)
	SET_BOUNDARY(1, FIRST_CANDIDATE, LAST_CANDIDATE)
	SET_POSITOIN(1, this->candidate_str.rbegin())

	// Enumerate the lower bounded portion.
	if (enumerate_double_character(hashtable, results))
	{
		return;
	}

	SET_BOUNDARY(0, char_to_candidate(original_str.back())+1, LAST_CANDIDATE)

	// Enumerate the upper bounded portion.
	if (enumerate_double_character(hashtable, results))
	{
		return;
	}

	this->candidate_str.pop_back();

	/**
	 * Score = 2
	 *      S S D E| + S S D S|
	 */

	DEBUG_MESG( "Score = 2: S S D E| + S S D S|" )

	if( original_str.size() > 1 )
	{
		SET_BOUNDARY(0, BOUNDARY(1)+1,LAST_CANDIDATE )

		// Enumerate the lower bounded portion.
		if (enumerate_toggle_single_character(hashtable, results,original_str.back()))
		{
			return;
		}

	}

	/**
	 * Score = 3
	 *      S D S S|
	 */

	DEBUG_MESG( "Score = 3: S D S S|" )
	if( original_str.size() > 2 )
	{
		SET_BOUNDARY(0, FIRST_CANDIDATE, BOUNDARY(2))
		SET_POSITOIN(0, this->candidate_str.rbegin()+2);

		// Enumerate the lower bounded portion.
		if (enumerate_single_character(hashtable, results))
		{
			return;
		}

	/**
	 * Score = 3
	 *      S S E E|
	 */

	DEBUG_MESG( "Score = 3: S S E E|" )

		this->candidate_str.erase( this->candidate_str.end()-2, this->candidate_str.end() );

		if (NOT_FOUND(this->candidate_str))
		{
			results.push_back(this->candidate_str);
			PRINT_CANDIDATE()
		}

		// Restore the last two character.
		this->candidate_str.insert(this->candidate_str.end(), original_str.end()-2, original_str.end());

	} // end of bracket: original_str.size() > 2

	/**
	 * Score = 3
	 *      S S D D|
	 *      S S D S|D
	 */

	if( original_str.size() > 1 )
	{
		DEBUG_MESG( "Score = 3: S S D D| + S S D S|D " )
		SET_BOUNDARY(0, FIRST_CANDIDATE, BOUNDARY(1))
		SET_POSITOIN(0, this->candidate_str.rbegin()+1)
		SET_BOUNDARY(1, FIRST_CANDIDATE, BOUNDARY(0))
		SET_POSITOIN(1, this->candidate_str.rbegin())
		if( enumerate_triple_character( hashtable, results ) )
		{
			return;
		}
		this->candidate_str[ original_str.size()-2 ] = *( original_str.rbegin()+1);
	}
	/**
	 * Score = 3
	 *      S S S S|D D
	 */

	DEBUG_MESG("Score = 3: S S S S|D D")
	this->candidate_str.resize(original_str.size()+2);
	SET_BOUNDARY(0, FIRST_CANDIDATE, LAST_CANDIDATE )
	SET_BOUNDARY(1, FIRST_CANDIDATE, LAST_CANDIDATE )
	SET_POSITOIN(0, this->candidate_str.rbegin()+1)
	SET_POSITOIN(1, this->candidate_str.rbegin())
	if( enumerate_double_character( hashtable, results ) )
	{
		return;
	}
	this->candidate_str.resize(original_str.size());

	/**
	 * Score = 3
	 *      S S D S|D
	 *      S S D D|
	 */
	if( original_str.size() > 1 )
	{
		DEBUG_MESG( "Score = 3: S S D D| + S S D S|D " )
		SET_BOUNDARY(0, BOUNDARY(1)+1, LAST_CANDIDATE)
		SET_POSITOIN(0, this->candidate_str.rbegin()+1)
		SET_BOUNDARY(1, FIRST_CANDIDATE, BOUNDARY(0))
		SET_POSITOIN(1, this->candidate_str.rbegin())
		if( enumerate_triple_character( hashtable, results ) )
		{
			return;
		}
		this->candidate_str[ original_str.size()-2 ] = *( original_str.rbegin()+1);
	}

	/**
	 * Score = 3
	 *      S D S S|
	 */
	if( original_str.size() > 2 )
	{
		DEBUG_MESG("Score = 3: S D S S|")
		SET_BOUNDARY(0, BOUNDARY(2)+1, LAST_CANDIDATE)
		SET_POSITOIN(0, this->candidate_str.rbegin()+2)
		if( enumerate_single_character( hashtable, results ) )
		{
			return;
		}
	}
}

bool dsa::recommendation::enumerate_single_character(const std::unordered_map<std::string, unsigned int>& hashtable, std::vector<std::string>& results, int level)
{
	// Backup the character that is going to be changed.
	const char backup = *(this->positions[level]);

	// Enumertate through the characters in the table.
	for (char i = this->boundaries[level].lower; i < this->boundaries[level].upper; i++)
	{
		*(this->positions[level]) = this->candidate_chars[i];
		if( NOT_FOUND( this->candidate_str ) )
		{
			results.push_back(this->candidate_str);
			PRINT_CANDIDATE()
		}

		if( results.size() >= TARGET_AMOUNT )
		{
			return true;
		}
	}

	// Restore the last character.
	*(this->positions[level]) = backup;

	return false;
}

bool dsa::recommendation::enumerate_double_character(const std::unordered_map<std::string, unsigned int>& hashtable, std::vector<std::string>& results)
{
	// Backup the character that is going to be changed.
	const char backup = *(this->positions[0]);

	// Enumertate through the characters in the table.
	for (char i = this->boundaries[0].lower; i < this->boundaries[0].upper; i++)
	{
		*(this->positions[0]) = this->candidate_chars[i];

		// Call lower level.
		if (enumerate_single_character(hashtable, results, 1))
		{
			return true;
		}
	}

	// Restore the last character.
	*(this->positions[0]) = backup;

	return false;
}

bool dsa::recommendation::enumerate_triple_character(const std::unordered_map<std::string, unsigned int>& hashtable, std::vector<std::string>& results)
{

	// Enumertate through the characters in the table.
	for (char i = this->boundaries[0].lower; i < this->boundaries[0].upper; i++)
	{
		*(candidate_str.rbegin()+1) = this->candidate_chars[i];
		SET_POSITOIN(1, this->candidate_str.rbegin())
		if (enumerate_single_character(hashtable, results, 1))
		{
			return true;
		}

		this->candidate_str.push_back('0');

		SET_BOUNDARY(2, FIRST_CANDIDATE, LAST_CANDIDATE)
		SET_POSITOIN(2, this->candidate_str.rbegin())

		if (enumerate_single_character(hashtable, results, 2))
		{
			return true;
		}

		this->candidate_str.pop_back();

	}

	return false;
}

bool dsa::recommendation::enumerate_toggle_single_character(const std::unordered_map<std::string, unsigned int>& hashtable, std::vector<std::string>& results, char toggle_character)
{
	// Backup the character that is going to be changed.
	const char backup = *(this->candidate_str.rbegin()+1);

	for (char i = this->boundaries[0].lower; i < this->boundaries[0].upper; i++)
	{
		this->candidate_str.pop_back();
		this->candidate_str.back() = this->candidate_chars[i];
		if( NOT_FOUND( this->candidate_str ) )
		{
			results.push_back(this->candidate_str);
			PRINT_CANDIDATE()
		}

		if( results.size() >= TARGET_AMOUNT )
		{
			return true;
		}

		this->candidate_str.push_back( toggle_character );
		if( NOT_FOUND( this->candidate_str ) )
		{
			results.push_back(this->candidate_str);
			PRINT_CANDIDATE()
		}

		if( results.size() >= TARGET_AMOUNT )
		{
			return true;
		}
	}

	// Restore the last character.
	*(this->candidate_str.rbegin()+1) = backup;

	return false;
}

char dsa::recommendation::char_to_candidate(const char c)
{
	if (c < 'A')
	{
		return c - '0';				// c is a digit
	}
	else if (c < 'a')
	{
		return c - 'A' + 10;		// c is an uppercase alphabet.
	}
	else
	{
		return c - 'a' + 10 + 26;	// c is a lowercase alphabet.
	}
}
