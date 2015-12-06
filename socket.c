#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "socket.h"
#include "string.h"

#ifndef APP_PORT
#define APP_PORT "8080"
#endif

#ifndef BACKLOG
#define BACKLOG 10
#endif


int bind_socket(struct addrinfo *res)
{
    struct addrinfo hints;
    int sockFD;

    memset(&hints, 0, sizeof(hints)); // Zero out struct
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM; // TCP for Telnet
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, APP_PORT, &hints, &res);

    sockFD = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (bind(sockFD, res->ai_addr, res->ai_addrlen) == -1)
    {
        fprintf(stderr, "Failed to bind to socket %d\n", sockFD);

        freeaddrinfo(res);
        close(sockFD);

        return -1;
    }

    else
    {
        freeaddrinfo(res);

        return sockFD;
    }
}

int accept_connection(struct addrinfo *res)
{
    struct sockaddr_storage theirAddr;
    socklen_t addrSize;

    int listenFD, newFD;

    if ((listenFD = bind_socket(res)) == -1)
    {
        return -1;
    }

    // Listen for connections

    listen(listenFD, BACKLOG);

    addrSize = sizeof(theirAddr);

    newFD = accept(listenFD, (struct sockaddr *) &theirAddr, &addrSize);

    return newFD;
}
/* EXAMPLE USAGE
int main()
{
    // Listen for and accept a new connection

    struct addrinfo *res;

    int bytesSent, connectionFD, len;

    char *msg = "Wake up, Neo...\r\n";

    if ((connectionFD = accept_connection(res)) == -1)
    {
        return -1;
    }

    len = strlen(msg);

    bytesSent = send(connectionFD, msg, len, 0);

    printf("Bytes sent: %d\n", bytesSent);

    return 0;
}
*/
