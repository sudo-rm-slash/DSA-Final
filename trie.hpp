#include "char_map.hpp"

namespace dsa
{
	class trie
	{
	private:
		struct trie_node
		{
			char_map<trie_node*> children;
			account* ptr_account = nullptr;
		};

		trie_node root;

	public:
		/*
		 * @brief EXPLANATION
		 * 
		 * @param str EXPLANATION
		 * @return EXPLANATION
		 */
		account* find(char* str);

		/*
		 * @brief EXPLANATION
		 * 
		 * @param str EXPLANATION
		 * @param ptr_account EXPLANATION
		 * @return Void.
		 */
		void insert(char* str, account* ptr_account);

		/*
		 * @brief EXPLANATION
		 * 
		 * @param str EXPLANATION
		 * @return Void
		 */
		void remove(char* str);
	};
}
