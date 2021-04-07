#include "cstdio"
#include <cstdlib>
#include "point.h"
#include "figure.h"
#include "errors.h"
#include "file_proc.h"

int points_alloc(points_info& pts, const int len)
{
    pts.n = len;
    pts.arr = (point*) calloc(len, sizeof(point));

    if (!pts.arr)
        return PTR_ALL_ERR;

    return OK;
}


void points_free(points_info &pts)
{
    if (pts.arr)
        free(pts.arr);
}


int read_point(point& dot, FILE* const f)
{
    if (fscanf(f, "%lf%lf%lf", &dot.x, &dot.y, &dot.z) != 3)
        return FILE_FORMAT_ERR;

    return OK;
}


int read_n_points(points_info &pts, FILE *const f)
{
    int err = 0;
    for (int i = 0; i < pts.n && !err; i++)
    {
        if (read_point(pts.arr[i], f))
            err = FILE_FORMAT_ERR;
    }
    return err;
}


int read_points(points_info &pts, FILE* const f)
{
    int n;
    int err = 0;

    err = read_amount(n, f);
    if (!err)
    {
        if (n)
            err = points_alloc(pts, n);
        else
            err = NO_DOTS;

        if (!err)
        {
            if ((err = read_n_points(pts, f)) == FILE_FORMAT_ERR)
                points_free(pts);
        }
    }
    return err;
}
