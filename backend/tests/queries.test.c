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

book_t* db_book_1 = NULL;
book_t* db_book_2 = NULL;
book_t* db_book_3 = NULL;
book_t* db_book_4 = NULL;
book_t* db_book_5 = NULL;
book_t* db_book_6 = NULL;

loan_t* db_loan_1 = NULL;
loan_t* db_loan_2 = NULL;
loan_t* db_loan_3 = NULL;
loan_t* db_loan_4 = NULL;
loan_t* db_loan_5 = NULL;
loan_t* db_loan_6 = NULL;

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
// 	 1   | 'Harry Potter'             | 'J.K.Rowling'        | 'Bloomsbury'                | 'Fantasy,Young adult literature,     | '1997-06-26 00:00:00'  | 10         --db_book_1
//       |                            |                      |                             |  Adventure fiction'                  |                        |
//       |                            |                      |                             |                                      |                        |
// 	 2   | '1984'                     | 'G.Orwell'           | 'Secker & Warburg'          | 'Fiction,Science fiction,Mystery'    | '1949-06-08 00:00:00'  | 6          --db_book_2  
//       |                            |                      |                             |                                      |                        |
// 	 3   | 'Karamazov Brothers'       | 'F.Dostoevskij'      | 'The Russian Messenger'     | 'Fiction,Novel,Mystery,              | '1980-11-01 00:00:00'  | 4          --db_book_3
//       |                            |                      |                             |  Historical fiction,Literary fiction'|                        |
//       |                            |                      |                             |                                      |                        |
// 	 4   | 'Programming  Principles   | 'Bjarne Stroustrup'  | 'Pearson'                   | 'Education'                          | '2014-05-15 00:00:00'  | 3          --db_book_4
//       |  and Practices Using C++'  |                      |                             |                                      |                        |      
//       |                            |                      |                             |                                      |                        | 
// 	 5   | 'The Lord of the Rings'    | 'John Ronald Reuel   | 'George Allen and Unwin     | 'Fantasy fiction,Adventure fiction'  | '1954-07-29 00:00:00'  | 2          --db_book_5
//       |                            |  Tolkien'            | (UK) Houghton Mifflin (US)' |                                      |                        |     
//       |                            |                      |                             |                                      |                        |
// 	 6   | 'The Hunger Games'         | 'Suzanne Collins'    | 'Scholastic Press'          | 'Science fiction,Adventure fiction,  | '2008-09-14 00:00:00'  | 7          --db_book_6
//       |                            |                      |                             |  Young adult literature'             |                        |

// LOANS:
//  ID | STARTING_TIME         | ENDING_TIME            | ACC.ID | BOOK ID
//  -----------------------------------------------------------------------
// 	1  | '2024-04-02 00:00:00' | '2024-04-14 00:00:00'  | 1      | 1         --db_loan_1
// 	2  | '2024-04-05 00:00:00' | '2024-04-18 00:00:00'  | 2      | 2         --db_loan_2
// 	3  | '2024-04-08 00:00:00' | '2024-04-12 00:00:00'  | 3      | 4         --db_loan_3
// 	4  | '2024-04-10 00:00:00' | '2024-04-20 00:00:00'  | 3      | 2         --db_loan_4
// 	5  | '2024-04-11 00:00:00' | '2024-04-16 00:00:00'  | 4      | 5         --db_loan_5
// 	6  | '2024-04-12 00:00:00' | '2024-04-18 00:00:00'  | 5      | 1         --db_loan_6

#define EXPECT_NULLPTR(a_pointer) \
    EXPECT_EQ(a_pointer, nullptr)

#define ASSERT_NOT_NULLPTR(a_pointer) \
    ASSERT_NE(a_pointer, nullptr)

#define EXPECT_ACCOUNT_EQUAL(actual_account, expected_account) \
    do { \
        EXPECT_EQ((actual_account)->account_id, (expected_account)->account_id); \
        EXPECT_STREQ((actual_account)->name, (expected_account)->name); \
        EXPECT_STREQ((actual_account)->surname, (expected_account)->surname); \
        EXPECT_STREQ((actual_account)->email, (expected_account)->email); \
    } while (0)

