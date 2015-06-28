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

std::list<const char*> dsa::trie::wildcard(const char* str)
{
	now_search_id += 1;
	traveler tr_root = this -> get_traveler();
	return wildcard_node(tr_root , str);
}

std::list<const char*> dsa::trie::wildcard_node( traveler& node, const char* str)
{
	std::list<const char*> list;
	traveler tr_node = node;

	if (*str == '*')
	{
		for (auto tr_child = tr_node.child_next(); tr_child.valid(); tr_child = tr_node.child_next())
		{

			if (*str == '*')
			{
				wildcard_node( tr_node, (str + 1) );				
				wildcard_node( tr_child, (str + 1) );
				wildcard_node( tr_child, str );

			}
		}
	}else if( *str == '?' ){

		for (auto tr_child = tr_node.child_next(); tr_child.valid(); tr_child = tr_node.child_next()){	       	
			list.merge( wildcard_node( tr_child, (str + 1) ) );
		}

	}
	else if (*str == '\0')
	{
		//std::cerr << "...at the leaf " << node.get_char() << std::endl;

		traveler leaf = tr_node.child('\0');
		if (leaf.valid() && leaf.get_search_id() < now_search_id )
		{
			leaf.update_search_id( now_search_id );
			
			//std::cerr << "...a valid leaf" << std::endl;

			std::list<char> buffer;
			traveler parent = tr_node;
			while( parent.get_char() != '!')
			{
				//std::cerr << "...current_char=" << parent.get_char() << std::endl;
				buffer.push_back( parent.get_char());
				parent = parent.parent();
			}

			char* username = new char[101];
			int i = 0;
			for(auto itr = buffer.rbegin(); itr != buffer.rend(); ++itr)
			{
				std::cerr << *itr ;
				username[i] = *itr;
			}
			std::cerr << std::endl;

			list.push_back(username);
		}
	}
	else
	{
		traveler tr_child = tr_node.child(*str);
		if (tr_child.valid())
		{
			list.merge(wildcard_node(tr_child, str + 1));
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

