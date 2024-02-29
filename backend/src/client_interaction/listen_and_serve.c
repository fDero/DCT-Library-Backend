
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

client_t* accept_connection(){
		client_t* client = (client_t*)malloc(sizeof(client));
		client->addrlen = sizeof(client->address);
    client->socket = accept(server_socket, &client->address, &client->addrlen);
    assert(client->socket > 0);
		struct timeval timeout;
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;
    setsockopt(client->socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0;
    return client;
}

char* get_client_ip(client_t* client){
		char* ip = (char*)malloc(sizeof(char) * INET6_ADDRSTRLEN);
		ip[0] = '\0';
		if (client->address.sa_family == AF_INET) {
				sockaddr_in_t *addr_in = (sockaddr_in_t*)&client->address;
				inet_ntop(AF_INET, &(addr_in->sin_addr), ip, INET6_ADDRSTRLEN);
		} else if (client->address.sa_family == AF_INET6) {
				sockaddr_in6_t *addr_in6 = (sockaddr_in6_t*)&client->address;
				inet_ntop(AF_INET6, &(addr_in6->sin6_addr), ip, INET6_ADDRSTRLEN);
		}
		return ip;
}

int get_client_port(client_t* client){
		int port = 0;
		if (client->address.sa_family == AF_INET) {
				sockaddr_in_t *addr_in = (sockaddr_in_t*)&client->address;
				port = ntohs(addr_in->sin_port);
		} else if (client->address.sa_family == AF_INET6) {
				sockaddr_in6_t *addr_in6 = (sockaddr_in6_t*)&client->address;
				port = ntohs(addr_in6->sin6_port);
		}
		return port;
}

void* client_handler(void* client_void_ptr){
    client_t* client = (client_t*) client_void_ptr;

		char* client_ip = get_client_ip(client);
		int client_port = get_client_port(client);

		pthread_setspecific(db_conn_key, (void*)open_db_connection());
    char buffer[BUFFERSIZE];

    while(read(client->socket, buffer, BUFFERSIZE) > 0){
    	buffer[BUFFERSIZE - 1] = '\0';
    	console_log(YELLOW, "Request received from a client (%s:%d):\n%s\n", client_ip, client_port, buffer);
			http_request_t* request = http_request_decode(buffer);
    	http_response_t* response = respond(request);
			char* response_str = http_response_encode(response);
    	send(client->socket, response_str, strlen(response_str), MSG_EOR);
    	console_log(YELLOW, "Response sent to the client (%s:%d):\n%s\n", client_ip, client_port, response_str);
			free(response_str);
			const char* keepalive_str = get_header_value(request, "Connection");
			if(keepalive_str == NULL || strcmp(keepalive_str, "keep-alive") != 0){
				console_log(RED, "Closing the connection to the client (%s:%d)\n", client_ip, client_port);
				http_request_destroy(request);
				break;
			}
			http_request_destroy(request);
		}
    console_log(GREEN, "Closing the connection to the client (%s:%d)\n", client_ip, client_port);
    close(client->socket);
		free(client);
		free(client_ip);
    pthread_exit(0);
}

void listen_and_serve(){
    server_port = atoi(getenv("SERVER_PORT"));
    server_max_connections = atoi(getenv("SERVER_MAX_CONNECTION"));
    assert (server_port > 0);
    assert (server_max_connections > 0);
		console_log(GREEN, "Creating a socket for the server\n");
    create_listening_socket();
		console_log(GREEN, "Binding the socket\n");
    bind_listening_socket();
		console_log(GREEN, "Listening for connections\n");
    const int listening_error = listen(server_socket, server_max_connections);
    assert (listening_error == 0);
    while(1){
				console_log(GREEN, "Waiting to accept a connection\n");
        client_t* client_ptr = accept_connection();
        pthread_t client_handler_thread;
        pthread_create(&client_handler_thread, NULL, client_handler, client_ptr);
        pthread_detach(client_handler_thread);
    }
}