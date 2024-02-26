#ifndef DB_UTILS_H
#define DB_UTILS_H
#include <postgresql/libpq-fe.h>
#include <stdlib.h>
#include <pthread.h>

typedef PGconn db_conn_t;
typedef PGresult resultset_t;

extern pthread_key_t db_conn_key;

extern char db_conn_info[1024];

void db_connection_init();
db_conn_t* open_db_connection();
void close_db_connection(db_conn_t* conn);
void close_db_connection_callback(void* conn);

#endif