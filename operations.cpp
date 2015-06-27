#include "operations.hpp"

dsa::disjoint_sets<int> relationships;	// The relationships between accounts.
dsa::storage accounts;					// The actual objects, which hold the info of each account.

dsa::trie lookup_table;					// The TRIE structure that holds the entire search operation.

dsa::history transaction_history;		// The transaction history between accounts.
int last_login;							// The ID(int) of the last successfully login account(string).

void dsa::login()
{
	// Acquire the username and password.
	char username[101] = {0};
	char password[101] = {0};
	std::cin >> username >> password;

	// Find the account ID(int) by account name(string).
	last_login = lookup_table.find(username);
	if (last_login == -1)
	{
		std::cout << "ID " << username << " not found" << std::endl;
		return;
	}

	std::cerr << "...user_id=" << last_login << std::endl;

	// Authenticate the account's password.
	if (!accounts[last_login].authenticate(password))
	{
		std::cout << "wrong password" << std::endl;

		// Reset last_login to undefined(-1).
		last_login = -1;
		
		return;
	}

	// Print login success message.
	std::cout << "success" << std::endl;
}

void dsa::create()
{
	// Acquire the username and password.
	char username[101] = {0};
	char password[101] = {0};
	std::cin >> username >> password;

	// Verify whether the account exists or not.
	int user_id = lookup_table.find(username);
	if (user_id != -1)
	{
		std::cerr << "...user exists." << std::endl;

		//
		// TODO: Recommends 10 best unused ids
		//

		return;
	}

	// Acqurie the pointer to account in the storage.
	int storage_index = accounts.insert(username, password);
	std::cerr << "...pointer acquired" << std::endl;

	// Add the pointer to disjoint set, and acquire the generated ID(int).
	int generated_id = relationships.make_set(storage_index);
	std::cerr << "...new relationship in the disjoint set" << std::endl;

	// Store the generated ID(int) along with the account name(string) in TRIE.
	lookup_table.insert(username, generated_id);
	std::cerr << "...inserted in TRIE" << std::endl;

	// Print create success message.
	std::cout << "success" << std::endl;
}

void dsa::del()
{
	// Acquire the username and password.
	char username[101] = {0};
	char password[101] = {0};
	std::cin >> username >> password;

	// Find the account ID(int) by account name(string).
	int user_id = lookup_table.find(username);
	if (user_id == -1)
	{
		std::cout << "ID " << username << " not found" << std::endl;
		return;
	}

	// Authenticate the account's password.
	if (!accounts[last_login].authenticate(password))
	{
		std::cout << "wrong password" << std::endl;
		return;
	}

	// Remove the entry in TRIE.
	lookup_table.remove(username);

	// Print login success message.
	std::cout << "success" << std::endl;
}

void dsa::merge()
{
	// Acquire the variables.
	char username_1[101] = {0};
	char password_1[101] = {0};
	std::cin >> username_1 >> password_1;

	char username_2[101] = {0};
	char password_2[101] = {0};
	std::cin >> username_2 >> password_2;

	// Find the account ID(int) by account name(string).
	// ...First account.
	int user_id_1 = lookup_table.find(username_1);
	if (user_id_1 == -1)
	{
		std::cout << "ID " << username_1 << " not found" << std::endl;
		return;
	}
	// ...Second account.
	int user_id_2 = lookup_table.find(username_2);
	if (user_id_2 == -1)
	{
		std::cout << "ID " << username_2 << " not found" << std::endl;
		return;
	}

	// Authenticate the account's password.
	// ...First account.
	if (!accounts[user_id_1].authenticate(password_1))
	{
		std::cout << "wrong password1" << std::endl;
		return;
	}
	// ...Second account.
	if (!accounts[user_id_2].authenticate(password_2))
	{
		std::cout << "wrong password2" << std::endl;
		return;
	}

	// Transfer the cash.
	// ...Wipe the original account.
	int cash = accounts[user_id_2].wipe_account();
	// ...Transfer the money to the root account.
	accounts[user_id_1].deposit(cash);
	// ...Merge the related user list.
	std::vector<int> combined(accounts[user_id_1].get_related_history().size() + accounts[user_id_2].get_related_history().size());
	std::set_union(std::begin(accounts[user_id_1].get_related_history()), std::end(accounts[user_id_1].get_related_history()),
	               std::begin(accounts[user_id_2].get_related_history()), std::end(accounts[user_id_2].get_related_history()),
	               std::back_inserter(combined));
	accounts[user_id_1].set_related_history(accounts[user_id_2].get_related_history());

	// Link the accounts' relationships.
	relationships.link(user_id_1, user_id_2);

	// Remove the entry of the second account in TRIE.
	lookup_table.remove(accounts[user_id_2].get_name());

	// Print transfer sucess message.
	std::cout << "success, " << accounts[user_id_1].get_name() << " has " << accounts[user_id_1].get_money() << " dollars" << std::endl;
}

