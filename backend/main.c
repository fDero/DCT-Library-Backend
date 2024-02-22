
#include <postgresql/libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

#include "db_connection.h"
#include "queries.h"
#include "data_objects.h"
#include "socket_handlers.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <http_parser.h>
#include <cjson/cJSON.h>

void json_test() {

    // Create a JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        fprintf(stderr, "Failed to create JSON object.\n");
        return;
    }

    // Add key-value pairs to the JSON object
    cJSON_AddStringToObject(root, "name", "John Doe");
    cJSON_AddNumberToObject(root, "age", 30);
    cJSON_AddBoolToObject(root, "is_student", cJSON_False);

    // Create an array and add it to the JSON object
    cJSON *grades = cJSON_CreateIntArray((const int[]){90, 85, 88}, 3);
    cJSON_AddItemToObject(root, "grades", grades);

    // Convert the JSON object to a string
    char *jsonString = cJSON_Print(root);
    if (jsonString == NULL) {
        fprintf(stderr, "Failed to convert JSON object to string.\n");
        cJSON_Delete(root);
		return;
	}

    // Print the JSON string
    printf("JSON Object:\n%s\n", jsonString);

    // Clean up memory
    cJSON_Delete(root);
    free(jsonString);
}


int on_url(http_parser* parser, const char* at, size_t length) {
    printf("URL: %.*s\n", (int)length, at);
    return 0;
}

int on_header_field(http_parser* parser, const char* at, size_t length) {
    printf("Header Field: %.*s\n", (int)length, at);
    return 0;
}

int on_header_value(http_parser* parser, const char* at, size_t length) {
    printf("Header Value: %.*s\n", (int)length, at);
    return 0;
}

int on_message_complete(http_parser* parser) {
    printf("Message Complete\n");
    return 0;
}

void http_test() {

    // Initialize http_parser parser
    http_parser parser;
    http_parser_settings settings;
    http_parser_settings_init(&settings);
    settings.on_url = on_url;
    settings.on_header_field = on_header_field;
    settings.on_header_value = on_header_value;
    settings.on_message_complete = on_message_complete;

    http_parser_init(&parser, HTTP_REQUEST);
   // Example HTTP request to parse
    const char* request_data = "GET /path HTTP/1.1\r\nHost: example.com\r\n\r\n";
    size_t request_length = strlen(request_data);

    // Parse the HTTP request
    size_t parsed = http_parser_execute(&parser, &settings, request_data, request_length);

    if (parsed != request_length) {
        fprintf(stderr, "Error parsing HTTP request\n");
        return;
    }
}

int main() {

    setbuf(stdout, NULL);

	json_test();
	http_test();
	listen_and_serve();
}
