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
    char *body;
    char *headers[];
    int statusCode;
} Response;

#endif // TYPES_H
