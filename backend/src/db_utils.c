#define _XOPEN_SOURCE
#define __USE_XOPEN
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "db_utils.h"

void timestamp_to_string(char* str, size_t size, const timestamp_t* ts) {
	strftime(str, size, DB_TIMESTAMP_FORMAT, ts);
}

void string_to_timestamp(timestamp_t* ts, const char* str) {
	strptime(str, DB_TIMESTAMP_FORMAT, ts);
}
