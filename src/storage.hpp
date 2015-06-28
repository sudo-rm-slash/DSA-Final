#ifndef __STORAGE_HPP__
#define __STORAGE_HPP__

#include "account.hpp"			// dsa::account

#include <vector>				// std::vector
#include <string>				// std::string


namespace dsa
{
	class storage
	{
	private:
		std::vector<dsa::account> container;
	
	public:
		//
		// @brief Create a new account in the system.
		//
		// @param username The username of the new account.
		// @param password Un-encrypted password of the new account.
		// @return The index of the newly created account in the storage.
		//
		unsigned int new_account(std::string& username, std::string& password);

		//
		// @brief Merging the contents of two accounts.
		//
		void merge(unsigned int master, unsigned int slave);

		//
		// @brief Provide  direct access to the storage using subscripting.
		//
		dsa::account& operator[](unsigned int n);

		//
		// @brief A constant overloaded version of operator[].
		//
		const dsa::account& operator[](unsigned int n) const;
	};
}

#endif