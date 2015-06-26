#ifndef __HISTORY_HPP__
#define __HISTORY_HPP__

#include <vecotor>		// std::vector

#include "account.hpp"

namespace dsa
{
	class history
	{
	private:
		std::vector<account> container;

		/*
		 * @brief Convert the transaction relationship into a single key.
		 *
		 * @param from_id From this account...
		 * @param to_id ...to this account.
		 * @return Return the converted key.
		 */
		long long convert_to_key(const int& from_id, const int& to_id);
		
		/*
		 * @brief Modify the ID in the converted key.
		 *
		 * @param position The position of the ID, from or to.
		 * @param original The original ID.
		 * @param after The new ID.
		 */
		long modify_key(const int& original, const int& after);

	public:
		history();
		virtual ~history();

		/* 
		 * @brief Insert a new history entry.
		 *
		 * @param from_id The account that initiate the transaction.
		 * @param to_id The account that receive the transaction.
		 * @param value The amount of cash transfered in this transaction.
		 * @return Void.
		 */
		void insert(const int& from_id, const int& to_id, unsigned int value);
		
		/* 
		 * @brief Modify the history (for merge purpose).
		 *
		 * @param before_id The original ID enlisted in the history.
		 * @param after_id The new ID.
		 * @return Void.
		 */
		void modify(const int& before_id, const int& after_id);
	};
}

#endif