#ifndef QUERIES_H
#define QUERIES_H

#include "db_utils.h"
#include "utils.h"
#include "data_objects.h"

#define QUERY_STRING_MAX_LENGTH 1024

resultset_t* perform_query(db_conn_t* connection, const char* query_string);

void extract_account(resultset_t* resultset, int row, account_t* account);
void extract_book(resultset_t* resultset, int row, book_t* book);
void extract_loan(resultset_t* resultset, int row, loan_t* loan);

account_array_t* perform_account_array_query(db_conn_t* connection, const char* query_string);
book_array_t*    perform_book_array_query(db_conn_t* connection, const char* query_string);
loan_array_t*    perform_loan_array_query(db_conn_t* connection, const char* query_string);

account_t*       perform_account_query(db_conn_t* connection, const char* query_string);
book_t*          perform_book_query(db_conn_t* connection, const char* query_string);
loan_t*          perform_loan_query(db_conn_t* connection, const char* query_string);

account_t*       get_account_by_id(db_conn_t* connection, int id);
account_t*       get_account_by_email(db_conn_t* connection, const char* email);
account_t*       get_account_by_loan_id(db_conn_t* connection, int id);
account_array_t* get_accounts_by_book_id(db_conn_t* connection, int id);

book_t*          get_book_by_id(db_conn_t* connection, int id);
book_t*          get_book_by_loan_id(db_conn_t* connection, int id);
book_array_t*    get_books_by_account_id(db_conn_t* connection, int id);
book_array_t*    get_books_by_title(db_conn_t* connection, const char* title);
book_array_t*    get_books_by_author(db_conn_t* connection, const char* author);
book_array_t*    get_books_by_publisher(db_conn_t* connection, const char* publisher);
book_array_t*    get_books_by_genres(db_conn_t* connection, const char* genres);
book_array_t*    get_books_by_release_date(db_conn_t* connection, const timestamp_t* release_date);
book_array_t*    get_books_by_data_match(
                    db_conn_t* connection, const char* title, const char* author, 
                    const char* publisher, const char* genres, const timestamp_t* release_date);

loan_t*          get_loan_by_id(db_conn_t* connection, int id);
loan_array_t*          get_loans_by_account_id(db_conn_t* connection, int id);
loan_array_t*          get_loans_by_book_id(db_conn_t* connection, int id);

#endif