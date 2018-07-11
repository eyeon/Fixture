#ifndef RASTERLAYER_H
#define RASTERLAYER_H

#include <QGraphicsPixmapItem>

#include "layer.h"

class RasterLayer : public Layer, public QGraphicsPixmapItem
{
public:
    RasterLayer(QString name,QImage image,
                int x, int y,
                int height, int width);
    ~RasterLayer();

    void setSelected(bool select);
    void setZvalue(int z);

private:
    QImage _image;
};

#endif // RASTERLAYER_H
