
#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"
#include "llhttp.h"
#include "curl/urlapi.h"

#define HTTP_RESPONSE_STARTING_HEADER_CAPACITY 8

extern pthread_key_t http_request_key;

#define STARTING_HEADERS_CAPACITY 16
#define STARTING_QUERY_PARAMS_CAPACITY 16
#define HEADERS_MULTIPLICATION_FACTOR 2
#define QUERY_PARAMS_MULTIPLICATION_FACTOR 2

struct header_line
{
	char const *name;
	char const *value;
};

struct query_param
{
	char const *name;
	char const *value;
};

typedef struct header_line header_line_t;
typedef struct query_param query_param_t;

struct http_request
{
	char const *_origin_addr;
	char *_source;
	size_t _headers_capacity;
	size_t _query_params_capacity;

	char const *method;
	char const *host;
	char const *path;
	query_param_t *query_params;
	char *version;
	header_line_t *headers;
	char const *payload;
	size_t headers_num;
	size_t query_params_num;
};

typedef struct http_request http_request_t;

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

http_request_t* http_request_decode(const char* http_request_str);
void http_request_destroy(http_request_t* http_request_ptr);

const char* get_header_value(http_request_t* request, const char* header_name);
const char* get_query_param_value(http_request_t* request, const char* query_param_name);

void http_response_init(http_response_t* response);
char* http_response_encode(http_response_t* response);
void http_response_destroy(http_response_t* response);
void http_response_set_version(http_response_t* response, const char* version);
void http_response_set_status(http_response_t* response, const char* status);
void http_response_set_phrase(http_response_t* response, const char* phrase);
void http_response_add_header(http_response_t* response, const char* name, const char* value);
void http_response_set_payload(http_response_t* response, const char* payload);

#endif