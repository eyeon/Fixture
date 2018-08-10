#ifndef PANTOOL_H
#define PANTOOL_H

#include "abstractperception.h"
#include "tooloptions/pan_menu.h"

/**
 * @brief class Pan responsible for different properties and functions of
 * the hand tool, like panning across a zoomed scene
 */
class Pan : public AbstractPerception
{
public:
    Pan(QWidget * parent = 0);
    Pan(const Pan &other);
    ~Pan();
    void move(QGraphicsSceneMouseEvent * event);
    void press(QGraphicsSceneMouseEvent * event);
    void release(QGraphicsSceneMouseEvent * event);
    QWidget * getToolMenu();
    void connectMenu();
    Tool * clone() const;
};

#endif // PANTOOL_H
