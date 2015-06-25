#ifndef __DISJOINT_SETS_HPP__
#define __DISJOINT_SETS_HPP__

#include <vector>			// std::vector

// TODO: Function descriptions.
namespace dsa
{
	class disjoint_sets
	{
	private:
		struct node
		{
			node* parent;	// The parent node of this node.
			int id;			// The index of this node.
			int rank;		// Roughly represent the max height of the node in its subtree.
		};
		std::vector<node*> sets;
		int set_count;
		int element_count;

	public:
		disjoint_sets();
		virtual ~disjoint_sets();

		void make_set(int num_to_add);

		/*
		 * @brief Find the set child belongs to.
		 *
		 * @ param child The child to look up for.
		 * @ return The set ID of the root node.
		 */
		int find_set(int id) const;

		/*
		 * @brief Merge the sets that child1 and child2 belogns to.
		 *
		 * @param child1 The first child.
		 * @param child2 The second child.
		 * @return Void.
		 */
		void link(int id1, int id2);

		/*
		 * @brief Get the number of sets this container currently holds.
		 *
		 * @return The sets count.
		 */
		int get_sets();

		/*
		 * @brief Get the number of elements this container currently holds.
		 *
		 * @return The elements count.
		 */
		int get_elements();
	};
}

#endif
