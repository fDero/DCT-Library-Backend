
#include "socket_handlers.h"
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFERSIZE 1024

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

int accept_connection(){
    socklen_t socket_address_len = sizeof(socket_address);
    int client_socket = accept(server_socket, (sockaddr_t*)&socket_address, &socket_address_len);  
    assert(client_socket > 0);
    return client_socket;
}

void* client_handler(void* client_socket_ptr){
    int client_socket = *((int*) client_socket_ptr);
    free((int*)client_socket_ptr);
    char buffer[BUFFERSIZE];
    while(read(client_socket, buffer, BUFFERSIZE) > 0){
        printf("messaggio inviato dal client (e ricevuto dal server: ) %s", buffer);
    }
    close(client_socket);
    pthread_exit(0);
}

void listen_and_serve(){
    server_port = atoi(getenv("SERVER_PORT"));
    server_max_connections = atoi(getenv("SERVER_MAX_CONNECTION"));
    assert (server_port > 0);
    assert (server_max_connections > 0);
    create_listening_socket();
    bind_listening_socket();
    const int listening_error = listen(server_socket, server_max_connections);
    assert (listening_error == 0);
    while(1){
        void* client_socket_ptr = (int*)malloc(sizeof(int));
        *((int*)client_socket_ptr) = accept_connection();
        pthread_t client_handler_thread;
        pthread_create(&client_handler_thread, NULL, client_handler, client_socket_ptr);
        pthread_detach(client_handler_thread);
    }
}