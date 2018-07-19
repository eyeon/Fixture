#ifndef BOUNDINGRECTITEM_H
#define BOUNDINGRECTITEM_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMap>

namespace TransformTool {
    class BoundingRectItem;
}

class TransformTool::BoundingRectItem : public QGraphicsRectItem
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
    HotSpot checkMouse(QGraphicsSceneMouseEvent *event);

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
    QRectF *r0, *r1, *r2, *r3, *r4, *r5, *r6, *r7;
    bool _transformMode;
    QMap<int,HotSpot> _mouseTriggers;
    QMap<int,QRectF*> _rectList;

    void setTriggers();
};

#endif // BOUNDINGRECTITEM_H
