#include "layer.h"
#include "rasterlayer.h"

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

void Layer::write(QDataStream &ds) const
{
    ds << getName() << getType();
}

QDataStream &operator<<(QDataStream &out, const Layer* layer)
{
    layer->write(out);
    return out;
}
QDataStream& operator<<(QDataStream& ds, const Layer &layer)
{
    layer.write(ds);
    return ds;
}

QDataStream& operator>>(QDataStream& ds, Layer &layer)
{
    layer.read(ds);
    return ds;
}

QDataStream& operator <<(QDataStream& stream, const QList<Layer*>& l){
    stream << l.size();
    for(auto& a_ptr: l){
        stream << *a_ptr;
    }
    return stream;
}

QDataStream& operator >>(QDataStream& stream, QList<Layer*> &layers){
    layers.clear();
    int size;
    int type;

    stream >> size;

    QString name;
    layers.reserve(size);

    for(int i =0; i<size; ++i){

        stream >> name >> type;
        Layer::LayerType val = static_cast<Layer::LayerType>(type);
        Layer* layer = Layer::create(name, val);

        stream >> *layer;
        layers.push_back(layer);
    }
    return stream;
}

Layer* Layer::create(const QString &name, Layer::LayerType type)
{
    switch (type) {
    case Layer::RASTER:
        return new RasterLayer(name);
        break;
    default:
        Q_UNREACHABLE();
        break;
    }
}
