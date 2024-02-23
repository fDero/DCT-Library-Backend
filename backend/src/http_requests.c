
#include "http.h"
#include "utils.h"
#include <stdio.h>

http_request_t* http_request_decode(char* http_request_str){
    
    // INIT
    http_request_t* request = (http_request_t*)malloc(sizeof(http_request_t));
    alloc_and_strcpy(&(request->source), http_request_str);
    int len = strlen(http_request_str);
    int current_char_index = 0;
    bool correct = true;
    
    
    // METHOD
    request->method = request->source + current_char_index;
    advance_to_next_whitespace(request->source, &current_char_index);
    correct &= (request->source[current_char_index] == ' ');
    correct &= (current_char_index < len);
    if (correct) {
        request->source[current_char_index] = '\0';
    }
    current_char_index++;


    // URL
    request->url = request->source + current_char_index;
    advance_to_next_whitespace(request->source, &current_char_index);
    correct &= (request->source[current_char_index] == ' ');
    correct &= (current_char_index < len);
    if (correct) {
        request->source[current_char_index] = '\0';
    }
    current_char_index++;


    // VERSION
    request->version = request->source + current_char_index;
    advance_to_next_carriage_return(request->source, &current_char_index);
    correct &= (request->source[current_char_index] == '\r');
    correct &= (current_char_index < len);
    if (correct) {
        request->source[current_char_index++] = '\0';
        correct &= (request->source[current_char_index++] == '\n');
    }


    // HEADERS
    request->headers = request->source + current_char_index;
    while (
        (request->source)[current_char_index] != '\r' && 
        (request->source)[current_char_index] != '\n' && 
        (request->source)[current_char_index] != '\0' 
    ){
        if (current_char_index >= len) {
            correct = false;
            break;
        }
        advance_to_next_carriage_return(request->source, &current_char_index);
        correct &= (request->source[current_char_index++] == '\r');
        correct &= (request->source[current_char_index++] == '\n');
    } 
    correct &= (current_char_index < len);
    if (correct){
        request->source[current_char_index - 1] = '\0';
    }
    correct &= (request->source[current_char_index++] == '\r');
    correct &= (request->source[current_char_index++] == '\n');
    

    // PAYLOAD
    request->payload = request->source + current_char_index;
    correct &= (request->payload - request->method) < len;
    

    // FINALIZE
    if (correct) {
        return request;
    }
    else {
        free(request->source);
        free(request);
        return NULL;
    }
}
