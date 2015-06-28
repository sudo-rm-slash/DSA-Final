#include "operations.hpp"

void dsa::login()
{
	std::cin >> username >> password;

	// Check the existance of the username.
	last_login_id = lookup_table.find_specific(username);
	if (last_login_id == -1)
	{
		std::cout << "ID " << username << " not found" << std::endl;
		return;
	}
	// TODO:
	// Wil the user the master owner after the lookup?
	// Do I need to reverse lookup for it?

	// Authenticate the password.
	if (accounts[last_login_id].authenticate(password))
	{
		std::cout << "success" << std::endl;
	}
	else
	{
		std::cout << "wrong password" << std::endl;

		// Reset the last_login
		last_login_id = -1;
	}
}

void dsa::create()
{
	std::cin >> username >> password;

	// Check the existance of the username.
	int id = lookup_table.find_specific(username);
	if (id != -1)
	{
		std::cout << "ID " << username << " exists,";

		// Get suggestions and print them.
		lookup_table.suggest_nonexists(username, suggestions);
		if (suggestions.size() > 0)
		{
			std::cout << suggestions[0];
			for (int i = 1; i < suggestions.size(); i++)
			{
				std::cout << ',' << suggestions[i];
			}
		}
		std::cout << std::endl;

		return;
	}

	// Create a new account in the storage.
	int index = accounts.new_account(username, password);

	// Add the relationship of this account.
	id = relationship.add_user(index);

	// Store the account into the lookup table.
	lookup_table.insert(username, id);

	std::cout << "success" << std::endl;
}

void dsa::delete_()
{

}

void dsa::merge()
{

}

void dsa::deposit()
{

}

void dsa::withdraw()
{

}

void dsa::transfer()
{

}

void dsa::find()
{

}

void dsa::search()
{

}