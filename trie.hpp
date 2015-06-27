#include <exception>

#include "art.hpp"

namespace dsa
{
	// A wrapper for art.
	class trie
	{
	private:
		art_tree* root;
	public:
		trie()
		{
			root = new art_tree;
			if (art_tree_init(root) != 0)
			{
				throw std::runtime_error("Runtime error: Failed to initialize ART root node.\n");
			}
		}

		~trie()
		{
			if (art_tree_destroy(root) != 0)
			{
				throw std::runtime_error("Runtime error: Failed to destroy ART.\n");
			}
			delete root;
		}

		/*
		 * @brief Find the corresponding data with the string str.
		 *
		 * @param str The string act as the key.
		 * @return If finded, return the data. Otherwise, if the key does not exist, return -1.
		 */
		int find(const char* str)
		{
			int* result = (int*)art_search(root, reinterpret_cast<const unsigned char*>(str), std::strlen(str));
			if (result == NULL)
			{
				return -1;
			}
			else
			{
				return *result;
			}
		}

		/*
		 * @brief Insert one key-data pair.
		 *
		 * @param str The string acts as key.
		 * @param ptr_account The key.
		 * @return Void.
		 */
		void insert(const char* str, int account_index)
		{
			int* index_to_store = new int;
			*index_to_store = account_index;

			std::cerr << "...TRIE >>> insert()" << std::endl;
			art_insert(root, reinterpret_cast<const unsigned char*>(str), std::strlen(str), index_to_store);
		}

		/*
		 * @brief Remove the key-data pair, if exist.
		 *
		 * @param str The key of the data to be removed.
		 * @return Void
		 */
		void remove(const char* str)
		{
			art_delete(root, reinterpret_cast<const unsigned char*>(str), std::strlen(str));
		}
	};
}
