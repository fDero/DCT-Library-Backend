
#define _XOPEN_SOURCE
#define __USE_XOPEN
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "utils.h"

void timestamp_to_string(char* str, size_t size, const timestamp_t* ts) {
    strftime(str, size, TIMESTAMP_STRING_FORMAT, ts);
}

timestamp_t string_to_timestamp(const char* str) {
    timestamp_t timestamp;
    strptime(str, TIMESTAMP_STRING_FORMAT, &timestamp);
    return timestamp;
}

bool timestamp_equal(const timestamp_t* ts1, const timestamp_t* ts2) {
    char str1[STRING_TIMESTAMP_MAX_LENGTH];
    char str2[STRING_TIMESTAMP_MAX_LENGTH];
    timestamp_to_string(str1, STRING_TIMESTAMP_MAX_LENGTH, ts1);
    timestamp_to_string(str2, STRING_TIMESTAMP_MAX_LENGTH, ts2);
    return !strcmp(str1, str2);
}

void alloc_and_strcpy(char** destination, const char* source) {
    *destination = (char*)malloc(sizeof(char) * strlen(source) + 1);
    strcpy(*destination, source);
}

void advance_to_next_target(char* string, int* current_char_index,
                            char target) {
    char current = string[*current_char_index];
    while (current != '\0' && current != target) {
        (*current_char_index) += 1;
        current = string[*current_char_index];
    }
}

void advance_to_next_targets(char* string, int* current_char_index,
                             const char* targets) {
    char current = string[*current_char_index];
    while (current != '\0') {
        for (int i = 0; i < strlen(targets); i++) {
            if (current == targets[i]) {
                return;
            }
        }
        (*current_char_index) += 1;
        current = string[*current_char_index];
    }
}

void advance_to_next_whitespace(char* string, int* current_char_index) {
    advance_to_next_target(string, current_char_index, ' ');
}

void advance_to_next_carriage_return(char* string, int* current_char_index) {
    advance_to_next_target(string, current_char_index, '\r');
}

void advance_to_next_newline(char* string, int* current_char_index) {
    advance_to_next_target(string, current_char_index, '\n');
}