#include "http.h"

void http_response_init(http_response_t* response){
    response->version = NULL;
    response->status = NULL;
    response->phrase = NULL;
    response->header_capacity = HTTP_RESPONSE_STARTING_HEADER_CAPACITY;
    response->header_names = (char**) malloc(sizeof(char*) * response->header_capacity);
    response->header_values = (char**) malloc(sizeof(char*) * response->header_capacity);
    response->headers_num = 0;
    response->payload = NULL;
}

char* http_response_encode(http_response_t* response, size_t* size){
    size_t buffer_size = 0;
    size_t current_char = 0;
    short version_size = strlen(response->version);
    short status_size = strlen(response->status);
    size_t phrase_size = strlen(response->phrase);
    size_t payload_size = response->payload != NULL ? strlen(response->payload) : 0;
    buffer_size += version_size + status_size + phrase_size + payload_size + 7;
    size_t header_names_size[response->headers_num];
    size_t header_values_size[response->headers_num];
    for(int i = 0; i < response->headers_num; i++){
        header_names_size[i] = strlen(response->header_names[i]);
        header_values_size[i] = strlen(response->header_values[i]);
        buffer_size += header_names_size[i] + header_values_size[i] + 4;
    }
    char* buffer = (char*)malloc(sizeof(char) * buffer_size);
    sprintf(buffer, "%s %s %s\r\n", response->version, response->status, response->phrase);
    current_char += version_size + status_size + phrase_size + 4;
    for(int i = 0; i < response->headers_num; i++){
        sprintf(buffer + current_char, "%s: %s\r\n", response->header_names[i], response->header_values[i]);
        current_char += header_names_size[i] + header_values_size[i] + 4;
    }
    sprintf(buffer + current_char, "\r\n%s", response->payload != NULL ? response->payload : "");
    *size = buffer_size - 1;
    return buffer;
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
    if(response->headers_num == response->header_capacity){
        response->header_capacity *= 2;
        response->header_names = (char**) realloc(response->header_names, sizeof(char*) * response->header_capacity);
        response->header_values = (char**) realloc(response->header_values, sizeof(char*) * response->header_capacity);
    }
    alloc_and_strcpy(&(response->header_names[response->headers_num]), name);
    alloc_and_strcpy(&(response->header_values[response->headers_num]), value);
    response->headers_num++;
}

void http_response_set_payload(http_response_t* response, const char* payload){
    alloc_and_strcpy(&(response->payload), payload);
}