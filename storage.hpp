#ifndef __STORAGE_HPP__
#define __STORAGE_HPP__

#include <vector>		// std::vector

#include "account.hpp"	// dsa::account

namespace dsa 
{
	class storage
	{
	private:
		std::vector<dsa::account> container;

	public:
		storage();
		virtual ~storage();	

		/*
		 * @brief Insert a new item into the storage.
		 *
		 * @param password Password of the new account.
		 * @return The address of the newly inserted item.
		 */
		int insert(const char* password);

		/*
		 * @brief Subscripting operator overload to easily acquire specific account.
		 *
		 * @param associated_id The associated ID.
		 * @return Void.
		 */
		dsa::account& operator[](const int& account_index);
	};
}

#endif
