
#include "http.h"
#include "utils.h"
#include <ctype.h>
#include <stdio.h>
	
void http_request_destroy(http_request_t* http_request_ptr){
    free(http_request_ptr->header_names);
    free(http_request_ptr->header_values);
    free(http_request_ptr->query_param_names);
    free(http_request_ptr->query_param_values);
    free(http_request_ptr->source);
    free(http_request_ptr);
};

http_request_t* http_request_init(){
    http_request_t* request = (http_request_t*)malloc(sizeof(http_request_t));
    request->source = NULL;
    request->headers_num = 0;
    request->query_params_num = 0;
    request->header_names = NULL;
    request->header_values = NULL;
    request->query_param_names = NULL;
    request->query_param_values = NULL;
    return request;
}

void validate_http_request(http_request_t* request, bool* correct){
    *correct &= (strcmp(request->method, "") != 0);
    *correct &= (strcmp(request->version, "") != 0);
    *correct &= (strcmp(request->path, "") != 0);
    *correct &= !is_blank_char(request->version[0]);
    *correct &= !is_blank_char(request->path[0]);
    *correct &= !is_blank_char(request->method[0]);
}

void finalize_http_request(http_request_t* request, int request_path_index){
    request->source[request_path_index] = '\0';
    request->path++;
}

http_request_t* http_request_decode(char* http_request_str) {

    int len = -1;
    if (http_request_str == NULL || (len = strlen(http_request_str)) <= 0){
        return NULL;
    }

    http_request_t* request = http_request_init();
    alloc_and_strcpy(&(request->source), http_request_str);
    int current_char_index = 0;
    bool correct = true;
    
    int request_method_index   = parse_http_request_method(request, &current_char_index, len, &correct);
    int request_path_index     = parse_http_request_host(request, &current_char_index, len, &correct);
    int request_query_index    = parse_http_request_query(request, &current_char_index, len, &correct);
    int request_headline_index = parse_http_headline_termintaion(request, &current_char_index, len, &correct);
    int request_headers_index  = parse_http_request_headers(request, &current_char_index, len, &correct);
    int request_payload_index  = parse_http_request_payload(request, &current_char_index, len, &correct);

    validate_http_request(request, &correct);
    finalize_http_request(request, request_path_index);
    
    if(correct){
        return request;
    } else {
        http_request_destroy(request);
        return NULL;
    }
}