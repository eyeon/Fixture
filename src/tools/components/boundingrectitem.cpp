#include "boundingrectitem.h"

using namespace TransformTool;

BoundingRectItem::BoundingRectItem()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    _transformMode = false;
    _width         = 0;
    _height        = 0;
}

void BoundingRectItem::setPoints(QPointF min, QPointF max)
{
    _boundingRect.setTopLeft(min);
    _boundingRect.setBottomRight(max);

    _width  = max.x() - min.x();
    _height = max.y() - min.y();
}

void BoundingRectItem::paint(QPainter *painter,
     const QStyleOptionGraphicsItem *  option,
     QWidget *                         widget)
{
    painter->setPen(QPen(Qt::gray, 1, Qt::DashLine));
    if (_transformMode) {
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
        painter->drawLine(_boundingRect.topLeft(), _boundingRect.bottomRight());
        painter->drawLine(_boundingRect.bottomLeft(), _boundingRect.topRight());
    }
    painter->drawRect(_boundingRect);
    QPointF topleft = _boundingRect.topLeft();
    topleft -= QPointF(2, 2);
    QPointF bottomRight = _boundingRect.topLeft();
    bottomRight += QPointF(2, 2);
    QRectF r(topleft, bottomRight);
    painter->setPen(QPen(Qt::gray, 1, Qt::SolidLine));
    if (_transformMode) {
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    }
    painter->drawRect(r);
    r.translate(_width / 2, 0);
    painter->drawRect(r);
    r.translate(_width / 2 + 0.75, 0);
    painter->drawRect(r);
    r.translate(0, _height / 2);
    painter->drawRect(r);
    r.translate(0, _height / 2 + 0.75);
    painter->drawRect(r);
    r.translate(-1 * _width / 2, 0);
    painter->drawRect(r);
    r.translate(-1 * _width / 2 - 0.75, 0);
    painter->drawRect(r);
    r.translate(0, -1 * _height / 2 - 0.75);
    painter->drawRect(r);
} // BoundingRectItem::paint

QRectF BoundingRectItem::boundingRect() const
{
    return QRectF(_boundingRect.topLeft() - QPointF(5, 5),
                  _boundingRect.bottomRight() + QPointF(5, 5));
}

BoundingRectItem::HotSpot BoundingRectItem::checkMouse(
     QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();

    // Kind of an ugly hack, should be improved
    QPointF tl = _boundingRect.topLeft() - QPointF(5, 5);
    QPointF br = tl + QPointF(10, 10);
    QRectF rect(tl, br);

    if (rect.contains(pos)) {
        return BoundingRectItem::HotSpot::ScaleTopLeftCorner;
    }

    rect.translate(_width / 2, 0);
    if (rect.contains(pos)) {
        return BoundingRectItem::HotSpot::ScaleTopBoundary;
    }

    rect.translate(_width / 2, 0);
    if (rect.contains(pos)) {
        return BoundingRectItem::HotSpot::ScaleTopRightCorner;
    }

    rect.translate(0, _height / 2);
    if (rect.contains(pos)) {
        return BoundingRectItem::HotSpot::ScaleRightBoundary;
    }

    rect.translate(0, _height / 2);
    if (rect.contains(pos)) {
        return BoundingRectItem::HotSpot::ScaleBottomRightCorner;
    }

    rect.translate(-1 * _width / 2, 0);
    if (rect.contains(pos)) {
        return BoundingRectItem::HotSpot::ScaleBottomBoundary;
    }

    rect.translate(-1 * _width / 2, 0);
    if (rect.contains(pos)) {
        return BoundingRectItem::HotSpot::ScaleBottomLeftCorner;
    }

    rect.translate(0, -1 * _height / 2);
    if (rect.contains(pos)) {
        return BoundingRectItem::HotSpot::ScaleLeftBoundary;
    }

    return BoundingRectItem::HotSpot::Move;
} // BoundingRectItem::checkMouse
