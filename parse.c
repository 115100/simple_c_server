#include <stdio.h>

#include "parse.h"
#include "types.h"


// Take and parse user HTTP request
Request request_parse(char *queryString)
{
	Request req;

	if (sscanf(queryString, "%ms %ms %ms", &(req.method), &(req.resource), &(req.protocol)) == EOF)
	{
		fprintf(stderr, "Query doesn't match pattern: %s\n", queryString);
	}

	return req;
}
