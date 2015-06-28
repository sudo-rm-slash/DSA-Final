#include "operations.hpp"

void dsa::login()
{
	std::cin >> username >> password;

	// Check the existance of the username.
	last_login_id = lookup_table.find_specific(username);
	if(last_login_id == -1)
	{
		std::cout << "ID " << username << " not found" << std::endl;
		return;
	}
	// TODO:
	// Wil the user the master owner after the lookup?
	// Do I need to reverse lookup for it?
	
	// Authenticate the password.
	if(accounts[last_login_id].authenticate(password))
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