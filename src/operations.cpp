#include "operations.hpp"

void dsa::login()
{
	std::cin >> username >> password;

	// Check the existance of the username.
	if (finder.exists(username))
	{
		last_login_id = finder.find_specific(username);
	}
	else
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
	if (finder.exists(username))
	{
		std::cout << "ID " << username << " exists,";

		// Get suggestions and print them.
		finder.suggest_nonexists(username, suggestions);
		if (suggestions.size() > 0)
		{
			std::cout << suggestions[0];
			for (auto itr = std::begin(suggestions); itr != std::end(suggestions); ++itr)
			{
				std::cout << ',' << *itr;
			}
		}
		std::cout << std::endl;

		return;
	}

	// Create a new account in the storage.
	unsigned int index = accounts.new_account(username, password);

	// Add the relationship of this account.
	unsigned int id = ownerships.add_user(index);

	// Store the account into the lookup table.
	finder.insert(username, id);

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