
#include <postgresql/libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>
#include "tables.h"
#include "arrays.h"
#include "queries.h"
#include "utils.h"

void initialize_connection_info(string_t conninfo)
{
	sprintf(conninfo, "dbname = %s user = %s password = %s host = %s port = %s",
			getenv("POSTGRES_DB"), getenv("POSTGRES_USER"),
			getenv("POSTGRES_PASSWORD"), getenv("POSTGRES_HOST"),
			getenv("POSTGRES_PORT"));
}

int main()
{
	printf("hello world! %s\n", getenv("POSTGRES_PORT"));

	char conninfo[500];
	initialize_connection_info(conninfo);
	pg_conn_t conn = PQconnectdb(conninfo);
	assert(PQstatus(conn) == CONNECTION_OK);

	books_array_t books_array = perform_book_query("SELECT * FROM Book", conn);
	for (int i = 0; i < books_array.array_size; i++)
	{
		printf("%s\n", books_array.array_storage[i].title);
	}

	printf("everything works!\n");
}
