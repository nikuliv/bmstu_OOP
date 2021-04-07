#ifndef DRAWING_H
#define DRAWING_H
#include "QGraphicsView"
#include "graph.h"
#include "point.h"
#include "connections.h"

struct draw
{
    QGraphicsView *gV;
    int w;
    int h;
};

struct point_coord
{
    double x;
    double y;
};

point_coord get_dot(point *dots, const int n);
point_coord point_transform(point_coord dot, draw arg);
void draw_connections(points_info pts, connections_info links, draw arg, graphics a);
void draw_line(point_coord p1, point_coord p2, graphics a, draw arg);
void my_addLine(graphics a, int x1, int x2, int y1, int y2);

#endif // DRAWING_H
