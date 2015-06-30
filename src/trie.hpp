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
			
			//Get the pointer of the node where the traveler is. 
			trie_node* get_node();

		public:
			traveler();
			
			//Note: if an invalid node is insert, SEGMENTATION FAULT may happen.
			traveler(trie_node*);

			//If it is first time used to a parent travel object, it will return the first child traveler.
			//And the second time will return the second child of the child.
			//If there is no anymore child, it will return an invalid child.
			traveler child_next();

			//Find the child of a parent node which is of the index.
			//If such child is not found, it will return an invalid child.
			traveler child(char);

			//Check whether or not the node the traveler at is valid.
			bool valid();			
			
			//When traveler is at the leaf, it will return the data the leaf store.
			int get_data();		 

			//Get the character of the node the traveler at.
			char get_char(); 		

			//TBA
			traveler parent(); 	       

			//When traveler is at the leaf, it will return the search id of the leaf.
			//It is used with update_search_id to prevent the wildcard from duplicate output. 
			unsigned int get_search_id();

			//When traveler is at the leaf, it will update the search id of the leaf.
			//Whenever the leaf is searched, it should use it to sync its search_id with now_search_id
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
		void wildcard_node( std::vector<unsigned int>& result, traveler& node, const char* str);
		
	};
}
