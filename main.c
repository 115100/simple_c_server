#include "parse.c"
#include "server.c"

int main()
{
    // TODO: Optionally read from CLI instead of prompting for input
    Request req;
    int status_code;

    req = request_parse();

    status_code = execute_request(&req);

    free(req.method);
    free(req.resource);
    free(req.protocol);

    if(!(200 <= status_code < 400))
    {
        return 1;
    }

    return 0;
}
