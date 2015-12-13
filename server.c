#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "cat.h"
#include "ls.h"
#include "server.h"
#include "string.h"
#include "types.h"

void get(Response *resp, char *resource)
{
    char filename[PATH_MAX];
    char *searchFolder = "html";

    memset(filename, 0, PATH_MAX);

    strcat(filename, searchFolder);
    strcat(filename, resource);

    if (find_resource("html", filename) == 1)
    {
        free(resource);

        cat(filename, &(resp->body));
    }

    else
    {
        resp->body = "";
    }
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
