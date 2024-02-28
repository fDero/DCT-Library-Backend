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

char* server;

void init_server_str(){
	char server_env [50];
	strcpy(server_env, getenv("SERVER"));
	server = (char*)malloc(sizeof(char) * strlen(server_env) + 1);
	strcpy(server, server_env);
}

int main() {
	char* hashed_string = sha256_hash_string("Hello World");
	printf("%s\n\n\n", hashed_string);
	free(hashed_string);

	init_server_str();
	console_log(GREEN, "Initiating DB connection\n");
	db_connection_init();
	console_log(GREEN, "Initiating server routine\n");
	listen_and_serve();
}
