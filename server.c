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


int http_send(int connectionFD, char *message)
{
	return send(connectionFD, message, strlen(message), 0);
}

int client_request(int connectionFD, Request *req)
{
	// Presume length of query inc. \0 to be this at most.
	char queryString[100];

	int bytesReceived = recv(connectionFD, queryString, 100, 0);

	return request_parse(queryString, req);
}

int respond_to_client(int connectionFD, Request *req)
{
	if (strcmp(req->protocol, "HTTP/1.1") != 0)
	{
		// 400
		http_send(connectionFD, "HTTP/1.1 400 Bad Request\n");
		http_send(connectionFD, "Content-Type: text/plain\n");
		http_send(connectionFD, "Content-Length: 16\n\r\n");
		// TODO: CLEAN UP
		http_send(connectionFD, "400 Bad Request.");
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
			http_send(connectionFD, "HTTP/1.1 200 OK\n");
			http_send(connectionFD, "Content-Type: text/html\n");
			cat(filename, connectionFD);
		}

		else
		{
			// 404
			http_send(connectionFD, "HTTP/1.1 404 Not Found\n");
			http_send(connectionFD, "Content-Type: text/html\n");
			// TODO: CLEAN UP
			http_send(connectionFD, "Content-Length: 14\n\r\n");
			http_send(connectionFD, "404 Not Found.");
		}
	}

	else
	{
		// 400
		http_send(connectionFD, "HTTP/1.1 400 Bad Request\n");
		http_send(connectionFD, "Content-Type: text/plain\n");
		// TODO: CLEAN UP
		http_send(connectionFD, "Content-Length: 16\n\r\n");
		http_send(connectionFD, "400 Bad Request.");
		return 1;
	}

	return 0;
}
