
#include <pthread.h>
#include <arpa/inet.h>

typedef struct sockaddr_in sockaddr_in_t;
typedef struct sockaddr sockaddr_t;

void listen_and_serve();
void* client_handler(void* client_scoket_ptr);