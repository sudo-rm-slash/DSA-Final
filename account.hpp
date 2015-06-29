#ifndef __ACCOUNT_HPP__
#define __ACCOUNT_HPP__

#define MD5_BYTE_LEN 33 // Fixed length 33 byte 

#include <utility>      // std::pair
#include <cstring>      // std::strncpy, std::strcmp
#include <vector>       // std::vector

#include "md5.hpp"      // md5

#define FIELD_SIZE  101

namespace dsa
{
	class account
	{
	private:
        char password[FIELD_SIZE];    // MD5 encoded password.

        int money;                    // Amount of cash stored in this account.

		std::vector<int> related_history;    // A list of indices, showing which history entry it has participated in.
	
    public:
        account(const char* password);
        virtual ~account();

        /*
         * @brief Authenticate a non-encoded password with the one stored here.
         *
         * @param password A non-encoded password to compare with.
         * @return Indicate whether the password is correct or not.
         */
        bool  authenticate(const char* password) const;
	   
        /*
         * @brief Setup the account with designated info.
         *
         * @param password The password to assign.
         * @return Void.
         */
        void set_account(const char* password);
        
        /*
         * @brief Wipe the account, aka, the reset the account to contain no cash.
         *
         * @return Return the amount of cash before the wipe.
         */
        int wipe_account();

        /*
         * @brief Deposit money to this account.
         *
         * @param value The amount of cash to deposit in this account.
         * @return The new statistic of the cash in this account.
         */
		int deposit(int value);

        /*
         * @brief Withdraw money from this account.
         *
         * @param value The amount of cash to withdraw from this account.
         * @return The new statistic of the cash in this account, and whether this 
         *         operation succeed or not.
         */
        std::pair<bool, int> withdraw(int value);

        /*
         * @brief Get the amount of cash in this account.
         *
         * @return Return the amount of cash in this account.
         */
		int get_money() const;

        /*
         * @brief Get the related transaction history with this account.
         *
         * @return Return the related history indices in vector.
         */
        std::vector<int>& get_related_history();

        /*
         * @brief Add a related history with this account.
         *
         * @return Voids.
         */
         void add_related_history(const int& user_index);

        /*
         * @brief Set the related history with this account using a pre-defined vector.
         *
         * @return Void.
         */
         void set_related_history(std::vector<int>&);
	};
}

#endif
