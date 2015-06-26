template <class T>
dsa::storage<T>::storage()
{
	// Initialize the vector.
	this->container.clear();
}

template <class T>
dsa::storage<T>::~storage()
{
	// Wipe out the private variable.
	this->container.clear();
}

template <class T>
T* dsa::storage<T>::insert(const T& item) const
{
	container.push_back(item);
	return container.data() + container.size() - 1;
}

template <class T>
T& dsa::storage<T>::operator[](const int& account_index)
{
	return container.data()[account_index];
}