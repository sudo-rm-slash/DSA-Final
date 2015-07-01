#include "operations.hpp"


dsa::storage dsa::accounts;					// The accounts themselves.
dsa::relationships dsa::ownerships;			// The ownership between accounts.
dsa::lookup_table dsa::finder;				// Support functions to find accounts.

dsa::history dsa::transaction_history;		// The grand transaction history. History depends on accounts and ownerships.

std::string dsa::username, dsa::password;	// Username and password for reuse.
std::string dsa::username2, dsa::password2;	// Secondary username and password storage for merge() to reuse.
unsigned int dsa::last_login_id;			// Last login ID (relationship ID).

std::vector<std::string> dsa::suggestions;	// Container to store all the suggestions.


void dsa::login()
{
	std::cin >> username >> password;

	// Check the existance of the username.
	unsigned int id;
	if (finder.exists(username))
	{
		id = finder.find_specific(username);
#ifdef DEBUG
		std::cerr << "...id = " << id << std::endl;
#endif
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
	if (accounts[id].authenticate(password))
	{
		std::cout << "success" << std::endl;
		last_login_id = id;
	}
	else
	{
		std::cout << "wrong password" << std::endl;
	}
}

void dsa::create()
{
	std::cin >> username >> password;

	// Check the existance of the username.
	if (finder.exists(username))
	{
		std::cout << "ID " << username << " exists, ";

		// Get suggestions and print them.
		finder.suggest_nonexists(username, suggestions);
		if (suggestions.size() > 0)
		{
			std::cout << suggestions[0];
			for (auto itr = std::next(std::begin(suggestions)); itr != std::end(suggestions); ++itr)
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
#ifdef DEBUG
	std::cerr << "...id = " << id << std::endl;
#endif

	// Store the account into the lookup table.
	finder.insert(username, id);

	std::cout << "success" << std::endl;
}

void dsa::delete_()
{
	std::cin >> username >> password;

	unsigned int id;
	if (finder.exists(username))
	{
		id = finder.find_specific(username);
	}
	else
	{
		std::cout << "ID " << username << " not found" << std::endl;
		return;
	}

	// Authenticate the account's password.
	if (accounts[id].authenticate(password))
	{
		finder.remove(username);
		std::cout << "success" << std::endl;
	}
	else
	{
		std::cout << "wrong password" << std::endl;
	}
}

void dsa::merge()
{
	std::cin >> username >> password;
	std::cin >> username2 >> password2;

	// Check the existance of the usernames.
	unsigned int id, id2;
	if (finder.exists(username))
	{
		id = finder.find_specific(username);
#ifdef DEBUG
		std::cerr << "...id = " << id << std::endl;
#endif
	}
	else
	{
		std::cout << "ID " << username << " not found" << std::endl;
		return;
	}
	if (finder.exists(username2))
	{
		id2 = finder.find_specific(username2);
#ifdef DEBUG
		std::cerr << "...id = " << id2 << std::endl;
#endif
	}
	else
	{
		std::cout << "ID " << username2 << " not found" << std::endl;
		return;
	}

	// Authenticate the passwords.
	if (!accounts[id].authenticate(password))
	{
		std::cout << "wrong password1" << std::endl;
		return;
	}
	if (!accounts[id2].authenticate(password2))
	{
		std::cout << "wrong password2" << std::endl;
		return;
	}

	// Merge the accounts.
	unsigned int new_stat = accounts[id].merge_with(id, accounts[id2]);

	// Link the relationships.
	ownerships.link_users(id, id2);

	// Remove the entry of the second acccount.
	finder.remove(username2);
	//finder.remove(accounts[id2].get_username());

	std::cout << "success, " << username << " has " << new_stat << " dollars" << std::endl;
}

void dsa::deposit()
{
	unsigned int value;
	std::cin >> value;

	std::cout << "success, " << accounts[last_login_id].deposit(value) << " dollars in current account" << std::endl;
}

void dsa::withdraw()
{
	unsigned int value;
	std::cin >> value;

	auto status = accounts[last_login_id].withdraw(value);
	if (status.first)
	{
		std::cout << "success, " << status.second << " dollars left in current account" << std::endl;
	}
	else
	{
		std::cout << "fail, " << status.second << " dollars only in current account" << std::endl;
	}
}

void dsa::transfer()
{
	unsigned int value;
	std::cin >> username >> value;

	// Check the existance of the usernames.
	unsigned int id;
	if (finder.exists(username))
	{
		id = finder.find_specific(username);
	}
	else
	{
		std::cout << "ID " << username << " not found, ";

		// Get suggestions and print them.
		finder.suggest_exists(username, suggestions);
		if (suggestions.size() > 0)
		{
			std::cout << suggestions[0];
			for (auto itr = std::next(std::begin(suggestions)); itr != std::end(suggestions); ++itr)
			{
				std::cout << ',' << *itr;
			}
		}
		std::cout << std::endl;

		return;
	}

	// Withdraw from the source account.
	auto status = accounts[last_login_id].withdraw(value);
	if (status.first)
	{
		std::cout << "success, " << status.second << " dollars left in current account" << std::endl;
	}
	else
	{
		std::cout << "fail, " << status.second << " dollars only in current account" << std::endl;
		return;
	}

	// Deposit to the given account. "value" is equal to "status.second".
	accounts[id].deposit(value);

	// Add an entry in the history.
	unsigned int index = transaction_history.insert(last_login_id, id, value);
#ifdef DEBUG
	std::cerr << "...index = " << index << std::endl;
#endif

	// Add the history index to both accounts.
	accounts[last_login_id].add_related_history(index);
	accounts[id].add_related_history(index);
}

void dsa::find()
{
	std::cin >> username;

	// Respect the spec, ignoring specific ID.
	//finder.find_wildcard(username, suggestions);
	finder.find_wildcard(username, last_login_id, suggestions);
	if (suggestions.size() > 0)
	{
		std::sort( suggestions.begin(), suggestions.end() );
		std::cout << suggestions[0];
		for (auto itr = std::next(std::begin(suggestions)); itr != std::end(suggestions); ++itr)
		{
			std::cout << ',' << *itr;
		}
	}
	std::cout << std::endl;
}

void dsa::search()
{
	std::cin >> username;

	// Check the existance of the usernames.
	std::vector<unsigned int> ids;
	if (!finder.exists(username, ids))
	{
		std::cout << "no record" << std::endl;
		return;
	}

	// Find their common history.
	std::map<unsigned int, std::vector<unsigned int> > results;
	for (const auto& id : ids)
	{
		std::vector<unsigned int> temp;
		if( id == ownerships.find_root(id))
		{
			accounts[last_login_id].get_common_history(accounts[id], temp);
			if( last_login_id == ownerships.find_root(id) )
			{
				auto it = remove_if( temp.begin(), temp.end(), [](unsigned int history_index){ 
							return !transaction_history.check_self_history(history_index); 
						});
				temp.erase( it, temp.end());
#ifdef DEBUG
				std:: cout << "Same root! \n";
				std::cout<<"Remaining history between self:\n";
				for(auto his:temp)
					std::cout << his << " ";
#endif
			}
			results.insert({id, temp});
		}
	}

#ifdef DEBUG
	std::cerr << "...history_length = " << results.size() << std::endl;
	std::cerr << "...history" << std::endl;
	for(const auto& item : results)
	{
		std::cerr << "..." << item.first << ", [";
		for(const auto& his : item.second)
			std::cerr << his << ", ";
		std::cerr << "]" << std::endl;
	}
#endif

	bool is_empty = true;
	for (const auto& user : results)
	{
#ifdef DEBUG
		std::cerr << "...id = " << user.first << std::endl;
#endif

		for (const auto& index : user.second)
		{
			std::cout << transaction_history.find(index, user.first) << std::endl;
			if( is_empty )
				is_empty = false;
		}
	}

	if (is_empty)
	{
		// Warning ! Beware empty vector in each result
		std::cout << "no record" << std::endl;
	}

}
