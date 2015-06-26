#ifndef __ACCOUNT_HPP__
#define __ACCOUNT_HPP__

#define MD5_BYTE_LEN 33 // Fixed length 33 byte 

#include <utility>      // std::pair
#include <cstring>      // std::strncpy, std::strcmp
#include <vector>       // std::vector

#include "md5.hpp"      // md5
#include "history.hpp"  // dsa::history

namespace dsa
{
	class account
	{
	private:
		int money;
		char* ID;
		char md5_password[ MD5_BYTE_LEN ];
		std::vector<unsigned int> transfer_history; // vector of transfer history 

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
