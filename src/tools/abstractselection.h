#ifndef ABSTRACTSELECTION_H
#define ABSTRACTSELECTION_H

#include "tool.h"
#include "../layers/layer.h"

#include <QMouseEvent>
#include <QGraphicsScene>

class AbstractSelection : public virtual Tool
{
    Q_OBJECT

public:
    AbstractSelection();

public:
    inline void setScene(QGraphicsScene* scene) { _scene = scene;}

protected:
    QGraphicsScene *_scene;

};

#endif // ABSTRACTSELECTION_H
