#ifndef SERVER_H
#define SERVER_H
#include "types.h"

int get(char *resource);
int client_request(int connectionFD, Request *req);
int respond_to_client(int connectionFD, Request *req);

#endif // SERVER_H
