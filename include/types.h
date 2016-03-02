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
    int statusCode;
    char *headers[];
} Response;

#endif // TYPES_H
