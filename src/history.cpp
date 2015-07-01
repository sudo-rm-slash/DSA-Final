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
	unsigned int to_id = ownerships.find_root(this->container[index].to);
	unsigned int associated_id = ownerships.find_root( associated_id_ );
#ifdef DEBUG
	std::cerr << "...from_id = " << this->container[index].from << " -> " << from_id << std::endl;
	std::cerr << "...to_id = " << this->container[index].to << " -> " << to_id << std::endl;
	std::cerr << "...associated_id = " << associated_id << " -> " << associated_id << std::endl;
#endif
	if( from_id == to_id ){
#ifdef DEBUG
		std::cerr << "...from_id == to_id" << std::endl;
#endif
		if( this->container[index].priority == dsa::priority_t::FROM )
		{
			string_builder << "To " << accounts[to_id].get_username() << ' ' << this->container[index].amount << std::endl
						   << "From " << accounts[to_id].get_username() << ' ' << this->container[index].amount;
		}
		else
		{
			string_builder << "From " << accounts[to_id].get_username() << ' ' << this->container[index].amount << std::endl
						   << "To " << accounts[to_id].get_username() << ' ' << this->container[index].amount;
		}
		return string_builder.str();
	}
	else if (from_id == associated_id)
	{
#ifdef DEBUG
		std::cerr << "...from_id == associated_id" << std::endl;
#endif
		string_builder << "From ";
	}
	else if (to_id == associated_id)
	{
#ifdef DEBUG
		std::cerr << "...to_id == associated_id" << std::endl;
#endif
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
void dsa::history::set_priority(unsigned int index, unsigned int master_id)
{
	if( this->container[index].from == master_id )
		this->container[index].priority = priority_t::FROM;
	else 
		this->container[index].priority = priority_t::TO;
}	
bool dsa::history::check_self_history(unsigned int index)
{
	// std::cout<<"From root: " <<ownerships.find_root( this->container[index].from )<<" To root: "<<ownerships.find_root( this->container[index].to )<<std::endl;
	if( ownerships.find_root( this->container[index].from ) == ownerships.find_root( this->container[index].to ) )
		return true;
	else
		return false;
}
