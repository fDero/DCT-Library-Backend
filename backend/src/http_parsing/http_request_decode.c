
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
    *correct &= *correct
        && (strcmp(request->method, "") != 0)
        && (strcmp(request->version, "") != 0)
        && (strcmp(request->path, "") != 0)
        && !is_blank_char(request->version[0])
        && !is_blank_char(request->path[0])
        && !is_blank_char(request->method[0]);
}

void validate_http_query_params(http_request_t* request, bool* correct, int len){
    for (int i = 0; i < request->query_params_num; i++){
        *correct &= *correct
            && (strcmp(request->query_param_names[i], "") != 0)
            && (strcmp(request->query_param_values[i], "") != 0);
    }
}

void finalize_http_request(http_request_t* request){
    int request_path_index = request->path - request->source;
    request->source[request_path_index] = '\0';
    request->path++;
}

http_request_t* http_request_decode(char* http_request_str) {

    int len = -1;
    if (http_request_str == NULL || (len = strlen(http_request_str)) <= 0){
        return NULL;
    }

    bool correct = true;
    http_request_t* request = http_request_init();
		// request->source = (char*)malloc(len + 1);
		// http_request_string_decode(http_request_str, request->source, len + 1, &correct);
		// console_log(RED, http_request_str);
		// console_log(BLUE, request->source);
		alloc_and_strcpy(&request->source, http_request_str);
    int current_char_index = 0;
    
		console_log(CYAN, "method(%d)\n", correct);
    parse_http_request_method(request, &current_char_index, len, &correct);
		console_log(CYAN, "host(%d)\n", correct);
    parse_http_request_host(request, &current_char_index, len, &correct);
		console_log(CYAN, "path(%d)\n", correct);
    parse_http_request_path(request, &current_char_index, len, &correct);
		console_log(CYAN, "query(%d)\n", correct);
    parse_http_request_query(request, &current_char_index, len, &correct);
		console_log(CYAN, "version(%d)\n", correct);
    parse_http_request_version(request, &current_char_index, len, &correct);
		console_log(CYAN, "headline(%d)\n", correct);
    parse_http_headline_termination(request, &current_char_index, len, &correct);
		console_log(CYAN, "headers(%d)\n", correct);
    parse_http_request_headers(request, &current_char_index, len, &correct);
		console_log(CYAN, "headers_termination(%d)\n", correct);
    parse_http_headers_termination(request, &current_char_index, len, &correct);
		console_log(CYAN, "payload(%d)\n", correct);
    parse_http_request_payload(request, &current_char_index, len, &correct);

    validate_http_request(request, &correct);
    validate_http_query_params(request, &correct, len);
    finalize_http_request(request);
    
    if(correct){
				console_log(GREEN, "Correct request\n");
        return request;
    } else {
				console_log(GREEN, "Incorrect request\n");
        http_request_destroy(request);
        return NULL;
    }
}