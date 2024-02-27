
#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

#define MAX_HEADERS 100
#define MAX_PARAMS 100
#define HTTP_RESPONSE_STARTING_HEADER_CAPACITY 8

struct http_request {
    char* source;
    char const* method;
    char const* host;
    char const* path;
    char ** query_param_names;
    char ** query_param_values;
    char const* version;
    char ** header_names;
    char ** header_values;
    char const* payload;
    int headers_num;
    int query_params_num;
};

struct http_response {
    char* version;
    char* status;
    char* phrase;
    char ** header_names;
    char ** header_values;
    int headers_num;
		int header_capacity;
    char* payload;
};

typedef struct http_request http_request_t;
typedef struct http_response http_response_t;
typedef struct http_header_pack http_header_pack;

http_request_t* http_request_decode(char* http_request_str);
void http_request_destroy(http_request_t* http_request_ptr);

void parse_http_request_method(http_request_t* request, int* current_char_index, int len, bool* correct);
void parse_http_request_host(http_request_t* request, int* current_char_index, int len, bool* correct);
void parse_http_request_path(http_request_t* request, int* current_char_index, int len, bool* correct);
void parse_http_request_version(http_request_t* request, int* current_char_index, int len, bool* correct);
void parse_http_headline_termination(http_request_t* request, int* current_char_index, int len, bool* correct);
void parse_http_request_payload(http_request_t* request, int* current_char_index, int len, bool* correct);
void parse_http_request_headers(http_request_t* request, int* current_char_index, int len, bool* correct);
void parse_http_request_query(http_request_t* request, int* current_char_index, int len, bool* correct);
void parse_http_headers_termination(http_request_t* request, int* current_char_index, int len, bool* correct);

void http_response_init(http_response_t* response);
char* http_response_encode(http_response_t* response);
void http_response_destroy(http_response_t* response);
void http_response_set_version(http_response_t* response, const char* version);
void http_response_set_status(http_response_t* response, const char* status);
void http_response_set_phrase(http_response_t* response, const char* phrase);
void http_response_add_header(http_response_t* response, const char* name, const char* value);
void http_response_set_payload(http_response_t* response, const char* payload);

#endif