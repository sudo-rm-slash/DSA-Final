#ifndef __DISJOINT_SETS_HPP__
#define __DISJOINT_SETS_HPP__

// TODO: Function descriptions.
namespace dsa
{
	template <class T>
	class disjoint_sets
	{
	private:
		struct node
		{
			node* parent;	// The parent node of this node.
			int id;			// The index of this node.
			int rank;		// Roughly represent the max height of the node in its subtree.
			T data;			// The data this node carries.
		};
		std::vector<node*> sets;

	public:
		disjoint_sets();
		virtual ~disjoint_sets();

		void make_set(const T& item);

		/*
		 * @brief Find the set child belongs to.
		 *
		 * @ param child The child to look up for.
		 * @ return The set ID of the root node.
		 */
		int find_set(const T& child) const;

		/*
		 * @brief Merge the sets that child1 and child2 belogns to.
		 *
		 * @param child1 The first child.
		 * @param child2 The second child.
		 * @return Void.
		 */
		void link(const T& child1, const T& child2);

		/*
		 * @brief Get the number of sets this container currently holds.
		 *
		 * @return The sets count.
		 */
		int get_sets();
	};
}

#endif
