#ifndef __STORAGE_HPP__
#define __STORAGE_HPP__

#include <vector>		// std::vector

#include "md5.hpp"		// md5

namespace dsa 
{
	template <class T>
	class storage
	{
	private:
		std::vector<T> container;

	public:
		storage();
		virtual ~storage();	

		/*
		 * @brief Insert a new item into the storage.
		 *
		 * @param item New item to insert.
		 * @return The address of the newly inserted item.
		 */
		//T* insert(const T&& item);
		T* insert(const char* username, const char* password);

		/*
		 * @brief Subscripting operator overload to easily acquire specific account.
		 *
		 * @param associated_id The associated ID.
		 * @return Void.
		 */
		T& operator[](const int& account_index);
	};
}

#include "storage.tpp"

#endif
