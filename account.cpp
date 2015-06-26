#include "account.hpp"

namespace dsa
{
	account::account(const char* username, const char* password)
	{
        // Set the username.
		this->username = new char[std::strlen(username) + 1];
        std::strcpy(this->username, username);

        // Set the password.
        this->password = new char[std::strlen(password) + 1];
        std::strcpy(this->password, password);

        // Reset the amount of cash this account holds to 0.
		money = 0;
	}

	bool account::authenticate(const char* password)
	{
		return (std::strcmp(this->password, md5(password)) == 0);
	}

	int account::deposit(int dollar)
	{
		return (this->money += dollar);
	}

	std::pair<bool, int> account::withdraw(int dollar)
	{
		if (dollar < this->money)
		{
			return std::pair<bool, int>(false, this->money);
		}

		this->money -= dollar;

		return std::pair<bool, int>(true, this->money);
	}

	int account::merge(account& mergee)
	{
		std::vector<unsigned int> history_union(transfer_history.size() + mergee.transfer_history.size());
		auto history_union_end = std::set_union(
		                             this->transfer_history.begin(),
		                             this->transfer_history.end(),
		                             mergee.transfer_history.begin(),
		                             mergee.transfer_history.end(),
		                             history_union.begin()
		                         );
		history_union.resize(history_union_end - history_union.begin());

		this->transfer_history = std::move(history_union);

		return (this->money += mergee.money);
	}

	bool account::search(account& transferee)
	{
		std::vector<unsigned int> history_intersection(std::max(transfer_history.size(), transferee.transfer_history.size()));
		auto history_intersection_end = std::set_intersection(
		                                    this->transfer_history.begin(),
		                                    this->transfer_history.end(),
		                                    transferee.transfer_history.begin(),
		                                    transferee.transfer_history.end(),
		                                    history_intersection.begin()
		                                );
		history_intersection.resize(history_intersection_end - history_intersection.begin());

		for (auto transfer_record : history_intersection)
		{
			transaction_history[ transfer_record ];
		}

		if (history_intersection.empty())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	char* account::get_name()
	{
		return ID;
	}

	int account::get_money()
	{
		return money;
	}
}
