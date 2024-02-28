
#include <hiredis/hiredis.h>
extern redisContext *cache_connection;

void insert_key_value_pair_into_cache(const char* key, const char* val);
char* get_value_by_key(const char* key);