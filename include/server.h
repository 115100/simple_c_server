#ifndef SERVER_H
#define SERVER_H
#include "types.h"

char *get(char *resource);
Response build_response(Request *req);

#endif // SERVER_H
