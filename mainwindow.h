#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "uav.h"
#include "environment.h"
#include "region.h"
#include <QTimer>
#include <QDebug>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // scene parameters
    qreal scene_x;
    qreal scene_y;
    qreal scene_center_x;
    qreal scene_center_y;

private slots:

//    void on_addRegion1_clicked();
    void draw_bc(QGraphicsScene *scene);


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    Uav *v1;
    Uav *v2;
    Uav *v3;
    Uav *v4;
    Uav *v5;

    QVector<QGraphicsItem* > rlist;

    QTimer *timer;
    QTimer *bc_timer;
};

#endif // MAINWINDOW_H
