#include "history.hpp"

unsigned int dsa::history::insert(unsigned int from_id, unsigned int to_id, unsigned int cash)
{
	this->container.emplace_back(from_id, to_id, cash);
	return this->container.size() - 1;
}

std::string dsa::history::find(unsigned int primary, unsigned int slave)
{
	// Output placeholder.
	std::string output = "";

	if (this->container[primary].from == slave)
	{
		output += "From ";
	}
	else if (this->container[primary].to == slave)
	{
		output += "To ";
	}
	else
	{
		throw std::invalid_argument("Invalid argument: Query ID isn't in the requested history entry.\n");
	}

}