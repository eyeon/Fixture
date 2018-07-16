#include "rasterlayer.h"
#include <QDebug>

RasterLayer::RasterLayer(const QString &name, const QImage &image):
    Layer(name, Layer::RasterLayer), _image(image)
{
    QIcon ico(QPixmap::fromImage(image));
    setIcon(ico);
    setPixmap(QPixmap::fromImage(image));
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

void RasterLayer::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    QStyleOptionGraphicsItem tampered(*option);
    tampered.state &= ~QStyle::State_Selected;
    QGraphicsPixmapItem::paint(painter,&tampered,widget);
}
