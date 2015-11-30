#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"

// Take and parse user HTTP request
Request request_parse()
{
    Request req;

    printf("Request: ");
    scanf("%ms %ms %ms", &(req.method), &(req.resource), &(req.protocol));

    return req;
}
