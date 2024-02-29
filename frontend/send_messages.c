
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/wait.h>

#define PORT 8080

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *message ="GET / HTTP/1.1\r\n"
									 "Host: localhost:8080\r\n"
									 "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:122.0) Gecko/20100101 Firefox/122.0\r\n"
									 "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\n"
									 "Accept-Language: en-US,en;q=0.5\r\n"
									 "Accept-Encoding: gzip, deflate, br\r\n"
									 "DNT: 1\r\n"
									 "Connection: keep-alive\r\n"
									 "Upgrade-Insecure-Requests: 1\r\n"
									 "Sec-Fetch-Dest: document\r\n"
									 "Sec-Fetch-Mode: navigate\r\n"
									 "Sec-Fetch-Site: none\r\n"
									 "Content-Length: 1\r\n"
									 "Sec-Fetch-User: ?1\r\n\r\n"
          				 "a\0";

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    // Specify server address and port
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    // Send data
    send(sock, message, strlen(message), 0);
    printf("Message sent: %s\n", message);

		char buffer[1000];

		read(sock, buffer, 1000);
		printf("Response received: %s\n", buffer);

    // Close the socket
    close(sock);
    return 0;
}
