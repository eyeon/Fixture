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

    void drawBounds(bool draw);
    void setTransformMode(bool set);

private:
    void drawBoundingRect();
    void removeBoundingRect();

    BoundingRectItem *_rect;
};

#endif // SELECTTOOL_H
