#ifndef __DISJOINT_SETS_HPP__
#define __DISJOINT_SETS_HPP__

#include <vector>			// std::vector
#include <cstddef>			// NULL


namespace dsa
{
	class disjoint_sets
	{
	private:
		struct node
		{
			node* parent;		// The parent node of this node.
			unsigned int id;	// The relationship ID of the node
			int rank;			// Roughly represent the max height of the node in its subtree.
			unsigned int data;	// The storage index of the node.
		};
		std::vector<node*> sets;

		unsigned int set_count;
		unsigned int element_count;

	public:
		disjoint_sets();
		~disjoint_sets();

		/*
		 * @brief Create a new disjoint set in the forest.
		 *
		 * @ param value The child that the newly created set contains.
		 * @ return Generated ID.
		 */
		unsigned int make_set(unsigned int data);

		/*
		 * @brief Find the set child belongs to.
		 *
		 * @ param child The child to look up for.
		 * @ return The set ID of the root node.
		 */
		unsigned int find_root(unsigned int id) const;

		/*
		 * @brief Merge the sets that child1 and child2 belogns to.
		 *
		 * @param child1 The first child.
		 * @param child2 The second child.
		 * @return Void.
		 */
		void link(unsigned int id1, unsigned int id2);

		/*
		 * @brief Get the data stored in the specified node.
		 * 
		 * @param id The generated ID of the node.
		 * @return The data.
		 */
		unsigned int get_data(unsigned int id) const;
		
		/*
		 * @brief Get the number of sets this container currently holds.
		 *
		 * @return The sets count.
		 */
		unsigned int get_set_count() const;

		/*
		 * @brief Get the number of elements this container currently holds.
		 *
		 * @return The elements count.
		 */
		unsigned int get_element_count() const;
	};
}

#endif
