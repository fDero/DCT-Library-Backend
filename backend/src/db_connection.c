#include "db_connection.h"

void get_connection_info(char* conninfo) {
    sprintf(conninfo, "dbname = %s user = %s password = %s host = %s port = %s",
            getenv("POSTGRES_DB"), getenv("POSTGRES_USER"),
            getenv("POSTGRES_PASSWORD"), getenv("POSTGRES_HOST"),
            getenv("POSTGRES_PORT"));
}

conn_t* get_db_connection() {
    char conn_info[1024];
    get_connection_info(conn_info);
    conn_t* conn = PQconnectdb(conn_info);
    return PQstatus(conn) == CONNECTION_OK ? conn : NULL;
}