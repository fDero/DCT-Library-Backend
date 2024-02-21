#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <stdlib.h>
#include <postgresql/libpq-fe.h>
#include "db_utils.h"

void get_connection_info(char* conninfo);
conn_t* open_db_connection();
void close_db_connection(conn_t* conn);

#endif