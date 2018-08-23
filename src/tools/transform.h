#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "abstractselection.h"
#include "components/boundingrectitem.h"
#include "tooloptions/transform_menu.h"

/**
 * @brief class Transform responsible for different properties and functions of
 * the transform tool, which is being used for moving, scaling and rotating items
 */
class Transform : public AbstractSelection
{
    Q_OBJECT

public:
    Transform(QWidget *parent = nullptr);
    Transform(const Transform &other);
    ~Transform();

    void move(QGraphicsSceneMouseEvent *event);
    void press(QGraphicsSceneMouseEvent *event);
    void release(QGraphicsSceneMouseEvent *event);

    void setTransformMode(bool set);
    QWidget * getToolMenu();
    Tool * clone() const;
    void updateBounds();

public slots:
    void drawBounds(bool draw);
    inline void setAutoSelect(bool set){ _autoSelect = set; }
    void actionTaken(bool accept);

private:
    void drawBoundingRect();
    void connectMenu(TransformMenu *menu);
    void init();

    TransformTool::BoundingRectItem *_rect;
    TransformTool::BoundingRectItem::HotSpot _handle;
    bool _boundsDrawn, _autoSelect;
    QPointF _prevPos, _curPos;
    Qt::MouseButton _mouseButton;
    QList<QTransform> _curState, _prevState;
    QList<QGraphicsItem *> _curItems;
    qreal _scalex, _scaley;
    qreal width, height;
    qreal _totaldx, _totaldy;

signals:
    void switchedToTransformMode(bool enable);
};

#endif // SELECTTOOL_H
