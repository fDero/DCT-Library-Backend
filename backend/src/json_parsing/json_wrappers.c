#include "json.h"

void json_destroy(json_t* json){
    if (json != NULL && json->refcount > 0) {
        json_decref(json);
    }
}

char* json_to_string(json_t* json){
    return json_dumps(json, JSON_COMPACT);
}

char* json_to_string_and_free(json_t* json){
    char* str = json_dumps(json, JSON_COMPACT);
    json_destroy(json);
    return str;
}

json_t* init_json_object(){
    return json_object();
}

json_t* init_json_array(){
    return json_array();
}

void add_numeric_field_to_json_obj(json_t* json, const char* field_name, int value){
    json_object_set_new(json, field_name, json_integer(value));
}

void add_text_field_to_json_obj(json_t* json, const char* field_name, const char* text){
    json_object_set_new(json, field_name, json_string(text));
}

void add_timestamp_field_to_json_obj(json_t* json, const char* field_name, const timestamp_t* timestamp){
    char timestamp_str[30];
    timestamp_to_string(timestamp_str, 30, timestamp);
    json_object_set_new(json, field_name, json_string(timestamp_str));
}

void add_json_array_field_to_json_object(json_t* dest_object, const char* field_name, json_t* arr){
    json_object_set_new(dest_object, field_name, arr);
}

void add_numeric_item_to_json_array(json_t* dest_array, int src_item){
    json_array_append_new(dest_array, json_integer(src_item));
}

void add_json_item_to_json_array(json_t* dest_array, json_t* src_item){
    json_array_append_new(dest_array, src_item);
}

bool extract_int_from_json(json_t* json, const char* field_name, int* value){
    json_t* field = json_object_get(json, field_name);
    if(json_is_integer(field)){
        *value = json_integer_value(field);
        return true;
    }
    return false;
}

bool extract_text_from_json(json_t* json, const char* field_name, char** str){
    json_t* field = json_object_get(json, field_name);
    if(json_is_string(field)){
        *str = strdup(json_string_value(field));
        return true;
    }
    return false;
}

bool extract_timestamp_from_json(json_t* json, const char* field_name, timestamp_t* timestamp){
    json_t* field = json_object_get(json, field_name);
    if(json_is_string(field)){
        timestamp_t* tempts = string_to_timestamp(json_string_value(field)); 
        *timestamp = *tempts;
		free(tempts);
    }
    return false;
}

json_t* json_from_string(const char* json_text){
    return json_loads(json_text, 0, NULL);
}

size_t number_of_json_fields(json_t* json){
   return json_object_size(json);
}
