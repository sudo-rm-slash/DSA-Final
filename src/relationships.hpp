#ifndef __RELATIONSHIPS_HPP__
#define __RELATIONSHIPS_HPP__

#include "disjoint_sets.hpp"	// dsa:::disjoint_sets

#include <string>				// std::string
#include <memory>				// std::unique_ptr


namespace dsa
{
	class relationships
	{
	private:
		dsa::disjoint_sets container;

	public:
		relationships();
		~relationships();


		//
		// @brief Add a new account in the relationship chain.
		//
		// @param index The storage index of the newly added account.
		// @return The id of this account in the relationship chain. 
		//
		unsigned int add_user(unsigned int index);

		// 
		// @brief Find the real owner of the account in question.
		//
		// @param id The ID of the account for quering.
		// @return The real account that holds the one in question.
		//
		unsigned int find_root(unsigned int id) const;

		//
		// @brief TODO
		//
		void link_users(unsigned int user1, unsigned int user2);
	};
}

#endif