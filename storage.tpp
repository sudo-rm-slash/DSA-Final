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
T* dsa::storage<T>::insert(const char* username, const char* password)
{
	//std::cerr << "...start insert" << std::endl;

	//this->container.push_back(std::move(item));
	this->container.emplace(this->container.end(), username, md5(password));
	//std::cerr << "...push_back duplicate item" << std::endl;

	return &(this->container.back());
}

template <class T>
T& dsa::storage<T>::operator[](const int& account_index)
{
	return this->container[account_index];
}