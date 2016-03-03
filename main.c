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
	memset(&req, 0, sizeof(req));

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
			continue;
		}

		if (client_request(connectionFD, &req))
		{
			goto FREE;
		}

		if (respond_to_client(connectionFD, &req))
		{
			goto FREE;
		}

FREE:
		close(connectionFD);
		if (req.method) free(req.method);
		if (req.resource) free(req.resource);
		if (req.protocol) free(req.protocol);
	}

	// Free/close all handles/mallocs
	close(listenFD);

	return 0;
}
