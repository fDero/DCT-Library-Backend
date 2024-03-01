
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

bool check_query_params(
	char** expected_query_param_names, 
	int expected_query_param_num, 
	http_request_t* request,
	bool check_strict
){
	if (request->query_params_num != expected_query_param_num) {
		if (request->query_params_num > expected_query_param_num || check_strict == CHECK_STRICT){
			return false;
		}
	}
	for (int i = 0; i < expected_query_param_num; i++){
		bool query_param_found = false;
		for (int j = 0; j < request->query_params_num; j++){
			if (strcmp(expected_query_param_names[i], request->query_params[j].name) == 0){
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