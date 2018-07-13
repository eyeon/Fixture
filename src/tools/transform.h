#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include <QDebug>

#include "abstractselection.h"
#include "components/boundingrectitem.h"

class Transform : public AbstractSelection
{
public:
    Transform(QWidget *parent=0);
    ~Transform();
    void move(QMouseEvent *event);
    void press(QMouseEvent *event);
    void release(QMouseEvent *event);

private:
    void drawBoundingRect();

    BoundingRectItem *_rect;
    bool _transformMode, _drawBounds;
};

#endif // SELECTTOOL_H