void dsa::deposit()
{
	// Acquire the variable.
	int money;
	std::cin >> money;

	// Deposit the money to the last succesfully login account(int).
	std::cout << "success, " << accounts[last_login].deposit(money) << " dollars in current account" << std::endl;
}

void dsa::withdraw()
{
	// Acquire the variable.
	int money;
	std::cin >> money;

	// Withdraw the money from the last succesfully login account(int).
	auto status = accounts[last_login].withdraw(money);
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
	// Acquire the username(string).
	char username[101] = {0};
	int value;
	std::cin >> username >> value;

	// Find the account ID(int) by account name(string).
	int user_id = lookup_table.find(username);
	if (user_id == -1)
	{
		std::cout << "ID " << username << " not found" << std::endl;
		return;
	}

	// Deposit and withdraw cash from the respective account.
	// ...Withdraw.
	auto status = accounts[last_login].withdraw(value);
	if (status.first)
	{
		std::cout << "success, " << status.second << " dollars left in current account" << std::endl;
	}
	else
	{
		std::cout << "fail, " << status.second << " dollars only in current account" << std::endl;

		//
		// TODO: Recommends 10 best unused ids
		//

		return;
	}
	// ...Desposit.
	accounts[user_id].deposit(value);

	// Add an entry in the history and record it to the list.
	int index = transaction_history.insert(last_login, user_id, value);
	accounts[last_login].add_related_history(index);
	accounts[user_id].add_related_history(index);
}

void dsa::find()
{
	// Acquire the username(string).
	char username[101] = {0};
	std::cin >> username;

	// Find the matches ID by TRIE.
	lookup_table.wildcard_print(username);
}

void dsa::search()
{
	// Acquire the username(string).
	char username[101] = {0};
	std::cin >> username;

	// Find the account ID(int) by account name(string).
	int user_id = lookup_table.find(username);
	if (user_id == -1)
	{
		std::cout << "ID " << username << " not found" << std::endl;
		return;
	}

	// Set the criteria to last successfully login account(int).
	transaction_history.set_criteria(last_login);

	// Print out all the history.
	if (last_login == user_id)
	{
		std::cerr << "...transfer to itself." << std::endl;

		//
		// TODO: Print out all history entries with identical transferer and transferee.
		// 		 i.e. From A to A
		//
	}
	else
	{
		std::cerr << "...start finding intersection." << std::endl;

		// Find the intersected items in the list, which means it's a pair of transaction history.
		std::vector<int> common;
		std::vector<int> list_1 = accounts[last_login].get_related_history();
		std::vector<int> list_2 = accounts[user_id].get_related_history();
		std::set_intersection(std::begin(list_1), std::end(list_1),
		                      std::begin(list_2), std::end(list_2),
		                      std::back_inserter(common));

		std::cerr << "...list_1.size()=" << list_1.size() << ", list_2.size()=" << list_2.size() << std::endl;

		if (common.empty())
		{
			std::cout << "no record" << std::endl;
		}
		else
		{
			// Iterate through all the history indices.
			for (const auto& index : common)
			{
				transaction_history[index];
			}
		}
	}
}
