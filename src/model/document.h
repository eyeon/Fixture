#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "../layers/layer.h"
#include "canvas.h"

class document
{
public:
    document(QList<Layer*> layers, Canvas *canvas);
};

#endif // DOCUMENT_H
