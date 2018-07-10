#include "mainwindow.h"
#include "ui_mainwindow.h"

static const int UAVCount = 5;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create scene, set scene rect
    scene = new QGraphicsScene(this);
    qreal scene_x = 1500.0;
    qreal scene_y = 900.0;
    qreal scene_center_x = -500;
    qreal scene_center_y = -300;
    QRectF scene_rect(scene_center_x, scene_center_y, scene_x, scene_y);
    scene->setSceneRect(scene_rect);
    scene->addRect(scene_rect);

    // add grid
    int cell_dimension = 25;
    int cell_x; int cell_y; cell_x = cell_y = cell_dimension;
    for (int i= scene_center_x; i<= scene_center_x + scene_x - cell_x; i += cell_x) {
        for (int j = scene_center_y; j <= scene_center_y + scene_y - cell_y; j += cell_y) {
            QBrush cell_brush(Qt::blue, Qt::SolidPattern);
            QPen cell_pen(cell_brush, 0.2, Qt::SolidLine);
            scene->addRect(i, j, cell_x, cell_y, cell_pen);
        }
    }

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

//     adding uav item objects
    v1 = new Uav(80.0, 20.0); scene->addItem(v1);
    v2 = new Uav(20.0, 20.0); scene->addItem(v2);
    v3 = new Uav(60.0, 20.0); scene->addItem(v3);
    v4 = new Uav(10.0, 20.0); scene->addItem(v4);
    v5 = new Uav(100.0, 20.0); scene->addItem(v5);

//     timer for animation
//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
//    timer->start(1000 / 33);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::on_addRegion1_clicked()
//{
//    Region* region = new Region();
//    scene->addItem(region);
//    rlist.push_back(region);
//    qDebug() << scene->items();
//}
