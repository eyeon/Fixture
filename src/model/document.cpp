#include "document.h"

Document::Document(const QList<Layer *> layers, const QSharedDataPointer<Canvas> canvas) :
    _layers(layers),
    _canvas(canvas)
{
}

Document::write(QDataStream &out) const
{
    out << _layers << _canvas;
}

Document::read(QDataStream &in)
{
    QList<Layer*> layers;
    QSharedDataPointer<Canvas> canvas;
    in >> layers >> canvas;

    _layers = layers;
    _canvas = canvas;
}

QDataStream &operator <<(QDataStream &out, const Document &document)
{
    document.write(out);
    return out;
}

QDataStream &operator >>(QDataStream &in, Document &document)
{
    document.read(in);
    return in;
}

