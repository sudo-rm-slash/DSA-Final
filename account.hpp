#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_ 

#define MD5_BYTE 16 
// fixed length 16 byte ( 128 bits )

namespace dsa 
{
	class transfers_history;


    class account
    {

    public:

		account(){}

        account(const char* password);

        bool authenticate(const char* password);

        int deposit(int dollar);

        std::pair<bool,int> withdraw(int dollar);

		int lookup_transfers_history( const char* ID );

		void merge_transfers_history( account& rhs );

    private:

        int money;
        const char md5_password[ MD5_BYTE ]; 
		transfers_history* history;

    };

	struct record
	{
		enum t_transfer { TO, FROM };	

		record(){}

		bool operator < ( const record& rhs ) const
		{
			return timestamp < rhs.timestamp;
		}

		t_transfer transfer_type;
		int dollar;
		int timestamp;
	}

	struct transfers_history
	{
		bool operator == ( const record& rhs ) const
		{
			return  owner[transferee] == owner[rhs.transferee] ;
		}

		int transferee;
		std::vector<record> records;
	};

};

#endif
