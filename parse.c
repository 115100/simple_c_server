#include <stdio.h>

#include "parse.h"
#include "types.h"


// Take and parse user HTTP request
int request_parse(char *queryString, Request *req)
{
	return sscanf(queryString, "%ms %ms %ms", &(req->method), &(req->resource), &(req->protocol));
}
