#include "rasterlayer.h"


RasterLayer::RasterLayer(const QString &name):
    Layer(name, Layer::RASTER)
{
}

RasterLayer::RasterLayer(const RasterLayer &other):
    Layer(other.getName(), Layer::RASTER)
{
    create(other.getPixmap());
}

RasterLayer::RasterLayer(const QString &name, const QImage &image):
    Layer(name, Layer::RASTER)
{
    create(QPixmap::fromImage(image));;
}

RasterLayer::RasterLayer(const QString &name, const QPixmap &pixmap) :
    Layer(name, Layer::RASTER)

{
    create(pixmap);
}

void RasterLayer::create(const QPixmap &pixmap)
{
    QIcon icon(pixmap);
    setIcon(icon);
    setPixmap(pixmap);

    QGraphicsPixmapItem::setFlags(QGraphicsItem::ItemIsMovable |
                                  QGraphicsItem::ItemIsSelectable);
}

RasterLayer::~RasterLayer()
{
}

void RasterLayer::setLocked(bool lock)
{
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable,!lock);
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
void RasterLayer::setParent(QGraphicsItem *parent)
{
    QGraphicsPixmapItem::setParentItem(parent);
}


void RasterLayer::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    QStyleOptionGraphicsItem tampered(*option);
    tampered.state &= ~QStyle::State_Selected;
    QGraphicsPixmapItem::paint(painter,&tampered,widget);
}

void RasterLayer::write(QDataStream &ds) const
{

    Layer::write(ds);
    ds << getPixmap() << getPos();
}

void RasterLayer::read(QDataStream &ds)
{
    QPixmap pixmap;
    QPointF pos;
    ds >> pixmap >> pos;
    create(pixmap);
    setPos(pos);

    qDebug() << getName() << getPixmap() << getPos();
}

Layer* RasterLayer::clone() const
{
    return new RasterLayer(*this);
}

