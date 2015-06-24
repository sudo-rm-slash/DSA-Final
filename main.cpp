#include <map>			// std::map
#include <functional>	// std::function
#include <string>		// std::string
#include <iostream>		// std::cin
#include <stdexcept>	// std::invalid_argument

#include "operations.hpp"

namespace dsa
{
	/*
	 * Definitions
	 */
	typedef std::map<std::string, std::function<void()> > functions;


	/*
	 * Global variables.
	 */
	namespace global
	{
		dsa::functions lookup_table;
	}


	/*
	 * Generate function lookup table.
	 */
#define INSERT(NAME, FUNC) dsa::global::lookup_table.insert(std::pair<std::string, std::function<void()> >(NAME, FUNC))
	void functions_init()
	{
		INSERT("login", login);
		INSERT("create", create);
		INSERT("delete", remove);
		INSERT("merge", merge);
		INSERT("deposit", deposit);
		INSERT("withdraw", withdraw);
		INSERT("transfer", transfer);
		INSERT("find", find);
		INSERT("search", search);
	}
}


/*
 * Main function
 */
int main()
{
	// Generate "name to function" lookup table beforehand.
	dsa::functions_init();

	// Start parsing strings
	std::string operation;
	while (std::cin >> operation)
	{
		// Find the target function.
		auto search = dsa::global::lookup_table.find(operation);
		if (search == dsa::global::lookup_table.end())
		{
			throw std::invalid_argument("Invalid operation \"" + operation + "\".\n");
		}

		// Execute the function.
		search->second();
	}

	return 0;
}
