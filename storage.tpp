template <class T>
dsa::storage::storage()
{
	// Initialize the vector.
	this->container.clear();
}

template <class T>
dsa::storage::~storage()
{
	// Wipe out the private variable.
	this->container.clear();
}

template <class T>
T* dsa::storage::insert(const T& item) const
{
	container.push_back(item);
	return container.data() + container.size() - 1;
}

template <class T>
void dsa::storage::operator[](const int& account_index)
{
	
}