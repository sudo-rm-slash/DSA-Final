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

		std::vector<int> transfer_history;    // A list of IDs(int), showing which account has interactions with.
	
    public:
		account(const char* ID, const char* password);

		std::pair<bool, int> withdraw(int dollar);
		bool  authenticate(const char* password);
		int   deposit(int dollar);
		int   merge(account& mergee);
		bool  search(account& transferee);
		char* get_name();
		int   get_money();
	};
}

#endif
