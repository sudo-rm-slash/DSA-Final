#include <map>			// std::map
#include <functional>	// std::function
#include <iostream>		// std::cin
#include <stdexcept>	// std::invalid_argument
#include <sstream>		// std::stringstream

#include "operations.hpp"

/*
 * Definitions
 */
typedef std::map<const char*, std::function<void()> > functions;

#define OP_BUFFER_SIZE	10


/*
 * Generate function lookup table.
 */
void functions_init(functions &lookup_table)
{
#define INSERT(NAME, FUNC) lookup_table.insert(std::pair<const char*, std::function<void()> >(NAME, FUNC))

	INSERT("login", 	dsa::login);
	INSERT("create", 	dsa::create);
	INSERT("delete", 	dsa::del);
	INSERT("merge", 	dsa::merge);
	INSERT("deposit", 	dsa::deposit);
	INSERT("withdraw", 	dsa::withdraw);
	INSERT("transfer",	dsa::transfer);
	INSERT("find", 		dsa::find);
	INSERT("search", 	dsa::search);
}


/*
 * Main function
 */
int main()
{
	// Generate "name to function" lookup table beforehand.
	functions lookup_table;
	functions_init(lookup_table);

	// Initialize operation buffer.
	char operation[OP_BUFFER_SIZE];
	std::memset(operation, 0, sizeof(char) * OP_BUFFER_SIZE);

	// Start parsing strings
	while (std::cin >> operation)
	{
		// Find the target function.
		auto search = lookup_table.find(operation);
		if (search == lookup_table.end())
		{
			std::stringstream ss;
			ss << "Invalid operation \"" << operation << "\"." << std::endl;
			throw std::invalid_argument(ss.str());
		}

		// Execute the function.
		search->second();

		// Reinitialize the operation string buffer.
		std::memset(operation, 0, sizeof(char) * OP_BUFFER_SIZE);
	}

	return 0;
}
