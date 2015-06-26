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
