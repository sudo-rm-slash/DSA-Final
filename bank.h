#ifndef _BANK_H
#define _BANK_H 


/** 
 * @Function:  login
 * 
 * @Param:     id
 * @Param:     password
 * 
 * @Return:   status flag: 0 for failure, 1 for success, 3 for not found 
 */
int login( char* id, char* password );


/** 
 * @Function:  create
 * 
 * @Param:     id
 * @Param:     password
 * 
 * @Return:   status flag: 0 for failure( id already exist ), 1 for success
 */
int create( char* id, char* password );


/** 
 * @Function:  delete
 * 
 * @Param:     id
 * @Param:     password
 * 
 * @Return:   status flag: 0 for failure, 1 for success, 3 for not found 
 */
int _delete( char* id, char* password );


/** 
 * @Function:  merge
 * 
 * @Param:     id1
 * @Param:     password1
 * @Param:     id2
 * @Param:     password2
 * 
 * @Return:    status flag:  0 for failure, 1 for success.
 */
int merge( char* id1, char* password1, char* id2, char* password2 );

/** 
 * @Function:  deposit: deposit into last-login-id
 *
 * @Param:     dollar: the money to be deposited
 * 
 * @Return:    money in current account 
 */
uint64_t deposit( uint64_t dollar );


/** 
 * @Function:  withdraw: withdraw from last-login-id
 * 
 * @Param:     dollar: the money to be withdrawn
 * @Param:     remain: the money remained in account after the withdraw
 * 
 * @Return:    status flag:  0 for failure, 1 for success.
 */
int withdraw( uint64_t dollar, uint64_t* remain );

/** 
 * @Function:  transfer: transfer from last-login-id to some given id
 * 
 * @Param:     id: the receiver
 * @Param:     dollar: the money to be transferred  
 * @Param:     remain: the money remained in account after the transfer 
 * 
 * @Return:   status flag: 0 for failure, 1 for success, 3 for not found 
 */
int transfer( char* id, uint64_t dollar, uint64_t remain );

/** 
 * @Function:  find
 * 
 * @Param:     pattern
 */
void find( char* pattern );

/** 
 * @Function:  search
 * 
 * @Param:     id
 * 
 * @Return:    status flag: 0 for not found, 1 for success, 2 for no record
 */
int search( char* id );



#endif
