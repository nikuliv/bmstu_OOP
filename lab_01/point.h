#ifndef POINT_H
#define POINT_H

#include <cstdio>

struct point
{
    double x;
    double y;
    double z;
};

struct points_info
{
    int n;
    point* arr;
};

int points_alloc(points_info &pts, const int len);
void points_free(points_info &pts);

int read_point(point &dot, FILE* const f);
int read_n_points(point &dots, const int n, FILE* const f);
int read_points(points_info &pts, FILE* const f);

#endif // POINT_H
