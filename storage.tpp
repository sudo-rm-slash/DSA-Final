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
T* dsa::storage<T>::insert(const T& item)
{
	this->container.push_back(item);
	return std::addressof(this->container.data()[this->container.size() - 1]);
}

template <class T>
T& dsa::storage<T>::operator[](const int& account_index)
{
	return this->container.data()[account_index];
}