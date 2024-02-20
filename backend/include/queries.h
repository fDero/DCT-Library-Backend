
#ifndef DBQUERIES
#define DBQUERIES
#include <assert.h>
#include <postgresql/libpq-fe.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "arrays.h"
#include "tables.h"
#include "utils.h"

#define QUERY_STRING_MAX_SIZE 1024

resultset_t perform_query(const pg_conn_t connection, const string_t query_string);
accounts_array_t perform_account_query(const pg_conn_t connection, const string_t query_string);
books_array_t perform_book_query(const pg_conn_t connection, const string_t query_string);
loans_array_t perform_loan_query(const pg_conn_t connection, const string_t query_string);

account_t get_account_by_id(const pg_conn_t connection, const int id);
account_t get_account_by_email(const pg_conn_t connection, const string_t email);

#endif