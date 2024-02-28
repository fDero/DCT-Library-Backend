#ifndef RESPOND_H
#define RESPOND_H

#include "http.h"
#include "authentication.h"
#include "queries.h"
#include "pthread.h"
#include "json.h"
#include "data_objects.h"
#include "db_utils.h"
#include "utils.h"

extern char *server;

http_response_t* respond(http_request_t* request);

http_response_t* response_bad_request(http_request_t* request);
http_response_t* response_unauthorized(http_request_t* request);
http_response_t* response_get_books(http_request_t* request);
http_response_t* response_get_loans(http_request_t* request);

#endif