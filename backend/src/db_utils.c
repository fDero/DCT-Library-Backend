#define _XOPEN_SOURCE
#define __USE_XOPEN
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "db_utils.h"

void timestamp_to_string(char* str, size_t size, const timestamp_t* ts) {
	strftime(str, size, DB_TIMESTAMP_FORMAT, ts);
}

timestamp_t string_to_timestamp(const char* str) {
	timestamp_t timestamp;
	strptime(str, DB_TIMESTAMP_FORMAT, &timestamp);
	return timestamp;
}
