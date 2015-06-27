#include "storage.hpp"

dsa::storage::storage()
{
	// Initialize the vector.
	this->container.clear();
}

dsa::storage::~storage()
{
	// Wipe out the private variable.
	this->container.clear();
}

int dsa::storage::insert(const char* username, const char* password)
{
	this->container.emplace_back(username, password);
	return this->container.size() - 1;
}

dsa::account& dsa::storage::operator[](const int& account_index)
{
	return this->container[account_index];
}