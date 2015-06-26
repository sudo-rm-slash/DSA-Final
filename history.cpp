#include "history.hpp"

dsa::history::history()
{
	// Initialize the vector.
	this->container.clear();
}

dsa::history::~history()
{
	// Wipe out the private variable.
	this->container.clear();
}

int dsa::history::insert(const int& from_id, const int& to_id, unsigned int value)
{
	// Append a new entry.
	this->container.insert(this->container.end(), 1, (entry*)NULL);

	// Convert the IDs into a key.
	int index = this->container.size() - 1;
	this->container[index] = new entry();
	this->container[index]->from = from_id;
	this->container[index]->to = to_id;
	this->container[index]->value = value;

	return index;
}
