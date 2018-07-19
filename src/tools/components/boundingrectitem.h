#ifndef BOUNDINGRECTITEM_H
#define BOUNDINGRECTITEM_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QDebug>

namespace TransformTool {
    class BoundingRectItem;
}

class BoundingRectItem : public QGraphicsRectItem
{
public:

    enum HotSpot{
        ScaleTopLeftCorner,
        ScaleTopRightCorner,
        ScaleBottomLeftCorner,
        ScaleBottomRightCorner,
        ScaleTopBoundary,
        ScaleBottomBoundary,
        ScaleLeftBoundary,
        ScaleRightBoundary,
        RotateTopLeftCorner,
        RotateTopRightCorner,
        RotateBottomLeftCorner,
        RotateBottomRightCorner,
        Move
    };

    BoundingRectItem();

    inline void transformMode(bool set){ _transformMode = set; }
    void setPoints(QPointF min,QPointF max);

signals:
    void mouseIsHovering(HotSpot);

protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QRectF boundingRect() const;

private:
    QRectF _boundingRect;
    qreal _width, _height;

    bool _transformMode;
};

#endif // BOUNDINGRECTITEM_H
