
#include "queries.h"

book_array_t* get_books(db_conn_t* connection, int limit){
    char buffer[QUERY_STRING_MAX_LENGTH];
    if (limit != DB_GET_ALL)
        sprintf(buffer, "SELECT * FROM select_n_books(%d)", limit);
    else
        sprintf(buffer, "SELECT * FROM select_n_books(null)");
    return perform_book_array_query(connection, buffer);
}

book_array_t* get_books_by_ids(db_conn_t* connection, const char* ids){
    char buffer[QUERY_STRING_MAX_LENGTH];
    sprintf(buffer, "SELECT * FROM books_by_ids(ARRAY[%s])", ids);
    return perform_book_array_query(connection, buffer);
}

book_t* get_book_by_id(db_conn_t* connection, int id){
    char buffer[QUERY_STRING_MAX_LENGTH];
    sprintf(buffer, "SELECT * FROM book_by_id(%d)", id);
    return perform_book_query(connection, buffer);
}

book_array_t* get_books_by_account_id(db_conn_t* connection, int id){
    char buffer[QUERY_STRING_MAX_LENGTH];
    sprintf(buffer, "SELECT * FROM books_by_account_id(%d)", id);
    return perform_book_array_query(connection, buffer);
}

book_t* get_book_by_loan_id(db_conn_t* connection, int id){
    char buffer[QUERY_STRING_MAX_LENGTH];
    sprintf(buffer, "SELECT * FROM book_by_loan_id(%d)", id);
    return perform_book_query(connection, buffer);
}

book_array_t* get_books_by_title(db_conn_t* connection, const char* title){
    char buffer[QUERY_STRING_MAX_LENGTH];
    sprintf(buffer, "SELECT * FROM books_by_title('%s')", title);
    return perform_book_array_query(connection, buffer);
}

book_array_t* get_books_by_author(db_conn_t* connection, const char* author){
    char buffer[QUERY_STRING_MAX_LENGTH];
    sprintf(buffer, "SELECT * FROM books_by_author('%s')", author);
    return perform_book_array_query(connection, buffer);
}

book_array_t* get_books_by_publisher(db_conn_t* connection, const char* publisher){
    char buffer[QUERY_STRING_MAX_LENGTH];
    sprintf(buffer, "SELECT * FROM books_by_publisher('%s')", publisher);
    return perform_book_array_query(connection, buffer);
}

book_array_t* get_books_by_genres(db_conn_t* connection, const char* genres){
    char buffer[QUERY_STRING_MAX_LENGTH];
    sprintf(buffer, "SELECT * FROM books_by_genres('%s')", genres);
    return perform_book_array_query(connection, buffer);
}

book_array_t* get_books_by_release_date(db_conn_t* connection, const timestamp_t* release_date){
    char string_timestamp[STRING_TIMESTAMP_MAX_LENGTH] = "";
    timestamp_to_string(string_timestamp, STRING_TIMESTAMP_MAX_LENGTH,
                        release_date);
    char buffer[QUERY_STRING_MAX_LENGTH];
    sprintf(buffer, "SELECT * FROM books_by_release_date('%s')",
            string_timestamp);
    return perform_book_array_query(connection, buffer);
}

book_array_t* get_books_by_data_match(
    db_conn_t* connection, const char* ids, const char* title,
    const char* author, const char* publisher,
    const char* genres, const char* release_date, int limit
){
    char buffer[QUERY_STRING_MAX_LENGTH];
    char limit_buffer[30];
    char timestamp_buffer[release_date ? strlen(release_date) + 3 : 5];
    sprintf(timestamp_buffer, release_date ? "'%s'" : "null", release_date);
    sprintf(limit_buffer, "%d", limit);
    sprintf(buffer, "SELECT * FROM books_by_data_match(ARRAY[%s]::integer[], '%s', '%s', '%s', '%s', %s, %s)",
    ids ? ids : "",
    title ? title : "",
    author ? author : "",
    publisher ? publisher : "",
    genres ? genres : "",
    timestamp_buffer,
    limit != DB_GET_ALL ? limit_buffer : "null");
    return perform_book_array_query(connection, buffer);
}