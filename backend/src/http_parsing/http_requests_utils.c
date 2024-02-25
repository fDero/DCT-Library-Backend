
#include "http.h"
#include "utils.h"
#include <ctype.h>
#include <stdio.h>
	
int parse_http_request_method(http_request_t* request, int* current_char_index, int len, bool* correct){
    request->method = request->source + *current_char_index;
    skip_string_terminating_with_target_safe(request->source, current_char_index, len, ' ', " \n\r", correct);
    return *current_char_index;
}

int parse_http_request_host(http_request_t* request, int* current_char_index, int len, bool* correct){
    request->host = request->source + *current_char_index;
    skip_hostname(request->source, current_char_index, len, correct);
    request->path = request->source + *current_char_index;
    return *current_char_index;
}

int parse_http_headline_termintaion(http_request_t* request, int* current_char_index, int len, bool* correct){
    skip_string_terminating_with_target_safe(request->source, current_char_index, len, ' ', " \n\r", correct);
    request->version = request->source + *current_char_index;
    skip_string_terminating_with_target_safe(request->source, current_char_index, len, '\r', " \n\r", correct);
    *correct &= (request->source[(*current_char_index)++] == '\n');
    return *current_char_index;
}

int parse_http_request_payload(http_request_t* request, int* current_char_index, int len, bool* correct){
    request->payload = request->source + *current_char_index;
    *correct &= (request->payload - request->method) < len;
    return *current_char_index;
}
