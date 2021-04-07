#include "drawing.h"
#include "graph.h"

point_coord get_dot(point *dots, int n)
{
    point_coord dot = {dots[n].x, dots[n].y};
    return dot;
}


point_coord point_transform(point_coord dot, draw arg)
{
    point_coord tmp;

    tmp.x = dot.x + arg.w/2;
    tmp.y = dot.y + arg.h/2;

    return tmp;
}


void draw_connections(points_info pts, connections_info links, draw arg, graphics a)
{
    point_coord p1, p2;

    for (int i = 0; i < links.n; i++)
    {
        p1 = get_dot(pts.arr, links.arr[i].p1);
        p2 = get_dot(pts.arr, links.arr[i].p2);
        draw_line(p1, p2, a, arg);
    }
}


void draw_line(point_coord p1, point_coord p2, graphics a, draw arg)
{
    p1 = point_transform(p1, arg);
    p2 = point_transform(p2, arg);

    my_addLine(a, p1.x, p2.x, p1.y, p2.y);
}

void my_addLine(graphics a, int x1, int x2, int y1, int y2)
{
    a.scene->addLine(x1, y1, x2, y2, a.pen);
}

