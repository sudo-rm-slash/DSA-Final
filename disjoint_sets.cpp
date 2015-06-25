#include <vector>		// std::vector

#include "disjoint_sets.hpp"

namespace dsa
{
	template <class T>
	disjoint_sets<T>::disjoint_sets()
	{
		// Initialize the vector.
		sets.clear();
	}

	template <class T>
	disjoint_sets<T>::~disjoint_sets()
	{
		
	}

	template <class T>
	void disjoint_sets<T>::make_set(const T& item)
	{

	}

	template <class T>
	int disjoint_sets<T>::find_set(int id) const
	{
		node* current_node;

		// Find the root element that represents the set which id belongs to.
		current_node = sets[id];
		while (current_node->parent != NULL)
		{
			current_node = current_node->parent;
		}

		node* root = current_node;

		// Update the parents of id, make those elements direct children of root.
		current_node = sets[id];
		while (current_node != root)
		{
			node* next = current_node->parent;
			current_node->parent = root;
			current_node = next;
		}

		return root->id;
	}

	template <class T>
	void disjoint_sets<T>::link(int id1, int id2)
	{
		// Already the same union.
		if (id1 == id2)
		{
			return;
		}

		node* set1 = nodes[id1];
		node* set2 = nodes[id2];

		// Determine which node represent the higher rank.
		if (set1->rank > set2->rank)
		{
			set2->parent = set1;
		}
		else if (set1->rank < set2->rank)
		{
			set1->parent = set2;
		}
		else
		{
			set2->parent = set1;

			// Increase the rank of a set to break the tie.
			++set1->rank;
		}
	}

	template <class T>
	int disjoint_sets<T>::get_sets()
	{
		return this->sets.size();
	}
}