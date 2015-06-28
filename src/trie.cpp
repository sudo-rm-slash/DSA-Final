#include "trie.hpp"

dsa::trie::trie(){
	now_search_id = 0;
}

int dsa::trie::find(const char* str)
{
	unsigned int depth = 0;
	char key;
	trie_node* node = &root;

	do
	{
		key = str[depth++];
		node = node->children.find(key);

		if (node == nullptr)
		{
			return -1;
		}
	}
	while (key != '\0');

	return node->ptr_account;
}

void dsa::trie::insert(const char* str, const int ptr_account)
{
	unsigned int depth = 0;
	char key;
	trie_node* parent;
	trie_node* node = &root;
	do
	{
		key = str[depth++];
		parent = node;
		node = node->children.find(key);
		if (node == nullptr)
		{
			dsa::trie::trie_node* new_node = new dsa::trie::trie_node;
			parent->children.insert(key, new_node);
			node = new_node;
			node->parent = parent;
		}
		node -> character = key;
	}
	while (key != '\0');

	if (node->ptr_account == -1)
	{
		node->ptr_account = ptr_account;
	}

}

#define MAX_LENGTH 100
void dsa::trie::remove(const char* str)
{
	trie_node* node_stack[MAX_LENGTH];
	unsigned int depth = 0;
	char key;
	trie_node* node = &root;

	do
	{
		node_stack[depth] = node;
		key = str[depth];
		depth += 1;
		node = node->children.find(key);

		if (node == nullptr)
		{
			return;
		}
	}
	while (key != '\0');

	node->ptr_account = -1;

	depth --;

	node = node_stack[depth];

	while (depth > 0 && node->children.get_size() == 0)
	{
		depth -= 1;
		node = node_stack[depth];
		trie_node* empty_node = node->children.remove(str[depth]);
		delete empty_node;
	}
}

void  dsa::trie::wildcard(std::vector<unsigned int>&result, const char* str)
{
	now_search_id += 1;
	traveler tr_root = this -> get_traveler();
        wildcard_node(result, tr_root , str);
}

void dsa::trie::wildcard_node( std::vector<int>&result, traveler& tr_node, const char* str)
{

	switch( *str ){
        case '*':
	{
		for (auto tr_child = tr_node.child_next(); tr_child.valid(); tr_child = tr_node.child_next())
		{

			if (*str == '*')
			{
				wildcard_node( list, tr_node, (str + 1) );				
				wildcard_node( list, tr_child, (str + 1) );
				wildcard_node( list, tr_child, str );

			}
		}
		break;
	}
	case '?':
        {

		for (auto tr_child = tr_node.child_next(); tr_child.valid(); tr_child = tr_node.child_next()){	       	
		        wildcard_node( list, tr_child, (str + 1) );
		}
		break;
	}
	case '\0':
	{

		traveler leaf = tr_node.child('\0');
		if (leaf.valid() && leaf.get_search_id() < now_search_id )
		{
			leaf.update_search_id( now_search_id );
			
			list.push_back( leaf.get_data() );

			// std::list<char> buffer;
			// traveler parent = tr_node;
			// while( parent.get_char() != '!')
			// {
			// 	buffer.push_back( parent.get_char());
			// 	parent = parent.parent();
			// }

			// char* username = new char[101];
			// int i = 0;
			// for(auto itr = buffer.rbegin(); itr != buffer.rend(); ++itr)
			// {
			// 	std::cerr << *itr ;
			// 	username[i] = *itr;
			// }
			// std::cerr << std::endl;

		}
	}
	default:
	{
		traveler tr_child = tr_node.child(*str);
		if (tr_child.valid())
			{
				wildcard_node(list, tr_child, ( str + 1 ));
			}
	
	}
	}

	return list;
}

dsa::trie::traveler::traveler()
{
	node = nullptr ;
}

dsa::trie::traveler::traveler(trie_node* node)
	: map_iterator(node -> children.get_iterator())
{
	this -> node = node;
}

dsa::trie::traveler dsa::trie::traveler::child_next()
{
	trie_node*node = map_iterator.get_data();
	map_iterator.next();
	if (node == nullptr)
	{
		return traveler();
	}
	return traveler(node);
}

dsa::trie::traveler dsa::trie::traveler::child(char index)
{
	trie_node* next_node = node -> children.find(index);
	return traveler(next_node);
}

dsa::trie::trie_node* dsa::trie::traveler::get_node()
{
	return node;
}

bool dsa::trie::traveler::valid()
{
	if (node == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int dsa::trie::traveler::get_data()
{
	if (this -> valid())
	{
		return this -> node -> ptr_account;
	}
	else
	{
		return -1;
	}
}

dsa::trie::traveler dsa::trie::traveler::parent()
{
	return traveler(this -> get_node() -> parent);
}

char dsa::trie::traveler::get_char()
{
	return this -> get_node() -> character;
}

unsigned int dsa::trie::traveler::get_search_id()
{
	return this -> get_node() -> search_id;
}

void  dsa::trie::traveler::update_search_id(unsigned int now_search_id)
{
	this -> get_node() -> search_id = now_search_id;
}


dsa::trie::traveler dsa::trie::get_traveler()
{
	return traveler(&root);
}

