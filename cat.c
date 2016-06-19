#include <fcntl.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#include "cat.h"
#include "server.h"
#include "string.h"

#ifndef MAX_SEND_BUFFER
#define MAX_SEND_BUFFER 512
#endif


int cat(char *file, int connectionFD)
{
	int sfd;

	if ((sfd = open(file, O_RDONLY)) == -1)
	{
		fprintf(stderr, "Can't open file %s\n", file);
		return 1;
	}

	int bytesRead;
	int bytesSent;
	char sendBuffer[MAX_SEND_BUFFER];
	int contentLength;
	char contentLengthHeader[30];

	// Send Content-Length header
	contentLength = lseek(sfd, 0, SEEK_END);
	lseek(sfd, 0, SEEK_SET);
	bytesRead = snprintf(contentLengthHeader, 30, "Content-Length: %d\n\r\n", contentLength);
	send(connectionFD, contentLengthHeader, bytesRead, 0);

	while (bytesRead = read(sfd, sendBuffer, MAX_SEND_BUFFER))
		// Flush send buffer
		bytesSent = send(connectionFD, sendBuffer, bytesRead, 0);

	close(sfd);

	return 0;
}
