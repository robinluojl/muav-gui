#ifndef UAV_H
#define UAV_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QRandomGenerator>

class Uav : public QGraphicsItem
{
public:
    Uav();
    Uav(double a, double b);

    QRectF boundingRect() const override;
//    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    qreal uav_x;
    qreal uav_y;
    qreal uav_th;
    QPointF uav_center_wrt_scene;

    bool pressed;
    QRectF footprintBound();
    qreal radius;
    qreal environment_dimension;

protected:
    void advance(int step) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:


        // from colliding mice
    qreal angle;
    qreal speed;
    qreal mouseEyeDirection;

    QColor color;

};

#endif // UAV_H
