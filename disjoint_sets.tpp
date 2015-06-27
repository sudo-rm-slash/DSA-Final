template <class T>
dsa::disjoint_sets<T>::disjoint_sets()
{
	// Initialize the vector.
	this->sets.clear();

	// Reset the element counter and set counter.
	this->element_count = this->set_count = 0;
}

template <class T>
dsa::disjoint_sets<T>::~disjoint_sets()
{
	// Delete all the nodes in this container.
	for (int i = 0; i < element_count; i++)
	{
		delete this->sets[i];
	}

	// Wipe out all the private variables.
	this->sets.clear();
	this->element_count = this->set_count = 0;
}

template <class T>
int dsa::disjoint_sets<T>::make_set(const T data)
{
	sets.insert(sets.end(), 1, (node*)NULL);

	int index = this->element_count;
	this->sets[index] = new node();		// Generate new node.
	this->sets[index]->parent = NULL;	// No further parent node exists.
	this->sets[index]->id = index;		// Generated ID of current node.
	this->sets[index]->rank = 0;		// Default ranking.
	this->sets[index]->data = data;		// Data stored in this node.

	// Update element counts.
	++(this->element_count);

	// Return the generated index.
	return this->sets[index]->id;
}

template <class T>
int dsa::disjoint_sets<T>::find_root(int id) const
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
void dsa::disjoint_sets<T>::link(int id1, int id2)
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
		++(set1->rank);
	}

	// Since two sets are linked together, one less set to maintain.
	--(this->set_count);
}

template <class T>
T& dsa::disjoint_sets<T>::get_data(int id) const
{
	return this->sets[id]->data;
}

template <class T>
int dsa::disjoint_sets<T>::get_sets()
{
	return this->set_count;
}

template <class T>
int dsa::disjoint_sets<T>::get_elements()
{
	return this->element_count;
}
