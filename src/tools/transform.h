#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include <QDebug>

#include "abstractselection.h"
#include "components/boundingrectitem.h"
#include "tooloptions/transform_menu.h"

class Transform : public AbstractSelection
{
    Q_OBJECT

public:
    Transform(QWidget *parent=0);
    ~Transform();
    void move(QMouseEvent *event);
    void press(QMouseEvent *event);
    void release(QMouseEvent *event);

    void setTransformMode(bool set);
    QWidget *getToolMenu();

public slots:
    void drawBounds(bool draw);

private:
    void drawBoundingRect();
    void removeBoundingRect();
    void connectMenu(TransformMenu *menu);

    BoundingRectItem *_rect;
    bool _boundsDrawn;
};

#endif // SELECTTOOL_H