#define EXPECT_BOOK_EQUAL(actual_book, expected_book) \
    do { \
        EXPECT_EQ((actual_book)->book_id, (expected_book)->book_id); \
        EXPECT_STREQ((actual_book)->title, (expected_book)->title); \
        EXPECT_STREQ((actual_book)->author, (expected_book)->author); \
        EXPECT_STREQ((actual_book)->publisher, (expected_book)->publisher); \
        EXPECT_STREQ((actual_book)->genres, (expected_book)->genres); \
        EXPECT_TRUE(timestamp_equal(&(actual_book)->release_date, &(expected_book)->release_date)); \
        EXPECT_EQ((actual_book)->total_copies, (expected_book)->total_copies); \
    } while (0)


#define EXPECT_LOAN_EQUAL(actual_loan, expected_loan) \
    do { \
        EXPECT_EQ((actual_loan)->loan_id, (expected_loan)->loan_id); \
        EXPECT_TRUE(timestamp_equal(&(actual_loan)->starting_time, &(expected_loan)->starting_time)); \
        EXPECT_TRUE(timestamp_equal(&(actual_loan)->ending_time, &(expected_loan)->ending_time)); \
        EXPECT_EQ((actual_loan)->account_id, (expected_loan)->account_id); \
        EXPECT_EQ((actual_loan)->book_id, (expected_loan)->book_id); \
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

bool contains_book(const book_array_t* book_array, const book_t* book) {
		if(book_array == nullptr) return false;
    for (size_t i = 0; i < book_array->size; ++i) {
        const book_t* current_book = book_array->storage + i;
        if (book->book_id == current_book->book_id &&
						strcmp(book->title, current_book->title) == 0 &&
            strcmp(book->author, current_book->author) == 0 &&
            strcmp(book->publisher, current_book->publisher) == 0 &&
            strcmp(book->genres, current_book->genres) == 0 &&
						timestamp_equal(&(book)->release_date, &(current_book)->release_date) &&
						book->total_copies == current_book->total_copies) {
            return true;
        }
    }
    return false;
}

bool contains_loan(const loan_array_t* loan_array, const loan_t* loan) {
		if(loan_array == nullptr) return false;
    for (size_t i = 0; i < loan_array->size; ++i) {
        const loan_t* current_loan = loan_array->storage + i;
        if (loan->loan_id == current_loan->loan_id &&
						timestamp_equal(&(loan)->starting_time, &(current_loan)->starting_time) &&
						timestamp_equal(&(loan)->ending_time, &(current_loan)->ending_time) &&
						loan->account_id == current_loan->account_id &&
						loan->book_id == current_loan->book_id) {
            return true;
        }
    }
    return false;
}

TEST_F(Database, get_accounts_1){
  account_array_t* accounts = get_accounts(conn, 1);
	ASSERT_NOT_NULLPTR(accounts);
	EXPECT_EQ(accounts->size, 1);
  if(accounts != NULL) account_array_destroy(accounts);
}

TEST_F(Database, get_accounts_2){
  account_array_t* accounts = get_accounts(conn, 4);
	ASSERT_NOT_NULLPTR(accounts);
	EXPECT_EQ(accounts->size, 4);
  if(accounts != NULL) account_array_destroy(accounts);
}

TEST_F(Database, get_accounts_3){
  account_array_t* accounts = get_accounts(conn, DB_GET_ALL);
	ASSERT_NOT_NULLPTR(accounts);
	EXPECT_EQ(accounts->size, 6);
  if(accounts != NULL) account_array_destroy(accounts);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_account_by_id_1){
  account_t* account = get_account_by_id(conn, 1);
	ASSERT_NOT_NULLPTR(account);
  EXPECT_ACCOUNT_EQUAL(account, db_account_1);
  if(account != NULL) account_destroy(account);
}

TEST_F(Database, get_account_by_id_2){
  account_t* account = get_account_by_id(conn, 4);
	ASSERT_NOT_NULLPTR(account);
  EXPECT_ACCOUNT_EQUAL(account, db_account_4);
  if(account != NULL) account_destroy(account);
}

TEST_F(Database, get_account_by_id_3){
  account_t* account = get_account_by_id(conn, 9999);
  EXPECT_NULLPTR(account);
  if(account != NULL) account_destroy(account);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_account_by_email_1){
  account_t* account = get_account_by_email(conn, "emma.johnson@example.com");
	ASSERT_NOT_NULLPTR(account);
  EXPECT_ACCOUNT_EQUAL(account, db_account_2);
  if(account != NULL) account_destroy(account);
}

TEST_F(Database, get_account_by_email_2){
  account_t* account = get_account_by_email(conn, "sophia.davis@example.com");
	ASSERT_NOT_NULLPTR(account);
  EXPECT_ACCOUNT_EQUAL(account, db_account_6);
  if(account != NULL) account_destroy(account);
}

TEST_F(Database, get_account_by_email_3){
  account_t* account = get_account_by_email(conn, "biddibi.boddibi@bu.com");
  EXPECT_NULLPTR(account);
  if(account != NULL) account_destroy(account);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_account_by_loan_id_1){
  account_t* account = get_account_by_loan_id(conn, 1);
	ASSERT_NOT_NULLPTR(account);
  EXPECT_ACCOUNT_EQUAL(account, db_account_1);
  if(account != NULL) account_destroy(account);
}

TEST_F(Database, get_account_by_loan_id_2){
  account_t* account = get_account_by_loan_id(conn, 4);
	ASSERT_NOT_NULLPTR(account);
  EXPECT_ACCOUNT_EQUAL(account, db_account_3);
  if(account != NULL) account_destroy(account);
}

TEST_F(Database, get_account_by_loan_id_3){
  account_t* account = get_account_by_loan_id(conn, 9999);
  EXPECT_NULLPTR(account);
  if(account != NULL) account_destroy(account);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_accounts_by_book_id_1){
  account_array_t* accounts = get_accounts_by_book_id(conn, 1);
	ASSERT_NOT_NULLPTR(accounts);
	EXPECT_EQ(accounts->size, 2);
	EXPECT_TRUE(contains_account(accounts, db_account_1));
	EXPECT_TRUE(contains_account(accounts, db_account_5));
  if(accounts != NULL) account_array_destroy(accounts);
}

TEST_F(Database, get_accounts_by_book_id_2){
  account_array_t* accounts = get_accounts_by_book_id(conn, 5);
	ASSERT_NOT_NULLPTR(accounts);
	EXPECT_EQ(accounts->size, 1);
	EXPECT_TRUE(contains_account(accounts, db_account_4));
  if(accounts != NULL) account_array_destroy(accounts);
}

TEST_F(Database, get_accounts_by_book_id_3){
  account_array_t* accounts = get_accounts_by_book_id(conn, 9999);
	EXPECT_NULLPTR(accounts);
  if(accounts != NULL) account_array_destroy(accounts);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_books_1){
  book_array_t* books = get_books(conn, 1);
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 1);
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_2){
  book_array_t* books = get_books(conn, 3);
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 3);
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_3){
  book_array_t* books = get_books(conn, DB_GET_ALL);
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 6);
  if(books != NULL) book_array_destroy(books);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_book_by_id_1){
  book_t* book = get_book_by_id(conn, 1);
	ASSERT_NOT_NULLPTR(book);
  EXPECT_BOOK_EQUAL(book, db_book_1);
  if(book != NULL) book_destroy(book);
}

