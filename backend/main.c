#include <postgresql/libpq-fe.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_objects.h"
#include "db_utils.h"
#include "http.h"
#include "queries.h"
#include "socket_handlers.h"
#include "json.h"
#include <pthread.h>

int main() {
		db_connection_init();
    listen_and_serve();
}
