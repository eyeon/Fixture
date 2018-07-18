#include "rasterlayer.h"

RasterLayer::RasterLayer(QString name, QImage image,
                         QGraphicsItem *parentItem):
    Layer(name,Layer::RasterLayer), _image(image)
{
    QIcon ico(QPixmap::fromImage(image));
    setIcon(ico);
    setPixmap(QPixmap::fromImage(image));
    QGraphicsPixmapItem::setFlags(QGraphicsItem::ItemIsMovable |
                                  QGraphicsItem::ItemIsSelectable);
    setParentItem(parentItem);

}

RasterLayer::~RasterLayer()
{
}

void RasterLayer::setLocked(bool lock)
{
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable,!lock);
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsSelectable,!lock);
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