TEST_F(Database, get_book_by_id_2){
  book_t* book = get_book_by_id(conn, 3);
	ASSERT_NOT_NULLPTR(book);
  EXPECT_BOOK_EQUAL(book, db_book_3);
  if(book != NULL) book_destroy(book);
}

TEST_F(Database, get_book_by_id_3){
  book_t* book = get_book_by_id(conn, 9999);
  EXPECT_NULLPTR(book);
  if(book != NULL) book_destroy(book);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_book_by_loan_id_1){
  book_t* book = get_book_by_loan_id(conn, 3);
	ASSERT_NOT_NULLPTR(book);
  EXPECT_BOOK_EQUAL(book, db_book_4);
  if(book != NULL) book_destroy(book);
}

TEST_F(Database, get_book_by_loan_id_2){
  book_t* book = get_book_by_loan_id(conn, 6);
	ASSERT_NOT_NULLPTR(book);
  EXPECT_BOOK_EQUAL(book, db_book_1);
  if(book != NULL) book_destroy(book);
}

TEST_F(Database, get_book_by_loan_id_3){
  book_t* book = get_book_by_loan_id(conn, 9999);
  EXPECT_NULLPTR(book);
  if(book != NULL) book_destroy(book);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_books_by_account_id_1){
  book_array_t* books = get_books_by_account_id(conn, 3);
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 2);
	EXPECT_TRUE(contains_book(books, db_book_4));
	EXPECT_TRUE(contains_book(books, db_book_2));
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_account_id_2){
  book_array_t* books = get_books_by_account_id(conn, 5);
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 1);
	EXPECT_TRUE(contains_book(books, db_book_1));
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_account_id_3){
  book_array_t* books = get_books_by_account_id(conn, 9999);
	EXPECT_NULLPTR(books);
  if(books != NULL) book_array_destroy(books);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_books_by_title_1){
  book_array_t* books = get_books_by_title(conn, "1984");
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 1);
	EXPECT_TRUE(contains_book(books, db_book_2));
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_title_2){
  book_array_t* books = get_books_by_title(conn, "");
	EXPECT_NULLPTR(books);
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_title_3){
  book_array_t* books = get_books_by_title(conn, "biddibi boddibi bu");
	EXPECT_NULLPTR(books);
  if(books != NULL) book_array_destroy(books);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_books_by_author_1){
  book_array_t* books = get_books_by_author(conn, "John Ronald Reuel Tolkien");
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 1);
	EXPECT_TRUE(contains_book(books, db_book_5));
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_author_2){
  book_array_t* books = get_books_by_author(conn, "");
	EXPECT_NULLPTR(books);
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_author_3){
  book_array_t* books = get_books_by_author(conn, "biddibi boddibi bu");
	EXPECT_NULLPTR(books);
  if(books != NULL) book_array_destroy(books);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_books_by_publisher_1){
  book_array_t* books = get_books_by_publisher(conn, "George Allen and Unwin (UK) Houghton Mifflin (US)");
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 1);
	EXPECT_TRUE(contains_book(books, db_book_5));
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_publisher_2){
  book_array_t* books = get_books_by_publisher(conn, "");
	EXPECT_NULLPTR(books);
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_publisher_3){
  book_array_t* books = get_books_by_publisher(conn, "biddibi boddibi bu");
	EXPECT_NULLPTR(books);
  if(books != NULL) book_array_destroy(books);
}


