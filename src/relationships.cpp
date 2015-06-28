#include "relationships.hpp"


dsa::relationships::relationships()
{

}

dsa::relationships::~relationships()
{

}

unsigned int dsa::relationships::add_user(unsigned int index)
{
	return container.make_set(index);
}

unsigned int dsa::relationships::find_root(unsigned int id) const
{
	return container.find_root(id);
}

void dsa::relationships::link_users(unsigned int user1, unsigned int user2)
{
	container.link(user1, user2);
}