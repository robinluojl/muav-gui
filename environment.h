#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Environment : public QGraphicsItem
{
public:
    Environment();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool pressed;
    bool new_region_created;
    QVector<QPointF> selectedPoints;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // ENVIRONMENT_H
