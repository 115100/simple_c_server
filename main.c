#include <stdlib.h>
#include <unistd.h>

#include "parse.h"
#include "server.h"
#include "socket.h"
#include "string.h"
#include "types.h"


int main()
{
    Request req;
    Response resp;

    char queryString[100];
    int listenFD, connectionFD, bytesReceived;
    struct addrinfo *res;

    if ((listenFD = bind_socket(res)) == -1)
    {
        return -1;
    }

    if ((connectionFD = accept_connection(listenFD)) == -1)
    {
        return -1;
    }

    bytesReceived = recv(connectionFD, queryString, 100, 0);

    queryString[bytesReceived] = '\0';

    req = request_parse(queryString);

    resp = build_response(&req);
    printf("Body: %s\n", resp.body);
    printf("Length: %d\n", strlen(resp.body));

    send(connectionFD, resp.body, strlen(resp.body) + 1, 0);

    // Free/close all handles/mallocs
    close(listenFD);
    close(connectionFD);

    return 0;
}
