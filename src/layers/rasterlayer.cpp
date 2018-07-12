#include "rasterlayer.h"
#include <QDebug>

RasterLayer::RasterLayer(QString name, QImage image,
                         int x, int y, int height, int width):
    Layer(name,Layer::RasterLayer,x,y,height,width), _image(image)
{
    QIcon ico(QPixmap::fromImage(image));
    setIcon(ico);
    setPixmap(QPixmap::fromImage(image));
    QGraphicsPixmapItem::setFlags(QGraphicsItem::ItemIsMovable |
                                  QGraphicsItem::ItemIsSelectable |
                                  QGraphicsItem::ItemSendsGeometryChanges);
    _drawBounds = false;
    _transformMode = false;

}

RasterLayer::~RasterLayer()
{
}

void RasterLayer::setSceneSelected(bool select)
{
    QGraphicsItem::setSelected(select);
}

void RasterLayer::setLayerSelected(bool select)
{
    QListWidgetItem::setSelected(select);
}

void RasterLayer::setZvalue(int z)
{
    QGraphicsPixmapItem::setZValue(z);
}

QVariant RasterLayer::itemChange(GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsItem::itemChange(change, value);
}

void RasterLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QStyleOptionGraphicsItem tampered(*option);
    tampered.state &= ~QStyle::State_Selected;
    QGraphicsPixmapItem::paint(painter,&tampered,widget);

    if(option->state & QStyle::State_Selected && _drawBounds){
        painter->setPen(QPen(Qt::gray, 0.5, Qt::DashLine));
        if(_transformMode){
            painter->setPen(QPen(Qt::black, 0.5, Qt::SolidLine));
        }
        painter->drawRect(boundingRect());
        QPointF topleft = boundingRect().topLeft();
        topleft -= QPointF(2,2);
        QPointF bottomRight = boundingRect().topLeft();
        bottomRight += QPointF(2,2);
        QRectF r(topleft,bottomRight);
        painter->setPen(QPen(Qt::gray, 0.5, Qt::SolidLine));
        if(_transformMode){
            painter->setPen(QPen(Qt::black, 0.5, Qt::SolidLine));
        }
        painter->drawRect(r);
        r.translate(pixmap().width()/2,0);
        painter->drawRect(r);
        r.translate(pixmap().width()/2 + 0.75,0);
        painter->drawRect(r);
        r.translate(0,pixmap().height()/2);
        painter->drawRect(r);
        r.translate(0,pixmap().height()/2 + 0.75);
        painter->drawRect(r);
        r.translate(-1 * pixmap().width()/2,0);
        painter->drawRect(r);
        r.translate(-1 * pixmap().width()/2 - 0.75,0);
        painter->drawRect(r);
        r.translate(0,-1 * pixmap().height()/2 - 0.75);
        painter->drawRect(r);
    }

}
