#include "account.hpp"

dsa::account::account(const char* username, const char* password)
{
	// Set username and password.
	std::memset(this->username, 0, sizeof(char) * FIELD_SIZE);
	std::strcpy(&this->username[0], username);

	std::memset(this->password, 0, sizeof(char) * FIELD_SIZE);
	std::strcpy(&this->password[0], md5(password));

	// Reset the amount of cash this account holds to 0.
	this->money = 0;
}

dsa::account::~account()
{
	// Reset the amount of cash.
	this->money = 0;

	// Wipe the ID list.
	this->related_history.clear();
}

bool dsa::account::authenticate(const char* password) const
{
	// Compare the encypted password.
	return (std::strcmp(this->password, md5(password)) == 0);
}

void dsa::account::set_account(const char* username, const char* password)
{
	std::strcpy(this->username, username);
	std::strcpy(this->password, password);
}

int dsa::account::wipe_account()
{
	int value = this->money;
	this->money = 0;
	return value;
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

char* dsa::account::get_name() const
{
	return const_cast<char*>(&username[0]);
}

int dsa::account::get_money() const
{
	return money;
}

std::vector<int>& dsa::account::get_related_history()
{
	return related_history;
}

void dsa::account::add_related_history(const int& history_index)
{
	std::cerr << "...add new related history=" << history_index << std::endl;
	this->related_history.push_back(history_index);
}

void dsa::account::set_related_history(std::vector<int>& new_vector)
{
	this->related_history = new_vector;
}
