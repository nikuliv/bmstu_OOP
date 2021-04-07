#ifndef FIGURE_H
#define FIGURE_H
#include "point.h"
#include "connections.h"
#include "drawing.h"
#include "operations.h"
#include "task_manager.h"

struct figure
{
    points_info points;
    connections_info connections;
};

figure& init();
void free_figure(figure& fig);
void copy_figure(figure& fig, figure& tmp);
int load_figure(figure &ob, const file_inf &filename);

int draw_figure(figure &fig, const draw arg);

int move_figure(figure& fig, const move coeff);
int scale_figure(figure& fig, const scale coeff);
int turn_figure(figure& fig, const turn coeff);

#endif // FIGURE_H
