
#include "queries.h"

book_t* get_book_by_id(db_conn_t* connection, int id)
{
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM book_by_id(%d)", id);
	return perform_book_query(connection, buffer);
}

book_array_t* get_books_by_account_id(db_conn_t* connection, int id)
{
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM books_by_account_id(%d)", id);
	return perform_book_array_query(connection, buffer);
}

book_t* get_book_by_loan_id(db_conn_t* connection, int id)
{
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM book_by_loan_id(%d)", id);
	return perform_book_query(connection, buffer);
}

book_array_t* get_books_by_title(db_conn_t* connection, const char* title)
{
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM books_by_title('%s')", title);
	return perform_book_array_query(connection, buffer);
}

book_array_t* get_books_by_author(db_conn_t* connection, const char* author)
{
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM books_by_author('%s')", author);
	return perform_book_array_query(connection, buffer);
}

book_array_t* get_books_by_publisher(db_conn_t* connection, const char* publisher)
{
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM books_by_publisher('%s')", publisher);
	return perform_book_array_query(connection, buffer);
}

book_array_t* get_books_by_release_date(db_conn_t* connection, const timestamp_t* release_date)
{
	char string_timestamp[STRING_TIMESTAMP_MAX_LENGTH] = "";
	timestamp_to_string(string_timestamp, STRING_TIMESTAMP_MAX_LENGTH,release_date);
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM books_release_date('%s')", string_timestamp);
	return perform_book_array_query(connection, buffer);
}

book_array_t* get_books_by_data_match(
	db_conn_t* connection, const char* title, const char* author, 
	const char* publisher, const timestamp_t* release_date
){
	char buffer[100];
	char query_string[300] = "SELECT * FROM Book WHERE ";
	if (title != NULL){
		sprintf(buffer, "title = %s AND ", title);
		strcat(buffer, query_string);
	}
	if (author != NULL){
		sprintf(buffer, "author = %s AND ", author);
		strcat(buffer, query_string);
	}
	if (publisher != NULL){
		sprintf(buffer, "publisher = %s AND ", publisher);
		strcat(buffer, query_string);
	}
	if (release_date != NULL){
		char release_date_str[30];
		timestamp_to_string(release_date_str, 30, &(release_date));
		sprintf(buffer, "release_date = %s AND ", release_date_str);
		strcat(buffer, query_string);
	}
	strcat(buffer, " TRUE");
	return perform_book_array_query(connection, query_string);
}