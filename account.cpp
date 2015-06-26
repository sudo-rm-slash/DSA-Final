#include "account.hpp"
#include "md5.hpp"

extern dsa::history history;

namespace dsa 
{
    account::account(std::string& ID, std::string& password): ID(new char[ID.size()+1]), money(0)
    {
        strcpy( this->ID , ID.c_str() );
        strncpy( this->md5_password , md5( password ) , MD5_BYTE_LEN );
    }

    bool account::authenticate(const char* password) {
        return strcmp( md5(password), this->md5_password ) == 0;
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
									this->transfer_history.begin(), 
									this->transfer_history.end(),
									mergee->history.begin(), 
									mergee->history.end(),
									history_union.begin()
								);
		hisotry_union.resize(hisotry_union_end - hisotry_union.begin()); 

		this->transfer_history = std::move( hisotry_union );

		return ( this->money += mergee->money );
	}

	bool account::search(account* transferee)
	{
		dsa::history.set_criteria( this->id );

		account* transferee = trie.find( ID );

		if( transferee != this )
		{
			std::vector<unsigned int> history_intersection( std::max(history.size(),transferee->history.size()) );
			auto history_intersection_end = std::set_intersection (
										this->transfer_history.begin(), 
										this->transfer_history.end(),
										transferee->history.begin(), 
										transferee->history.end(),
										history_intersection.begin()
									);
			history_intersection.resize(history_intersection_end - intersection.begin()); 

			for( auto transfer_record: history_intersection )
			{
				dsa::history[ transfer_record ];	
			}

			if( history_intersection.empty() )
				return false;
			else
				return true;
		}
		else
		{
			for( auto transfer_record: this->history )
			{
				dsa::history.print_self( transfer_record );
			}
		}
	}
};
