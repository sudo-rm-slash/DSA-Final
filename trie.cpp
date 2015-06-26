#include "trie.hpp"

account* dsa::trie::find(char* str)
{

	uint depth = 0;
	char key = 1;
	trie_node* node = &root;
	while (key != '\0')
	{
		key = str[depth++];
		node = node->children.find(key);
		if (node == nullptr)
		{
			return nullptr;
		}
	}
	return node->ptr_account;
}

void dsa::trie::insert(char* str, account* ptr_account)
{

	uint depth = 0;
	char key = 1;
	trie_node* parent;
	trie_node* node = &root;
	while (key != '\0')
	{
		key = str[depth++];
		parent = node;
		node = node->children.find(key);
		if (node == nullptr)
		{
			dsa::trie::trie_node* new_node = new dsa::trie::trie_node;
			parent->children.insert(key, new_node);
			node = new_node;
			//cerr << "Trie 35: " << new_node
			//Can do compression here.
		}
	}
	if (node->ptr_account == nullptr)
	{
		node->ptr_account = ptr_account;
	}

}

#define MAX_LENGTH 100
void dsa::trie::remove(char* str)
{

	trie_node* node_stack[MAX_LENGTH];
	uint depth = 0;
	char key = 1;
	trie_node* node = &root;
	while (key != '\0')
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
	node->ptr_account = nullptr;

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
