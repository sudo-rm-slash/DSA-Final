#include "history.hpp"}

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

void dsa::history::insert(const int& from_id, const int& to_id, unsigned int value)
{
	// Append a new entry.
	this->container.insert(this->container.end(), 1, (entry*)NULL);

	// Convert the IDs into a key.
	int index = this->container.size() - 1;
	this->container[index] = new entry();
	this->container[index]->key = convert_to_key(from_id, to_id);
	this->container[index]->value = value;
}

long long dsa::history::convert_to_key(const int& from_id, const int& to_id)
{

}

void dsa::history::modify(const int& before_id, const int& after_id)
{

}

long dsa::history::modify_key(const int& original, const int& after)
{

}