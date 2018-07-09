#include "rasterlayer.h"

RasterLayer::RasterLayer(QString name, QImage image,
                         int x, int y, int height, int width):
    Layer(name,Layer::RasterLayer,x,y,height,width), _image(image)
{
    QIcon ico(QPixmap::fromImage(image));
    setIcon(ico);
}

RasterLayer::~RasterLayer()
{

}
