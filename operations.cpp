#include "operations.hpp"

dsa::disjoint_sets<int> relationships;

void dsa::login()
{
	std::cout << "login()" << std::endl;
}

void dsa::create()
{
	std::cout << "create()" << std::endl;

	int input;
	std::cin >> input;
	std::cout << "...Input=" << input << ", ";
	std::cout << "ID=" << relationships.make_set(input) << std::endl;

	// Generate new block in the storage.

	// Acqurie the pointer to the block in the storage.

	// Add the pointer to disjoint set, and acquire the generated ID.

	// Store the generated ID along with the account string in TRIE.
}

void dsa::del()
{
	std::cout << "delete()" << std::endl;
}

void dsa::merge()
{
	std::cout << "merge()" << std::endl;

	int a, b;
	std::cin >> a >> b;
	std::cout << "...a=" << a << ", b=" << b << std::endl;

	relationships.link(a, b);
}

void dsa::deposit()
{
	std::cout << "deposit()" << std::endl;
}

void dsa::withdraw()
{
	std::cout << "withdraw()" << std::endl;
}

void dsa::transfer()
{
	std::cout << "transfer()" << std::endl;
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
}
