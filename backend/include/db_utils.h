#ifndef DB_UTILS_H
#define DB_UTILS_H
#include <postgresql/libpq-fe.h>

typedef struct tm timestamp_t;

typedef PGconn db_conn_t;
typedef PGresult resultset_t;

#endif