//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_books_by_genres_1){
  book_array_t* books = get_books_by_genres(conn, "Fiction");
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 2);
	EXPECT_TRUE(contains_book(books, db_book_2));
	EXPECT_TRUE(contains_book(books, db_book_3));
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_genres_2){
  book_array_t* books = get_books_by_genres(conn, "Science fiction,Fiction");
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 1);
	EXPECT_TRUE(contains_book(books, db_book_2));
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_genres_3){
  book_array_t* books = get_books_by_genres(conn, "Young adult literature,Education");
	EXPECT_NULLPTR(books);
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_genres_4){
  book_array_t* books = get_books_by_genres(conn, "");
	EXPECT_NULLPTR(books);
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_genres_5){
  book_array_t* books = get_books_by_genres(conn, ",,,,");
	EXPECT_NULLPTR(books);
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_genres_6){
  book_array_t* books = get_books_by_genres(conn, "biddibi boddibi bu");
	EXPECT_NULLPTR(books);
  if(books != NULL) book_array_destroy(books);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_books_by_release_date_1){
	timestamp_t ts = string_to_timestamp("2014-05-15 00:00:00");
  book_array_t* books = get_books_by_release_date(conn, &ts);
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 1);
	EXPECT_TRUE(contains_book(books, db_book_4));
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_release_date_2){
	timestamp_t ts = string_to_timestamp("1997-06-26 00:00:00");
  book_array_t* books = get_books_by_release_date(conn, &ts);
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 1);
	EXPECT_TRUE(contains_book(books, db_book_1));
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_release_date_3){
	timestamp_t ts = string_to_timestamp("2077-01-01 00:00:00");
  book_array_t* books = get_books_by_release_date(conn, &ts);
	EXPECT_NULLPTR(books);
  if(books != NULL) book_array_destroy(books);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_books_by_data_match_1){
	timestamp_t ts = string_to_timestamp("2008-09-14 00:00:00");
  book_array_t* books = get_books_by_data_match(conn,"The Hunger Games","Suzanne Collins","Scholastic Press","Adventure fiction,Science fiction", &ts);
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 1);
	EXPECT_TRUE(contains_book(books, db_book_6));
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_data_match_2){
  book_array_t* books = get_books_by_data_match(conn, "Harry Potter", NULL, "The Russian Messenger", NULL, NULL);
	EXPECT_NULLPTR(books);
  if(books != NULL) book_array_destroy(books);
}

