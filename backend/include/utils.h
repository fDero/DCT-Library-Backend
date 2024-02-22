#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>

void alloc_and_strcpy(char* *destination, const char* source);

void timestamp_to_string(char* str, size_t size, const timestamp_t* ts);

timestamp_t string_to_timestamp(const char* str);

#endif