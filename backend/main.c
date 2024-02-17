
#include <stdio.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>

void initialize_connection_info(char* conninfo){
    sprintf(conninfo, "dbname = %s user = %s password = %s host = %s port = %s",
        getenv("POSTGRES_DB"), getenv("POSTGRES_USER"), getenv("POSTGRES_PASSWORD"),
        getenv("POSTGRES_HOST"), getenv("POSTGRES_PORT")
    );
}

int main(){

	printf("hello world! %s\n", getenv("POSTGRES_PORT"));

    	char conninfo[500];
    	initialize_connection_info(conninfo);
    	PGconn* conn = PQconnectdb(conninfo);
    	if (PQstatus(conn) != CONNECTION_OK)
    	{
		const char* error_msg = "Connection to database failed: %s";
        	fprintf(stderr, error_msg, PQerrorMessage(conn));
        	PQfinish(conn);
    		exit(EXIT_SUCCESS);
    	}
	printf("everything works!\n");
}
