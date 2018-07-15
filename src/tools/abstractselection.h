#ifndef ABSTRACTSELECTION_H
#define ABSTRACTSELECTION_H

#include "tool.h"
#include "../layers/layer.h"

#include <QMouseEvent>
#include <QGraphicsScene>
#include <QDebug>

class AbstractSelection : public Tool
{
    Q_OBJECT

public:
    AbstractSelection(QIcon ico, const QString &name, QCursor cur, ToolGroup group, ToolType type, QWidget* parent = 0);

public:
    inline void setScene(QGraphicsScene* scene) { _scene = scene;}

protected:
    QGraphicsScene *_scene;

};

#endif // ABSTRACTSELECTION_H
