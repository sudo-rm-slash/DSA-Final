#include "account.hpp"

namespace dsa
{
	account(const char* password)
	{
		strncpy(md5_password , MD5(password) , MD5_BYTE);
	}

	bool account::authenticate(const char* password)
	{
		return strcmp(MD5(password), md5_password) == 0;
	}

	int account::deposit(int dollar)
	{
		return (money += dollar);
	}

	std::pair<bool, int> account::withdraw(int dollar)
	{
		if (dollar < money)
		{
			return std::pair<bool, int>(false, money);
		}

		money -= dollar;

		return std::pair<bool, int>(true, money);
	}
};
