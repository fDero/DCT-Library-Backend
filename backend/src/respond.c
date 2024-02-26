#include "respond.h"

http_response_t* respond(http_request_t* request){
	if(request == NULL){
		return response_bad_request(request);
	}
	if(!strcmp(request->method,"GET")){
		if(!strcmp(request->path, "books")){
			return response_get_books(request);
		}
		return response_bad_request(request);
	}
	return response_bad_request(request);
}