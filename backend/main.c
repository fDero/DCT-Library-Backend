
#include <postgresql/libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

#include "db_connection.h"
#include "queries.h"
#include "data_objects.h"
#include "socket_handlers.h"

int main() {
	db_connection_init();
	listen_and_serve();
}
