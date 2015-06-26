#include <map>			// std::map
#include <functional>	// std::function
#include <iostream>		// std::cin
#include <stdexcept>	// std::invalid_argument
#include <sstream>		// std::stringstream
#include <cstring>		// std::strcmp

#include "operations.hpp"

/*
 * Definitions
 */
struct string_comparer : public std::binary_function<const char*, const char*, bool>
{
public:
	bool operator()(const char* str1, const char* str2) const
	{
		return std::strcmp(str1, str2) < 0;
	}
};
typedef std::map<const char*, std::function<void()>, string_comparer> functions;

#define OP_BUFFER_SIZE	10


/*
 * Generate function lookup table.
 */
void functions_init(functions &function_lookup_table)
{
#define INSERT(NAME, FUNC) function_lookup_table.insert(std::pair<const char*, std::function<void()> >(NAME, FUNC))

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
	functions function_lookup_table;
	functions_init(function_lookup_table);

	// Initialize operation buffer.
	char *operation = new char[OP_BUFFER_SIZE];
	std::memset(operation, 0, sizeof(char) * OP_BUFFER_SIZE);

	// Start parsing strings
	while (std::cin >> operation)
	{
		std::cerr << ">>> \"" << operation << "\" START <<<" << std::endl;

		// Find the target function.
		auto search = function_lookup_table.find(operation);
		if (search == function_lookup_table.end())
		{
			std::stringstream ss;
			ss << "Invalid operation \"" << operation << "\"." << std::endl;
			throw std::invalid_argument(ss.str());
		}

		// Execute the function.
		search->second();

		// Reinitialize the operation string buffer.
		std::memset(operation, 0, sizeof(char) * OP_BUFFER_SIZE);

		std::cerr << ">>> END <<<" << std::endl << std::endl;
	}

	delete operation;

	return 0;
}
