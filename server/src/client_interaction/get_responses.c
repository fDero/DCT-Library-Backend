
#include "respond.h"

http_response_t* response_get_books(http_request_t* request){
    char const * valid_params[] = {"title", "author", "publisher", "genres", "release-date", "id"};
    if(http_request_contains_payload(request) || !http_request_validate_query_params(request, valid_params, 6, HTTP_CHECK_LOSE)){
        return response_bad_request(request);
    }

    decoded_jwt_t* token = authorize(request);
    char* new_token = NULL;
    if(token != NULL && is_jwt_about_to_expire(token)){    
        const char* desired_exp = get_header_value(request, "X-Token-Duration");
        char* new_token = generate_token(token->account_id, get_token_duration(desired_exp));
    }

    http_response_t* response = basic_response(request);
    http_response_set_status(response, "200");
    http_response_set_phrase(response, "OK");
    db_conn_t* connection = (db_conn_t*) pthread_getspecific(db_conn_key);
	
    const char* title = get_query_param_value(request, "title");
    const char* author = get_query_param_value(request, "author");
    const char* publisher = get_query_param_value(request, "publisher");
    const char* genres = get_query_param_value(request, "genres");
    const char* release_date = get_query_param_value(request, "release-date");
    const char* ids = get_query_param_value(request, "id");
    book_array_t* books;
    books = get_books_by_data_match(connection, ids, title, author, publisher, genres, release_date, 200);

    char* payload = book_array_to_json_string(books);
    http_response_set_payload(response, payload);

    http_response_add_header(response, "Content-Type", "application/json");
    char buff[20];
    sprintf(buff, "%lu", strlen(payload));
    http_response_add_header(response, "Content-Length", buff);

    if(new_token != NULL){
        http_response_add_header(response, "Set-Cookie", new_token);
    }

    decoded_jwt_destroy(token);
    free(new_token);
    book_array_destroy(books);
    free(payload);
    return response;
}

http_response_t* response_get_loans(http_request_t* request, int loans_type){

    if (http_request_contains_payload(request) || http_request_contains_query(request)){
        return response_bad_request(request);
    }

    decoded_jwt_t* token = authorize(request);
    char* new_token = NULL;
    if(token == NULL){
        return response_unauthorized(request);
    }
    if(is_jwt_about_to_expire(token)){
        const char* desired_exp = get_header_value(request, "X-Token-Duration");
        char* new_token = generate_token(token->account_id, get_token_duration(desired_exp));
    }

    http_response_t* response = basic_response(request);
    http_response_set_status(response, "200");
    http_response_set_phrase(response, "OK");
    db_conn_t* connection = (db_conn_t*) pthread_getspecific(db_conn_key);
    loan_array_t* loans = (loans_type == ALL_LOANS ? get_loans_by_account_id(connection, token->account_id) : get_expired_loans_by_account_id(connection, token->account_id));

    char* payload = loan_array_to_json_string(loans);
    http_response_set_payload(response, payload);
    http_response_add_header(response, "Content-Type", "application/json");
    char buff[20];
    sprintf(buff, "%lu", strlen(payload));
    http_response_add_header(response, "Content-Length", buff);

    if(new_token != NULL){
        http_response_add_header(response, "Set-Cookie", new_token);
    }

    decoded_jwt_destroy(token);
    free(new_token);
    loan_array_destroy(loans);
    free(payload);
    return response;
}

http_response_t* response_get_account(http_request_t* request){

    if (http_request_contains_payload(request) || http_request_contains_query(request)){
        return response_bad_request(request);
    }

    decoded_jwt_t* token = authorize(request);
    char* new_token = NULL;
    if(token == NULL){
        return response_unauthorized(request);
    }
    if(is_jwt_about_to_expire(token)){
        const char* desired_exp = get_header_value(request, "X-Token-Duration");
        char* new_token = generate_token(token->account_id, get_token_duration(desired_exp));
    }
    http_response_t* response = basic_response(request);
    http_response_set_status(response, "200");
    http_response_set_phrase(response, "OK");
    
    db_conn_t* connection = (db_conn_t*) pthread_getspecific(db_conn_key);
    account_t* account = get_account_by_id(connection, token->account_id);
    char* payload = account_to_json_string(account);
    http_response_set_payload(response, payload);
    http_response_add_header(response, "Content-Type", "application/json");
    char buff[20];
    sprintf(buff, "%lu", strlen(payload));
    http_response_add_header(response, "Content-Length", buff);

    if(new_token != NULL){
        http_response_add_header(response, "Set-Cookie", new_token);
    }

    decoded_jwt_destroy(token);
    free(new_token);
    account_destroy(account);
    free(payload);

    return response;
}