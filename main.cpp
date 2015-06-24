#include <map>			// std::map
#include <functional>	// std::function
#include <string>		// std::string

namespace dsa
{
	/*
	 * Definitions
	 */
	typedef std::map<const char*, std::function<void()> > functions;


	/*
	 * Global variables.
	 */
	namespace inputs
	{
		std::string var1, var2, var3, var4;
	}

	namespace global
	{
		dsa::functions lookup_table;
	}


	/*
	 * Operations.
	 */
	void login()
	{

	}

	void create()
	{

	}

	void remove()
	{

	}

	void merge()
	{

	}

	void deposit()
	{

	}

	void withdraw()
	{

	}

	void transfer()
	{

	}

	void find()
	{

	}

	void search()
	{

	}


	/*
	 * Generate function lookup table.
	 */
	void functions_init()
	{
		dsa::global::lookup_table.insert(std::make_pair("login", login));
		dsa::global::lookup_table.insert(std::make_pair("create", create));
		dsa::global::lookup_table.insert(std::make_pair("delete", remove));
		dsa::global::lookup_table.insert(std::make_pair("merge", merge));
		dsa::global::lookup_table.insert(std::make_pair("deposit", deposit));
		dsa::global::lookup_table.insert(std::make_pair("withdraw", withdraw));
		dsa::global::lookup_table.insert(std::make_pair("transfer", transfer));
		dsa::global::lookup_table.insert(std::make_pair("find", find));
		dsa::global::lookup_table.insert(std::make_pair("search", search));
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
	while (true)
	{
		// Get the target function.

		// Execute the function.

		// (Deprecated) Print the result.
	}

	return 0;
}
