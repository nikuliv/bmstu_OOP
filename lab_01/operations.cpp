#include "math.h"
#include "operations.h"
#include "errors.h"
#include "figure.h"

void move_point(point& dot, move coeff)
{
    dot.x += coeff.dx;
    dot.y += coeff.dy;
    dot.z += coeff.dz;
}

int move_points(points_info& pts, move coeff)
{
    if(!pts.arr)
        return NO_DOTS;
    int err = 0;

    for(int i = 0; i < pts.n; i++)
        move_point(pts.arr[i], coeff);

    return err;
}


void scale_point(point& dot, scale coeff)
{
    dot.x *= coeff.kx;
    dot.y *= coeff.ky;
    dot.z *= coeff.kz;
}

int scale_points(points_info& pts, scale coeff)
{
    if(!pts.arr)
        return NO_DOTS;
    int err = 0;

    for(int i = 0; i < pts.n; i++)
        scale_point(pts.arr[i], coeff);

    return err;
}


double d_cos(const double angle)
{
    return cos(angle);
}

double d_sin(const double angle)
{
    return sin(angle);
}

double to_radians(const double angle)
{
    return angle * M_PI / 180;
}

void turn_point_in_plane(double& coord_1, double &coord_2, const double angle)
{
    double temp_1 = coord_1;
    double temp_2 = coord_2;
    double rad_angle = to_radians(angle);
    double cos_ang = d_cos(rad_angle);
    double sin_ang = d_sin(rad_angle);

    coord_1 = temp_1 * cos_ang + temp_2 * sin_ang;
    coord_2 = temp_2 * cos_ang - temp_1 * sin_ang;
}

void turn_point(point& dot, turn coeff)
{
    turn_point_in_plane(dot.y, dot.z, coeff.ox);
    turn_point_in_plane(dot.z, dot.x, coeff.oy);
    turn_point_in_plane(dot.x, dot.y, coeff.oz);
}


int turn_points(points_info& pts, turn coeff)
{
    if(!pts.arr)
        return NO_DOTS;
    int err = 0;

    for(int i = 0; i < pts.n; i++)
    {
        turn_point(pts.arr[i], coeff);
    }

    return err;
}
