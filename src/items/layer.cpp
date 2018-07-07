#include "layer.h"

/**
 * @brief Layer::layer Constructs a new Layer for storing Raster Images
 * @param name
 * @param image
 * @param x, y
 * @param height, width
 */
Layer::Layer(QString name, QImage &image,
             int x, int y,
             int height, int width):
    _name(name),_image(image), _x(x), _y(y),
    _width(width), _height(height),
    _type(LayerType::RasterLayer)
{
    QIcon ico(QPixmap::fromImage(image));
    _item = new QListWidgetItem(ico,name);
    _item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    _item->setSizeHint(QSize(0,40));
}

Layer::~Layer()
{
}

void Layer::setScale(double factor)
{
    _width *= factor;
    _height *= factor;
}

void Layer::setPos(int x, int y)
{
    _x = x;
    _y = y;
}
