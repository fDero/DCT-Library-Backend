
#define _XOPEN_SOURCE
#define __USE_XOPEN
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <pthread.h>
#include "utils.h"

pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
char* server = NULL;

const bool COLORED_OUTPUT_ENABLED = true;

void init_env(){
	char server_env [50];
	strcpy(server_env, getenv("SERVER"));
	server = (char*)malloc(sizeof(char) * strlen(server_env) + 1);
	strcpy(server, server_env);
}

void read_file(char* path, char** out_string){
	int file_length;
	FILE *file = fopen(path, "rb");
	if (file == NULL){
        *out_string = NULL;
        return;
    }
	fseek(file, 0, SEEK_END);
	file_length = ftell(file);
	fseek(file, 0, SEEK_SET);
	*out_string = (char*)malloc(file_length + 1);
	fread(*out_string, 1, file_length, file);
	(*out_string)[file_length] = '\0';
	fclose(file);
}

int log_to_console(const char* color, const char* str, ...) {
    va_list arguments;
    va_start(arguments, str);
	pthread_mutex_lock(&log_mutex);
	
	if (COLORED_OUTPUT_ENABLED && color != NULL) {
		printf("%s", color);
		fflush(stdout);
	}

	char* time_str = get_current_time("%Y-%m-%d %H:%M:%S");
	printf("%s: ", time_str);
	free(time_str);
	fflush(stdout);
	
    int ret = vprintf(str, arguments);
	fflush(stdout);

    va_end(arguments);
	if (COLORED_OUTPUT_ENABLED && color != NULL) {
		printf("%s", DEFAULT_COLOR);
		fflush(stdout);
	}

	pthread_mutex_unlock(&log_mutex);
	return ret;
}

char* get_current_time(const char* format){
	time_t now = time(NULL);
	timestamp_t* now_timestamp = gmtime(&now);
	char* time_str = (char*)malloc(sizeof(char) * 40);
	strftime(time_str, 40, format, now_timestamp);
	return time_str;
}

bool is_blank_char(char c){
    return c == '\r' || c == '\n' ||
    c == ' ' || c == '\t' || c == '\0';
}

void timestamp_to_string(char* str, size_t size, const timestamp_t* ts) {
    strftime(str, size, TIMESTAMP_STRING_FORMAT, ts);
}

timestamp_t* string_to_timestamp(const char* str) {
	if(str == NULL) return NULL;
    timestamp_t* timestamp = (timestamp_t*)malloc(sizeof(timestamp_t));
    strptime(str, TIMESTAMP_STRING_FORMAT, timestamp);
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

void alloc_and_arrcopy(char*** dest, char** src, int size){
    *dest = (char**)malloc(sizeof(char*) * size);
    for (size_t i = 0; i < size; i++){
        (*dest)[i] = src[i];
    }
}

void advance_to_next_target(char* string, int* current_char_index, char target) {
    char current = string[*current_char_index];
    while (current != '\0' && current != target) {
        (*current_char_index) += 1;
        current = string[*current_char_index];
    }
}

void advance_to_next_targets(char* string, int* current_char_index, const char* targets, int len) {
    char current = string[*current_char_index];
    while (current != '\0' && (*current_char_index) < len) {
        for (int i = 0; i < strlen(targets); i++) {
            if (current == targets[i]) {
                return;
            }
        }
        (*current_char_index) += 1;
        current = string[*current_char_index];
    }
}

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
){
    if (!*correct) return;
    advance_to_next_targets(string, current_char_index, targets, len);
    *correct &= (string[*current_char_index] == target);
    *correct &= (*current_char_index < len);
    if (*correct) {
        string[*current_char_index] = '\0';
    }
    (*current_char_index)++;
}

void skip_character_safe(
    char* string, int* current_char_index, int len,
    char target, const char* avoid, bool* correct
){
    if (!*correct) return;
    *correct &= (string[*current_char_index] == target);
    (*current_char_index)++;
    while (*current_char_index < len && string[*current_char_index] == target) {
        (*current_char_index)++;
    }
    for (int i = 0; i < strlen(avoid); i++) {
        *correct &= (string[*current_char_index] != avoid[i]);
    }
    *correct &= (*current_char_index < len);
}

void skip_hostname(
    char* string, int* current_char_index, 
    int len, bool* correct
){
    bool hostname_found = true;
    const char* hostname_pattern = "http://";
    for (int i = 0; i < 7; i++){
        hostname_found &= ((*current_char_index + i) < len);
        if (!hostname_found){
            break;
        }
        hostname_found &= (hostname_pattern[i] == string[*current_char_index + i]);
    }
    if (hostname_found){
        (*current_char_index) += 7;
        advance_to_next_targets(string, current_char_index, "/ \r\n\0", len);
        *correct &= (*current_char_index < len);
        *correct &= ( (string[*current_char_index] == '/') || (string[*current_char_index] == ' ') );
    }
}