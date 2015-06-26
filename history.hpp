#ifndef __HISTORY_HPP__
#define __HISTORY_HPP__

#include <vector>		// std::vector
#include <algorithm>	// std::find_if
#include <ostream>		// std::ostream, std::cout

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

		int base_id;		// Normally, it's the last successful login ID.
		ostream output;		// Default output method.

		/*
		 * DEPRECATED
		 *
		 * @brief Inline method for std::find_if lambda operation.
		 *
		 * @param from_id From whom...
		 * @param to_id ...to whom.
		 * @return Whether the condition matches the setting.
		 */
		inline bool criteria_match(const int& from_id, const int& to_id);

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

		/*
		 * @brief Set the base ID variable, normally, it denotes the last successful login ID.
		 *
		 * @param base_id The base ID.
		 * @return Void.
		 */
		void set_criteria(const int& base_id);

		/*
		 * @brief Override the default output stream (std::cout).
		 *
		 * @param stream Desired ostream object.
		 * @return Void.
		 */
		void set_output_stream(const ostream& stream);

		/*
		 * @brief Subscripting operator overload to easily print out A/B related entries,
		 *		  Use set_critera before using this function.
		 *
		 * @param associated_id The associated ID.
		 * @return Void.
		 */
		void operator[](const int& associated_id);
	};
}

#endif
