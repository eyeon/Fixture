#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "../layers/layer.h"
#include "canvas.h"

class Document
{
public:
    Document(const QList<Layer *> layers, const QSharedDataPointer<Canvas> canvas);
    void write(QDataStream&) const;
    void read(QDataStream&);
    friend QDataStream& operator>>(QDataStream& ds, Document& document);
    friend QDataStream& operator<<(QDataStream& ds, const Document &document);

private:
    QList<Layer*> _layers;
    QSharedDataPointer<Canvas> _canvas;
};

#endif // DOCUMENT_H
