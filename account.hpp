

#define MD5_BYTE 16 
// fixed length 16 byte ( 128 bits )
namespace dsa 
{
    class account
    {

    public:

        account::account(const char* password);

        int check_password(const char* password);

        void deposit(int dollar);

        std::pair<bool,int> withdraw(int dollar);

    private:

        int money;
        const char md5_password[ MD5_BYTE ]; 

    };

}
