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
            return response_get_loans(request, ALL_LOANS);
        }
        if(strcmp(request->path, "expired-loans") == 0){
             return response_get_loans(request, EXPIRED_LOANS);
        }
        if(strcmp(request->path, "account") == 0){
            return response_get_account(request);
        }
        return response_not_found(request);
    }

    if(strcmp(request->method,"POST") == 0){
        if(strcmp(request->path, "login") == 0){
            return response_post_login(request);
        }
        if(strcmp(request->path, "registration") == 0){
            return response_post_registration(request);
        }
        if(strcmp(request->path, "loans") == 0){
            return response_post_loans(request);
        }
        if(strcmp(request->path, "returns") == 0){
            return response_post_returns(request);
        }
        return response_not_found(request);
    }

    return response_method_not_allowed(request);
}
