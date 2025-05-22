
#include "respond.h"
#include "json.h"
#include "jwt.h"
#include "queries.h"
#include "cache.h"
#include "hash.h"

http_response_t* response_post_login(http_request_t* request){
    if (http_request_contains_query(request)){
        return response_bad_request(request);
    }
    const char* content_type = get_header_value(request, "Content-Type");
    const char* accept = get_header_value(request, "Accept");
    if (content_type == NULL || strcmp(content_type, "application/json") != 0){
        return response_unsupported_media_type(request);
    }
    if (accept != NULL && strstr(accept, "application/json") == NULL){
        return response_not_acceptable(request);
    }
    json_t* json = json_from_string(request->payload);
    char* email = NULL;
    char* password = NULL;
    if (
        number_of_json_fields(json) != 2 ||
        !extract_text_from_json(json, "email", &email) ||
        !extract_text_from_json(json, "password", &password)
    ){
        free(email);
        free(password);
        return response_unprocessable_entity(request);
    }
    json_destroy(json);
    db_conn_t* connection = (db_conn_t*) pthread_getspecific(db_conn_key);
    char* salt = get_password_salt(connection, email);
    char* hashed_password = sha256_salted_hash_alnum(password, salt);
    int id = validate_account(connection, email, hashed_password);
    if (id >= 1) {
        http_response_t* response = basic_response(request);
        http_response_set_status(response, "200");
	    http_response_set_phrase(response, "OK");
        const char* desired_exp = get_header_value(request, "X-Token-Duration");
        char* token = generate_token(id, get_token_duration(desired_exp));
        http_response_add_header(response, "Set-Cookie", token);
        free(salt);
        free(token);
        free(hashed_password);
        free(email);
        free(password);
        return response;
    }
    free(salt);
    free(hashed_password);
    free(email);
    free(password);
    return response_unauthorized(request);
}

http_response_t* response_post_registration(http_request_t* request){
    if (http_request_contains_query(request)){
        return response_bad_request(request);
    }
    const char* content_type = get_header_value(request, "Content-Type");
    const char* accept = get_header_value(request, "Accept");
    if (content_type == NULL || strcmp(content_type, "application/json") != 0){
        return response_unsupported_media_type(request);
    }
    if (accept != NULL && strstr(accept, "application/json") == NULL){
        return response_not_acceptable(request);
    }
    json_t* json = json_from_string(request->payload);
    char* name = NULL;
    char* surname = NULL;
    char* email = NULL;
    char* password = NULL;
    if (
        number_of_json_fields(json) != 4 ||
        !extract_text_from_json(json, "name", &name) ||
	    !extract_text_from_json(json, "surname", &surname) ||
        !extract_text_from_json(json, "email", &email) ||
	    !extract_text_from_json(json, "password", &password)
    ){
        free(name);
        free(surname);
        free(email);
        free(password);
        return response_unprocessable_entity(request);
    }
    json_destroy(json);
    db_conn_t* connection = (db_conn_t*) pthread_getspecific(db_conn_key);
    char* salt = sha256_hash_string_alnum(email);
    char* hashed_password = sha256_salted_hash_alnum(password, salt);
    account_t* account;
    char* error_code = NULL;
    int account_id = insert_account(connection, name, surname, email, hashed_password, salt, &error_code);
    free(hashed_password);
    free(name);
    free(surname);
    free(email);
    free(password);
    free(salt);
    if (account_id > 0) {
        http_response_t* response = basic_response(request);
        http_response_set_status(response, "200");
	    http_response_set_phrase(response, "OK");
        const char* desired_exp = get_header_value(request, "X-Token-Duration");
        char* token = generate_token(account_id, get_token_duration(desired_exp));
        http_response_add_header(response, "Set-Cookie", token);
        free(token);
        return response;
    }
    return response_conflict(request);
}

