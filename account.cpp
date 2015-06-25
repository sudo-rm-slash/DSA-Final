
#include <cstring>

namespace dsa 
{

    account::account( const char* password )
    {
        strncpy( md5_password , MD5( password ) , MD5_BYTE );
    }
    int check_password(const char* password)
    {
        return strcmp( MD5(password), md5_password ) == 0;
    }

    void deposit(int dollar)
    {
        money += dollar;
    }

    std::pair<bool,int> withdraw(int dollar)
    {
        if( dollar < money )
            return std::pair<bool,int>( false, money );

        money -= dollar;

        return std::pair<bool,int>( true, money );
    }

};
