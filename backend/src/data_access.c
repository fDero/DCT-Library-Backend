
#define _XOPEN_SOURCE
#define __USE_XOPEN
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include "data_access.h"

resultset_t* perform_query(db_conn_t* connection, const char* query_string)
{
	resultset_t* resultset = PQexec(connection, query_string);
	assert(PQresultStatus(resultset) == PGRES_TUPLES_OK);
	return resultset;
}

void extract_account(resultset_t* resultset, int row, account_t* account)
{
	alloc_and_strcpy(&(account->name), PQgetvalue(resultset, row, 0));
	alloc_and_strcpy(&(account->surname), PQgetvalue(resultset, row, 1));
	alloc_and_strcpy(&(account->email), PQgetvalue(resultset, row, 2));
	account->borrowed_books = atoi(PQgetvalue(resultset, row, 3));
	account->account_id = atoi(PQgetvalue(resultset, row, 4));
}

void extract_book(resultset_t* resultset, int row, book_t* book)
{
	alloc_and_strcpy(&(book->title), PQgetvalue(resultset, row, 0));
	alloc_and_strcpy(&(book->author), PQgetvalue(resultset, row, 1));
	alloc_and_strcpy(&(book->publisher), PQgetvalue(resultset, row, 2));
	strptime(PQgetvalue(resultset, row, 3), "%Y-%m-%d %H:%M:%S", &(book->release_date));
	book->total_copies = atoi(PQgetvalue(resultset, row, 4));
	book->borrowed_copies = atoi(PQgetvalue(resultset, row, 5));
	book->book_id = atoi(PQgetvalue(resultset, row, 6));
}

void extract_loan(resultset_t* resultset, int row, loan_t* loan)
{
	strptime(PQgetvalue(resultset, row, 0), "%Y-%m-%d %H:%M:%S", &(loan->starting_time));
	strptime(PQgetvalue(resultset, row, 1), "%Y-%m-%d %H:%M:%S", &(loan->ending_time));
	loan->account_id = atoi(PQgetvalue(resultset, row, 2));
	loan->book_id = atoi(PQgetvalue(resultset, row, 3));
	loan->loan_id = atoi(PQgetvalue(resultset, row, 4));
}

account_array_t* perform_account_array_query(db_conn_t* connection, const char* query_string)
{
	resultset_t* resultset = perform_query(connection, query_string);
	int row_count = PQntuples(resultset);
	int col_count = PQnfields(resultset);
	assert(col_count == 5);
	account_array_t* output_array = (account_array_t*)malloc(sizeof(account_array_t));
	account_array_init(output_array, row_count);
	for (int row = 0; row < row_count; row++)
	{
		extract_account(resultset, row, output_array->storage + row);
	}
	PQclear(resultset);
	return output_array;
}

book_array_t* perform_book_array_query(db_conn_t* connection, const char* query_string)
{
	fflush(stdout);
	resultset_t* resultset = perform_query(connection, query_string);
	int row_count = PQntuples(resultset);
	int col_count = PQnfields(resultset);
	assert(col_count == 7);
	book_array_t* output_array = (book_array_t*)malloc(sizeof(book_array_t));
	book_array_init(output_array, row_count);
	for (int row = 0; row < row_count; row++)
	{
		extract_book(resultset, row, output_array->storage + row);
	}
	PQclear(resultset);
	return output_array;
}

loan_array_t* perform_loan_array_query(db_conn_t* connection, const char* query_string)
{
	resultset_t* resultset = perform_query(connection, query_string);
	int row_count = PQntuples(resultset);
	int col_count = PQnfields(resultset);
	assert(col_count == 5);
	loan_array_t* output_array = (loan_array_t*)malloc(sizeof(loan_array_t));;
	loan_array_init(output_array, row_count);
	for (int row = 0; row < row_count; row++)
	{
		extract_loan(resultset, row, output_array->storage + row);
	}
	PQclear(resultset);
	return output_array;
}

account_t* perform_account_query(db_conn_t* connection, const char* query_string)
{
	resultset_t* resultset = perform_query(connection, query_string);
	int row_count = PQntuples(resultset);
	int col_count = PQnfields(resultset);
	assert(col_count == 5);
	assert(row_count == 1);
	account_t* output = (account_t*)malloc(sizeof(account_t));
	extract_account(resultset, 0, output);
	PQclear(resultset);
	return output;
}

book_t* perform_book_query(db_conn_t* connection, const char* query_string)
{
	resultset_t* resultset = perform_query(connection, query_string);
	int row_count = PQntuples(resultset);
	int col_count = PQnfields(resultset);
	assert(col_count == 5);
	assert(row_count == 1);
	book_t* output = (book_t*)malloc(sizeof(book_t));
	extract_book(resultset, 0, output);
	PQclear(resultset);
	return output;
}

loan_t* perform_loan_query(db_conn_t* connection, const char* query_string)
{
	resultset_t* resultset = perform_query(connection, query_string);
	int row_count = PQntuples(resultset);
	int col_count = PQnfields(resultset);
	assert(col_count == 5);
	assert(row_count == 1);
	loan_t* output = (loan_t*)malloc(sizeof(loan_t));
	extract_loan(resultset, 0, output);
	PQclear(resultset);
	return output;
}