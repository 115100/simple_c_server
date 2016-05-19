#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "parse.h"
#include "server.h"
#include "socket.h"
#include "string.h"
#include "types.h"

#define NUM_THREADS 2

pthread_mutex_t lock;


void *serve_loop(void *listenFD)
{
	Request req = {0};
	int connectionFD;

	while (1)
	{
		pthread_mutex_lock(&lock);

		if ((connectionFD = accept_connection((long) listenFD)) == -1)
		{
			pthread_mutex_unlock(&lock);
			continue;
		}

		pthread_mutex_unlock(&lock);

		if (client_request(connectionFD, &req) != 3)
		{
			goto FREE;
		}

		respond_to_client(connectionFD, &req);

FREE:
		close(connectionFD);

		free(req.method);
		req.method = NULL;
		free(req.resource);
		req.resource = NULL;
		free(req.protocol);
		req.protocol = NULL;
	}
}


int main()
{
	long listenFD;
	struct addrinfo *res;

	pthread_t tid[NUM_THREADS];

	if (pthread_mutex_init(&lock, NULL))
	{
		return 1;
	}

	if ((listenFD = bind_socket(res)) == -1)
	{
		return 127;
	}

	for (int i=0; i < NUM_THREADS; i++)
	{
		if(pthread_create(&(tid[i]), NULL, &serve_loop, (void *) listenFD))
		{
			close(listenFD);
			return 128;
		}
	}

	pause();

	// Free/close all handles/mallocs
	close(listenFD);

	return 0;
}
