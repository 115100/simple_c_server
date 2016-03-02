#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "cat.h"
#include "ls.h"
#include "parse.h"
#include "server.h"
#include "string.h"
#include "types.h"


int client_request(int connectionFD, Request *req)
{
	char queryString[100]; // Presume length of query inc. \0 to be this at most.
	int bytesReceived = recv(connectionFD, queryString, 100, 0);

	*req = request_parse(queryString);

	return 0;
}

int respond_to_client(int connectionFD, Request *req)
{
	if (strcmp(req->protocol, "HTTP/1.1") != 0)
	{
		// 400
		// TODO: CLEAN UP
		send(connectionFD, "HTTP/1.1 400 Bad Request\n", 25, 0);
		send(connectionFD, "Content-Type: text/plain\n", 25, 0);
		send(connectionFD, "Content-Length: 16\n\r\n", 21, 0);
		send(connectionFD, "400 Bad Request.", 16, 0);

		fprintf(stderr, "Protocol `%s` not implemented\n", req->protocol);
		return 1;
	}

	if (strcmp(req->method, "GET") == 0)
	{
		char filename[PATH_MAX];
		const char *searchFolder = "html";

		memset(filename, 0, PATH_MAX);

		strcat(filename, searchFolder);
		strcat(filename, req->resource);

		if (find_resource(searchFolder, filename) == 1)
		{
			// 200
			// TODO: CLEAN UP
			send(connectionFD, "HTTP/1.1 200 OK\n", 16, 0);
			send(connectionFD, "Content-Type: text/html\n", 24, 0);
			cat(filename, connectionFD);
		}

		else
		{
			// 404
			// TODO: CLEAN UP
			send(connectionFD, "HTTP/1.1 404 Not Found\n", 23, 0);
			send(connectionFD, "Content-Type: text/html\n", 24, 0);
			send(connectionFD, "Content-Length: 14\n\r\n", 21, 0);
			send(connectionFD, "404 Not Found.", 14, 0);
		}
	}

	else
	{
		// 400
		// TODO: CLEAN UP
		send(connectionFD, "HTTP/1.1 400 Bad Request\n", 25, 0);
		send(connectionFD, "Content-Type: text/plain\n", 25, 0);
		send(connectionFD, "Content-Length: 16\n\r\n", 21, 0);
		send(connectionFD, "400 Bad Request.", 16, 0);

		fprintf(stderr, "Not Implemented\n");
		return 1;
	}

	return 0;
}
