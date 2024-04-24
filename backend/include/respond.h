#ifndef RESPOND_H
#define RESPOND_H

#include "http.h"
#include "queries.h"
#include "pthread.h"
#include "json.h"
#include "data_objects.h"
#include "db_utils.h"
#include "utils.h"
#include "jwt.h"

#define ALL_LOANS 1
#define EXPIRED_LOANS 0

extern char *server;

http_response_t* respond(http_request_t* request);

decoded_jwt_t* authorize(http_request_t* request);
char* generate_token(int account_id, unsigned long exp_time);

http_response_t* basic_response(http_request_t* request);

http_response_t* response_bad_request(http_request_t* request);
http_response_t* response_unauthorized(http_request_t* request);
http_response_t* response_not_found(http_request_t* request);
http_response_t* response_method_not_allowed(http_request_t* request);

http_response_t* response_get_books(http_request_t* request);
http_response_t* response_get_loans(http_request_t* request, int loans_type);
http_response_t* response_get_account(http_request_t* request);

http_response_t* response_post_login(http_request_t* request);
http_response_t* response_post_registration(http_request_t* request);
http_response_t* response_post_loans(http_request_t* request);
http_response_t* response_post_returns(http_request_t* request);

http_response_t* response_unsupported_media_type(http_request_t* request);
http_response_t* response_not_acceptable(http_request_t* request);
http_response_t* response_conflict(http_request_t* request);
http_response_t* response_unprocessable_entity(http_request_t* request);
http_response_t* response_unimplemented(http_request_t* request);

#endif
