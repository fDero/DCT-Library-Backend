
#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_HEADERS 100

struct http_request {
  char* source;
  char const* method;
	char const* url;
	char const* version;
	char const* headers;
	char ** header_names;
	char ** header_values;
	char const* payload;
	int headers_num;
};

struct http_response {
    char* source;
    char* version;
	char* status;
	char* phrase;
	char* headers;
	char* payload;
};

struct http_header_pack {
	char** header_fields;
	char** header_values;
};

typedef struct http_request http_request_t;
typedef struct http_response http_response_t;
typedef struct http_header_pack http_header_pack;

http_request_t* http_request_decode(char* http_request_str);

#endif