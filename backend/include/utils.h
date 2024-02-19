#ifndef DBUTILS
#define DBUTILS
#include <postgresql/libpq-fe.h>

typedef char *string_t;
typedef struct tm timestamp_t;

typedef PGconn *pg_conn_t;
typedef PGresult *resultset_t;

#endif