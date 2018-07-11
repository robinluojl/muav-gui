#include "mainwindow.h"
#include "ui_mainwindow.h"

qreal scene_x = 1500.0;
qreal scene_y = 900.0;
qreal scene_center_x = -500;
qreal scene_center_y = -300;
int cell_dimension = 25;
int cell_x = cell_dimension;
int cell_y = cell_dimension;

static const int UAVCount = 5;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create scene, set scene rect
    scene = new QGraphicsScene(this);

    QRectF scene_rect(scene_center_x, scene_center_y, scene_x, scene_y);
    scene->setSceneRect(scene_rect);
    scene->addRect(scene_rect);

    // add grid

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
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(1000 / 33);

//    timer for besenham's circles
    bc_timer = new QTimer(this);
    connect(bc_timer, SIGNAL(timeout()), this, SLOT(draw_bc(scene)));
    bc_timer->start(1000 / 33);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//    function to draw Besenham's circles
void MainWindow::draw_bc(QGraphicsScene *scene)
{
    QPointF start = (v1->uav_center_wrt_scene);
    qreal x = start.x() + v1->radius;
    qreal y = start.y();
//    int x = radius; int x  = v1->uav_y - v1->radius;
//    int y = 0; int y = v1->uav_x;
    qreal err = 0;
    QBrush bc_brush(Qt::red, Qt::SolidPattern);
    QPen bc_pen(bc_brush, 0.2, Qt::SolidLine);

//    while (x >= y)
//    {
//        putpixel(x0 + x, y0 + y, 7);
        scene->addRect(x, y, cell_x, cell_y, bc_pen);
//        putpixel(x0 + y, y0 + x, 7);
//        putpixel(x0 - y, y0 + x, 7);
//        putpixel(x0 - x, y0 + y, 7);
//        putpixel(x0 - x, y0 - y, 7);
//        putpixel(x0 - y, y0 - x, 7);
//        putpixel(x0 + y, y0 - x, 7);
//        putpixel(x0 + x, y0 - y, 7);

//    if (err <= 0)
//    {
//        y += 1;
//        err += 2*y + 1;
//    }

//    if (err > 0)
//    {
//        x -= 1;
//        err -= 2*x + 1;
//    }
}

//void MainWindow::on_addRegion1_clicked()
//{
//    Region* region = new Region();
//    scene->addItem(region);
//    rlist.push_back(region);
//    qDebug() << scene->items();
//}
