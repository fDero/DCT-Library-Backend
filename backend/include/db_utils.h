#ifndef DB_UTILS_H
#define DB_UTILS_H
#include <postgresql/libpq-fe.h>

typedef PGconn db_conn_t;
typedef PGresult resultset_t;
typedef struct tm timestamp_t;

void timestamp_to_string(char* str, const timestamp_t* ts);

#endif