#include <iostream>

#include "operations.hpp"
#include "disjoint_sets.hpp"


namespace dsa
{
	
	namespace global
	{
		dsa::disjoint_sets<int> objects;
	}
	void login()
	{
		std::cout << "login()" << std::endl;
	}

	void create()
	{
		std::cout << "create()" << std::endl;

		int input;
		std::cin >> input;
		std::cout << "...Input=" << input << std::endl;

		global::objects.make_set(input);
	}

	void remove()
	{
		std::cout << "delete()" << std::endl;
	}

	void merge()
	{
		std::cout << "merge()" << std::endl;

		int a, b;
		std::cin >> a >> b;
		std::cout << "...a=" << a << ", b=" << b << std::endl;

		global::objects.link(a, b);
	}

	void deposit()
	{
		std::cout << "deposit()" << std::endl;
	}

	void withdraw()
	{
		std::cout << "withdraw()" << std::endl;
	}

	void transfer()
	{
		std::cout << "transfer()" << std::endl;
	}

	void find()
	{
		std::cout << "find()" << std::endl;

		int id;
		std::cin >> id;
		std::cout << "...Parent of " << id << " is ";

		std::cout << global::objects.find_set(id) << std::endl;
	}

	void search()
	{
		std::cout << "search()" << std::endl;
	}
}