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

	int listenFD, connectionFD;
	struct addrinfo *res;

	if ((listenFD = bind_socket(res)) == -1)
	{
		return 127;
	}

	while (1)
	{
		if ((connectionFD = accept_connection(listenFD)) == -1)
		{
			return 127;
		}

		if (client_request(connectionFD, &req))
		{
			return 400;
		}

		if (respond_to_client(connectionFD, &req))
		{
			return 500;
		}

		free(req.method);
		free(req.resource);
		free(req.protocol);
		close(connectionFD);
	}

	// Free/close all handles/mallocs
	close(listenFD);

	return 0;
}
