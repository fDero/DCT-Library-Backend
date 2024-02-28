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

#include <hiredis/hiredis.h>

extern redisContext *c;
//char* insert_unique_value_in_cache_and_get_key(const char* val);
//char* retrieve_value_from_cache_with_key(const char* key);

void init_server_str(){
	char server_env [50];
	strcpy(server_env, getenv("SERVER"));
	server = (char*)malloc(sizeof(char) * strlen(server_env) + 1);
	strcpy(server, server_env);
}

int main() {
	setbuf(stdout, NULL);
	char* hashed_string = sha256_hash_string("Hello World");
	printf("%s\n\n\n", hashed_string);
	free(hashed_string);
    redisReply *reply;

	printf("Hello Hello Hello\n");

	int redis_port = atoi(getenv("REDISPORT"));
	printf("%d\n", redis_port);
    c = redisConnect(getenv("REDISHOST"), redis_port);
    if (c->err) {
        printf("error: %s\n", c->errstr);
        return 1;
    }

	printf("Hello\n");

    /* PING server */
    reply = redisCommand(c,"PING %s", "Hello World");
    printf("RESPONSE: %s\n", reply->str);
    freeReplyObject(reply);

	

    redisFree(c);

	init_server_str();
	console_log(GREEN, "Initiating DB connection\n");
	db_connection_init();
	console_log(GREEN, "Initiating server routine\n");
	listen_and_serve();
}
