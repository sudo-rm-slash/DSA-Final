#include "history.hpp"

dsa::history::history()
{
	// Initialize the vector.
	this->container.clear();

	// Reset the base ID flag.
	this->base_id = -1;

	// Set the default output method as std::cout.
	this->output = std::cout;
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

void set_criteria(const int& base_id)
{
	this->base_id = base_id;
}

void set_output_stream(const ostream& stream)
{
	this->output = stream;
}

void dsa::history::operator[](const int& associated_id)
{
	// First round of the search.
	auto it = std::find_if(std::begin(this->container), std::end(this->container), [](entry e)
	{
		if ((e.from == this->base_id) && (e.to == associated_id))
		{
			output << "To " << e.value << std::endl;
			return true;
		}
		else if ((e.from == associated_id) && (e.to == this->base_id))
		{
			output << "From " << e.value << std::endl;
			return true;
		}
		else
		{
			return false;
		}
	});

	// Quit when no record exist, which means the iterator is pointed at the end.
	if (it == std::end(this->container))
	{
		output << "no output\n";
		return;
	}

	while (it != std::end(this->container))
	{
		it = std::find_if(std::next(it), std::end(this->container), [](entry e)
		{
			if ((e.from == this->base_id) && (e.to == associated_id))
			{
				output << "To " << e.value << std::endl;
				return true;
			}
			else if ((e.from == associated_id) && (e.to == this->base_id))
			{
				output << "From " << e.value << std::endl;
				return true;
			}
			else
			{
				return false;
			}
		});
	}
}
