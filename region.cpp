#include "region.h"

Region::Region()
{

}

QRectF Region::boundingRect() const
{
    QPointF scene_to_item = mapFromScene(-300, -300);
    return QRectF(scene_to_item.x(), scene_to_item.y(), 800, 800);
}

void Region::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QVector<QPointF>::iterator itr; itr = selectedPoints.begin(); selectedPoints.push_back(*itr);
            QPolygonF new_region(selectedPoints);
            QPainterPath new_path;
            // QLinearGradient new_gradient;
            new_path.addPolygon(new_region);
            QColor blue20 = Qt::blue;
            blue20.setAlphaF( 0.2 );
    //        painter->setBrush( green70 );
            QBrush brush; brush.setColor(blue20); brush.setStyle(Qt::SolidPattern);
            painter->fillPath(new_path, brush);
            selectedPoints.clear();
}

void Region::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        qDebug() << "Left " << event->pos();
        selectedPoints.push_back(event->pos());
    }
    else if (event->buttons() & Qt::RightButton) {
        qDebug() << "Right " << event->pos();
        update();
    }
}

void Region::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}
