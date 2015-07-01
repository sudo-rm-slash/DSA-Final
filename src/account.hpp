#ifndef __ACCOUNT_HPP__
#define __ACCOUNT_HPP__

#include "md5.hpp"			// md5

#include <string>			// std::string
#include <vector>			// std::vector
#include <utility>			// std::pair
#include <algorithm>		// std::set_union
#include <iostream>			// std::cerr


namespace dsa
{

	class account
	{
	private:
		std::string username;
		std::string password;	// MD5 encoded password.


	protected:
		unsigned int cash;							// Amount of cash this account holds.
		std::vector<unsigned int> related_history;	// History entried that relates to this account.


	public:
		account(std::string& password);
		account(std::string& username, std::string& password);	// DEPRECATED

		/**
		 * Authenticate the password with the one stored in the account.
		 * @return Boolean value incidcate whehter the authentication succeeded or failed.
		 */
		bool authenticate(const std::string& password) const;

		/**
		 * Deposit money into this account.
		 * @arg value The amount of cash to save into this account.
		 * @return The amount of cash this account holds after the depoist.
		 */
		unsigned int deposit(unsigned int value);

		/**
		 * Withdraw money from this account.
		 * @arg value The amount of cash to withdraw from this account.
		 * @return A pair of value, first one indicates the operation succeed or not, second one indicates the amount of cash left.
		 */
		std::pair<bool, unsigned int> withdraw(unsigned int value);

		/**
		 * Merge the contents of another account with current one.
		 * @arg master_id The id of the master who is being merged into
		 * @arg slave The target account to merge with this one.
		 */
		unsigned int merge_with(unsigned int master_id, dsa::account& slave);

		/**
		 * Add a related history in the list.
		 * @arg slave The target account to merge with this one.
		 */
		void add_related_history(unsigned int index);

		/**
		 * Get the username of this account.
		 * @return The username.
		 */
		const std::string& get_username() const;

		/**
		 * Get the username of this account.
		 * @arg compared_account The account to compare with.
		 * @arg results The container to store the common history.
		 */
		void get_common_history(dsa::account& compared_account, std::vector<unsigned int>& results);
	};
}

#endif
