#define MD5_BYTE 16     // Fixed length 16 byte (128 bits)

#include <utility>      // std::pair
#include <cstring>      // std::strncpy, std::strcmp

#include "md5.hpp"      // MD5

namespace dsa
{
	class account
	{
	private:
		int money;
		const char md5_password[ MD5_BYTE ];

	public:
		account(const char* password);

		bool authenticate(const char* password);
		int deposit(int dollar);
		std::pair<bool, int> withdraw(int dollar);
	};

}
