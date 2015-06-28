#include "history.hpp"

unsigned int dsa::history::insert(unsigned int from_id, unsigned int to_id, unsigned int cash)
{
	this->container.emplace_back(from_id, to_id, cash);
	return this->container.size() - 1;
}

std::string  dsa::history::find(unsigned int index, unsigned int associated_id)
{
	// Reset the string builder.
	this->string_builder.str(std::string());
	this->string_builder.clear();

	// Identify the direction and push into the placeholder.
	if (this->container[primary].from == slave)
	{
		string_builder << "From ";
	}
	else if (this->container[primary].to == slave)
	{
		string_builder << "To ";
	}
	else
	{
		throw std::invalid_argument("Invalid argument: Query ID isn't in the requested history entry.\n");
	}

	// Reverse lookup the username.
	int root = relationships.find_root(slave);
	this->string_builder << storage[root].get_username();

	// Print the amount of money.
	this->string_builder << this->container[primary];

	// Acquire the string.
	return this->string_builder.str();
}