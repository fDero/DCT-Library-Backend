
#include "http.h"
#include "utils.h"
#include <ctype.h>
#include <stdio.h>

void http_request_destroy(http_request_t *http_request)
{
	free(http_request->headers);
	free(http_request->query_params);
	free(http_request->_source);
	free(http_request);
};

const char* get_header_value(http_request_t* request, const char* header_name){
    for (int i = 0; i < request->headers_num; i++){
        if (strcmp(request->headers[i].name, header_name) == 0){
            return request->headers[i].value;
        }
    }
    return NULL;
}

const char* get_query_param_value(http_request_t* request, const char* query_param_name){
    for (int i = 0; i < request->query_params_num; i++){
        if (strcmp(request->query_params[i].name, query_param_name) == 0){
            return request->query_params[i].value;
        }
    }
    return NULL;
}