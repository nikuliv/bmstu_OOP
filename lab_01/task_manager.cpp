#include "task_manager.h"
#include "errors.h"
#include "operations.h"
#include "figure.h"
#include "file_proc.h"

int tasks(request &req)
{
    static figure fig = init();
    int  err = 0;

    switch (req.act)
    {
    case INIT:
        break;
    case LOAD_FILE:
        err = load_figure(fig, req.file);
        break;
    case DRAW:
        err = draw_figure(fig, req.dr);
        break;
    case MOVE:
        err = move_figure(fig, req.mo);
        break;
    case SCALE:
        err = scale_figure(fig, req.sc);
        break;
    case TURN:
        err = turn_figure(fig, req.tu);
        break;
    case QUIT:
        free_figure(fig);
        break;
    default:
        err = UNKNOWN_COMMAND;
    }

    return err;
}
