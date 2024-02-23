
#include <postgresql/libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

#include "db_utils.h"
#include "queries.h"
#include "data_objects.h"
#include "socket_handlers.h"
#include "http.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cjson/cJSON.h>
#include <pthread.h>

int main() {
    db_connection_init();
    setbuf(stdout, NULL);

    printf("c backend started\n");

	char request_str[2048] = 
        "GET /somedir/page HTTP/3.3\r\n"
        //"Host: www.host.it\r\n"
        //"Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0"
    ;

    const http_request_t* request = http_request_decode(request_str);
    if (request != NULL){
        printf("HEADERS: \n%s\n", request->headers);
        printf("METHOD:  %s\n",   request->method);
        printf("URL:     %s\n",   request->url);
        printf("VERSION: %s\n",   request->version);
        printf("PAYLOAD: %s\n",   request->payload);
    }
    else {
        printf("bad request\n");
    }
	//listen_and_serve();
}
