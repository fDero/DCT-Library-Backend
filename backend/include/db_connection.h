#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <stdlib.h>
#include <postgresql/libpq-fe.h>
#include "db_utils.h"

extern char db_conn_info[1024];

void db_connection_init();
db_conn_t* open_db_connection();
void close_db_connection(db_conn_t* conn);

#endif