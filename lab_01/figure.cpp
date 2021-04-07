#include "cstdio"
#include <cstdlib>
#include "figure.h"
#include "errors.h"
#include "point.h"
#include "connections.h"
#include "drawing.h"
#include "graph.h"
#include "operations.h"
#include "task_manager.h"

figure& init()
{
    static figure fig;

    fig.points.n = 0;
    fig.points.arr = NULL;

    fig.connections.n = 0;
    fig.connections.arr = NULL;

    return fig;
}


void free_figure(figure& fig)
{
    fig.points.n = 0;
    points_free(fig.points);

    fig.connections.n = 0;
    connections_free(fig.connections);
}

void copy_figure(figure& fig, figure& tmp)
{
    fig.points.n = tmp.points.n;
    fig.points.arr = tmp.points.arr;

    fig.connections.n = tmp.connections.n;
    fig.connections.arr = tmp.connections.arr;
}


int load_figure(figure& fig, const file_inf &file)
{
    FILE *f = fopen(file.filename, "r");
    if (!f)
        return FILE_NOT_FOUND;
    figure fig_tmp = init();

    int err = read_points(fig_tmp.points, f);
    if (!err)
    {
        err = read_connections(fig_tmp.connections, f);
        if (err != OK)
            points_free(fig_tmp.points);
    }
    fclose(f);

    if (!err)
    {
        free_figure(fig);
        copy_figure(fig, fig_tmp);
    }

    return err;
}

int draw_figure(figure &fig, draw arg)
{
    graphics a;

    int err = init_graph(a, arg.gV);
    if (err)
        return err;

    draw_connections(fig.points, fig.connections, arg, a);

    a.scene->setSceneRect(QRectF(QPointF(0, 0), QSizeF(arg.w, arg.h)));
    set(arg.gV, a);

    return err;
}

int move_figure(figure& fig, move coeff)
{
    return move_points(fig.points, coeff);
}

int scale_figure(figure& fig, scale coeff)
{
    return scale_points(fig.points, coeff);
}

int turn_figure(figure& fig, turn coeff)
{
    return turn_points(fig.points, coeff);
}
