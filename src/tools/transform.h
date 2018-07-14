#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include <QDebug>

#include "abstractselection.h"
#include "components/boundingrectitem.h"
#include "tooloptions/transform_menu.h"

class Transform : public AbstractSelection
{
public:
    Transform(QWidget *parent=0);
    ~Transform();
    void move(QMouseEvent *event);
    void press(QMouseEvent *event);
    void release(QMouseEvent *event);

    void setTransformMode(bool set);
    void drawBounds(bool draw);
    QWidget *getToolMenu();

private slots:
    void updateBounds();

private:
    void drawBoundingRect();
    void removeBoundingRect();
    void connectMenu();

    BoundingRectItem *_rect;
    bool _boundsDrawn;
};

#endif // SELECTTOOL_H
