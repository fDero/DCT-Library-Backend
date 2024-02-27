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

bool COLORED_OUTPUT_ENABLED = true;

int main() {
		console_log(GREEN, "Initiating DB connection\n");
		db_connection_init();
		console_log(GREEN, "Initiating server routine\n");
    listen_and_serve();
}
