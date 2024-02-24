
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
		char* header_names[MAX_HEADERS];
		char* header_values[MAX_HEADERS];
		request->headers_num = 0;
    
    
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
        (request->source)[current_char_index] != '\0' &&
				(correct &= request->headers_num) < MAX_HEADERS
    ){
        if (current_char_index >= len) {
            correct = false;
            break;
        }
				header_names[request->headers_num] = request->source + current_char_index;
				advance_to_next_targets(request->source, &current_char_index, ":\r\n");
				correct &= (request->source[current_char_index] == ':');
    		correct &= (current_char_index < len);
				if(correct){ 
					request->source[current_char_index++] = '\0';
				}
				correct &= (request->source[current_char_index++] == ' ');
				while(current_char_index < len && request->source[current_char_index] == ' '){
					current_char_index++;
				}
        correct &= (request->source[current_char_index] != '\r');
        correct &= (request->source[current_char_index] != '\n');
    		correct &= (current_char_index < len);
				if(correct){
					header_values[request->headers_num++] = request->source + current_char_index;
				}
        advance_to_next_carriage_return(request->source, &current_char_index);
        correct &= (request->source[current_char_index] == '\r');
				if(correct){
        	request->source[current_char_index++] = '\0';
				}
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
				request->header_names = (char**) malloc (sizeof(char*) * request->headers_num);
				request->header_values = (char**) malloc (sizeof(char*) * request->headers_num);
				for(size_t i = 0; i < request->headers_num; i++){
					request->header_names[i] = header_names[i];
					request->header_values[i] = header_values[i];
				}
        return request;
    }
    else {
        free(request->source);
        free(request);
        return NULL;
    }
}