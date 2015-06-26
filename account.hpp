#ifndef __ACCOUNT_HPP__
#define __ACCOUNT_HPP__

#define MD5_BYTE_LEN 33 // Fixed length 33 byte 

#include <utility>      // std::pair
#include <cstring>      // std::strncpy, std::strcmp
#include <vector>       // std::vector

#include "md5.hpp"      // md5

namespace dsa
{
	class account
	{
	private:
		char* username;       // Username(string).
        char* password;       // MD5 encoded password.

        int money;            // Amount of cash stored in this account.

		std::vector<int> related_users;    // A list of IDs(int), showing which account has interactions with.
	
    public:
		account(const char* username, const char* password);
        virtual ~account();

        /*
         * @brief Authenticate a non-encoded password with the one stored here.
         *
         * @param password A non-encoded password to compare with.
         * @return Indicate whether the password is correct or not.
         */
        bool  authenticate(const char* password) const;
		  
        /*
         * @brief Deposit money to this account.
         *
         * @param value The amount of cash to deposit in this account.
         * @return The new statistic of the cash in this account.
         */
		int deposit(int value);

        /*
         * @brief Withdraw money from this account.
         *
         * @param value The amount of cash to withdraw from this account.
         * @return The new statistic of the cash in this account, and whether this 
         *         operation succeed or not.
         */
        std::pair<bool, int> withdraw(int value);

		int merge(account& mergee);
		bool search(account& transferee);

        /*
         * @brief Get the username of this account.
         *
         * @return Return the username(string) of this account.
         */
		char* get_name() const;

        /*
         * @brief Get the amount of cash in this account.
         *
         * @return Return the amount of cash in this account.
         */
		int get_money() const;

        /*
         * @brief Get the related user with this account.
         *
         * @return Return the related users(int) in vector.
         */
        std::vector<int>& get_related_user();
	};
}

#endif
