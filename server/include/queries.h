#ifndef QUERIES_H
#define QUERIES_H

#include "db_utils.h"
#include "utils.h"
#include "data_objects.h"
#include <stdbool.h>

#define DB_GET_ALL -7489289
#define QUERY_STRING_MAX_LENGTH 1024

resultset_t*     perform_query(db_conn_t* connection, const char* query_string);

void             extract_account(resultset_t* resultset, int row, account_t* account);
void             extract_book(resultset_t* resultset, int row, book_t* book);
void             extract_loan(resultset_t* resultset, int row, loan_t* loan);
int              perform_int_query(db_conn_t* connection, const char* query_string);
char*            perform_string_query(db_conn_t* connection, const char* query_string);

account_array_t* perform_account_array_query(db_conn_t* connection, const char* query_string);
book_array_t*    perform_book_array_query(db_conn_t* connection, const char* query_string);
loan_array_t*    perform_loan_array_query(db_conn_t* connection, const char* query_string);

account_t*       perform_account_query(db_conn_t* connection, const char* query_string);
book_t*          perform_book_query(db_conn_t* connection, const char* query_string);
loan_t*          perform_loan_query(db_conn_t* connection, const char* query_string);

account_array_t* get_accounts(db_conn_t* connection, int limit);
account_t*       get_account_by_id(db_conn_t* connection, int id);
account_t*       get_account_by_email(db_conn_t* connection, const char* email);
account_t*       get_account_by_loan_id(db_conn_t* connection, int id);
account_array_t* get_accounts_by_book_id(db_conn_t* connection, int id);

book_array_t*    get_books(db_conn_t* connection, int limit);
book_array_t* 	 get_books_by_ids(db_conn_t* connection, const char* ids);
book_t*          get_book_by_id(db_conn_t* connection, int id);
book_t*          get_book_by_loan_id(db_conn_t* connection, int id);
book_array_t*    get_books_by_account_id(db_conn_t* connection, int id);
book_array_t*    get_books_by_title(db_conn_t* connection, const char* title);
book_array_t*    get_books_by_author(db_conn_t* connection, const char* author);
book_array_t*    get_books_by_publisher(db_conn_t* connection, const char* publisher);
book_array_t*    get_books_by_genres(db_conn_t* connection, const char* genres);
book_array_t*    get_books_by_release_date(db_conn_t* connection, const timestamp_t* release_date);
book_array_t*    get_books_by_data_match(
                    db_conn_t* connection, const char* ids, const char* title, const char* author, 
                    const char* publisher, const char* genres, const char* release_date, int limit
                );

loan_array_t*    get_loans(db_conn_t* connection, int limit);
loan_t*          get_loan_by_id(db_conn_t* connection, int id);
loan_array_t*    get_loans_by_account_id(db_conn_t* connection, int id);
loan_array_t*    get_loans_by_book_id(db_conn_t* connection, int id);
loan_array_t*    get_expired_loans_by_account_id(db_conn_t* connection, int id);

loan_t*          insert_loan(db_conn_t* connection, int book_id, int account_id, char** error_code);
bool             delete_loan(db_conn_t* connection, int loan_id, int account_id);
int              insert_account(
                    db_conn_t* connection, const char* name, const char* surname,
                    const char* email, const char* hashed_password, const char* salt,
                    char** error_code
                );

int              validate_account(db_conn_t* connection, const char* email, const char* password);
char*            get_password_salt(db_conn_t* connection, const char* email);

#endif
