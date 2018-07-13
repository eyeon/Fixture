#ifndef BOUNDINGRECTITEM_H
#define BOUNDINGRECTITEM_H

#include <QGraphicsRectItem>

class BoundingRectItem : QGraphicsRectItem
{
public:
    BoundingRectItem(QPointF max, QPointF min);

protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QRectF _boundingRect;
    qreal _width, _height;

    bool _transformMode;
};

#endif // BOUNDINGRECTITEM_H
