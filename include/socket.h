#ifndef SOCKET_H
#define SOCKET_H

#include <netdb.h>

int bind_socket(struct addrinfo *res);
int accept_connection(int listenFD);

#endif // SOCKET_H