http_response_t* response_post_returns(http_request_t* request){
    if (http_request_contains_query(request)){
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

    const char* content_type = get_header_value(request, "Content-Type");
    if (content_type == NULL || strcmp(content_type, "application/json") != 0){
        return response_unsupported_media_type(request);
    }

    const char* accept = get_header_value(request, "Accept");
    if (accept != NULL && strstr(accept, "application/json") == NULL){
        return response_not_acceptable(request);
    }

    json_t* json = json_from_string(request->payload);
    int_array_t* loan_ids = int_array_from_json(json);
    json_destroy(json);

    if(loan_ids == NULL){
        return response_unprocessable_entity(request);
    }

    db_conn_t* connection = (db_conn_t*) pthread_getspecific(db_conn_key);
    json_t* successful_loans = init_json_array();
    json_t* unsuccessful_loans = init_json_array();

    for(int i = 0; i < loan_ids->size; i++){
        bool deleted = delete_loan(connection, loan_ids->storage[i], token->account_id);
        if(deleted){
            add_numeric_item_to_json_array(successful_loans, loan_ids->storage[i]);
            log_to_console(MAGENTA, "Loan deleted successfully, %d\n", loan_ids->storage[i]);
        }
        else {
            add_numeric_item_to_json_array(unsuccessful_loans, loan_ids->storage[i]);
            log_to_console(MAGENTA, "Loan not deleted (error), %d\n", loan_ids->storage[i]);
         }
    }

    json_t* outcome_json = init_json_object();
    add_json_array_field_to_json_object(outcome_json, "successful", successful_loans);
    add_json_array_field_to_json_object(outcome_json, "failures", unsuccessful_loans);

    char* outcome_str = json_to_string(outcome_json);
    char content_len[20];
    sprintf(content_len, "%zu", strlen(outcome_str));

    http_response_t* response = basic_response(request);
    http_response_set_status(response, "200");
    http_response_set_phrase(response, "OK");
    http_response_add_header(response, "Content-Type", "application/json");
    http_response_add_header(response, "Content-Length", content_len);
    http_response_set_payload(response, outcome_str);
    if (new_token != NULL){
       http_response_add_header(response, "Set-Cookie", new_token);
    }

    free(outcome_str);
    json_destroy(outcome_json);
    decoded_jwt_destroy(token);
    free(new_token);

    return response;
}

http_response_t* response_post_loans(http_request_t* request){

    if (http_request_contains_query(request)){
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

    const char* content_type = get_header_value(request, "Content-Type");
    if (content_type == NULL || strcmp(content_type, "application/json") != 0){
        return response_unsupported_media_type(request);
    }

    const char* accept = get_header_value(request, "Accept");
    if (accept != NULL && strstr(accept, "application/json") == NULL){
        return response_not_acceptable(request);
    }

    json_t* json = json_from_string(request->payload);
    int_array_t* book_ids = int_array_from_json(json);
    json_destroy(json);

    if(book_ids == NULL){
        return response_unprocessable_entity(request);
    }

    db_conn_t* connection = (db_conn_t*) pthread_getspecific(db_conn_key);
    json_t* successful_loans = init_json_array();
    json_t* unsuccessful_loans = init_json_array();

    for(int i = 0; i < book_ids->size; i++){
        char* error_code = NULL;
        loan_t* loan = insert_loan(connection, book_ids->storage[i], token->account_id, &error_code);
        if(loan != NULL) {
            json_t* loan_json = loan_to_json(loan);
            add_json_item_to_json_array(successful_loans, loan_json);
            log_to_console(MAGENTA, "Loan inserted successfully, %d\n", loan->book_id);
        }
        else {
            json_t* error_json = init_json_object();
            add_numeric_field_to_json_obj(error_json, "book-id", book_ids->storage[i]);
            add_text_field_to_json_obj(error_json, "error-code", error_code);
            add_text_field_to_json_obj(error_json, "error-phrase", error_phrase(error_code));
            add_json_item_to_json_array(unsuccessful_loans, error_json);
        }
    }

    json_t* outcome_json = init_json_object();
    add_json_array_field_to_json_object(outcome_json, "successful", successful_loans);
    add_json_array_field_to_json_object(outcome_json, "failures", unsuccessful_loans);
    char* outcome_str = json_to_string(outcome_json);
    char content_len[20];
    sprintf(content_len, "%zu", strlen(outcome_str));

    http_response_t* response = basic_response(request);
    http_response_set_status(response, "200");
    http_response_set_phrase(response, "OK");
    http_response_add_header(response, "Content-Type", "application/json");
    http_response_add_header(response, "Content-Length", content_len);
    http_response_set_payload(response, outcome_str);
    if (new_token != NULL){
       http_response_add_header(response, "Set-Cookie", new_token);
    }

    free(outcome_str);
    json_destroy(outcome_json);
    decoded_jwt_destroy(token);
    free(new_token);

    return response;
}


