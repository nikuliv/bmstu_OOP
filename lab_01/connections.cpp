#include "cstdio"
#include <cstdlib>
#include "connections.h"
#include "figure.h"
#include "errors.h"
#include "file_proc.h"

int connections_alloc(connections_info &connections, const int len)
{
    connections.n = len;

    connections.arr = (connection*) calloc(len, sizeof(connection));
    if (!connections.arr)
        return PTR_ALL_ERR;

    return OK;
}


void connections_free(connections_info &connections)
{
    if (connections.arr)
        free(connections.arr);
}


int read_connection(connection& joints, FILE* const f)
{
    if (fscanf(f, "%d%d", &joints.p1, &joints.p2) != 2)
        return FILE_FORMAT_ERR;

    return OK;
}


int read_n_connections(connections_info& connection, FILE * const f)
{
    int err = OK;
    for (int i = 0; i < connection.n && !err; i++)
    {
        if (read_connection(connection.arr[i], f))
            err = FILE_FORMAT_ERR;
    }

    return err;
}


int read_connections(connections_info& connections, FILE* const f)
{
    int n;
    int err = OK;

    err = read_amount(n, f);
    if (!err)
    {
        if (n)
            err = connections_alloc(connections, n);
        else
            err = NO_LINKS;

        if (!err)
        {
            if ((err = read_n_connections(connections, f)) == FILE_FORMAT_ERR)
                connections_free(connections);
        }
    }
    return err;
}
