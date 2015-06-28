#ifndef __LOOKUP_TABLE_HPP__
#define __LOOKUP_TABLE_HPP__

//#include "trie.hpp"			// dsa::trie

#include <unordered_map>	// std::unordered_map
#include <set>			// std::priority_queue
#include <string>			// std::string
#include <vector>			// std::vector


#define WIPING_FACTOR	20	// When the size of queue equals this, wipe the queue until its size equals WANTED_AMOUNT.
#define WANTED_AMOUNT	10

namespace dsa
{
	class lookup_table
	{
	private:
		//dsa::trie tree_lookup;
		std::unordered_map<std::string, unsigned int> hashtable_lookup;
		dsa::recommendation<std::unordered_map<std::string, unsigned int> > suggestion_factory(hashtable_lookup);

		struct suggestion
		{
			unsigned int score;
			std::string username;

			suggestion(unsigned int score, std::string& username)
			{
				this->score = score;
				this->username = username;
			}
		};
		std::set<suggestion> suggestions_buffer;

		bool dirty_last_found_id = false;
		unsigned int last_found_id;		// Store the last lookup ID.

	public:
		/**
		 * Insert a new account entry in the lookup table.
		 * @arg username The string username.
		 * @arg id The relationship ID of the account.
		 * @return Void.
		 */
		void insert(const std::string& username, unsigned int id);

		/**
		 * Reomve an entry in the lookup table.
		 * @arg username The string username.
		 * @return Void.
		 */
		void remove(const std::string& username);

		/*
		 * Check whether specificed username exists in the table or not.
		 * @arg username The username to search for.
		 * @return Boolean value indicates exists or not.
		 */
		bool exists(const std::string& username);

		//
		// @brief TODO
		//
		unsigned int find_specific(const std::string& username);

		//
		// @brief TODO
		//
		void find_wildcard(const std::string& pattern, std::vector<unsigned int>& results);

		//
		// @brief Suggest exists accounts in the system.
		//
		// @param username The username to start with.
		// @param suggestions The container to hold the suggestions.
		//
		void suggest_exists(const std::string& username, std::vector<std::string>& suggestions);

		//
		// @brief Suggest non-exists accounts in the system.
		//
		// @param username The username to start with.
		// @param suggestions The container to hold the suggestions.
		//
		void suggest_nonexists(const std::string& username, std::vector<std::string>& suggestions);


	private:
		//
		// @brief TODO
		//
		unsigned int calculate_score(const std::string& str1, const std::string& str2);
	};
}

#endif