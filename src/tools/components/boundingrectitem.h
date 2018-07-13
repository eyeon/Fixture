#ifndef BOUNDINGRECTITEM_H
#define BOUNDINGRECTITEM_H

#include <QGraphicsRectItem>
#include <QPainter>

class BoundingRectItem : public QGraphicsRectItem
{
public:
    BoundingRectItem();

    inline void transformMode(bool set){ _transformMode = set; }
    void setPoints(QPointF min,QPointF max);

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
