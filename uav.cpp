#include "uav.h"
#include <qmath.h>
const qreal Pi = M_PI;
const qreal TwoPi = 2 * M_PI;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Uav::Uav() : uav_x(0), uav_y(0), uav_th(0), color(Qt::red), pressed(false)
{
//    setRotation(180);
    setFlag(ItemIsMovable);
    setRotation(QRandomGenerator::global()->bounded(360 * 16));
    setPos(QRandomGenerator::global()->bounded(500), QRandomGenerator::global()->bounded(500));
    uav_center_wrt_scene = mapToScene(uav_x, uav_y);
}

Uav::Uav(double a, double b) : uav_x(0), uav_y(0), uav_th(0), color(Qt::red), pressed(false), radius(a), environment_dimension(b)
{
    setFlag(ItemIsMovable);
    setRotation(QRandomGenerator::global()->bounded(360 * 16));
    setPos(QRandomGenerator::global()->bounded(500), QRandomGenerator::global()->bounded(500));
    uav_center_wrt_scene = mapToScene(uav_x, uav_y);
}

QRectF Uav::boundingRect() const
{
    qreal radius_ = this->radius;
//    qreal radius_ = radius;
    return QRectF(10.0 - radius_, 20.0 - radius_, 2*radius_, 2*radius_);
}

//QPainterPath Uav::shape() const
//{
//    QPainterPath path;
//    path.addRect(-10, -20, 20, 40);
//    return path;
//}

void Uav::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->drawRect(boundingRect());

    if(pressed) {
        color = Qt::red;
    } else {
        color = Qt::black;
    }
    painter->setBrush(color);
//    painter->drawEllipse(5, 0, 4, 40);
//    painter->drawEllipse(15, 12.5, 4, 15);
//    painter->drawEllipse(0, 18, 20, 4);
    painter->drawEllipse(10 - 2, 20 - 2, 2*2, 2*2);

    qreal radius_ = this->radius;
    QRectF footprint_rect(10.0 - radius_, 20.0 - radius_, 2*radius_, 2*radius_);
//    int startAngle = 0 * 16;
//    int endAngle = 360 * 16;

      QColor green20 = Qt::green;
      green20.setAlphaF( 0.2 );
      QBrush brush; brush.setColor(green20); brush.setStyle(Qt::Dense2Pattern);
      painter->setBrush(brush);
//      painter->drawPie(footprint_rect, startAngle, endAngle);
      painter->drawEllipse(footprint_rect);
}

void Uav::advance(int step)
{
    if (!step)
        return;
    // Don't move too far away
    QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));
    if (lineToCenter.length() > 150) {
        qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            // Rotate left
            angle += (angle < -Pi / 2) ? 0.25 : -0.25;
        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            // Rotate right
            angle += (angle < Pi / 2) ? 0.25 : -0.25;
        }
    } else if (::sin(angle) < 0) {
        angle += 0.25;
    } else if (::sin(angle) > 0) {
        angle -= 0.25;
    }

    // Try not to crash with any other mice
    QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                                                       << mapToScene(0, 0)
                                                       << mapToScene(-30, -50)
                                                       << mapToScene(30, -50));
    foreach (QGraphicsItem *item, dangerMice) {
        if (item == this)
            continue;

        QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
        qreal angleToMouse = std::atan2(lineToMouse.dy(), lineToMouse.dx());
        angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

        if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
            // Rotate right
            angle += 0.5;
        } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
            // Rotate left
            angle -= 0.5;
        }
    }

    // Add some random movement
    if (dangerMice.size() > 1 && QRandomGenerator::global()->bounded(10) == 0) {
        if (QRandomGenerator::global()->bounded(1))
            angle += QRandomGenerator::global()->bounded(1 / 500.0);
        else
            angle -= QRandomGenerator::global()->bounded(1 / 500.0);
    }

    speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;

    qreal dx = ::sin(angle) * 10;
    mouseEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed) * 3)));

    // scene parameters
//    QPointF scene_center_mapped = mapFromScene(-500, -300);
//    qreal scm_x = scene_center_mapped.x();
//    qreal scm_y = scene_center_mapped.y();



}

void Uav::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update(); // repaints the entire object
    QGraphicsItem::mousePressEvent(event);
}

void Uav::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update(); // repaints the entire object
    QGraphicsItem::mousePressEvent(event);
}


