#include <stdio.h>
#include <stdlib.h>

#include "server.h"
#include "string.h"

char *get(char *resource)
{
    // Simple ping/pong response; case sensitive
    if (strcmp(resource, "/ping") == 0)
    {
        return "pong";
    }
    // 404?
    else
    {
        return "";
    }
}

Response build_response(Request *req)
{
    Response resp;
    char *responseBody;

    if (strcmp(req->protocol, "HTTP/1.0") != 0)
    {
        fprintf(stderr, "Protocol `%s` not implemented\n", req->protocol);
        return resp;
    }

    if (strcmp(req->method, "GET") == 0)
    {
        resp.body = get(req->resource);
    }

    else
    {
        fprintf(stderr, "Not Implemented");
    }

    return resp;
}
