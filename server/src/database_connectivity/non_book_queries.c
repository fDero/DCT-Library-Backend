#include "queries.h"

account_array_t* get_accounts(db_conn_t* connection, int limit){
	char buffer[QUERY_STRING_MAX_LENGTH];
	if(limit != DB_GET_ALL)
		sprintf(buffer, "SELECT * FROM select_n_accounts(%d)", limit);
	else
		sprintf(buffer, "SELECT * FROM select_n_accounts(null)");
	return perform_account_array_query(connection, buffer);
}

account_t* get_account_by_id(db_conn_t* connection, int id) {
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM account_by_id(%d)", id);
	return perform_account_query(connection, buffer);
}

account_t* get_account_by_email(db_conn_t* connection, const char* email) {
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM account_by_email('%s')", email);
	return perform_account_query(connection, buffer);
}

account_array_t* get_accounts_by_book_id(db_conn_t* connection, int id) {
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM accounts_by_book_id('%d')", id);
	return perform_account_array_query(connection, buffer);
}

account_t* get_account_by_loan_id(db_conn_t* connection, int id) {
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM account_by_loan_id(%d)", id);
	return perform_account_query(connection, buffer);
}

loan_array_t* get_loans(db_conn_t* connection, int limit){
	char buffer[QUERY_STRING_MAX_LENGTH];
	if(limit != DB_GET_ALL)
		sprintf(buffer, "SELECT * FROM select_n_loans(%d)", limit);
	else
		sprintf(buffer, "SELECT * FROM select_n_loans(null)");
	return perform_loan_array_query(connection, buffer);
}

loan_t* get_loan_by_id(db_conn_t* connection, int id) {
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM loan_by_id(%d)", id);
	return perform_loan_query(connection, buffer);
}

loan_array_t* get_loans_by_account_id(db_conn_t* connection, int id) {
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM loans_by_account_id(%d)", id);
	return perform_loan_array_query(connection, buffer);
}

loan_array_t* get_loans_by_book_id(db_conn_t* connection, int id) {
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM loans_by_book_id(%d)", id);
	return perform_loan_array_query(connection, buffer);
}

loan_array_t* get_expired_loans_by_account_id(db_conn_t* connection, int id) {
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM expired_loans_by_account_id(%d)", id);
	return perform_loan_array_query(connection, buffer);
}

int validate_account(db_conn_t* connection, const char* email, const char* password) {
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM validate_account('%s', '%s')", email, password);
	return perform_int_query(connection, buffer);
}

char* get_password_salt(db_conn_t* connection, const char* email) {
	char buffer[QUERY_STRING_MAX_LENGTH];
	sprintf(buffer, "SELECT * FROM extract_account_salt('%s')", email);
	return perform_string_query(connection, buffer);
}