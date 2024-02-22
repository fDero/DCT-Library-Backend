#include "queries.h"

account_t* get_account_by_id(db_conn_t* connection, int id)
{
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM account_by_id(%d)", id);
	return perform_account_query(connection, buffer);
}

account_t* get_account_by_email(db_conn_t* connection, const char* email)
{
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM account_by_email('%s')", email);
	return perform_account_query(connection, buffer);
}

account_array_t* get_accounts_by_book_id(db_conn_t* connection, int id)
{
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM accounts_by_book_id('%d')", id);
	return perform_account_array_query(connection, buffer);
}

account_t* get_account_by_loan_id(db_conn_t* connection, int id)
{
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM account_by_loan_id(%d)", id);
	return perform_account_query(connection, buffer);
}

loan_t* get_loan_by_id(db_conn_t* connection, int id)
{
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM loan_by_id(%d)", id);
	return perform_loan_query(connection, buffer);
}

loan_t* get_loans_by_account_id(db_conn_t* connection, int id)
{
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM loans_by_account_id(%d)", id);
	return perform_loan_query(connection, buffer);
}

loan_t* get_loans_by_book_id(db_conn_t* connection, int id)
{
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM loans_by_book_id(%d)", id);
	return perform_loan_query(connection, buffer);
}