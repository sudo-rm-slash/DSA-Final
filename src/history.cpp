#include "history.hpp"


unsigned int dsa::history::insert(unsigned int from_id, unsigned int to_id, unsigned int cash)
{
	this->container.emplace_back(from_id, to_id, cash);
	return this->container.size() - 1;
}

std::string dsa::history::find(unsigned int index, unsigned int associated_id_)
{
	// Reset the string builder.
	this->string_builder.str(std::string());
	this->string_builder.clear();

	// Identify the direction and push into the placeholder.
	unsigned int from_id = ownerships.find_root(this->container[index].from);
	std::cerr << "...from_id = " << this->container[index].from << " -> " << from_id << std::endl;
	unsigned int to_id = ownerships.find_root(this->container[index].to);
	std::cerr << "...to_id = " << this->container[index].to << " -> " << to_id << std::endl;
	unsigned int associated_id = ownerships.find_root( associated_id_ );
	std::cerr << "...associated_id = " << associated_id_ << " -> " << associated_id << std::endl;
	if( from_id == to_id ){
		std::cerr << "...from_id == to_id" << std::endl;
		string_builder << "To " << accounts[to_id].get_username() << ' ' << this->container[index].amount << std::endl
			       << "From " << accounts[to_id].get_username() << ' ' << this->container[index].amount << std::endl;
		return string_builder.str();
	}
	else if (from_id == associated_id)
	{
		std::cerr << "...from_id == associated_id" << std::endl;
		string_builder << "From ";
	}
	else if (to_id == associated_id)
	{
		std::cerr << "...to_id == associated_id" << std::endl;
		string_builder << "To ";
	}
	else
	{
		throw std::invalid_argument("Invalid argument: Query ID isn't in the requested history entry.\n");
	}

	// Reverse lookup the username.
	int root = ownerships.find_root(associated_id);
	this->string_builder << accounts[root].get_username() << ' ';

	// Print the amount of money.
	this->string_builder << this->container[index].amount;

	// Acquire the string.
	return this->string_builder.str();
}
