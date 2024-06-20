
#ifndef JSON_H
#define JSON_H
#include "data_objects.h"
#include "utils.h"
#include <jansson.h>
#include <stdbool.h>
#include <assert.h>


void json_destroy(json_t* json);
json_t* json_from_string(const char*);
json_t* init_json_object();
json_t* init_json_array();

void add_numeric_field_to_json_obj(json_t* json, const char* field_name, int value);
void add_text_field_to_json_obj(json_t* json, const char* field_name, const char* text);
void add_timestamp_field_to_json_obj(json_t* json, const char* field_name, const timestamp_t* timestamp);
void add_json_item_to_json_array(json_t* dest_array, json_t* src_item);
void add_numeric_item_to_json_array(json_t* dest_array, int src_item);

void add_json_array_field_to_json_object(
     json_t* dest_object,
     const char* field_name,
     json_t* arr
);

char* json_to_string(json_t* json);
char* json_to_string_and_free(json_t* json);

char* account_to_json_string(account_t* account);
char* book_to_json_string(book_t* book);
char* loan_to_json_string(loan_t* loan);

char* account_array_to_json_string(account_array_t* account_array);
char* book_array_to_json_string(book_array_t* book_array);
char* loan_array_to_json_string(loan_array_t* loan_array);

json_t* account_to_json(account_t* account);
json_t* book_to_json(book_t* book);
json_t* loan_to_json(loan_t* loan);

json_t* account_array_to_json(account_array_t* account_array);
json_t* book_array_to_json(book_array_t* book_array);
json_t* loan_array_to_json(loan_array_t* loan_array);

account_t* account_from_json(json_t* json);
book_t* book_from_json(json_t* json);
loan_t* loan_from_json(json_t* json);
int_array_t* int_array_from_json(json_t* json);


char* json_to_string(json_t* json);
size_t number_of_json_fields(json_t* json);

bool extract_int_from_json(json_t* json, const char* field_name, int* value);
bool extract_text_from_json(json_t* json, const char* field_name, char** str);
bool extract_timestamp_from_json(json_t* json, const char* field_name, timestamp_t* timestamp);

#endif
