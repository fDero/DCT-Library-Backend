#ifndef DBUTILS
#define DBUTILS
#include <postgresql/libpq-fe.h>

typedef struct tm timestamp_t;

typedef PGconn conn_t;
typedef PGresult resultset_t;

#endif