#include <map>			// std::map
#include <functional>	// std::function
#include <string>		// std::string
#include <iostream>		// std::cin
#include <stdexcept>	// std::invalid_argument

#include "operations.hpp"

/*
 * Definitions
 */
typedef std::map<std::string, std::function<void()> > functions;


/*
 * Global variables.
 */
functions lookup_table;


/*
 * Generate function lookup table.
 */
#define INSERT(NAME, FUNC) lookup_table.insert(std::pair<std::string, std::function<void()> >(NAME, FUNC))
void functions_init()
{
	INSERT("login", 	dsa::login);
	INSERT("create", 	dsa::create);
	INSERT("delete", 	dsa::remove);
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
	functions_init();

	// Start parsing strings
	std::string operation;
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
	}

	return 0;
}
