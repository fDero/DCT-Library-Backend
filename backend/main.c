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
		console_log("%sInitiating DB connection%s\n", GREEN, WHITE);
		db_connection_init();
		console_log("%sInitiating server routine%s\n", GREEN, WHITE);
    listen_and_serve();
}
