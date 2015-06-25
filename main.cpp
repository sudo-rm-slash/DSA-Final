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
 * Generate function lookup table.
 */
void functions_init(functions &lookup_table)
{
#define INSERT(NAME, FUNC) lookup_table.insert(std::pair<std::string, std::function<void()> >(NAME, FUNC))

	INSERT("login", 	login);
	INSERT("create", 	create);
	INSERT("delete", 	del);
	INSERT("merge", 	merge);
	INSERT("deposit", 	deposit);
	INSERT("withdraw", 	withdraw);
	INSERT("transfer",	transfer);
	INSERT("find", 		find);
	INSERT("search", 	search);
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
