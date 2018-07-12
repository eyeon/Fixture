#ifndef RASTERLAYER_H
#define RASTERLAYER_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QGraphicsScene>

#include "layer.h"

class RasterLayer : public Layer, public QGraphicsPixmapItem
{
public:
    RasterLayer(QString name, QImage image,
                int x, int y,
                int height, int width, QGraphicsItem *parentItem);
    ~RasterLayer();

    void setSceneSelected(bool select);
    void setLayerSelected(bool select);
    void setZvalue(int z);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QImage _image;
};

#endif // RASTERLAYER_H
