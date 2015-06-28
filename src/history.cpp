#include "history.hpp"


unsigned int dsa::history::insert(unsigned int from_id, unsigned int to_id, unsigned int cash)
{
	this->container.emplace_back(from_id, to_id, cash);
	return this->container.size() - 1;
}

std::string dsa::history::find(unsigned int index, unsigned int associated_id)
{
	// Reset the string builder.
	this->string_builder.str(std::string());
	this->string_builder.clear();

	// Identify the direction and push into the placeholder.
	if (this->container[index].from == associated_id)
	{
		string_builder << "From ";
	}
	else if (this->container[index].to == associated_id)
	{
		string_builder << "To ";
	}
	else
	{
		throw std::invalid_argument("Invalid argument: Query ID isn't in the requested history entry.\n");
	}

	// Reverse lookup the username.
	int root = ownerships.find_root(associated_id);
	this->string_builder << accounts[root].get_username();

	// Print the amount of money.
	this->string_builder << this->container[index].amount;

	// Acquire the string.
	return this->string_builder.str();
}