
#include "json.h"
#include "utils.h"

json_t* init_json_object(){
    return cJSON_CreateObject();
}

json_t* init_json_array(){
    return cJSON_CreateArray();
}

void add_numeric_field_to_json_obj(json_t* json, char* field_name, int value){
    cJSON_AddNumberToObject(json, field_name, value);
}

void add_text_field_to_json_obj(json_t* json, char* field_name, char* text){
    cJSON_AddStringToObject(json, field_name, text);
}

void add_timestamp_field_to_json_obj(json_t* json, char* field_name, timestamp_t* timestamp){
    char timestamp_str[30];
    timestamp_to_string(timestamp_str, 30, timestamp);
    cJSON_AddStringToObject(json, field_name, timestamp_str);
}

void add_json_item_to_json_array(json_t* dest_array, json_t* src_item){
    cJSON_AddItemToArray(dest_array, src_item);
}