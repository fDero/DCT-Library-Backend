
#include "http.h"
#include "utils.h"
#include <ctype.h>
#include <stdio.h>

void http_request_destroy(http_request_t *http_request){
    free(http_request->query_params);
    free(http_request->_source);
    free(http_request->headers);
    free(http_request->version);
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

bool http_request_validate_query_params(
    http_request_t* request,
    char const ** expected_query_param_names, 
    int expected_query_param_num, 
    bool check_type
){
    if (request->query_params_num != expected_query_param_num) {
        if (request->query_params_num > expected_query_param_num || check_type == HTTP_CHECK_STRICT){
            return false;
        }
    }
    for (int i = 0; i < request->query_params_num; i++){
        bool query_param_found = false;
        for (int j = 0; j < expected_query_param_num; j++){
            if (strcmp(request->query_params[i].name, expected_query_param_names[j]) == 0){
                query_param_found = true;
                break;
            }
        }
        if (!query_param_found){
            return false;
        }
    }
    return true;
}

bool http_request_contains_query(http_request_t* request){
    return request->query_params_num > 0;
}

bool http_request_contains_payload(http_request_t* request){
    return request->payload != NULL && request->payload[0];
}