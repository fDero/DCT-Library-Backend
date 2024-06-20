#include <postgresql/libpq-fe.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "data_objects.h"
#include "db_utils.h"
#include "utils.h"
#include "http.h"
#include "queries.h"
#include "socket_handlers.h"
#include "json.h"
#include "respond.h"
#include "jwt.h"
#include "unistd.h"
#include <stdbool.h>

#include <hiredis/hiredis.h>
#include "cache.h"

void start_server(const bool debug_mode){
	log_to_console(GREEN, "Starting server\n");
	init_env();
	jwt_init();
	pthread_key_create(&http_request_key, NULL);
	setbuf(stdout, NULL);
	log_to_console(GREEN, "Initiating cache connection\n");
	cache_connection_init();
	log_to_console(GREEN, "Initiating Database connection\n");
	db_connection_init();
	init_db_global_variables();
	listen_and_serve(debug_mode);
}

int main(int argc, char** argv){
    if(argc > 1 && strcmp(argv[1], "--debug") != 0){
        log_to_console(RED, "Invalid arguments\n");
        exit(1);
    }
	start_server(argc > 1);
	return 0;
}
