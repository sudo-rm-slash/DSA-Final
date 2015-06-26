#ifndef __STORAGE_HPP__
#define __STORAGE_HPP__

#include <vector>		// std::vector

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
		T* insert(const T& item) const;
	};
}

#include "storage.tpp"

#endif
