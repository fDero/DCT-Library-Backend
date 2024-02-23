#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STRING_TIMESTAMP_MAX_LENGTH 50

typedef struct tm timestamp_t;

void alloc_and_strcpy(char* *destination, const char* source);

void timestamp_to_string(char* str, size_t size, const timestamp_t* ts);

timestamp_t string_to_timestamp(const char* str);

bool timestamp_equal(const timestamp_t* ts1, const timestamp_t* ts2);

#endif