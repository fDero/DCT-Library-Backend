
#include "http.h"
#include "utils.h"
#include <ctype.h>
#include <stdio.h>

void parse_http_request_query(http_request_t* request, int* current_char_index, int len, bool* correct){
    char* query_param_names[MAX_PARAMS];
    char* query_param_values[MAX_PARAMS];
    int query_param_counter = 0;
    while (correct && (request->source[*current_char_index] == '&' || request->source[*current_char_index] == '?')) {
        request->source[*current_char_index] = '\0';
        (*current_char_index)++;
        if ((*correct &= (++query_param_counter <= MAX_PARAMS))) {
            query_param_names[query_param_counter-1] = request->source + *current_char_index;
            skip_string_terminating_with_target_safe(request->source, current_char_index, len, '=', "= &\r\n\0", correct);
            query_param_values[query_param_counter-1] = request->source + *current_char_index;
            advance_to_next_targets(request->source, current_char_index, " &\0\r\n=", len);
            *correct &= (*current_char_index < len);
            *correct &= (request->source[*current_char_index] != '\0');
            *correct &= (request->source[*current_char_index] != '\n');
            *correct &= (request->source[*current_char_index] != '\r');
            *correct &= (request->source[*current_char_index] != '=');
        }
    }
    if (*correct) {
        alloc_and_arrcopy(&(request->query_param_names), query_param_names, query_param_counter);
        alloc_and_arrcopy(&(request->query_param_values), query_param_values, query_param_counter);
        request->query_params_num = query_param_counter;
    }
}

void parse_http_request_headers(http_request_t* request, int* current_char_index, int len, bool* correct){
    char* header_names[MAX_HEADERS];
    char* header_values[MAX_HEADERS];
    while (
        (request->source)[*current_char_index] != '\r' &&
        (request->source)[*current_char_index] != '\n' &&
        (request->source)[*current_char_index] != '\0' &&
        (*correct &= (*current_char_index < len))      &&
        (*correct &= (request->headers_num < MAX_HEADERS))
    ) {
        header_names[request->headers_num] = request->source + *current_char_index;
        skip_string_terminating_with_target_safe(request->source, current_char_index, len, ':', ":\r\n\0", correct);
        if (!(*correct)) return;
        *correct &= (request->source[*current_char_index] == ' ');
        (*current_char_index)++;
        header_values[request->headers_num++] = request->source + *current_char_index;
        skip_string_terminating_with_target_safe(request->source, current_char_index, len, '\r', "\r\n\0", correct);
        *correct &= (request->source[*current_char_index] == '\n');
        (*current_char_index)++;
    }
    if (*correct) {
        alloc_and_arrcopy(&(request->header_names), header_names, request->headers_num);
        alloc_and_arrcopy(&(request->header_values), header_values, request->headers_num);
    }
}
