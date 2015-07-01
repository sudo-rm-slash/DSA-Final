#ifndef __HISTORY_HPP__
#define __HISTORY_HPP__

#include "storage.hpp"			// dsa::storage
#include "relationships.hpp"	// dsa::relationships

#include <vector>				// std::vector
#include <sstream>				// std::ostringstream
#include <exception>			// std::invalid_argument


namespace dsa
{
	extern dsa::storage accounts;				// The accounts themselves.
	extern dsa::relationships ownerships;		// The ownership between accounts.

	enum priority_t { FROM , TO };

	class history
	{
	private:
		struct entry
		{
			unsigned int from;
			unsigned int to;
			unsigned int amount;
			bool priority;

			entry(unsigned int _from, unsigned int _to, unsigned int _amount)
				: from(_from), to(_to), amount(_amount)
			{
			}
		};
		std::vector<entry> container;

		std::ostringstream string_builder;


	public:
		/**
		 * Descriptions.
		 * @arg from_id From this account...
		 * @arg to_id transfer cash to this account.
		 * @arg cash The amount of cash being transfered.
		 * @return The history timestamp.
		 */
		unsigned int insert(unsigned int from_id, unsigned int to_id, unsigned int cash);

		/**
		 * Acquire an entry from specific index.
		 * @arg index The index of the entry.
		 * @arg The account of interest, which wil use to indicate the direction of the cash flow.
		 * @return A history entry in the form of string.
		 */
		std::string find(unsigned int index, unsigned int associated_id);

		/**
		 * Check if TO and FROM are the same person ( share the same root )
		 * @arg index The index of the entry.
		 * @return yes/no
		 */
		bool check_self_history(unsigned int index);

		/**
		 * Set the master id to identify who is printed first in search
		 * @arg index The index of the entry.
		 * @arg master_id
		 */
		void set_priority(unsigned int index, unsigned int master_id);
	};
}

#endif
