#ifndef DB_UTILS_H
#define DB_UTILS_H
#include <postgresql/libpq-fe.h>
#include <time.h>

#define DB_TIMESTAMP_FORMAT "%Y-%m-%d %H:%M:%S"

typedef PGconn db_conn_t;
typedef PGresult resultset_t;
typedef struct tm timestamp_t;

void timestamp_to_string(char* str, size_t size, const timestamp_t* ts);
void string_to_timestamp(timestamp_t* ts, const char* str);

#endif