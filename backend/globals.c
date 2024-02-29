
#include <hiredis/hiredis.h>

char* server;
redisContext *cache_connection;
pthread_key_t http_request_key;