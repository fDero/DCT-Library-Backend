
#include "http.h"
#include "utils.h"
#include <ctype.h>
#include <stdio.h>
	
void parse_http_request_method(http_request_t* request, int* current_char_index, int len, bool* correct){
    request->method = request->source + *current_char_index;
    skip_string_terminating_with_target_safe(request->source, current_char_index, len, ' ', " \n\r", correct);
}

void parse_http_request_host(http_request_t* request, int* current_char_index, int len, bool* correct){
    request->host = request->source + *current_char_index;
    skip_hostname(request->source, current_char_index, len, correct);
}

void parse_http_request_path(http_request_t* request, int* current_char_index, int len, bool* correct){
    request->path = request->source + *current_char_index;
    int x = *current_char_index;
    advance_to_next_targets(request->source, current_char_index, "? ");
    if (request->source[*current_char_index] != '?'){
        *current_char_index = x;
    }
}

void parse_http_request_version(http_request_t* request, int* current_char_index, int len, bool* correct){
    skip_string_terminating_with_target_safe(request->source, current_char_index, len, ' ', " \n\r", correct);
    request->version = request->source + *current_char_index;
}

void parse_http_headline_termination(http_request_t* request, int* current_char_index, int len, bool* correct){
    skip_string_terminating_with_target_safe(request->source, current_char_index, len, '\r', " \n\r", correct);
    *correct &= (request->source[(*current_char_index)++] == '\n');
}

void parse_http_request_payload(http_request_t* request, int* current_char_index, int len, bool* correct){
    request->payload = request->source + *current_char_index;
    *correct &= (request->payload - request->method) < len;
}

void parse_http_headers_termination(http_request_t* request, int* current_char_index, int len, bool* correct){
    *correct &= (*current_char_index < len);
    *correct &= (request->source[(*current_char_index)++] == '\r');
    *correct &= (request->source[(*current_char_index)++] == '\n');
}
