#include <vector>		// std::vector

#include "disjoint_sets.hpp"

namespace dsa
{
	template <class T>
	disjoint_sets<T>::disjoint_sets()
	{
		// Initialize the vector.
		this->sets.clear();

		// Reset the element counter and set counter.
		this->element_count = this->set_count = 0;
	}

	template <class T>
	disjoint_sets<T>::~disjoint_sets()
	{
		// Delete all the nodes in this container.
		for(int i = 0; i < element_count; i++)
			delete this->sets[i];

		// Wipe out all the private variables.
		this->sets.clear();
		this->element_count = this->set_count = 0;
	}

	template <class T>
	void disjoint_sets<T>::make_set(int num_to_add)
	{
		sets.insert(sets.end(), num_to_add, (node*)NULL);
		for(int i = this->element_count; i < this->element_count + num_to_add; i++)
		{
			this->sets[i] = new node();
			this->sets[i]->parent = NULL;
			this->sets[i]->index = i;
			this->sets[i]->rank = 0;
		}

		// Update element counts.
		this->element_count += num_to_add;
	}

	template <class T>
	int disjoint_sets<T>::find_set(int id) const
	{
		node* current_node;

		// Find the root element that represents the set which id belongs to.
		current_node = this->sets[id];
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

		node* set1 = this->sets[id1];
		node* set2 = this->sets[id2];

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

		// Since two sets are linked together, one less set to maintain.
		--this->set_count;
	}

	template <class T>
	int disjoint_sets<T>::get_sets()
	{
		return this->set_count;
	}

	template <class T>
	int disjoint_sets<T>::get_elements()
	{
		return this->element_count;
	}
}