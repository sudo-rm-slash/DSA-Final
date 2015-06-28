#ifndef __OPERATIONS_HPP__
#define __OPERATIONS_HPP__

#include "storage.hpp"			// dsa::storage
#include "relationships.hpp"	// dsa::relationships
#include "lookup_table.hpp"		// dsa::lookup_table
#include "history.hpp"			// dsa::history

#include <string>				// std::string
#include <vector>				// std::vector


namespace dsa
{
	/**
	 * Global variables in namespace "dsa".
	 */
	extern storage accounts;						// The accounts themselves.
	extern relationships ownerships;				// The ownership between accounts.
	extern lookup_table finder;						// Support functions to find accounts.

	extern history transaction_history;				// The grand transaction history.
													// History is dependent on accounts and ownerships.
	
	extern std::string username, password;			// Username and password for reuse. 
	extern unsigned int last_login_id;				// Last login ID (relationship ID).

	extern std::vector<std::string> suggestions;	// Container to store all the suggestions.


	//
	// @brief Login to a specific account.
	//
	void login();

	//
	// @brief Create a specific account with password
	//
	void create();

	//
	// @brief TODO
	//
	void delete_();

	//
	// @brief TODO
	//
	void merge();

	//
	// @brief TODO
	//
	void deposit();

	//
	// @brief TODO
	//
	void withdraw();

	//
	// @brief TODO
	//
	void transfer();

	//
	// @brief TODO
	//
	void find();

	//
	// @brief TODO
	//
	void search();
}

#endif
