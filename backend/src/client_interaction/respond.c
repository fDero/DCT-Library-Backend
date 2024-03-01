#include "respond.h"

http_response_t* respond(http_request_t* request){
	if(request == NULL){
		return response_bad_request(request);
	}
	if(!strcmp(request->method,"GET")){
		if(!strcmp(request->path, "books")){
			return response_get_books(request);
		}
		if(!strcmp(request->path, "loans")){
			return response_get_loans(request);
		}
		return response_not_found(request);
	}
	return response_method_not_allowed(request);
}