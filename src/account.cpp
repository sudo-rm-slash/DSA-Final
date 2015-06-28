#include "account.hpp"


dsa::account::account(std::string& password)
{
	// Save a blank username.
	this->username = "";

	// Store encrypted password.
	this->password = password;

	// Initialize the cash counter.
	this->cash = 0;

	// Wipe the history list.
	this->related_history.clear();
}
dsa::account::account(std::string& username, std::string& password)
{
	std::cerr << "DEPRECATED function, dsa::account::account(std::string&, std::string&)" << std::endl;

	//Save username and encrypted password.
	this->username = username;
	this->password = password;

	// Initialize the cash counter.
	this->cash = 0;

	// Wipe the history list.
	this->related_history.clear();
}

bool dsa::account::authenticate(const std::string& password) const
{
	return (this->password == password);
}

unsigned int dsa::account::deposit(unsigned int value)
{
	this->cash += value;
	return this->cash;
}

std::pair<bool, unsigned int> dsa::account::withdraw(unsigned int value)
{
	if (this->cash < value)
	{
		return std::make_pair(false, this->cash);
	}
	else
	{
		this->cash -= value;
		return std::make_pair(true, this->cash);
	}
}

unsigned int dsa::account::merge_with(dsa::account& slave)
{
	// Transfer the money.
	this->cash += slave.cash;
	slave.cash = 0;

	// Transfer the related history, union -> wipe slave -> copy.
	// ...union
	std::vector<unsigned int> temp;
	std::set_union(std::begin(this->related_history), std::end(this->related_history),
	               std::begin(slave.related_history), std::end(slave.related_history),
	               std::back_inserter(temp));
	// ...wipe the slave
	slave.related_history.clear();
	// ...copy
	this->related_history = temp;

	// Return new cash statistics.
	return this->cash;
}

void dsa::account::add_related_history(unsigned int index)
{
	this->related_history.push_back(index);

	std::cerr << "...new history added, new size = " << this->related_history.size() << std::endl;
}

const std::string& dsa::account::get_username() const
{
	return this->username;
}

void dsa::account::get_common_history(dsa::account& compared_account, std::vector<unsigned int>& results)
{
	// Find common history.
	std::vector<unsigned int> temp;
	std::set_intersection(std::begin(this->related_history), std::end(this->related_history),
	                      std::begin(compared_account.related_history), std::end(compared_account.related_history),
	                      std::back_inserter(temp));

	// Swap the vectors.
	results.swap(temp);
}
