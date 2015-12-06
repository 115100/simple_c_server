#include "parse.h"
#include "server.h"
#include "types.h"


int main()
{
    // TODO: Optionally read from CLI instead of prompting for input
    Request req;
    int statusCode;

    req = request_parse();

    statusCode = execute_request(&req);

    free(req.method);
    free(req.resource);
    free(req.protocol);

    if(!(200 <= statusCode < 400))
    {
        return 1;
    }

    return 0;
}
