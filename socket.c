#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
	struct addrinfo hints = {0};
	int sockFD;

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


int accept_connection(int listenFD)
{
	struct sockaddr_storage theirAddr;
	socklen_t addrSize;

	int newFD;

	// Listen for connections

	listen(listenFD, BACKLOG);

	addrSize = sizeof(theirAddr);

	newFD = accept(listenFD, (struct sockaddr *) &theirAddr, &addrSize);

	return newFD;
}
