
#include <hiredis/hiredis.h>
#include "cache.h"

void insert_key_value_pair_into_cache(const char* key, const char* val){
    redisReply* reply = redisCommand(cache_connection,"SET %s %s", key, val);
    freeReplyObject(reply);
}