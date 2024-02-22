
#include "json.h"
#include "utils.h"
#include "data_objects.h"
#include <stdbool.h>

json_t* init_json_object(){
    return cJSON_CreateObject();
}

json_t* init_json_array(){
    return cJSON_CreateArray();
}

void add_numeric_field_to_json_obj(json_t* json, const char* field_name, int value){
    cJSON_AddNumberToObject(json, field_name, value);
}

void add_text_field_to_json_obj(json_t* json, const char* field_name, const char* text){
    cJSON_AddStringToObject(json, field_name, text);
}

void add_timestamp_field_to_json_obj(json_t* json, const char* field_name, const timestamp_t* timestamp){
    char timestamp_str[30];
    timestamp_to_string(timestamp_str, 30, timestamp);
    cJSON_AddStringToObject(json, field_name, timestamp_str);
}

void add_json_item_to_json_array(json_t* dest_array, json_t* src_item){
    cJSON_AddItemToArray(dest_array, src_item);
}

bool extract_int_from_json(json_t* json, const char* field_name, int* value){
    json_t* field = NULL;
    field = cJSON_GetObjectItem(json, field_name);
    if (cJSON_IsNumber(field)){
        *value = (int)cJSON_GetNumberValue(field);
        cJSON_Delete(field);
        return true;
    }
    cJSON_Delete(field);
    return false;
}

bool extract_text_from_json(json_t* json, const char* field_name, char** str){
    json_t* field = NULL;
    field = cJSON_GetObjectItem(json, field_name);
    if (cJSON_IsNumber(field)){
        strcpy(*str, cJSON_GetStringValue(field));
        cJSON_Delete(field);
        return true;
    }
    cJSON_Delete(field);
    return false;
}

bool extract_timestamp_from_json(json_t* json, const char* field_name, timestamp_t* timestamp){
    json_t* field = NULL;
    field = cJSON_GetObjectItem(json, field_name);
    if (cJSON_IsString(field)){
        *timestamp = string_to_timestamp(cJSON_GetStringValue(field));
        cJSON_Delete(field);
        return true;
    }
    cJSON_Delete(field);
    return false;
}