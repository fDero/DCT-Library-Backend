#include "queries.h"

account_t* get_account_by_id(conn_t* connection, const int id)
{
	char buffer[QUERY_STRING_MAX_SIZE];
	sprintf(buffer, "SELECT * FROM account_by_id(%d)", id);
	return perform_account_query(connection, buffer);
}

account_t* get_account_by_email(conn_t* connection, const char* email)
{
	char buffer[QUERY_STRING_MAX_SIZE];
	sprintf(buffer, "SELECT * FROM account_by_email('%s')", email);
	return perform_account_query(connection, buffer);
}