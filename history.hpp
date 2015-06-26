#ifndef __HISTORY_HPP__
#define __HISTORY_HPP__

#include <vecotor>		// std::vector

#include "account.hpp"

namespace dsa
{
	class history
	{
	private:
		struct entry
		{
			int from;
			int to;
			unsigned int value;
		};

		std::vector<entry> container;

	public:
		history();
		virtual ~history();

		/*
		 * @brief Insert a new history entry.
		 *
		 * @param from_id The account that initiate the transaction.
		 * @param to_id The account that receive the transaction.
		 * @param value The amount of cash transfered in this transaction.
		 * @return The ID of current entry.
		 */
		int insert(const int& from_id, const int& to_id, unsigned int value);
	};
}

#endif