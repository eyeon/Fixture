#include "layer.h"

/**
 * @brief Layer::layer Constructs a new Layer for storing Raster Images
 * @param name
 * @param image
 * @param x, y
 * @param height, width
 */
Layer::Layer(QString name, LayerType type):
    _name(name),_type(type)
{
    setText(name);
    setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    setSizeHint(QSize(0,40));
}

Layer::~Layer()
{
}
