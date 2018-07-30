#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "../layers/layer.h"
#include "canvas.h"

class document
{
public:
    document(QList<Layer*> layers, QSharedDataPointer<Canvas> canvas);
};

#endif // DOCUMENT_H
