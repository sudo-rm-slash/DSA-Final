#ifndef __HISTORY_HPP__
#define __HISTORY_HPP__

#include <vector>			// std::vector
#include <utility>			// std::pair
#include <exception>		// std::invalid_argument


namespace dsa
{
	class history
	{
	public:
		enum direction { FROM = 0, TO };
	private:
		struct entry
		{
			unsigned int from;
			unsigned int to;
			unsigned int amount;

			entry(unsigned int _from, unsigned int _to, unsigned int _amount)
				: from(_from), to(_to), amount(_amount)
			{
			}
		};
		std::vector<entry> container;


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
		 * Subscripting operator overload to easily acquire A/B related entries.
		 * (true for "to", false for "from")
		 * @arg associated_id The associated ID.
		 * @return First field is the name, second field indicates the direction, last one is the amount of cash.
		 */
		std::pair<unsigned int, bool> find(unsigned int primary, unsigned int slave);
	};
}

#endif