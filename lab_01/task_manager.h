#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "drawing.h"
#include "operations.h"
#include "QFile"

enum action
{
    INIT,
    LOAD_FILE,
    DRAW,
    MOVE,
    SCALE,
    TURN,
    QUIT
};

struct file_inf
{
    char *filename;
};

struct request
{
    action act;
    union
    {
        struct file_inf file;
        struct draw dr;
        struct move mo;
        struct scale sc;
        struct turn tu;
    };
};

int tasks(request &args);

#endif // TASK_MANAGER_H
