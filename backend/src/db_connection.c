#include "db_connection.h"

char db_conn_info[1024];

void db_connection_init(){
	sprintf(db_conn_info, "dbname = %s user = %s password = %s host = %s port = %s",
            getenv("POSTGRES_DB"), getenv("POSTGRES_USER"),
            getenv("POSTGRES_PASSWORD"), getenv("POSTGRES_HOST"),
            getenv("POSTGRES_PORT"));
}

conn_t* open_db_connection() {
    conn_t* conn = PQconnectdb(db_conn_info);
    return PQstatus(conn) == CONNECTION_OK ? conn : NULL;
}

void close_db_connection(conn_t* conn){
	PQfinish(conn);
}