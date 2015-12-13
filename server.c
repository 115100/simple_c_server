#include <stdio.h>
#include <stdlib.h>

#include "cat.h"
#include "ls.h"
#include "server.h"
#include "string.h"
#include "types.h"

void get(Response *resp, char *resource)
{
    char *filename;

    // Get without the first forward slash
    sscanf(resource, "/%ms", &filename);

    // Simple ping/pong response; case sensitive
    if (find_resource("html", filename) == 1)
    {
        free(resource);

        cat(filename, &(resp->body));
    }

    free(filename);
}

Response build_response(Request *req)
{
    Response resp;

    if (strcmp(req->protocol, "HTTP/1.0") != 0)
    {
        fprintf(stderr, "Protocol `%s` not implemented\n", req->protocol);
        return resp;
    }

    free(req->protocol);

    if (strcmp(req->method, "GET") == 0)
    {
        get(&resp, req->resource);
    }

    else
    {
        fprintf(stderr, "Not Implemented\n");
    }

    free(req->method);
    free(req->resource);

    return resp;
}
