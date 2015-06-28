#include "char_map.hpp"
#include <list>
//#include "link_list.hpp"

namespace dsa
{
	class trie
	{
	private:
		struct trie_node
		{
			char_map<trie_node*> children;
			int ptr_account = -1;
			trie_node* parent;
			char character = '!';
			
		};

		trie_node root;
		void wildcard_print_node( trie_node*node, char* str );
	public:
		class traveler{
		private:
			trie_node* node;			
			char_map<trie_node*>::iterator map_iterator;			
		public:

			traveler();
			traveler(trie_node*);
			traveler child_next();
			traveler child(char);
			trie_node* get_node();
			bool valid();//Check whether or not the node 
			int get_data(); //Only meaningful when at leave. Get the index of account.
			char get_char(); //TBA
			traveler parent(); //TBA		       

		};


		/*
		 * @brief Find the corresponding data with the string str.
		 * 
		 * @param str The string act as the key.
		 * @return If finded, return the data. Otherwise, if the key does not exist, return -1.
		 */
		int find(char* str);

		/*
		 * @brief Insert one key-data pair.
		 * 
		 * @param str The string acts as key.
		 * @param ptr_account The key.
		 * @return Void.
		 */
		void insert(char* str, int ptr_account);

		/*
		 * @brief Remove the key-data pair, if exist.
		 * 
		 * @param str The key of the data to be removed.
		 * @return Void
		 */
		void remove(char* str);

		void wildcard_print(char* str );
		std::list<int> wildcard(char* str );
		std::list<int> wildcard_node( traveler& node, char* str );
		traveler get_traveler();
	};
}
