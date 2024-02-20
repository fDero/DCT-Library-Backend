
#include <postgresql/libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

#include "arrays.h"
#include "db_connection.h"
#include "queries.h"
#include "tables.h"
#include "utils.h"

int main() {
    printf("hello world! %s\n", getenv("POSTGRES_PORT"));

    conn_t* conn = get_db_connection();

    books_array_t books_array = perform_book_query(conn, "SELECT * FROM Book");
    for (int i = 0; i < books_array.array_size; i++) {
        printf("%s\n", books_array.array_storage[i].title);
    }
    printf("everything works!\n");
    account_t account = get_account_by_email(conn, "olivia.williams@example.com");
    printf("%s", account.name);
}
