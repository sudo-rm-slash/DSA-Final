#include "operations.hpp"

dsa::disjoint_sets objects;

void dsa::login()
{
	std::cout << "login()" << std::endl;
}

void dsa::create()
{
	std::cout << "create()" << std::endl;

	int input;
	std::cin >> input;
	std::cout << "...Input=" << input << std::endl;

	objects.make_set(input);
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

	objects.link(a, b);
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

	std::cout << objects.find_set(id) << std::endl;
}

void dsa::search()
{
	std::cout << "search()" << std::endl;
}
