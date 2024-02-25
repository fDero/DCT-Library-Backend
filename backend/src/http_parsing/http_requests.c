
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

http_request_t* http_request_decode(char* http_request_str) {


    // INIT
    int len = strlen(http_request_str);
	if(len == 0) {
        return NULL;
    }
    http_request_t* request = (http_request_t*)malloc(sizeof(http_request_t));
    alloc_and_strcpy(&(request->source), http_request_str);
    int current_char_index = 0;
    bool correct = true;
    request->headers_num = 0;



    // HEADLINE
    request->method = request->source + current_char_index;
    skip_string_terminating_with_target_safe(request->source, &current_char_index, len, ' ', " \n\r", &correct);
    request->host = request->source + current_char_index;
    
    skip_hostname(request->source, &current_char_index, len, &correct);
    request->path = request->source + current_char_index;
    int request_path_index = current_char_index;

    /* QUERY PARAMETERS */
    char* query_param_names[MAX_PARAMS];
    char* query_param_values[MAX_PARAMS];
    int query_param_counter = 0;
    int x = current_char_index;
    advance_to_next_targets(request->source, &current_char_index, "? ");
    if (request->source[current_char_index] == '?'){
        do {
            request->source[current_char_index++] = '\0';
            if ((correct &= (++query_param_counter <= MAX_PARAMS))) {
                query_param_names[query_param_counter-1] = request->source + current_char_index;
                skip_string_terminating_with_target_safe(request->source, &current_char_index, len, '=', "= &\r\n\0", &correct);
                query_param_values[query_param_counter-1] = request->source + current_char_index;
                advance_to_next_targets(request->source, &current_char_index, " &\0\r\n=");
                correct &= (current_char_index < len);
                correct &= (request->source[current_char_index] != '\0');
                correct &= (request->source[current_char_index] != '\n');
                correct &= (request->source[current_char_index] != '\r');
                correct &= (request->source[current_char_index] != '=');
            }
        } while (
            correct && request->source[current_char_index] == '&'
        );
    } 
    else {
        current_char_index = x;
    }
    
    skip_string_terminating_with_target_safe(request->source, &current_char_index, len, ' ', " \n\r", &correct);
    request->version = request->source + current_char_index;
    
    skip_string_terminating_with_target_safe(request->source, &current_char_index, len, '\r', " \n\r", &correct);
    correct &= (request->source[current_char_index++] == '\n');


    char* header_names[MAX_HEADERS];
    char* header_values[MAX_HEADERS];
    /* HEADERS */ {
        while (
            (request->source)[current_char_index] != '\r' &&
            (request->source)[current_char_index] != '\n' &&
            (request->source)[current_char_index] != '\0' &&
            (correct &= (current_char_index < len))       &&
            (correct &= (request->headers_num < MAX_HEADERS))
        ) {
            header_names[request->headers_num] = request->source + current_char_index;
            skip_string_terminating_with_target_safe(request->source, &current_char_index, len, ':', ":\r\n", &correct);
            skip_character_safe(request->source, &current_char_index, len, ' ', "\r\n", &correct);
            header_values[request->headers_num++] = request->source + current_char_index;
            advance_to_next_carriage_return(request->source, &current_char_index);
            skip_string_terminating_with_target(request->source, &current_char_index, len, '\r', &correct);
            correct &= (request->source[current_char_index++] == '\n');
        }

        correct &= (current_char_index < len);
        correct &= (request->source[current_char_index++] == '\r');
        correct &= (request->source[current_char_index++] == '\n');
    }



    // PAYLOAD
    request->payload = request->source + current_char_index;
    correct &= (request->payload - request->method) < len;




    // FINALIZE
    correct &= (strcmp(request->method, "") != 0);
    correct &= (strcmp(request->version, "") != 0);
    correct &= (strcmp(request->path, "") != 0);
    correct &= !is_blank_char(request->version[0]);
    correct &= !is_blank_char(request->path[0]);
    correct &= !is_blank_char(request->method[0]);

    request->source[request_path_index] = '\0';
    request->path++;

    if (correct) {
        request->query_params_num = query_param_counter;
        request->header_names  = (char**)malloc(sizeof(char*) * request->headers_num);
        request->header_values = (char**)malloc(sizeof(char*) * request->headers_num);
        
        request->query_param_names = (char**)malloc(sizeof(char*) * request->query_params_num);
        request->query_param_values = (char**)malloc(sizeof(char*) * request->query_params_num);
        for (size_t i = 0; i < request->headers_num; i++) {
            request->header_names[i] = header_names[i];
            request->header_values[i] = header_values[i];
        }
        for (size_t i = 0; i < request->query_params_num; i++) {
            request->query_param_names[i] = query_param_names[i];
            request->query_param_values[i] = query_param_values[i];
        }
        return request;
    } else {
        free(request->source);
        free(request);
        return NULL;
    }
}