#ifndef DB_UTILS_H
#define DB_UTILS_H
#include <postgresql/libpq-fe.h>
#include <stdlib.h>
#include <pthread.h>

typedef PGconn db_conn_t;
typedef PGresult resultset_t;

extern pthread_key_t db_conn_key;

extern char db_conn_info[1024];

struct database_gloabal_variable {
    char* name;
    char* value_string;
    int value_int;
};

typedef struct database_gloabal_variable database_gloabal_variable_t;

extern database_gloabal_variable_t* global_db_variables;
extern size_t global_db_variables_size;

void db_connection_init();
db_conn_t* open_db_connection();
void close_db_connection(db_conn_t* conn);
void close_db_connection_callback(void* conn);

void init_db_global_variables();
char* get_error_code(resultset_t* res);

resultset_t* perform_query(db_conn_t* connection, const char* query_string);
const char* error_phrase(const char* error_code);

#endif
