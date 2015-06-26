
#include <cstring>

namespace dsa 
{

    account::account(const char* password)
    {
        strncpy( md5_password , MD5( password ) , MD5_BYTE );
    }

    bool account::authenticate(const char* password)
    {
        return strcmp( MD5(password), md5_password ) == 0;
    }

    int account::deposit(int dollar)
    {
        return ( money += dollar );
    }

    std::pair<bool,int> account::withdraw(int dollar)
    {
        if( dollar < money )
            return std::pair<bool,int>( false, money );

        money -= dollar;

        return std::pair<bool,int>( true, money );
    }

	int lookup_transfers_history( const char* ID )
	{
		// transferee store the corresponding index of the ID owner
		int transferee = trie.find( ID )->index;

	}

	void merge_transfers_history( account& rhs )
	{
		auto merger = history.begin();
		auto mergee = rhs.history.begin();
	}
};
