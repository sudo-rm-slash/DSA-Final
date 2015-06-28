#include <exception>
#include <list>				// std::list
#include <iostream>			// std::cerr
#include <vector>
#include "char_map.hpp"

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
			unsigned int search_id = 0;
		};

		trie_node root;
		unsigned int now_search_id;		
	public:
		class traveler
		{
		private:
			trie_node* node;
			char_map<trie_node*>::iterator map_iterator;

		public:
			traveler();
			traveler(trie_node*);

			traveler child_next();
			traveler child(char);
			trie_node* get_node();
			bool valid();			//Check whether or not the node
			int get_data();			//Only meaningful when at leave. Get the index of account.
			char get_char(); 		//TBA
			traveler parent(); 		//TBA
			unsigned int get_search_id();
			void update_search_id(unsigned int now_search_id);

		};
		
		trie();
		/*
		 * @brief Find the corresponding data with the string str.
		 *
		 * @param str The string act as the key.
		 * @return If finded, return the data. Otherwise, if the key does not exist, return -1.
		 */
		int find(const char* str);

		/*
		 * @brief Insert one key-data pair.
		 *
		 * @param str The string acts as key.
		 * @param ptr_account The key.
		 * @return Void.
		 */
		void insert(const char* str, const int account_index);

		/*
		 * @brief Remove the key-data pair, if exist.
		 *
		 * @param str The key of the data to be removed.
		 * @return Void
		 */
		void remove(const char* str);

		/*
		 * @brief EXPLANATIONS
		 *
		 * @param VAR EXPLANATIONS
		 * @return RETURN
		 */
		void wildcard(std::vector<unsigned int>&result, const char* str);
		
		/*
		 * @brief EXPLANATIONS
		 *
		 * @param VAR EXPLANATIONS
		 * @return RETURN
		 */
		traveler get_traveler();

	private:
		/*
		 * @brief EXPLANATIONS
		 *
		 * @param VAR EXPLANATIONS
		 * @return RETURN
		 */
		void wildcard_node( std::vector<int>& result, traveler& node, const char* str);
		
	};
}
