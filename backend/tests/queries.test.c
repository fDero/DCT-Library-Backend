#include <gtest/gtest.h>
#include "tests_init.cpp"
#include "data_objects.h"
#include "queries.h"
#include "db_connection.h"
#include "stdbool.h"

db_conn_t* conn = NULL;
account_t* account1 = NULL;
account_t* account2 = NULL;
account_t* account3 = NULL;
account_t* account4 = NULL;
account_t* account5 = NULL;
account_t* account6 = NULL;

// ACCOUNTS:
//	  NAME     |  SURNAME    |  EMAIL                          |  ID
//   ----------------------------------------------------------------
// 	 'John'    |  'Smith'    |  'john.smith@example.com'     	 |  1
// 	 'Emma'    |  'Johnson'  |  'emma.johnson@example.com'     |  2
// 	 'William' |  'Brown'    |  'william.brown@example.com'    |  3
// 	 'Olivia'  |  'Williams' |  'olivia.williams@example.com'  |  4
// 	 'James'   |  'Jones'    |  'james.jones@example.com'      |  5
// 	 'Sophia'  |  'Davis'    |  'sophia.davis@example.com'     |  6


// BOOKS:
//   TITLE                      | AUTHOR               | PUBLISHER                   | RELEASE_DATE           |TOT.CP| ID
//   --------------------------------------------------------------------------------------------------------------------
// 	 'Harry Potter'             | 'J.K.Rowling'        | 'Bloomsbury'                | '1997-06-26 00:00:00'  | 10   | 1 
// 	 '1984'                     | 'G.Orwell'           | 'Secker & Warburg'          | '1949-06-08 00:00:00'  | 6    | 2 
// 	 'Karamazov Brothers'       | 'F.Dostoevskij'      | 'The Russian Messenger'     | '1980-11-01 00:00:00'  | 4    | 3
// 	 'Programming  Principles   | 'Bjarne Stroustrup'  | 'Pearson'                   | '2014-05-15 00:00:00'  | 3    | 4 
//    and Practices Using C++'  |                      |                             |                        |      |   
// 	 'The Lord of the Rings'    | 'John Ronald Reuel   | 'George Allen and Unwin     | '1954-07-29 00:00:00'  | 2    | 5
//                              |  Tolkien'            | (UK) Houghton Mifflin (US)' |                        |      | 
// 	 'The Hunger Games'         | 'Suzanne Collins'    | 'Scholastic Press'          | '2008-09-14 00:00:00'  | 7    | 6

// LOANS:
//  STARTING_TIME         | ENDING_TIME            | ACC.ID | BOOK ID | ID
//  ----------------------------------------------------------------------                                 
// 	'2024-04-02 00:00:00' | '2024-04-14 00:00:00'  | 1      | 1       | 1 
// 	'2024-04-05 00:00:00' | '2024-04-18 00:00:00'  | 2      | 2       | 2 
// 	'2024-04-08 00:00:00' | '2024-04-12 00:00:00'  | 3      | 4       | 3 
// 	'2024-04-10 00:00:00' | '2024-04-20 00:00:00'  | 3      | 2       | 4 
// 	'2024-04-11 00:00:00' | '2024-04-16 00:00:00'  | 4      | 5       | 5 
// 	'2024-04-12 00:00:00' | '2024-04-18 00:00:00'  | 5      | 1       | 6

#define EXPECT_ACCOUNT_EQUAL(_account1, _account2) \
    do { \
        EXPECT_STREQ((_account1)->name, (_account2)->name); \
        EXPECT_STREQ((_account1)->surname, (_account2)->surname); \
        EXPECT_STREQ((_account1)->email, (_account2)->email); \
        /* EXPECT_EQ((account1)->borrowed_books, (account2)->borrowed_books); */ \
        EXPECT_EQ((_account1)->account_id, (_account2)->account_id); \
    } while (0)

bool contains_account(const account_array_t* account_array, const account_t* account) {
    for (size_t i = 0; i < account_array->size; ++i) {
        const account_t* current_account = account_array->storage + i;
        if (strcmp(account->name, current_account->name) == 0 &&
            strcmp(account->surname, current_account->surname) == 0 &&
            strcmp(account->email, current_account->email) == 0 &&
						account->borrowed_books == current_account->borrowed_books &&
            account->account_id == current_account->account_id) {
            return true;
        }
    }
    return false;
}

TEST_F(Database, get_account_by_id){
  account_t* account = get_account_by_id(conn, 1);
  EXPECT_ACCOUNT_EQUAL(account, account1);
  account_destroy(account);
}

TEST_F(Database, get_account_by_email){
  account_t* account = get_account_by_email(conn, "emma.johnson@example.com");
  EXPECT_ACCOUNT_EQUAL(account, account2);
  account_destroy(account);
}

TEST_F(Database, get_accounts_by_book_id){
  account_array_t* accounts = get_accounts_by_book_id(conn, 1);
	EXPECT_TRUE(contains_account(accounts, account1));
	EXPECT_TRUE(contains_account(accounts, account5));
  account_array_destroy(accounts);
}