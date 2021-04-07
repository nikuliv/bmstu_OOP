#ifndef CONNECTION_H
#define CONNECTION_H
#include "point.h"

struct connection
{
    int p1;
    int p2;
};

struct connections_info
{
    int n;
    connection *arr;
};

int connections_alloc(connections_info &connections, const int len);
void connections_free(connections_info &connections);
int read_connection(connection &joints, FILE* const f);
int read_n_connections(connections_info& connection, FILE* const f);
int read_connections(connections_info& connections, FILE* const f);

#endif // CONNECTION_H
