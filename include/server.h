#ifndef SERVER_H
#define SERVER_H
#include "types.h"

char *get(char *resource);
int execute_request(Request *req);

#endif // SERVER_H
