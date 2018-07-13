#ifndef RASTERLAYER_H
#define RASTERLAYER_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QGraphicsScene>

#include "layer.h"

class RasterLayer : public Layer, public QGraphicsPixmapItem
{
public:
    RasterLayer(QString name, QImage image, QGraphicsItem *parentItem);
    ~RasterLayer();

    void setLocked(bool lock);
    void setSceneSelected(bool select);
    void setLayerSelected(bool select);
    void setZvalue(int z);

protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QImage _image;
};

#endif // RASTERLAYER_H
