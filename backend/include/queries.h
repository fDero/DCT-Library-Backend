#ifndef QUERIES_H
#define QUERIES_H

#include "data_access.h"

account_t* get_account_by_id(conn_t* connection, const int id);
account_t* get_account_by_email(conn_t* connection, const char* email);

#endif