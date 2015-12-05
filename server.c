#include <stdio.h>

#include "server.h"
#include "string.h"

char *get(char *resource)
{
    // Simple ping/pong response; case sensitive
    if (!strcmp(resource, "/ping"))
    {
        return "pong";
    }
    // 404?
    else
    {
        return "";
    }
}

int execute_request(Request *req)
{
    char *response;

    // Support just GET for now
    // TODO: Refactor so that it goes from resource -> method instead
    // of method -> resource
    if (strcmp(req->protocol, "HTTP/1.0"))
    {
        printf("Protocol `%s` not implemented\n", req->protocol);
        return 1;
    }

    if (!strcmp(req->method, "GET"))
    {
        response = get(req->resource);
    }
    else
    {
        printf("Not Implemented");
        return 501;
    }

    printf("%s", response);
    return 0;    
}
