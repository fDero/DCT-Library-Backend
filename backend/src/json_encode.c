
#include "data_objects.h"
#include <cjson/cJSON.h>
#include <assert.h>

cJSON* account_to_json(account_t* account){
    
    cJSON *json_object = cJSON_CreateObject();
    assert (json_object != NULL);
    
    cJSON_AddNumberToObject(json_object,  "id",      account->account_id);
    cJSON_AddStringToObject(json_object,  "name",    account->name);
    cJSON_AddStringToObject(json_object,  "surname", account->surname);
    cJSON_AddStringToObject(json_object,  "email",   account->email);
    return json_object;
}

cJSON* book_to_json(book_t* book){
    
    cJSON *json_object = cJSON_CreateObject();
    assert (json_object != NULL);
    
    char release_date_str[30];
    timestamp_to_string(release_date_str, 30, &(book->release_date));
    
    cJSON_AddNumberToObject(json_object,  "id",           book->book_id);
    cJSON_AddStringToObject(json_object,  "author",       book->author);
    cJSON_AddStringToObject(json_object,  "publisher",    book->publisher);
    cJSON_AddStringToObject(json_object,  "release_date", release_date_str);
    cJSON_AddNumberToObject(json_object,  "total_copies", book->total_copies);
    return json_object;
}

cJSON* loan_to_json(loan_t* loan){
    
    cJSON *json_object = cJSON_CreateObject();
    assert (json_object != NULL);
    
    char starting_time_str[30];
    char ending_time_str[30];
    timestamp_to_string(starting_time_str, 30, &(loan->starting_time));
    timestamp_to_string(ending_time_str, 30, &(loan->ending_time));
    
    cJSON_AddNumberToObject(json_object,  "id",             loan->loan_id);
    cJSON_AddStringToObject(json_object,  "starting_time",  starting_time_str);
    cJSON_AddStringToObject(json_object,  "ending_time",    ending_time_str);
    cJSON_AddNumberToObject(json_object,  "account_id",     loan->account_id);
    cJSON_AddNumberToObject(json_object,  "book_id",        loan->book_id);
    return json_object;
}

cJSON* account_array_to_json(account_array_t* account_array){
    cJSON *json_array = cJSON_CreateArray();
    for (int i = 0; i < account_array->size; i++){
        account_t* account = &(account_array->storage[i]);
        cJSON *json_account = book_to_json(account);
        cJSON_AddItemToArray(json_array, json_account);
    }
    return json_array;
}

cJSON* book_array_to_json(book_array_t* book_array){
    cJSON *json_array = cJSON_CreateArray();
    for (int i = 0; i < book_array->size; i++){
        book_t* book = &(book_array->storage[i]);
        cJSON *json_book = book_to_json(book);
        cJSON_AddItemToArray(json_array, json_book);
    }
    return json_array;
}

cJSON* loan_array_to_json(loan_array_t* loan_array){
    cJSON *json_array = cJSON_CreateArray();
    for (int i = 0; i < loan_array->size; i++){
        loan_t* loan = &(loan_array->storage[i]);
        cJSON *json_loan = loan_to_json(loan);
        cJSON_AddItemToArray(json_array, json_loan);
    }
    return json_array;
}