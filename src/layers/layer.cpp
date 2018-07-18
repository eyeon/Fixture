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
QDataStream &operator>>(QDataStream &out,  Layer* layer)
{
    QString name;
    int type;
    QPixmap pixmap;

    out >> name >> type >> pixmap;

    layer = new RasterLayer(name, pixmap.toImage());
    layer->read(out);
    return out;
}

QDataStream& operator <<(QDataStream& stream, const QList<Layer*>& l){
    stream << l.size();
    for(auto& a_ptr: l){
        stream << *a_ptr;
    }
    return stream;
}
QDataStream& operator >>(QDataStream& stream, QList<Layer*>& l){
    l.clear();
    int size;
    int type;
    stream>>size;
    QString name;
    QPixmap pixmap;

    Layer* tmp;
    for(int i =0; i<size; ++i){

        stream >> name >> type;
        switch (type) {
        case Layer::RASTER:
            stream >> pixmap;
            tmp = new RasterLayer(name, pixmap.toImage());
            break;
        default:
            break;
        }
        tmp->read(stream);

        qDebug() << tmp->getType() << tmp->getName() << tmp->getPixmap() << tmp->getPos();
        l.push_back(tmp);
    }
    return stream;
}

