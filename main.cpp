#include <map>			// std::map
#include <functional>	// std::function
#include <iostream>		// std::cin
#include <stdexcept>	// std::invalid_argument

#include "operations.hpp"

/*
 * Definitions
 */
typedef std::map<const char*, std::function<void()> > functions;


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

	// Start parsing strings
	char* operation = new char[10];
	while (std::cin >> operation)
	{
		// Find the target function.
		auto search = lookup_table.find(operation);
		if (search == lookup_table.end())
		{
			throw std::invalid_argument("Invalid operation \"" + operation + "\".\n");
		}

		// Execute the function.
		search->second();

		// Reinitialize the operation string buffer.
		operation = "";
	}

	return 0;
}
