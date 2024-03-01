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
	pthread_key_create(&http_request_key, NULL);
	setbuf(stdout, NULL);
	init_server_str();
	cache_connection_init();
	console_log(GREEN, "Initiating DB connection\n");
	db_connection_init();
	init_db_global_variables();

	for (int i = 0; i < global_db_variables_size; i++) {
		printf(
			"global db var(%s = %s \\ %d) \n", 
			global_db_variables[i].name, 
			global_db_variables[i].value_string,
			global_db_variables[i].value_int
		);
	}

	db_conn_t* connection = open_db_connection();
	char* error_code = NULL;
	loan_t loan;
	loan.account_id = 3;
	loan.book_id = 3;
	loan.starting_time = *string_to_timestamp("2024-04-02 00:00:00");
	loan.ending_time = *string_to_timestamp("2024-04-14 00:00:00");
	console_log(RED, "Inserting loan\n");
	int id = insert_loan(connection, &loan, &error_code);

	console_log(RED, "Error code: %s\n", error_code);
	console_log(RED, "Loan id: %d\n", id);

	close_db_connection(connection);

	console_log(GREEN, "Initiating server routine\n");
	listen_and_serve();
}

void main2() {
	cache_connection_init();
	redisReply *reply;
	reply = redisCommand(cache_connection,"PING %s", "Hello World");
    printf("RESPONSE: %s\n", reply->str);
    freeReplyObject(reply);
	
	char* key = generate_random_key();

	insert_key_value_pair_into_cache(key, "ok");

	char* val = get_value_by_key(key);
	printf("%s\n", val);
	free(val);
	free(key);
	redisFree(cache_connection);
}

void main3(){
	cache_connection_init();
	redisReply *reply;
	reply = redisCommand(cache_connection,"PING %s", "Hello World");
    printf("RESPONSE: %s\n", reply->str);
    freeReplyObject(reply);
	
	char* key = insert_value_with_autogenerated_unique_key("ok");

	insert_key_value_pair_into_cache(key, "ok");

	char* val = get_value_by_key(key);
	printf("%s\n", val);
	free(val);
	free(key);
	redisFree(cache_connection);
}

int main(){
	start_server();
	return 0;
}
