#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_ 

#define MD5_BYTE 16 
// fixed length 16 byte ( 128 bits )

namespace dsa 
{

    class account
    {

    public:

		account():money(0){}

        account(const char* password);

        bool authenticate(const char* password);

        int deposit(int dollar);

        std::pair<bool,int> withdraw(int dollar);

		int merge(account* mergee);

		int lookup_transfers_history( const char* ID );


    private:


        int money;
        char md5_password[ MD5_BYTE ]; 
		std::vector<unsigned int> history;

    };


};

#endif