TEST_F(Database, get_books_by_data_match_3){
  book_array_t* books = get_books_by_data_match(conn, NULL, NULL, NULL, NULL, NULL);
	ASSERT_NOT_NULLPTR(books);
	EXPECT_EQ(books->size, 6);
  if(books != NULL) book_array_destroy(books);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_loans_1){
  loan_array_t* loans = get_loans(conn, 1);
	ASSERT_NOT_NULLPTR(loans);
	EXPECT_EQ(loans->size, 1);
  if(loans != NULL) loan_array_destroy(loans);
}

TEST_F(Database, get_loans_2){
  loan_array_t* loans = get_loans(conn, 5);
	ASSERT_NOT_NULLPTR(loans);
	EXPECT_EQ(loans->size, 5);
  if(loans != NULL) loan_array_destroy(loans);
}

TEST_F(Database, get_loans_3){
  loan_array_t* loans = get_loans(conn, DB_GET_ALL);
	ASSERT_NOT_NULLPTR(loans);
	EXPECT_EQ(loans->size, 6);
  if(loans != NULL) loan_array_destroy(loans);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_loan_by_id_1){
  loan_t* loan = get_loan_by_id(conn, 1);
	ASSERT_NOT_NULLPTR(loan);
  EXPECT_LOAN_EQUAL(loan, db_loan_1);
  if(loan != NULL) loan_destroy(loan);
}

TEST_F(Database, get_loan_by_id_2){
  loan_t* loan = get_loan_by_id(conn, 5);
	ASSERT_NOT_NULLPTR(loan);
  EXPECT_LOAN_EQUAL(loan, db_loan_5);
  if(loan != NULL) loan_destroy(loan);
}

TEST_F(Database, get_loan_by_id_3){
  loan_t* loan = get_loan_by_id(conn, 9999);
  EXPECT_NULLPTR(loan);
  if(loan != NULL) loan_destroy(loan);
}

//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_loans_by_account_id_1){
  loan_array_t* loans = get_loans_by_account_id(conn, 3);
	ASSERT_NOT_NULLPTR(loans);
	EXPECT_EQ(loans->size, 2);
	EXPECT_TRUE(contains_loan(loans, db_loan_3));
	EXPECT_TRUE(contains_loan(loans, db_loan_4));
  if(loans != NULL) loan_array_destroy(loans);
}

TEST_F(Database, get_loans_by_account_id_2){
  loan_array_t* loans = get_loans_by_account_id(conn, 5);
	ASSERT_NOT_NULLPTR(loans);
	EXPECT_EQ(loans->size, 1);
	EXPECT_TRUE(contains_loan(loans, db_loan_6));
  if(loans != NULL) loan_array_destroy(loans);
}

TEST_F(Database, get_loans_by_account_id_3){
  loan_array_t* loans = get_loans_by_account_id(conn, 6);\
	EXPECT_NULLPTR(loans);
  if(loans != NULL) loan_array_destroy(loans);
}


//////////////////////////////////////////////////////////////////////////////

TEST_F(Database, get_loans_by_book_id_1){
  loan_array_t* loans = get_loans_by_book_id(conn, 2);
	ASSERT_NOT_NULLPTR(loans);
	EXPECT_EQ(loans->size, 2);
	EXPECT_TRUE(contains_loan(loans, db_loan_2));
	EXPECT_TRUE(contains_loan(loans, db_loan_4));
  if(loans != NULL) loan_array_destroy(loans);
}

TEST_F(Database, get_loans_by_book_id_2){
  loan_array_t* loans = get_loans_by_book_id(conn, 1);
	ASSERT_NOT_NULLPTR(loans);
	EXPECT_EQ(loans->size, 2);
	EXPECT_TRUE(contains_loan(loans, db_loan_1));
	EXPECT_TRUE(contains_loan(loans, db_loan_6));
  if(loans != NULL) loan_array_destroy(loans);
}

TEST_F(Database, get_loans_by_book_id_3){
  loan_array_t* loans = get_loans_by_book_id(conn, 6);\
	EXPECT_NULLPTR(loans);
  if(loans != NULL) loan_array_destroy(loans);
}