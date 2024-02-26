#include "http.h"

// struct http_response {
//     char* version;
//     char* status;
//     char* phrase;
//     char ** header_names;
//     char ** header_values;
//     int headers_num;
//     char* payload;
// };

void http_response_init(http_response_t* response) {
	response->version = NULL;
	response->status = NULL;
	response->phrase = NULL;
	response->header_names = NULL;
	response->header_values = NULL;
	response->headers_num = 0;
	response->payload = NULL;
}

char* http_response_encode(http_response_t* response) {
    //TODO
		return NULL;
}

void http_response_destroy(http_response_t* response){
	free(response->version);
	free(response->status);
	free(response->phrase);
	for(int i = 0; i < response->headers_num; i++){
		free(response->header_names[i]);
		free(response->header_values[i]);
	}
	free(response->header_names);
	free(response->header_values);
	free(response->payload);
	free(response);
}

void http_response_set_version(http_response_t* response, const char* version){
	alloc_and_strcpy(&(response->version), version);
}

void http_response_set_status(http_response_t* response, const char* status){
	alloc_and_strcpy(&(response->status), status);
}

void http_response_set_phrase(http_response_t* response, const char* phrase){
	alloc_and_strcpy(&(response->phrase), phrase);
}

void http_response_add_header(http_response_t* response, const char* name, const char* value){
	//TODO
}

void http_response_set_payload(http_response_t* response, const char* payload){
	alloc_and_strcpy(&(response->payload), payload);
}