#include <algorithm>
#include <cstring>

#include "md5.hpp"
#include "account.hpp"

namespace dsa 
{

    account::account(const char* password)
    {
        strncpy( this->md5_password , MD5( password ) , MD5_BYTE );
    }

    bool account::authenticate(const char* password)
    {
        return strcmp( MD5(password), this->md5_password ) == 0;
    }

    int account::deposit(int dollar)
    {
        return ( this->money += dollar );
    }

    std::pair<bool,int> account::withdraw(int dollar)
    {
        if( dollar < this->money )
            return std::pair<bool,int>( false, this->money );

        this->money -= dollar;

        return std::pair<bool,int>( true, this->money );
    }

	int merge(account* mergee)
	{
		std::vector<unsigned int> history_union( max(history.size(),transferee->history );
		auto history_union_end = std::set_union (
									this->history.begin(), 
									this->history.end(),
									mergee->history.begin(), 
									mergee->history.end(),
									history_union.begin()
								);
		hisotry_union.resize(hisotry_union_end - hisotry_union.begin()); 

		this->history = std::move( hisotry_union );

		return ( this->money += mergee->money );
	}

	int account::lookup_transfers_history( const char* ID )
	{
		account* transferee = trie.find( ID );

		if( transferee != this )
		{
			std::vector<unsigned int> history_intersection( std::max(history.size(),transferee->history.size()) );
			auto history_intersection_end = std::set_intersection (
										this->history.begin(), 
										this->history.end(),
										transferee->history.begin(), 
										transferee->history.end(),
										history_intersection.begin()
									);
			history_intersection.resize(history_intersection_end - intersection.begin()); 

			for( auto transfer_record: history_intersection )
			{
				dsa::history.print( transfer_record );	
			}
		}
		else
		{
			for( auto transfer_record: this->history )
			{
				dsa::history.print( transfer_record );
			}
		}
	}

};
