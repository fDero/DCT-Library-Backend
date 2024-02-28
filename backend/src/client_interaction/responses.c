#include "respond.h"

http_response_t* basic_response(http_request_t* request){
	http_response_t* response = (http_response_t*)malloc(sizeof(http_response_t));
	http_response_init(response);
	http_response_set_version(response, "HTTP/1.1");
	http_response_add_header(response, "Server", server);
	char* now = get_current_http_time();
	http_response_add_header(response, "Date", now);
	http_response_add_header(response, "Content-Language", "en");
	free(now);
	return response;
}

http_response_t* response_bad_request(http_request_t* request){
	http_response_t* response = basic_response(request);
	http_response_set_status(response, "400");
	http_response_set_phrase(response, "Bad Request");
	http_response_add_header(response, "Connection", "close");
	return response;
}

http_response_t* response_unauthorized(http_request_t* request){
	http_response_t* response = basic_response(request);
	http_response_set_status(response, "401");
	http_response_set_phrase(response, "Unauthorized");
	http_response_add_header(response, "Connection", "close");
	return response;
}

http_response_t* response_get_books(http_request_t* request){
	http_response_t* response = basic_response(request);
	http_response_set_status(response, "200");
	http_response_set_phrase(response, "OK");
	http_response_add_header(response, "Connection", "keep-alive");
	db_conn_t* connection = (db_conn_t*) pthread_getspecific(db_conn_key);
	
	const char* title = get_query_param_value(request, "title");
	const char* author = get_query_param_value(request, "author");
	const char* publisher = get_query_param_value(request, "publisher");
	const char* genres = get_query_param_value(request, "genres");
	const char* release_date = get_query_param_value(request, "release_date");
	const timestamp_t* release_date_timestamp = string_to_timestamp(release_date);
	const char* ids = get_query_param_value(request, "id");
	book_array_t* books;
	if(ids!=NULL){
		books = get_books_by_ids(connection, ids);
	}
	else {
		books = get_books_by_data_match(connection, title, author, publisher, genres, release_date_timestamp, 200);
	}

	char* payload = book_array_to_json_string(books);
	http_response_set_payload(response, payload);

	http_response_add_header(response, "Content-Type", "application/json");
	char buff[20];
	sprintf(buff, "%lu", strlen(payload));
	http_response_add_header(response, "Content-Length", buff);
	book_array_destroy(books);
	free(payload);
	return response;
}

http_response_t* response_get_loans(http_request_t* request){
	http_response_t* response = basic_response(request);
	http_response_set_status(response, "200");
	http_response_set_phrase(response, "OK");
	http_response_add_header(response, "Connection", "keep-alive");
	db_conn_t* connection = (db_conn_t*) pthread_getspecific(db_conn_key);
	
	int id = atoi(get_query_param_value(request, "account_id"));

	loan_array_t* loans = (id != 0 ? get_loans_by_account_id(connection, id) : NULL);
	
	char* payload = loan_array_to_json_string(loans);
	http_response_set_payload(response, payload);

	http_response_add_header(response, "Content-Type", "application/json");
	char buff[20];
	sprintf(buff, "%lu", strlen(payload));
	http_response_add_header(response, "Content-Length", buff);
	loan_array_destroy(loans);
	free(payload);
	return response;
}