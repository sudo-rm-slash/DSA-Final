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
#define INSERT(LUT, NAME, FUNC) LUT.insert(std::pair<std::string, std::function<void()> >(NAME, FUNC))
void functions_init(functions &lookup_table)
{
	INSERT(lookup_table, "login", 	dsa::login);
	INSERT(lookup_table, "create", 	dsa::create);
	INSERT(lookup_table, "delete", 	dsa::remove);
	INSERT(lookup_table, "merge", 	dsa::merge);
	INSERT(lookup_table, "deposit", 	dsa::deposit);
	INSERT(lookup_table, "withdraw", 	dsa::withdraw);
	INSERT(lookup_table, "transfer",	dsa::transfer);
	INSERT(lookup_table, "find", 		dsa::find);
	INSERT(lookup_table, "search", 	dsa::search);
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
