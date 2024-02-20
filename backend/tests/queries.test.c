#include "queries.h"

#include "test.h"

void get_connection_info(string_t conninfo) {
    sprintf(conninfo, "dbname = %s user = %s password = %s host = %s port = %s",
            getenv("POSTGRES_DB"), getenv("POSTGRES_USER"),
            getenv("POSTGRES_PASSWORD"), getenv("POSTGRES_HOST"),
            getenv("POSTGRES_PORT"));
}

int main(int argc, char* argv[]) {
    char conninfo[500];
    get_connection_info(conninfo);
    pg_conn_t conn = PQconnectdb(conninfo);
    assert(PQstatus(conn) == CONNECTION_OK);
    long* errnum = (long*)malloc(sizeof(long));
    *errnum = 0;

    account_t account = get_account_by_email(conn, "john.smith@example.com");
    test(errnum, strcmp(account.name, "John") == 0, "Account name is %s", account.name);
}