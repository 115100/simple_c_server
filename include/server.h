#ifndef SERVER_H
#define SERVER_H
#include "types.h"

void get(Response *resp, char *resource);
Response build_response(Request *req);

#endif // SERVER_H
