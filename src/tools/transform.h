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

    QWidget *getToolMenu();

    void setTransformMode(bool set);
    void updateBounds();

public slots:
    void drawBounds(bool draw);
    inline void setAutoSelect(bool set){ _autoSelect = set;}

private:
    void drawBoundingRect();
    void connectMenu(TransformMenu *menu);

    TransformTool::BoundingRectItem *_rect;
    bool _boundsDrawn,_autoSelect;
    QPointF _prevPos, _curPos;
    Qt::MouseButton _mouseButton;
};

#endif // SELECTTOOL_H
