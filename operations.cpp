#include "operations.hpp"
#include "history.hpp"

dsa::disjoint_sets<int> relationships;

dsa::history
dsa::account* last_login_account;

void dsa::login()
{
	std::cout << "login()" << std::endl;

	// Find the account ID(int) by account name(string).

	// MD5 the password.

	// Authenticate the account's password.

	// Update last succesfully login account.


	std::string ID[100], password[100];

	std::cin >> ID >> password;

	// return a pointer to the account object
	dsa::account* unauthenticated_account = dsa::trie.find(ID.c_str());

	if (unauthenticated_account == nullptr)
	{
		printf("ID %s not found\n", ID);
	}
	else if (!unauthenticated_account->authenticate(password.c_str()))
	{
		printf("wrong passowrd\n");
	}
	else
	{
		printf("sucess\n");
	}
}

void dsa::create()
{
	std::cout << "create()" << std::endl;

	// Generate new acount in the storage.

	// Acqurie the pointer to the block in the storage.

	// Add the pointer to disjoint set, and acquire the generated ID(int).

	// Store the generated ID(int) along with the account name(string) in TRIE.

	// 


	int input;
	std::cin >> input;
	std::cout << "...Input=" << input << ", ";
	std::cout << "ID=" << relationships.make_set(input) << std::endl;
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

	// First account...
	// Find the account ID(int) by account name(string).

	// MD5 the password.

	// Authenticate the account's password.


	// Second account...
	// Find the account ID(int) by account name(string).

	// MD5 the password.

	// Authenticate the account's password.

	
	// Link the accounts' relationships.

	// Remove the entry of the second account in TRIE.


	std::cin >> ID1 >> password1 >> ID2 >> password2 ;

	account* merger = dsa::trie.find(ID1);
	if (merger == nullptr)
	{
		std::cout << "ID " << ID1 << " not found\n";
		return;
	}

	account* mergee = dsa::trie.find(ID2);
	if (merger == nullptr)
	{
		std::cout << "ID " << ID1 << " not found\n";
		return;
	}

	if (!merger->authenticate(password1.c_str()))
	{
		std::cout << "wrong password1\n";
		return
	}

	if (!mergee->authenticate(password1.c_str()))
	{
		std::cout << "wrong password2\n";
		return
	}

	std::cout << "success, " << ID1 << " has " << merger->merge(mergee) << " dollars\n";
}

void dsa::deposit()
{
	std::cout << "deposit()" << std::endl;

	// Deposit the money to the last succesfully login account.
	

	int money;
	std::cin >> money;
	std::cout << "success, " << last_login_account->deposit(money) << " dollars in current account\n" ;
}

void dsa::withdraw()
{
	std::cout << "withdraw()" << std::endl;

	// Withdraw the money from the last succesfully login account.


	int money;
	std::cin >> money;
	std::pair<bool, int> status = last_login_account->withdraw(money);
	if (status.first)
	{
		std::cout << "success, " << status.second << " dollars left in current account\n";
	}
	else
	{
		std::cout << "fail, "    << status.second << " dollars only in current account\n";
	}
}

void dsa::transfer()
{
	std::cout << "transfer()" << std::endl;

	std::string ID;
	int money;
	std::cin >> ID >> money;

	account* transferee = dsa::trie.find(ID.c_str());

	if (transferee == nullptr)
	{
		std::cout << "ID " << ID << " not found, ";
		// TODO
		// 10 best recommendations
	}
	else
	{
		std::pair<bool, int> status = last_login_account->withdraw(money);

		if (status.first)
		{
			transferee->deposit(money);
			dsa::history.insert(last_login_account->owner , transferee->owner, money);
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

	int id;
	std::cin >> id;
	std::cout << "...Parent of " << id << " is ";

	std::cout << relationships.find_root(id) << std::endl;
}

void dsa::search()
{
	std::cout << "search()" << std::endl;

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
