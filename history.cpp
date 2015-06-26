#include "history.hpp"

extern dsa::disjoint_sets<dsa::account*> relationships;
extern dsa::storage<dsa::account> accounts;

dsa::history::history()
{
	// Initialize the vector.
	this->container.clear();

	// Reset the base ID flag.
	this->base_id = -1;
}

dsa::history::~history()
{
	// Delete all the entries in this container.
	for (int i = this->container.size() - 1; i >= 0; i--)
	{
		delete this->container[i];
	}

	// Wipe out all the private variables.
	this->container.clear();
	this->base_id = -1;
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

void dsa::history::set_criteria(const int& base_id)
{
	this->base_id = base_id;
}

void dsa::history::set_output_stream(std::ostream& stream)
{
	this->output = stream;
}

void dsa::history::operator[](const int& history_index)
{
	// Get the raw entry in the container.
	entry& pulled_history = this->container.data()[history_index];

	// Output the direction string.
	int query_id;
	if (pulled_history.from == base_id)
	{
		this->output << "To ";
		query_id = pulled_history.to;
	}
	else if (pulled_history.to == base_id)
	{
		this->output << "From ";
		query_id = pulled_history.from;
	}
	else
	{
		throw std::invalid_argument("Invalid argument: Queried ID isn't in current transaction entry.");
	}

	// Find the username and print it.
	int user_id = relationships.find_root(query_id);
	this->output << accounts[user_id].get_name() << " ";

	// Print the amount of money during this transaction.
	this->output << pulled_history.value << std::endl;
}
