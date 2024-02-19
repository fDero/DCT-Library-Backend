
#define _XOPEN_SOURCE
#define __USE_XOPEN
#define _GNU_SOURCE
#include "queries.h"

void alloc_and_strcpy(string_t *destination, string_t source)
{
    *destination = malloc(sizeof(char) * strlen(source));
    strcpy(*destination, source);
}

accounts_array_t perform_account_query(const string_t query_string, const pg_conn_t connection)
{
    resultset_t resultset = PQexec(connection, query_string);
    assert(PQresultStatus(resultset) == PGRES_TUPLES_OK);
    int row_count = PQntuples(resultset);
    int col_count = PQnfields(resultset);
    assert(col_count == 5);
    accounts_array_t output_array;
    output_array.array_size = row_count;
    output_array.array_storage = malloc(sizeof(*output_array.array_storage) * (row_count));
    for (int row = 0; row < row_count; row++)
    {
        alloc_and_strcpy(&(output_array.array_storage[row].name), PQgetvalue(resultset, row, 0));
        alloc_and_strcpy(&(output_array.array_storage[row].surname), PQgetvalue(resultset, row, 1));
        alloc_and_strcpy(&(output_array.array_storage[row].email), PQgetvalue(resultset, row, 2));
        output_array.array_storage[row].borrowed_books = atoi(PQgetvalue(resultset, row, 3));
        output_array.array_storage[row].account_id = atoi(PQgetvalue(resultset, row, 4));
    }
    return output_array;
}

books_array_t perform_book_query(const string_t query_string, const pg_conn_t connection)
{
    fflush(stdout);
    resultset_t resultset = PQexec(connection, query_string);
    assert(PQresultStatus(resultset) == PGRES_TUPLES_OK);
    int row_count = PQntuples(resultset);
    int col_count = PQnfields(resultset);
    assert(col_count == 7);
    books_array_t output_array;
    output_array.array_size = row_count;
    output_array.array_storage = malloc(sizeof(*output_array.array_storage) * (row_count));
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
    return output_array;
}

loans_array_t perform_loan_query(const string_t query_string, const pg_conn_t connection)
{
    resultset_t resultset = PQexec(connection, query_string);
    assert(PQresultStatus(resultset) == PGRES_TUPLES_OK);
    int row_count = PQntuples(resultset);
    int col_count = PQnfields(resultset);
    assert(col_count == 5);
    loans_array_t output_array;
    output_array.array_size = row_count;
    output_array.array_storage = malloc(sizeof(*output_array.array_storage) * (row_count));
    for (int row = 0; row < row_count; row++)
    {
        strptime(PQgetvalue(resultset, row, 0), "%Y-%m-%d %H:%M:%S", &(output_array.array_storage[row].starting_time));
        strptime(PQgetvalue(resultset, row, 1), "%Y-%m-%d %H:%M:%S", &(output_array.array_storage[row].ending_time));
        output_array.array_storage[row].account_id = atoi(PQgetvalue(resultset, row, 2));
        output_array.array_storage[row].book_id = atoi(PQgetvalue(resultset, row, 3));
        output_array.array_storage[row].loan_id = atoi(PQgetvalue(resultset, row, 4));
    }
    return output_array;
}
