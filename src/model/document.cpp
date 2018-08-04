#include "document.h"

Document::Document(const QList<Layer *>             layers,
                   const QSharedDataPointer<Canvas> canvas) :
    _layers(layers),
    _canvas(canvas)
{ }

Document::Document(const QString &name)
{
    _name = name;
}

bool Document::isDocumentValid(const QString &fileName)
{
    return fileName.endsWith(".fxt") || fileName.endsWith(".fxd");
}

void Document::write(QDataStream &out) const
{
    out << _magicNum << _version << *_canvas.constData() << _layers;
}

void Document::read(QDataStream &in)
{
    QList<Layer *> layers;
    Canvas * canvas = new Canvas(_name);

    qint64 magicNum;
    qint32 version;

    in >> magicNum >> version;

    if (magicNum != _magicNum) {
        // TODO: Add an exception for failure due to file incompatibility
        return;
    }

    in >> *canvas >> layers;

    _layers = layers;
    _canvas = QSharedDataPointer<Canvas>(canvas);
}

QDataStream &operator << (QDataStream &out, const Document &document)
{
    document.write(out);
    return out;
}

QDataStream &operator >> (QDataStream &in, Document &document)
{
    document.read(in);
    return in;
}
