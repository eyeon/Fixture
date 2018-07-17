#ifndef PANTOOL_H
#define PANTOOL_H

#include "abstractperception.h"
#include "tooloptions/pan_menu.h"

class Pan : public AbstractPerception
{
public:
    Pan(QWidget *parent=0);
    ~Pan();
    void move(QGraphicsSceneMouseEvent *event);
    void press(QGraphicsSceneMouseEvent *event);
    void release(QGraphicsSceneMouseEvent *event);
    QWidget* getToolMenu();
    void connectMenu();
};

#endif // PANTOOL_H
