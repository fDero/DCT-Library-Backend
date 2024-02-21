
#include <postgresql/libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

#include "db_connection.h"
#include "queries.h"
#include "data_objects.h"

int main() {
		db_connection_init();
    printf("hello world! %s\n", getenv("POSTGRES_PORT"));
		
    db_conn_t* conn = open_db_connection();

    book_array_t* books_array = perform_book_array_query(conn, "SELECT * FROM Book");
    for (int i = 0; i < books_array->size; i++) {
        printf("%s\n", books_array->storage[i].title);
    }
    printf("everything works!\n");
    account_t* account = get_account_by_id(conn, 1);
    printf("%s, %s, %s", account->name, account->surname, account->email);
		account_destroy(account);
		book_array_destroy(books_array);
		close_db_connection(conn);
}
