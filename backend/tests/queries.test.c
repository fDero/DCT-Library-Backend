#include <gtest/gtest.h>
#include "tests_init.cpp"
#include "data_objects.h"
#include "queries.h"
#include "db_utils.h"
#include "stdbool.h"

db_conn_t* conn = NULL;
account_t* db_account_1 = NULL;
account_t* db_account_2 = NULL;
account_t* db_account_3 = NULL;
account_t* db_account_4 = NULL;
account_t* db_account_5 = NULL;
account_t* db_account_6 = NULL;

// ACCOUNTS:
//  ID 	|  NAME     |  SURNAME    |  EMAIL                          
//  ----------------------------------------------------------------
//  1  	| 'John'    |  'Smith'    |  'john.smith@example.com'       		-- db_account_1
//  2 	| 'Emma'    |  'Johnson'  |  'emma.johnson@example.com'         -- db_account_2
//  3 	| 'William' |  'Brown'    |  'william.brown@example.com'        -- db_account_3
//  4 	| 'Olivia'  |  'Williams' |  'olivia.williams@example.com'      -- db_account_4
//  5 	| 'James'   |  'Jones'    |  'james.jones@example.com'          -- db_account_5
//  6 	| 'Sophia'  |  'Davis'    |  'sophia.davis@example.com'         -- db_account_6


// BOOKS:
//   ID  | TITLE                      | AUTHOR               | PUBLISHER                   | GENRES                               | RELEASE_DATE           |TOT. CP.
//   --------------------------------------------------------------------------------------|------------------------------------------------------------------------
// 	 1   | 'Harry Potter'             | 'J.K.Rowling'        | 'Bloomsbury'                | 'Fantasy,Young adult literature,     | '1997-06-26 00:00:00'  | 10 
//       |                            |                      |                             |  Adventure fiction'                  |                        |
//       |                            |                      |                             |                                      |                        |
// 	 2   | '1984'                     | 'G.Orwell'           | 'Secker & Warburg'          | 'Fiction,Science fiction,Mystery'    | '1949-06-08 00:00:00'  | 6     
//       |                            |                      |                             |                                      |                        |
// 	 3   | 'Karamazov Brothers'       | 'F.Dostoevskij'      | 'The Russian Messenger'     | 'Fiction,Novel,Mystery,              | '1980-11-01 00:00:00'  | 4   
//       |                            |                      |                             |  Historical fiction,Literary fiction'|                        |
//       |                            |                      |                             |                                      |                        |
// 	 4   | 'Programming  Principles   | 'Bjarne Stroustrup'  | 'Pearson'                   | 'Education                           | '2014-05-15 00:00:00'  | 3     
//       |  and Practices Using C++'  |                      |                             |                                      |                        |      
//       |                            |                      |                             |                                      |                        | 
// 	 5   | 'The Lord of the Rings'    | 'John Ronald Reuel   | 'George Allen and Unwin     | 'Fantasy fiction,Adventure fiction'  | '1954-07-29 00:00:00'  | 2    
//       |                            |  Tolkien'            | (UK) Houghton Mifflin (US)' |                                      |                        |     
//       |                            |                      |                             |                                      |                        |
// 	 6   | 'The Hunger Games'         | 'Suzanne Collins'    | 'Scholastic Press'          | 'Science fiction,Adventure fiction,  | '2008-09-14 00:00:00'  | 7   
//       |                            |                      |                             |  Young adult literature'             |                        |

// LOANS:
//  ID | STARTING_TIME         | ENDING_TIME            | ACC.ID | BOOK ID
//  -----------------------------------------------------------------------
// 	1  | '2024-04-02 00:00:00' | '2024-04-14 00:00:00'  | 1      | 1        
// 	2  | '2024-04-05 00:00:00' | '2024-04-18 00:00:00'  | 2      | 2        
// 	3  | '2024-04-08 00:00:00' | '2024-04-12 00:00:00'  | 3      | 4        
// 	4  | '2024-04-10 00:00:00' | '2024-04-20 00:00:00'  | 3      | 2        
// 	5  | '2024-04-11 00:00:00' | '2024-04-16 00:00:00'  | 4      | 5        
// 	6  | '2024-04-12 00:00:00' | '2024-04-18 00:00:00'  | 5      | 1       

#define EXPECT_NULLPTR(a_pointer) \
    EXPECT_EQ(a_pointer, nullptr)

#define EXPECT_NOT_NULLPTR(a_pointer) \
    EXPECT_NE(a_pointer, nullptr)

#define EXPECT_ACCOUNT_EQUAL(actual_account, expected_account) \
    do { \
				EXPECT_NOT_NULLPTR(actual_account); \
        EXPECT_EQ((actual_account)->account_id, (expected_account)->account_id); \
        EXPECT_STREQ((actual_account)->name, (expected_account)->name); \
        EXPECT_STREQ((actual_account)->surname, (expected_account)->surname); \
        EXPECT_STREQ((actual_account)->email, (expected_account)->email); \
    } while (0)


bool contains_account(const account_array_t* account_array, const account_t* account) {
		if(account_array == nullptr) return false;
    for (size_t i = 0; i < account_array->size; ++i) {
        const account_t* current_account = account_array->storage + i;
        if (account->account_id == current_account->account_id &&
						strcmp(account->name, current_account->name) == 0 &&
            strcmp(account->surname, current_account->surname) == 0 &&
            strcmp(account->email, current_account->email) == 0) {
            return true;
        }
    }
    return false;
}

TEST_F(Database, get_account_by_id_1){
  account_t* account = get_account_by_id(conn, 1);
  EXPECT_ACCOUNT_EQUAL(account, db_account_1);
  account_destroy(account);
}

TEST_F(Database, get_account_by_id_2){
  account_t* account = get_account_by_id(conn, 4);
  EXPECT_ACCOUNT_EQUAL(account, db_account_4);
  account_destroy(account);
}

TEST_F(Database, get_account_by_id_3){
  account_t* account = get_account_by_id(conn, 999);
  EXPECT_NULLPTR(account);
}

TEST_F(Database, get_account_by_email_1){
  account_t* account = get_account_by_email(conn, "emma.johnson@example.com");
  EXPECT_ACCOUNT_EQUAL(account, db_account_2);
  account_destroy(account);
}

TEST_F(Database, get_account_by_email_2){
  account_t* account = get_account_by_email(conn, "sophia.davis@example.com");
  EXPECT_ACCOUNT_EQUAL(account, db_account_6);
  account_destroy(account);
}

TEST_F(Database, get_account_by_email_3){
  account_t* account = get_account_by_email(conn, "bidibi.bodibi@bu.com");
  EXPECT_NULLPTR(account);
}

TEST_F(Database, get_accounts_by_book_id_1){
  account_array_t* accounts = get_accounts_by_book_id(conn, 1);
	EXPECT_TRUE(contains_account(accounts, db_account_1));
	EXPECT_TRUE(contains_account(accounts, db_account_5));
  account_array_destroy(accounts);
}

TEST_F(Database, get_accounts_by_book_id_2){
  account_array_t* accounts = get_accounts_by_book_id(conn, 5);
	EXPECT_TRUE(contains_account(accounts, db_account_4));
  account_array_destroy(accounts);
}

TEST_F(Database, get_accounts_by_book_id_3){
  account_array_t* accounts = get_accounts_by_book_id(conn, 999);
	EXPECT_NULLPTR(accounts);
}