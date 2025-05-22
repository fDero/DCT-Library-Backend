#include "db_utils.h"
#include "utils.h"

char db_conn_info[1024];

pthread_key_t db_conn_key;

void db_connection_init() {
    sprintf(db_conn_info,
        "dbname = %s user = %s password = %s host = %s port = %s",
        getenv("POSTGRES_DB"), getenv("POSTGRES_USER"),
        getenv("POSTGRES_PASSWORD"), getenv("POSTGRES_HOST"),
        getenv("POSTGRES_PORT")
    );
    pthread_key_create(&db_conn_key, close_db_connection_callback);
}

db_conn_t* open_db_connection() {
    db_conn_t* conn = PQconnectdb(db_conn_info);
    return PQstatus(conn) == CONNECTION_OK ? conn : NULL;
}

void close_db_connection(db_conn_t* conn) {
    PQfinish(conn);
}

void close_db_connection_callback(void* conn) {
    close_db_connection((db_conn_t*)conn);
}
