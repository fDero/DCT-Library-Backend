#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <stdlib.h>
#include <postgresql/libpq-fe.h>
#include "utils.h"

void get_connection_info(string_t conninfo);
conn_t get_db_connection();

#endif