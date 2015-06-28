#include "operations.hpp"

#include <map>			// std::map
#include <functional>	// std::function
#include <utility> 		// std::make_pair
#include <string>		// std::string
#include <iostream>		// std::cerr, std::endl
#include <exception>	// std::invalid_argument


typedef std::map<std::string, std::function<void()> > functions;

void init_function_lookup_table(functions &lookup_table)
{
#define INSERT(NAME, FUNC) lookup_table.insert(std::make_pair(NAME, FUNC))

	INSERT("login", 	dsa::login);
	INSERT("create", 	dsa::create);
	INSERT("delete", 	dsa::delete_);
	INSERT("merge", 	dsa::merge);
	INSERT("deposit", 	dsa::deposit);
	INSERT("withdraw", 	dsa::withdraw);
	INSERT("transfer",	dsa::transfer);
	INSERT("find", 		dsa::find);
	INSERT("search", 	dsa::search);
}


int main()
{
	// Generate name-function lookup table.
	functions function_lookup;
	init_function_lookup_table(function_lookup);

	std::string operation;
	while (std::cin >> operation)
	{
		std::cerr << ">>> \"" << operation << "\" START <<<" << std::endl;

		// Find the target function.
		auto search = function_lookup.find(operation);
		if(search == function_lookup.end())
		{
			throw std::invalid_argument("Invalid argument: Invalid operation.\n");
		}

		// Execute the function.
		search->second();

		std::cerr << ">>> END <<<" << std::endl;
	}

	return 0;
}