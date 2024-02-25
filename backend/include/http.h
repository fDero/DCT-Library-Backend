
#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_HEADERS 100
#define MAX_PARAMS 100

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
    char* source;
    char* version;
    char* status;
    char* phrase;
    char* headers;
    char* payload;
};

typedef struct http_request http_request_t;
typedef struct http_response http_response_t;
typedef struct http_header_pack http_header_pack;

http_request_t* http_request_decode(char* http_request_str);
void http_request_destroy(http_request_t* http_request_ptr);

int parse_http_request_method(http_request_t* request, int* current_char_index, int len, bool* correct);
int parse_http_request_host(http_request_t* request, int* current_char_index, int len, bool* correct);
int parse_http_headline_termintaion(http_request_t* request, int* current_char_index, int len, bool* correct);
int parse_http_request_payload(http_request_t* request, int* current_char_index, int len, bool* correct);
int parse_http_request_headers(http_request_t* request, int* current_char_index, int len, bool* correct);
int parse_http_request_query(http_request_t* request, int* current_char_index, int len, bool* correct);

#endif