#include "storage.hpp"

dsa::storage::storage()
{

}

dsa::storage::~storage()
{

}

unsigned int dsa::storage::new_account(std::string& username, std::string& password)
{
	// Construct the account in-place.
	this->container.emplace_back(username, password);

	// Return the index of the last item.
	return container.size() - 1;
}

void dsa::storage::merge(unsigned int master, unsigned int slave)
{
	this->container[master].merge_with(this->container[slave]);
}

dsa::account& dsa::storage::operator[](unsigned int n)
{
	return this->container[n];
}

const dsa::account& dsa::storage::operator[](unsigned int n) const
{
	return this->container[n];
}