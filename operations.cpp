#include "operations.hpp"
#include "history.hpp"
#include "account.hpp"

dsa::disjoint_sets<int> relationships;	// The relationships between accounts.
dsa::storage<dsa::account> accounts;	// The actual objects, which hold the info of each account.

dsa::trie lookup_table;					// The TRIE structure that holds the entire search operation.

dsa::history transaction_history;		// The transaction history between accounts.
int last_login;							// The ID(int) of the last successfully login account(string).

void dsa::login()
{
	std::cout << "login()" << std::endl;

	// Acquire the username and password.
	char username[101] = {0};
	char password[101] = {0};
	std::cin >> username >> password;

	// Find the account ID(int) by account name(string).
	last_login = dsa::lookup_table.find(username);
	if (last_login == -1)
	{
		std::cout << "ID " << username << " not found" << std::endl;
		return;
	}

	// Authenticate the account's password.
	if (!storage[last_login].authenticate(password))
	{
		std::cout << "wrong password" << std::endl;
		return;
	}

	// Print login success message.
	std::cout << "success" << std::endl;
}

void dsa::create()
{
	std::cout << "create()" << std::endl;

	std::string ID, password;
	std::cin >> ID >> password;

	std::cout << "ID " << ID << " exists, ";
	// TODO
	// Recommends 10 best unused ids
	
	auto new_account = dsa::storage.insert( new dsa::account(ID,password) );
	int  index       = dsa::relationships.make_set( new_account );
	dsa::lookup_table.insert( ID, index );

	// Generate new account in the storage.

	// Acqurie the pointer to account in the storage.

	// Add the pointer to disjoint set, and acquire the generated ID(int).

	// Store the generated ID(int) along with the account name(string) in TRIE.

	//


	int input;
	std::cin >> input;
	std::cout << "...Input=" << input << ", " << "ID=" << relationships.make_set(input) << std::endl;
}

void dsa::del()
{
	std::cout << "delete()" << std::endl;

	// Find the account ID(int) by account name(string).

	// MD5 the password.

	// Authenticate the account's password.

	// Remove the entry in TRIE.

}

void dsa::merge()
{
	std::cout << "merge()" << std::endl;

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
	if (!storage[user_id_1].authenticate(password_1))
	{
		std::cout << "wrong password1" << std::endl;
		return;
	}
	// ...Second account.
	if (!storage[user_id_2].authenticate(password_2))
	{
		std::cout << "wrong password2" << std::endl;
		return;
	}

	// Transfer the cash.
	storage[user_id_1].merge(storage[user_id_2]);

	// Link the accounts' relationships.
	relationships.link(user_id_1, user_id_2);

	// Remove the entry of the second account in TRIE.
	lookup_table.remove(storage[user_id_2].get_name());

	// Print transfer sucess message.
	std::cout << "success, " << storage[user_id_1].get_name() << " has " << storage[user_id_1].get_money() << " dollars" << std::endl;
}

void dsa::deposit()
{
	std::cout << "deposit()" << std::endl;

	// Acquire the variable.
	int money;
	std::cin >> money;

	// Deposit the money to the last succesfully login account(int).
	std::cout << "success, " << storage[last_login].deposit(money) << " dollars in current account" << std::endl;
}

void dsa::withdraw()
{
	std::cout << "withdraw()" << std::endl;

	// Acquire the variable.
	int money;
	std::cin >> money;

	// Withdraw the money from the last succesfully login account(int).
	auto status = storage[last_login].withdraw(money);
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
	std::cout << "transfer()" << std::endl;

	// Find the account ID(int) by account name(string).

	// Check whether the account exists.

	// Deposit and withdraw cash from the respective account.

	// Add an entry in the history.


	char username[101] = {0};
	int money;

	std::cin >> username >> money;

	int user_id = dsa::lookup_table.find(ID);

	if (user_id == -1)
	{
		std::cout << "ID " << ID << " not found, ";
		// TODO
		// 10 best recommendations
	}
	else
	{
		auto status = storage[user_id].withdraw(money);

		if (status.first)
		{
			storage[last_login].deposit(money);
			dsa::history.insert(last_login , user_id, money);
			std::cout << "success, " << status.second << " dollars left in current account\n";
		}
		else
		{
			std::cout << "fail, "    << status.second << " dollars only in current account\n";
		}
	}

}

void dsa::find()
{
	std::cout << "find()" << std::endl;

	// Find the matches ID by TRIE.


	int id;
	std::cin >> id;
	std::cout << "...Parent of " << id << " is ";

	std::cout << relationships.find_root(id) << std::endl;
}

void dsa::search()
{
	std::cout << "search()" << std::endl;

	// Find the account ID(int) by account name(string).

	// Set the criteria to last successfully login account(int).

	// Print out all the history.


	std::string ID;
	std::cin >> ID;

	account* transferee = dsa::trie.find(ID.c_str());
	if (transferee == nullptr)
	{
		std::cout << "ID " << ID << " not found\n";
	}
	else if (!last_login_account->search(transferee))
	{
		std::cout << "no record\n";
	}
}
