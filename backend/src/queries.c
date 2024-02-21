#include "queries.h"

account_t* get_account_by_id(db_conn_t* connection, const int id)
{
	char buffer[QUERY_STRING_MAX_SIZE];
	sprintf(buffer, "SELECT * FROM account_by_id(%d)", id);
	return perform_account_query(connection, buffer);
}

account_t* get_account_by_email(db_conn_t* connection, const char* email)
{
	char buffer[QUERY_STRING_MAX_SIZE];
	sprintf(buffer, "SELECT * FROM account_by_email('%s')", email);
	return perform_account_query(connection, buffer);
}

account_array_t* get_accounts_by_book_id(dbconn_t* connection, const int id)
{
	char buffer[QUERY_STRING_MAX_SIZE];
	sprintf(buffer, "SELECT * FROM account_by_book_id('%d')", id);
	return perform_account_array_query(connection, buffer);
}

account_t* get_account_by_loan_id(db_conn_t* connection, const int id)
{
	char buffer[QUERY_STRING_MAX_SIZE];
	sprintf(buffer, "SELECT * FROM account_by_loan_id(%d)", id);
	return perform_account_query(connection, buffer);
}

book_t* get_book_by_id(db_conn_t* connection, const int id)
{
	char buffer[QUERY_STRING_MAX_SIZE];
	sprintf(buffer, "SELECT * FROM book_by_id(%d)", id);
	return perform_book_query(connection, buffer);
}