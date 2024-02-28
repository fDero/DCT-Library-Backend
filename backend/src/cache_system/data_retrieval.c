

#include <hiredis/hiredis.h>
#include "utils.h"
#include "cache.h"

char* get_value_by_key(const char* key){
    redisReply* reply = redisCommand(cache_connection,"GET %s", key);
    if (reply == NULL || reply->type != REDIS_REPLY_STRING){
        freeReplyObject(reply);
        return NULL;
    }
    char* value;
    alloc_and_strcpy(&value, reply->str);
    freeReplyObject(reply);
    return value;
}