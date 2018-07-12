#include "rasterlayer.h"

RasterLayer::RasterLayer(QString name, QImage image,
                         int x, int y, int height, int width):
    Layer(name,Layer::RasterLayer,x,y,height,width), _image(image)
{
    QIcon ico(QPixmap::fromImage(image));
    setIcon(ico);
    setPixmap(QPixmap::fromImage(image));
    QGraphicsPixmapItem::setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);

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
