#ifndef QUERIES_H
#define QUERIES_H

#include "db_utils.h"
#include "data_access.h"

#define STRING_TIMESTAMP_MAX_LENGTH 50
#define QUERY_STRING_MAX_LENGTH 1024

account_t* get_account_by_id(db_conn_t* connection, const int id);
account_t* get_account_by_email(db_conn_t* connection, const char* email);

#endif