
#include "data_objects.h"
#include "utils.h"
#include <cjson/cJSON.h>
#include <stdbool.h>

typedef cJSON json_t;

json_t* init_json_object();
json_t* init_json_array();

void add_numeric_field_to_json_obj(json_t* json, char* field_name, int value);
void add_text_field_to_json_obj(json_t* json, char* field_name,char* text);
void add_timestamp_field_to_json_obj(json_t* json, char* field_name, timestamp_t* timestamp);
void add_json_item_to_json_array(json_t* dest_array, json_t* src_item);

json_t* account_to_json(account_t* account);
json_t* book_to_json(book_t* book);
json_t* loan_to_json(loan_t* loan);

json_t* account_array_to_json(account_array_t* account_array);
json_t* book_array_to_json(book_array_t* book_array);
json_t* loan_array_to_json(loan_array_t* loan_array);

account_t* account_from_json(json_t* json);
book_t* book_from_json(json_t* json);
loan_t* loan_from_json(json_t* json);

bool extract_int_from_json(json_t* json, const char* field_name, int* value);
bool extract_text_from_json(json_t* json, const char* field_name, char** str);
bool extract_timestamp_from_json(json_t* json, const char* field_name, timestamp_t* timestamp);