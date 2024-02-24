
#include <cjson/cJSON.h>
#include <postgresql/libpq-fe.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_objects.h"
#include "db_utils.h"
#include "http.h"
#include "queries.h"
#include "socket_handlers.h"

int main() {
    db_connection_init();
    setbuf(stdout, NULL);

    printf("c backend started\n");

    char request_str[2048] =
        "GET /somedir/page HTTP/3.3\r\n"
        "Host: www.host.it\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    if (request != NULL) {
        for (int i = 0; i < request->headers_num; i++) {
            printf("Header name %d: %s\n", i, request->header_names[i]);
            printf("Header value %d: %s\n", i, request->header_values[i]);
        }
        printf("METHOD:  %s\n", request->method);
        printf("URL:     %s\n", request->url);
        printf("VERSION: %s\n", request->version);
        printf("PAYLOAD: %s\n", request->payload);
    } else {
        printf("bad request\n");
    }
    // listen_and_serve();
}
