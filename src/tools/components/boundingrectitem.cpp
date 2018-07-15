#include "boundingrectitem.h"

BoundingRectItem::BoundingRectItem()
{    
    setFlag(QGraphicsItem::ItemIsMovable);
    _transformMode = false;
    _width = 0;
    _height = 0;
    setAcceptHoverEvents(true);

}

void BoundingRectItem::setPoints(QPointF min, QPointF max)
{
    _boundingRect.setTopLeft(min);
    _boundingRect.setBottomRight(max);

    _width = max.x() - min.x();
    _height = max.y() - min.y();
}

void BoundingRectItem::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
    if(_transformMode){
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    }
    painter->drawRect(_boundingRect);
    QPointF topleft = _boundingRect.topLeft();
    topleft -= QPointF(2,2);
    QPointF bottomRight = _boundingRect.topLeft();
    bottomRight += QPointF(2,2);
    QRectF r(topleft,bottomRight);
    painter->setPen(QPen(Qt::gray, 1, Qt::SolidLine));
    if(_transformMode){
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    }
    painter->drawRect(r);
    r.translate(_width/2,0);
    painter->drawRect(r);
    r.translate(_width/2 + 0.75,0);
    painter->drawRect(r);
    r.translate(0,_height/2);
    painter->drawRect(r);
    r.translate(0,_height/2 + 0.75);
    painter->drawRect(r);
    r.translate(-1 * _width/2,0);
    painter->drawRect(r);
    r.translate(-1 * _width/2 - 0.75,0);
    painter->drawRect(r);
    r.translate(0,-1 * _height/2 - 0.75);
    painter->drawRect(r);
}

QRectF BoundingRectItem::boundingRect() const
{
    return QRectF(_boundingRect.topLeft() - QPointF(5,5),_boundingRect.bottomRight() + QPointF(5,5));
}

void BoundingRectItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "hover entered";
}

void BoundingRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "hover leaved";
}

void BoundingRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "hover moved";
}
