#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "abstractselection.h"
#include "components/boundingrectitem.h"
#include "tooloptions/transform_menu.h"

class Transform : public AbstractSelection
{
    Q_OBJECT

public:
    Transform(QWidget *parent=0);
    ~Transform();
    void move(QGraphicsSceneMouseEvent *event);
    void press(QGraphicsSceneMouseEvent *event);
    void release(QGraphicsSceneMouseEvent *event);

    void setTransformMode(bool set);
    QWidget *getToolMenu();

public slots:
    void drawBounds(bool draw);
    inline void setAutoSelect(bool set){ _autoSelect = set;}

private:
    void drawBoundingRect();
    void removeBoundingRect();
    void connectMenu(TransformMenu *menu);

    BoundingRectItem *_rect;
    bool _boundsDrawn,_autoSelect;
};

#endif // SELECTTOOL_H
