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
        bool  authenticate(const char* password);
		  
        /*
         * @brief Deposit money to this account.
         *
         * @param value The amount of cash to deposit in this account.
         * @return The new statistic of the cash in this account.
         */
		int   deposit(int value);

        std::pair<bool, int> withdraw(int dollar);

		int   merge(account& mergee);
		bool  search(account& transferee);
		char* get_name();
		int   get_money();
	};
}

#endif
