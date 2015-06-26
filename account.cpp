#include "account.hpp"

dsa::account::account(const char* username, const char* password)
{
	// Set the username.
	this->username = new char[std::strlen(username) + 1];
	std::strcpy(this->username, username);

	// Set the password.
	this->password = new char[std::strlen(password) + 1];
	std::strcpy(this->password, password);

	// Reset the amount of cash this account holds to 0.
	this->money = 0;
}

dsa::account::~account()
{
	// Delete the char pointers.
	delete this->username;
	delete this->password;

	// Reset the amount of cash.
	this->money = 0;

	// Wipe the ID list.
	this->related_users.clear();
}

bool dsa::account::authenticate(const char* password) const
{
    // Compare the encypted password.
	return (std::strcmp(this->password, md5(password)) == 0);
}

int dsa::account::deposit(int value)
{
	// Add the additional cash to the counter.
	this->money += value;

	// Return the newest amount of cash.
	return this->money;
}

std::pair<bool, int> dsa::account::withdraw(int value)
{
	// Verify whether there are enough money in this account.
	if (this->money < value)
	{
		return std::make_pair(false, this->money);
	}
	else
	{
		// Subtract the money from this account.
		this->money -= value;

		return std::make_pair(true, this->money);
	}
}

int dsa::account::wipe_account() const
{
    int value = this->money;
    this->money = 0;
    return value;
}

/*
int dsa::account::merge(account& mergee)
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

bool dsa::account::search(account& transferee)
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
*/

char* dsa::account::get_name() const
{
	return username;
}

int dsa::account::get_money() const
{
	return money;
}

std::vector<int>& dsa::account::get_related_user()
{
    return related_users;
}
