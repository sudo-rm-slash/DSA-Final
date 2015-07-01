#include "storage.hpp"


unsigned int dsa::storage::new_account(std::string& username, std::string& password)
{
	// Construct the account in-place.
	this->container.emplace_back(username, password);

	// Return the index of the last item.
	return container.size() - 1;
}

dsa::account& dsa::storage::operator[](unsigned int n)
{
	return this->container[n];
}

const dsa::account& dsa::storage::operator[](unsigned int n) const
{
	return this->container[n];
}
