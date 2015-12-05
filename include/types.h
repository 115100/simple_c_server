#ifndef TYPES_H
#define TYPES_H

typedef struct
{
    char *method;
    char *resource;
    char *protocol;
} Request;

typedef struct
{
    char *statusCode;
    char *headers[];
    char *body;
} Response;

#endif // TYPES_H
