#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "point.h"

struct move
{
    int dx;
    int dy;
    int dz;
};

struct scale
{
    double kx;
    double ky;
    double kz;
};

struct turn
{
    int ox;
    int oy;
    int oz;
};

void move_point(point& dot, const move coeff);
int move_points(points_info& pts, const move coeff);

void scale_point(point& dot, const scale coeff);
int scale_points(points_info& pts, const scale coeff);

double d_cos(const double angle);
double d_sin(const double angle);

void turn_point_in_plane(double& coord_1, double &coord_2, const double angle);
void turn_point(point& dot, const turn coeff);
int turn_points(points_info& pts, const turn coeff);

#endif // OPERATIONS_H
