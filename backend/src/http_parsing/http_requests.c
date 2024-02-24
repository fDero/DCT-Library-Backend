
#include "http.h"
#include "utils.h"
#include <ctype.h>
#include <stdio.h>
	
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
    advance_to_next_targets(string, current_char_index, targets);
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

bool is_blank_char(char c){
    return c == '\r' || c == '\n' ||
    c == ' ' || c == '\t' || c == '\0';
}

void http_request_destroy(http_request_t* http_request_ptr){
    free(http_request_ptr->header_names);
    free(http_request_ptr->header_values);
    free(http_request_ptr->source);
    free(http_request_ptr);
};

http_request_t* http_request_decode(char* http_request_str) {
    
    // INIT
    http_request_t* request = (http_request_t*)malloc(sizeof(http_request_t));
    alloc_and_strcpy(&(request->source), http_request_str);
    int len = strlen(http_request_str);
    int current_char_index = 0;
    bool correct = true;
    char* header_names[MAX_HEADERS];
    char* header_values[MAX_HEADERS];
    request->headers_num = 0;

    // HEADLINE
    request->method = request->source + current_char_index;
    skip_string_terminating_with_target_safe(request->source, &current_char_index, len, ' ', " \n\r", &correct);
    request->url = request->source + current_char_index;
    skip_string_terminating_with_target_safe(request->source, &current_char_index, len, ' ', " \n\r", &correct);
    request->version = request->source + current_char_index;
    skip_string_terminating_with_target_safe(request->source, &current_char_index, len, '\r', " \n\r", &correct);
    correct &= (request->source[current_char_index++] == '\n');

    /* HEADERS */ {
        while (
            (request->source)[current_char_index] != '\r' &&
            (request->source)[current_char_index] != '\n' &&
            (request->source)[current_char_index] != '\0' &&
            (correct &= (current_char_index < len))       &&
            (correct &= (request->headers_num < MAX_HEADERS))
        ) {
            header_names[request->headers_num] = request->source + current_char_index;
            skip_string_terminating_with_target_safe(request->source, &current_char_index, len, ':', ":\r\n", &correct);
            skip_character_safe(request->source, &current_char_index, len, ' ', "\r\n", &correct);
            header_values[request->headers_num++] = request->source + current_char_index;
            advance_to_next_carriage_return(request->source, &current_char_index);
            skip_string_terminating_with_target(request->source, &current_char_index, len, '\r', &correct);
            correct &= (request->source[current_char_index++] == '\n');
        }

        correct &= (current_char_index < len);
        correct &= (request->source[current_char_index++] == '\r');
        correct &= (request->source[current_char_index++] == '\n');
    }

    // PAYLOAD
    request->payload = request->source + current_char_index;
    correct &= (request->payload - request->method) < len;

    // FINALIZE
    correct &= (strcmp(request->method, "") != 0);
    correct &= (strcmp(request->version, "") != 0);
    correct &= (strcmp(request->url, "") != 0);
    correct &= !is_blank_char(request->version[0]);
    correct &= !is_blank_char(request->url[0]);
    correct &= !is_blank_char(request->method[0]);
    if (correct) {
        request->header_names  = (char**)malloc(sizeof(char*) * request->headers_num);
        request->header_values = (char**)malloc(sizeof(char*) * request->headers_num);
        for (size_t i = 0; i < request->headers_num; i++) {
            request->header_names[i] = header_names[i];
            request->header_values[i] = header_values[i];
        }
        return request;
    } else {
        free(request->source);
        free(request);
        return NULL;
    }
}