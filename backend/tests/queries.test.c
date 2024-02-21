#include <gtest/gtest.h>
#include "tests_init.cpp"
#include "data_objects.h"
#include "queries.h"

db_conn_t* conn = NULL;

// INSERT INTO Account(name,surname,email, account_id) VALUES
// 	('John',    'Smith',    'john.smith@example.com'       , 1),
// 	('Emma',    'Johnson',  'emma.johnson@example.com'     , 2),
// 	('William', 'Brown',    'william.brown@example.com'    , 3),
// 	('Olivia',  'Williams', 'olivia.williams@example.com'  , 4),
// 	('James',   'Jones',    'james.jones@example.com'      , 5),
// 	('Sophia',  'Davis',    'sophia.davis@example.com'     , 6);

// INSERT INTO Book(title,author,publisher,release_date,total_copies, book_id) VALUES
// 	('Harry Potter','J.K.Rowling','Bloomsbury','1997-06-26 00:00:00', 10, 1),
// 	('1984', 'G.Orwell','Secker & Warburg','1949-06-08 00:00:00', 6, 2),
// 	('Karamazov Brothers','F.Dostoevskij','The Russian Messenger','1980-11-01 00:00:00', 4, 3);

// INSERT INTO Loan(starting_time, ending_time, account_id, book_id, loan_id) VALUES
// 	('2024-04-02 00:00:00','2024-04-14 00:00:00', 6, 1, 1);

// INSERT INTO Loan(starting_time, ending_time, account_id, book_id, loan_id) VALUES
// 	('2024-04-07 00:00:00','2024-04-14 00:00:00', 3, 2, 2);

// INSERT INTO Loan(starting_time, ending_time, account_id, book_id, loan_id) VALUES
// 	('2024-04-09 00:00:00','2024-04-14 00:00:00', 4, 1, 3);

TEST(Database, account_by_id){
	printf("\n\nHELLO\n%s\n\n", db_conn_info);
	account_t* account = get_account_by_id(conn, 1);
	EXPECT_EQ("John", account->name);
	EXPECT_EQ("Smith", account->surname);
	EXPECT_EQ("john.smith@example.com", account->email);
	account_destroy(account);
}
