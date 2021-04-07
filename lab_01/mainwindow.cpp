#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task_manager.h"
#include "errors.h"
#include "operations.h"
#define _POSIX_SOURCE
#include <unistd.h>
#undef _POSIX_SOURCE
#include <stdio.h>
#include <direct.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    request que;
    que.act = INIT;
    tasks(que);
}

MainWindow::~MainWindow()
{
    delete ui;
}

errors draw_action(Ui::MainWindow* ui)
{
    draw dr;

    dr.gV = ui->graphicsView;
    dr.h = ui->graphicsView->height();
    dr.w = ui->graphicsView->width();

    request que;
    que.act = DRAW;
    que.dr = dr;

    errors err = (errors) tasks(que);
    return err;
}

errors transform_and_show(request que, Ui::MainWindow* ui)
{
    errors err = (errors) tasks(que);
    if (err)
        return err;
    else
        err = draw_action(ui);

    return err;
}

void MainWindow::on_pushButton_load_clicked()
{
    #define MAXDIR 256
    request que;
    que.act = LOAD_FILE;
    char dir[MAXDIR];
    getcwd(dir, MAXDIR);
    que.file.filename = strdup(ui->file_name_field->text().toStdString().c_str());
    printf("%s", que.file.filename);
    errors err = transform_and_show(que, ui);
    if (err)
        error_handling(err);
}

void MainWindow::on_rotate_clicked()
{
    request que;
    que.act = TURN;

    que.tu.ox = ui->lineEdit_x_r->text().toFloat();
    que.tu.oy = ui->lineEdit_y_r->text().toFloat();
    que.tu.oz = ui->lineEdit_z_r->text().toFloat();

    errors err = transform_and_show(que, ui);
    if (err)
        error_handling(err);
}

void MainWindow::on_replace_clicked()
{
    request que;
    que.act = MOVE;

    que.mo.dx = ui->lineEdit_x->text().toInt();
    que.mo.dy = ui->lineEdit_y->text().toInt();
    que.mo.dz = ui->lineEdit_z->text().toInt();

    errors err = transform_and_show(que, ui);
    if (err)
        error_handling(err);
}

void MainWindow::on_scale_clicked()
{
    request que;
    que.act = SCALE;

    que.sc.kx = ui->lineEdit_x_s->text().toFloat();
    que.sc.ky = ui->lineEdit_y_s->text().toFloat();
    que.sc.kz = ui->lineEdit_z_s->text().toFloat();

    errors err = transform_and_show(que, ui);
    if (err)
        error_handling(err);
}
