#include "environment.h"
#include <QDebug>

Environment::Environment()
{
    pressed = false;
    new_region_created = false;
    setFlag(ItemIsMovable); // should ideally not be enabled
}

QRectF Environment::boundingRect() const
{
    QPointF scene_to_item = mapFromScene(-300, -300);
    return QRectF(scene_to_item.x(), scene_to_item.y(), 600, 600);
}

void Environment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    if(pressed)
    {
        brush.setColor(Qt::red);
    } else {
        brush.setColor(Qt::green);
    }

    painter->drawRect(rec);
    painter->fillRect(rec, brush);

    if (new_region_created) {
        QPolygonF new_region(selectedPoints);
        QPainterPath new_path;
        QLinearGradient new_gradient;
        new_path.addPolygon(new_region);
        painter->setBrush(new_gradient);
        painter->drawPath(new_path);
    }
}

void Environment::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

        pressed = true;

        // output the current cursor positions
        qDebug() << event->pos().x() << event->pos().y();

        // add each point to the vector selectedPoints
        selectedPoints.push_back(event->pos());

        // print all the points in the vector
        for (QVector<QPointF>::iterator itr = selectedPoints.begin(); itr < selectedPoints.end(); ++itr)
        {
            qDebug() << *itr;
        }
    }
    else if (event->button() == Qt::RightButton) {
        bool new_region_created = true;
    }
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Environment::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;

    // repaint item
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

