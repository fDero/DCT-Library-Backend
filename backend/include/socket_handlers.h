
#include <pthread.h>
#include <arpa/inet.h>

typedef struct sockaddr_in sockaddr_in_t;
typedef struct sockaddr_in6 sockaddr_in6_t;
typedef struct sockaddr sockaddr_t;

struct client{
	int socket;
	sockaddr_t address;
	socklen_t addrlen;
};

typedef struct client client_t;

void listen_and_serve();
void* client_handler(void* client_void_ptr);