
#include <hiredis/hiredis.h>
#include "db_utils.h"
#include "utils.h"

char* server = NULL;
redisContext* cache_connection = NULL;
size_t global_db_variables_size = 0;
database_gloabal_variable_t* global_db_variables = NULL;
pthread_key_t http_request_key;