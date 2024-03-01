#include "respond.h"

http_response_t* respond(http_request_t* request){
	if(request == NULL){
		return response_bad_request(request);
	}
	if(strcmp(request->method,"GET") == 0){
		if(strcmp(request->path, "books") == 0){
			return response_get_books(request);
		}
		if(strcmp(request->path, "loans") == 0){
			return response_get_loans(request);
		}
		if(strcmp(request->path, "expired-loans") == 0){
			return response_get_expired_loans(request);
		}
		return response_not_found(request);
	}
	return response_method_not_allowed(request);
}