
#ifndef DBQUERIES
#define DBQUERIES
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <postgresql/libpq-fe.h>
#include <string.h>
#include <time.h>
#include "tables.h"
#include "arrays.h"
#include "utils.h"

accounts_array_t perform_account_query(const string_t query_string, const pg_conn_t connection);
books_array_t perform_book_query(const string_t query_string, const pg_conn_t connection);
loans_array_t perform_loan_query(const string_t query_string, const pg_conn_t connection);

#endif