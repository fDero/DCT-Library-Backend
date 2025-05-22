
#include "socket_handlers.h"
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include "db_utils.h"
#include "http.h"
#include <sys/socket.h>
#include "respond.h"
#include <stdbool.h>

#define BUFFERSIZE 8192

int connection_timeout = 0;
int server_port = -1;
int server_max_connections = -1;
int server_socket = -1;
sockaddr_in_t socket_address;

void create_listening_socket(){
    int opt = 1;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    int socket_error = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    assert(socket_error == 0);
    assert(server_socket > 0);
}

void bind_listening_socket(){
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    socket_address.sin_port = htons(server_port);
    int bind_outcome = bind(server_socket, (sockaddr_t*)&socket_address, sizeof(socket_address));
    assert (bind_outcome == 0);
}

client_t* accept_connection(){
    client_t* client = (client_t*)malloc(sizeof(client_t));
    client->addrlen = sizeof(client->address);
    client->socket = accept(server_socket, &client->address, &client->addrlen);
    assert(client->socket > 0);
    struct timeval timeout;
    timeout.tv_sec = connection_timeout;
    timeout.tv_usec = 0;
    setsockopt(client->socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0;
    return client;
}

char* get_client_ip(client_t* client){
    char* ip = (char*)malloc(sizeof(char) * INET6_ADDRSTRLEN);
    ip[0] = '\0';
    if (client->address.sa_family == AF_INET){
        sockaddr_in_t *addr_in = (sockaddr_in_t*)&client->address;
        inet_ntop(AF_INET, &(addr_in->sin_addr), ip, INET6_ADDRSTRLEN);
    } else if (client->address.sa_family == AF_INET6){
        sockaddr_in6_t *addr_in6 = (sockaddr_in6_t*)&client->address;
        inet_ntop(AF_INET6, &(addr_in6->sin6_addr), ip, INET6_ADDRSTRLEN);
    }
    return ip;
}

int get_client_port(client_t* client){
    int port = 0;
    if (client->address.sa_family == AF_INET){
        sockaddr_in_t *addr_in = (sockaddr_in_t*)&client->address;
        port = ntohs(addr_in->sin_port);
    } else if (client->address.sa_family == AF_INET6){
        sockaddr_in6_t *addr_in6 = (sockaddr_in6_t*)&client->address;
        port = ntohs(addr_in6->sin6_port);
    }
    return port;
}

void* client_handler(void* client_void_ptr){
    client_t* client = (client_t*) client_void_ptr;
    char* client_ip = get_client_ip(client);
    int client_port = get_client_port(client);
    pthread_t tid = pthread_self();
    pthread_setspecific(db_conn_key, (void*)open_db_connection());
    pthread_setspecific(cache_connection_key, (void*)open_cache_connection());
    char buffer[BUFFERSIZE];
    int read_bytes = 0;

    while((read_bytes = read(client->socket, buffer, BUFFERSIZE - 1)) > 0){
        buffer[read_bytes] = '\0';
        log_to_console(YELLOW, "Request received from a client (%sclient=%s:%d%s -> %sthread=%lu%s):\n%s\n", MAGENTA, client_ip, client_port, YELLOW, BLUE, tid, YELLOW, buffer);
        
        http_request_t* request = http_request_decode(buffer);
        http_response_t* response = respond(request);
        size_t response_size = 0;
        char* response_str = http_response_encode(response, &response_size);
        send(client->socket, response_str, response_size, MSG_EOR);	
        log_to_console(YELLOW, "Response sent to the client (%sthread=%lu%s -> %sclient=%s:%d%s):\n%s\n", BLUE, tid, YELLOW, MAGENTA, client_ip, client_port, YELLOW,response_str);

        http_response_destroy(response);
        free(response_str);
        if (request != NULL){
            const char* keepalive = get_header_value(request, "Connection");
            http_request_destroy(request);
            if(keepalive == NULL || strcmp(keepalive, "keep-alive") != 0){
                break;
            }
        }
    }
    log_to_console(RED, "Closing the connection to the client (%sclient=%s:%d%s ; %sthread=%lu%s)\n", MAGENTA, client_ip, client_port, RED, BLUE, tid, RED);
    shutdown(client->socket, SHUT_RDWR);
    close(client->socket);
    free(client);
    free(client_ip);
    pthread_exit(0);
}

void listen_and_serve(const bool debug_mode){
    server_port = atoi(getenv("SERVER_PORT"));
    server_max_connections = atoi(getenv("SERVER_MAX_CONNECTION"));
    connection_timeout = atoi(getenv("CLIENT_CONNECTION_TIMEOUT"));
    assert (server_port > 0);
    assert (server_max_connections > 0);
    log_to_console(GREEN, "Creating a socket for the server\n");
    create_listening_socket();
    log_to_console(GREEN, "Binding the socket\n");
    bind_listening_socket();
    log_to_console(GREEN, "Listening for connections\n");
    const int listening_error = listen(server_socket, server_max_connections);
    assert (listening_error == 0);

    while(1){
        log_to_console(GREEN, "Waiting to accept a connection\n");
        client_t* client_ptr = accept_connection();
        if(debug_mode){
            client_handler(client_ptr);
            return;
        }
        pthread_t client_handler_thread;
        pthread_create(&client_handler_thread, NULL, client_handler, client_ptr);
        pthread_detach(client_handler_thread);
    }
}
