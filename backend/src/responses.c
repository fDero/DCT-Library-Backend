#include "respond.h"

http_response_t* response_bad_request(http_request_t* request){
	return NULL;
}

http_response_t* response_not_authenticated(http_request_t* request){
	return NULL;
}

http_response_t* response_get_books(http_request_t* request){
	http_response_t* response = (http_response_t*)malloc(sizeof(http_response_t));
	http_response_init(response);
	http_response_set_version(response, "HTTP/1.1");
	http_response_set_status(response, "200");
	http_response_set_phrase(response, "OK");
	db_conn_t* connection = (db_conn_t*) pthread_getspecific(db_conn_key);
	book_array_t* books = get_books(connection, 100);
	http_response_set_payload(response, book_array_to_json_string(books));
	book_array_destroy(books);
	return response;
}