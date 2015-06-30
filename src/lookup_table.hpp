#ifndef __LOOKUP_TABLE_HPP__
#define __LOOKUP_TABLE_HPP__

#define TRIE 					// Hard coded include choice.

#ifdef TRIE
#include "trie.hpp"				// dsa::trie
#elif ART
// TODO: include "art.hpp"
#endif
#include "recommendation.hpp"	// dsa::recommendation
#include "storage.hpp"			// dsa::storage

#include <unordered_map>		// std::unordered_map
#include <set>					// std::priority_queue
#include <utility>				// std::pair
#include <string>				// std::string
#include <vector>				// std::vector
#include <exception>			// std::invalid_argument
#include <algorithm>			// std::swap


#define WIPING_FACTOR	20	// When the size of queue equals this, wipe the queue until its size equals WANTED_AMOUNT.
#define WANTED_AMOUNT	10

namespace dsa
{
	extern storage accounts;


	class lookup_table
	{
	private:
#ifdef TRIE
		dsa::trie tree_lookup;
#elif ART
#endif
		std::unordered_map<std::string, unsigned int> hashtable_lookup;
		dsa::recommendation suggestion_factory;

		std::set<std::pair<unsigned int, std::string> > suggestions_buffer;

		bool dirty_last_found_id = false;
		unsigned int last_found_id;		// Store the last lookup ID.


	public:
		/**
		 * Insert a new account entry in the lookup table.
		 * @arg username The string username.
		 * @arg id The relationship ID of the account.
		 */
		void insert(const std::string& username, unsigned int id);

		/**
		 * Reomve an entry in the lookup table.
		 * @arg username The string username.
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

		/**
		 * Find all the accounts that match the wildcard pattern.
		 * @arg pattern The pattern to compare with.
		 * @arg results The container to store all the matched accounts.
		 */
		void find_wildcard(const std::string& pattern, std::vector<std::string>& results);

		/**
		 * Find all the accounts that match the wildcard pattern, but ignore the one specified.
		 * @arg pattern The pattern to compare with.
		 * @arg ignored_id The ID to ignore during the discovery.
		 * @arg results The container to store all the matched accounts.
		 */
		void find_wildcard(const std::string& pattern, unsigned int ignored_id, std::vector<std::string>& results);

		/**
		 * Suggest exists accounts in the system.
		 * @arg username The username to start with.
		 * @arg suggestions The container to hold the suggestions.
		 */
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
