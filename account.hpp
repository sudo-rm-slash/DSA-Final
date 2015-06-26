#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_ 

#define MD5_BYTE 16 
// fixed length 16 byte ( 128 bits )
namespace dsa 
{
	struct record;
	using transfer_history = std::vector<record>;

    class account
    {

    public:

        account::account(const char* password);

        bool authenticate(const char* password);

        int deposit(int dollar);

        std::pair<bool,int> withdraw(int dollar);

		int transfer_history_lookup( const char* ID );

    private:

        int money;
        const char md5_password[ MD5_BYTE ]; 
		transfer_history* history;

    };

	struct record
	{

		bool operator < ( const record& rhs ) const
		{
			return timestamp < rhs.timestamp;
		}

		int to;
		int from;
		int dollar;
		int timestamp;
	};

};

#endif
