#include "boundingrectitem.h"

using namespace TransformTool;

BoundingRectItem::BoundingRectItem()
{    
    setFlag(QGraphicsItem::ItemIsMovable);
    _transformMode = false;
    _width = 0;
    _height = 0;

    _rectList[0] = r0;
    _rectList[1] = r1;
    _rectList[2] = r2;
    _rectList[3] = r3;
    _rectList[4] = r4;
    _rectList[5] = r5;
    _rectList[6] = r6;
    _rectList[7] = r7;
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
    painter->setPen(QPen(Qt::gray, 1, Qt::DashLine));
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
    r0 = new QRectF(r);
    r.translate(_width/2,0);
    painter->drawRect(r);
    r1 = new QRectF(r);
    r.translate(_width/2 + 0.75,0);
    painter->drawRect(r);
    r2 = new QRectF(r);
    r.translate(0,_height/2);
    painter->drawRect(r);
    r3 = new QRectF(r);
    r.translate(0,_height/2 + 0.75);
    painter->drawRect(r);
    r4 = new QRectF(r);
    r.translate(-1 * _width/2,0);
    painter->drawRect(r);
    r5 = new QRectF(r);
    r.translate(-1 * _width/2 - 0.75,0);
    painter->drawRect(r);
    r6 = new QRectF(r);
    r.translate(0,-1 * _height/2 - 0.75);
    painter->drawRect(r);
    r7 = new QRectF(r);

    setTriggers();
}

QRectF BoundingRectItem::boundingRect() const
{
    return QRectF(_boundingRect.topLeft() - QPointF(5,5),
                  _boundingRect.bottomRight() + QPointF(5,5));
}

BoundingRectItem::HotSpot BoundingRectItem::checkMouse(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();
    QMapIterator<int,QRectF*> itr(_rectList);

    while(itr.hasNext()){
        itr.next();
        if(itr.value()->contains(pos)){

        }
    }

    return BoundingRectItem::HotSpot::Move;
}
