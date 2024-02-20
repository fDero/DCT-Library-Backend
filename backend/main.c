
#include <postgresql/libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

#include "arrays.h"
#include "queries.h"
#include "tables.h"
#include "utils.h"

void get_connection_info(string_t conninfo)
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
    get_connection_info(conninfo);
    pg_conn_t conn = PQconnectdb(conninfo);
    assert(PQstatus(conn) == CONNECTION_OK);

    books_array_t books_array = perform_book_query(conn, "SELECT * FROM Book");
    for (int i = 0; i < books_array.array_size; i++)
        {
            printf("%s\n", books_array.array_storage[i].title);
        }
    printf("everything works!\n");
		account_t account= get_account_by_email(conn, "olivia.williams@example.com");
		printf("%s", account.name);
}
