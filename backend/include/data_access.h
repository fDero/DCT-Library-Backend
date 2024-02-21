
#ifndef DATA_ACCESS_H
#define DATA_ACCESS_H
#include <assert.h>
#include <postgresql/libpq-fe.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "data_objects.h"
#include "db_utils.h"
#include "utils.h"

resultset_t* perform_query(conn_t* connection, const char* query_string);

void extract_account(resultset_t* resultset, int row, account_t* account);
void extract_book(resultset_t* resultset, int row, book_t* book);
void extract_loan(resultset_t* resultset, int row, loan_t* loan);

account_array_t* perform_account_array_query(conn_t* connection, const char* query_string);
book_array_t* perform_book_array_query(conn_t* connection, const char* query_string);
loan_array_t* perform_loan_array_query(conn_t* connection, const char* query_string);

account_t* perform_account_query(conn_t* connection, const char* query_string);
book_t* perform_book_query(conn_t* connection, const char* query_string);
loan_t* perform_loan_query(conn_t* connection, const char* query_string);

#endif