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
#include "cache.h"

char* sha256_hash_number(long long int num);

void init_server_str(){
	char server_env [50];
	strcpy(server_env, getenv("SERVER"));
	server = (char*)malloc(sizeof(char) * strlen(server_env) + 1);
	strcpy(server, server_env);
}

void cache_connection_init(){
	int redis_port = atoi(getenv("REDISPORT"));
	printf("%d\n", redis_port);
    cache_connection = redisConnect(getenv("REDISHOST"), redis_port);
    assert (!(cache_connection->err));
}

void start_server(){
	setbuf(stdout, NULL);
	init_server_str();
	cache_connection_init();
	console_log(GREEN, "Initiating DB connection\n");
	db_connection_init();
	console_log(GREEN, "Initiating server routine\n");
	listen_and_serve();
}

int main() {
	cache_connection_init();
	redisReply *reply;
	reply = redisCommand(cache_connection,"PING %s", "Hello World");
    printf("RESPONSE: %s\n", reply->str);
    freeReplyObject(reply);
	
	insert_key_value_pair_into_cache("abcd", "ok");

	char* val = get_value_by_key("abcd");
	printf("%s\n", val);
	free(val);


	redisFree(cache_connection);
}
