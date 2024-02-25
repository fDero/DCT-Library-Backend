#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define STRING_TIMESTAMP_MAX_LENGTH 50
#define TIMESTAMP_STRING_FORMAT "%Y-%m-%d %H:%M:%S"

typedef struct tm timestamp_t;

void alloc_and_strcpy(char* *destination, const char* source);

void timestamp_to_string(char* str, size_t size, const timestamp_t* ts);

timestamp_t string_to_timestamp(const char* str);

bool timestamp_equal(const timestamp_t* ts1, const timestamp_t* ts2);

void advance_to_next_targets(char* string, int* current_char_index, const char* targets);

void advance_to_next_target(char* string, int* current_char_index, char target);

void advance_to_next_whitespace(char* string, int* current_char_index);

void advance_to_next_carriage_return(char* string, int* current_char_index);

void advance_to_next_newline(char* string, int* current_char_index);

void skip_string_terminating_with_target(
    char* string, int* current_char_index,
    int len, char target, bool* correct
){
    if (!*correct) return;
    advance_to_next_target(string, current_char_index, target);
    *correct &= (string[*current_char_index] == target);
    *correct &= (*current_char_index < len);
    if (*correct) {
        string[*current_char_index] = '\0';
    }
    (*current_char_index)++;
}

void skip_string_terminating_with_target_safe(
    char* string, int* current_char_index, int len,
    char target, const char* targets, bool* correct
);

void skip_character_safe(
    char* string, int* current_char_index, int len,
    char target, const char* avoid, bool* correct
);
void skip_hostname(
    char* string, int* current_char_index, 
    int len, bool* correct
);

bool is_blank_char(char c);

#endif