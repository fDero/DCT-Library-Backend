
#define _XOPEN_SOURCE
#define __USE_XOPEN
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include "queries.h"

void alloc_and_strcpy(char* *destination, char* source)
{
	*destination = (char *)malloc(sizeof(char) * strlen(source));
	strcpy(*destination, source);
}

resultset_t* perform_query(conn_t* connection, const char* query_string)
{
	resultset_t* resultset = PQexec(connection, query_string);
	assert(PQresultStatus(resultset) == PGRES_TUPLES_OK);
	return resultset;
}

accounts_array_t perform_account_query(conn_t* connection, const char* query_string)
{
	resultset_t* resultset = perform_query(connection, query_string);
	int row_count = PQntuples(resultset);
	int col_count = PQnfields(resultset);
	assert(col_count == 5);
	accounts_array_t output_array;
	output_array.array_size = row_count;
	output_array.array_storage = (account_t *)malloc(sizeof(*output_array.array_storage) * (row_count));
	for (int row = 0; row < row_count; row++)
	{
		alloc_and_strcpy(&(output_array.array_storage[row].name), PQgetvalue(resultset, row, 0));
		alloc_and_strcpy(&(output_array.array_storage[row].surname), PQgetvalue(resultset, row, 1));
		alloc_and_strcpy(&(output_array.array_storage[row].email), PQgetvalue(resultset, row, 2));
		output_array.array_storage[row].borrowed_books = atoi(PQgetvalue(resultset, row, 3));
		output_array.array_storage[row].account_id = atoi(PQgetvalue(resultset, row, 4));
	}
	free(resultset);
	return output_array;
}

books_array_t perform_book_query(conn_t* connection, const char* query_string)
{
	fflush(stdout);
	resultset_t* resultset = perform_query(connection, query_string);
	int row_count = PQntuples(resultset);
	int col_count = PQnfields(resultset);
	assert(col_count == 7);
	books_array_t output_array;
	output_array.array_size = row_count;
	output_array.array_storage = (book_t *)malloc(sizeof(*output_array.array_storage) * (row_count));
	for (int row = 0; row < row_count; row++)
	{
		alloc_and_strcpy(&(output_array.array_storage[row].title), PQgetvalue(resultset, row, 0));
		alloc_and_strcpy(&(output_array.array_storage[row].author), PQgetvalue(resultset, row, 1));
		alloc_and_strcpy(&(output_array.array_storage[row].publisher), PQgetvalue(resultset, row, 2));
		strptime(PQgetvalue(resultset, row, 3), "%Y-%m-%d %H:%M:%S", &(output_array.array_storage[row].release_date));
		output_array.array_storage[row].total_copies = atoi(PQgetvalue(resultset, row, 4));
		output_array.array_storage[row].borrowed_copies = atoi(PQgetvalue(resultset, row, 5));
		output_array.array_storage[row].book_id = atoi(PQgetvalue(resultset, row, 6));
	}
	free(resultset);
	return output_array;
}

loans_array_t perform_loan_query(conn_t* connection, const char* query_string)
{
	resultset_t* resultset = perform_query(connection, query_string);
	int row_count = PQntuples(resultset);
	int col_count = PQnfields(resultset);
	assert(col_count == 5);
	loans_array_t output_array;
	output_array.array_size = row_count;
	output_array.array_storage = (loan_t *)malloc(sizeof(*output_array.array_storage) * (row_count));
	for (int row = 0; row < row_count; row++)
	{
		strptime(PQgetvalue(resultset, row, 0), "%Y-%m-%d %H:%M:%S", &(output_array.array_storage[row].starting_time));
		strptime(PQgetvalue(resultset, row, 1), "%Y-%m-%d %H:%M:%S", &(output_array.array_storage[row].ending_time));
		output_array.array_storage[row].account_id = atoi(PQgetvalue(resultset, row, 2));
		output_array.array_storage[row].book_id = atoi(PQgetvalue(resultset, row, 3));
		output_array.array_storage[row].loan_id = atoi(PQgetvalue(resultset, row, 4));
	}
	free(resultset);
	return output_array;
}

account_t get_account_by_id(conn_t* connection, const int id)
{
	char buffer[QUERY_STRING_MAX_SIZE];
	sprintf(buffer, "SELECT * FROM account_by_id(%d)", id);
	accounts_array_t accounts = perform_account_query(connection, buffer);
	account_t account = accounts.array_storage[0];
	free(accounts.array_storage);
	return account;
}

account_t get_account_by_email(conn_t* connection, const char* email)
{
	char buffer[QUERY_STRING_MAX_SIZE];
	sprintf(buffer, "SELECT * FROM account_by_email('%s')", email);
	accounts_array_t accounts = perform_account_query(connection, buffer);
	account_t account = accounts.array_storage[0];
	free(accounts.array_storage);
	return account;
}

