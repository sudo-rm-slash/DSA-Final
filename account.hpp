#ifndef __ACCOUNT_HPP__
#define __ACCOUNT_HPP__

#define MD5_BYTE_LEN 16 // Fixed length 16 byte (128 bits)

#include <utility>      // std::pair
#include <cstring>      // std::strncpy, std::strcmp
#include <vector>       // std::vector

#include "md5.hpp"      // MD5

namespace dsa
{
	class account
	{
	private:
		int money;
		const char* ID;
		const char md5_password[ MD5_BYTE_LEN ];
		std::vector<unsigned int> transfer_history;

	public:
		account(std::string& ID, std::string& password);
		account(const char* ID, const char* password);

		bool authenticate(const char* password);
		int deposit(int dollar);
		std::pair<bool, int> withdraw(int dollar);
		int merge(account* mergee);
		int search(account* transferee);
	};
}

#endif
