#include "transform.h"

/**
 * @brief Transform::Transform Constructs a transform tool
 * @param parent
 */
Transform::Transform(QWidget *parent) :
    AbstractSelection(QIcon(":/tools/select.svg"), "Transform Tool (V)",
                      QCursor(QIcon(":/tools/select.svg").pixmap(QSize(15, 15)),
                              0, 0),
                      Tool::SELECTION, Tool::TRANSFORM, parent)
{
    setShortcut(Qt::Key_V);
    _rect        = new TransformTool::BoundingRectItem();
    _boundsDrawn = false;
    _mouseButton = Qt::NoButton;
    _scalex      = 1;
    _scaley      = 1;
    _autoSelect  = false;
    _totaldx     = 0;
    _totaldy     = 0;
}

/**
 * @brief Transform::Transform
 * @param other
 */
Transform::Transform(const Transform &other) :
    AbstractSelection(QIcon(":/tools/select.svg"), "Transform Tool (V)",
                      QCursor(QIcon(":/tools/select.svg").pixmap(QSize(15, 15)),
                              0, 0),
                      Tool::SELECTION, Tool::TRANSFORM)
{
    _rect        = other._rect;
    _boundsDrawn = other._boundsDrawn;
    _mouseButton = other._mouseButton;
    _scalex      = other._scalex;
    _scaley      = other._scaley;
    _autoSelect  = other._autoSelect;
    _totaldx     = other._totaldx;
    _totaldy     = other._totaldy;

    setShortcut(Qt::Key_V);
}

/**
 * @brief Transform::~Transform
 */
Transform::~Transform()
{ }

/**
 * @brief Transform::press handles the mouse press event passed to it from the
 * QGraphicsScene
 * @param event
 */
void Transform::press(QGraphicsSceneMouseEvent *event)
{
    _prevPos = event->scenePos();
    QGraphicsItem *itm = _scene->itemAt(_prevPos, QTransform());
    _mouseButton = event->button();

    if (_boundsDrawn) {
        _handle = _rect->checkMouse(event);
    }

    if (_handle != TransformTool::BoundingRectItem::HotSpot::Move) {
        setTransformMode(true);
        _autoSelect = false;
        _curItems   = _scene->selectedItems();
        foreach(QGraphicsItem * itm, _curItems){
            _curState.push_back(itm->transform());
        }
        _prevState = _curState;
        return;
    }

    if (_autoSelect) {
        if (itm != 0 && itm->flags() & QGraphicsItem::ItemIsSelectable) {
            if (event->modifiers() & Qt::ControlModifier) {
                itm->setSelected(true);
            } else {
                if (_scene->selectedItems().length() <
                    2) _scene->clearSelection();
                itm->setSelected(true);
            }
        } else {
            _scene->clearSelection();
        }
        emit _scene->selectionChanged();
        drawBounds(_boundsDrawn);
        return;
    }

    if (!(_scene->selectedItems().contains(itm))) {
        _mouseButton = Qt::NoButton;
    }
} // Transform::press

/**
 * @brief Transform::release handles the mouse release event passed to it from the
 * QGraphicsScene
 * @param event
 */
void Transform::release(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    _mouseButton = Qt::NoButton;
    _curState.clear();
}

/**
 * @brief Transform::move handles the mouse move event passed to it from the
 * QGraphicsScene
 * @param event
 */
void Transform::move(QGraphicsSceneMouseEvent *event)
{
    _curPos = event->scenePos();
    qreal dx = _curPos.x() - _prevPos.x();
    qreal dy = _curPos.y() - _prevPos.y();


    if (_mouseButton == Qt::LeftButton) {
        if (_handle != TransformTool::BoundingRectItem::HotSpot::Move) {
            emit switchedToTransformMode(true);
        }

        switch (_handle) {
            case TransformTool::BoundingRectItem::HotSpot::Move: {
                foreach(QGraphicsItem * itm, _scene->selectedItems()){
                    itm->moveBy(dx, dy);
                    _totaldx += dx;
                    _totaldy += dy;
                }
                break;
            }

            case TransformTool::BoundingRectItem::HotSpot::
                ScaleBottomRightCorner: {
                _scalex = (width + dx) / width;
                _scaley = (height + dy) / height;
                for (int i = 0; i < _curItems.length(); i++) {
                    _curState[i].scale(_scalex, _scaley);
                    _curItems[i]->setTransform(_curState[i], false);
                }
                break;
            }

            case TransformTool::BoundingRectItem::HotSpot::ScaleTopLeftCorner: {
                _scalex = (width - dx) / width;
                _scaley = (height - dy) / height;
                for (int i = 0; i < _curItems.length(); i++) {
                    _curState[i].scale(_scalex, _scaley);
                    _curItems[i]->setTransform(_curState[i], false);
                    _curItems[i]->moveBy(dx, dy);
                    _totaldx += dx;
                    _totaldy += dy;
                }
                break;
            }

            case TransformTool::BoundingRectItem::HotSpot::ScaleTopRightCorner:
            {
                _scalex = (width + dx) / width;
                _scaley = (height - dy) / height;
                for (int i = 0; i < _curItems.length(); i++) {
                    _curState[i].scale(_scalex, _scaley);
                    _curItems[i]->setTransform(_curState[i], false);
                    _curItems[i]->moveBy(0, dy);
                    _totaldy += dy;
                }
                break;
            }

            case TransformTool::BoundingRectItem::HotSpot::ScaleBottomLeftCorner
                : {
                _scalex = (width - dx) / width;
                _scaley = (height + dy) / height;
                for (int i = 0; i < _curItems.length(); i++) {
                    _curState[i].scale(_scalex, _scaley);
                    _curItems[i]->setTransform(_curState[i], false);
                    _curItems[i]->moveBy(dx, 0);
                    _totaldx += dx;
                }
                break;
            }
            case TransformTool::BoundingRectItem::HotSpot::ScaleTopBoundary: {
                _scaley = (height - dy) / height;
                for (int i = 0; i < _curItems.length(); i++) {
                    _curState[i].scale(_scalex, _scaley);
                    _curItems[i]->setTransform(_curState[i], false);
                    _curItems[i]->moveBy(0, dy);
                    _totaldy += dy;
                }
                break;
            }

            case TransformTool::BoundingRectItem::HotSpot::ScaleBottomBoundary:
            {
                _scaley = (height + dy) / height;
                for (int i = 0; i < _curItems.length(); i++) {
                    _curState[i].scale(_scalex, _scaley);
                    _curItems[i]->setTransform(_curState[i], false);
                }
                break;
            }

            case TransformTool::BoundingRectItem::HotSpot::ScaleLeftBoundary: {
                _scalex = (width - dx) / width;
                for (int i = 0; i < _curItems.length(); i++) {
                    _curState[i].scale(_scalex, _scaley);
                    _curItems[i]->setTransform(_curState[i], false);
                    _curItems[i]->moveBy(dx, 0);
                    _totaldx += dx;
                }
                break;
            }

            case TransformTool::BoundingRectItem::HotSpot::ScaleRightBoundary: {
                _scalex = (width + dx) / width;
                for (int i = 0; i < _curItems.length(); i++) {
                    _curState[i].scale(_scalex, _scaley);
                    _curItems[i]->setTransform(_curState[i], false);
                }
                break;
            }

            case TransformTool::BoundingRectItem::HotSpot::
                RotateBottomLeftCorner: {
                break;
            }

            case TransformTool::BoundingRectItem::HotSpot::
                RotateBottomRightCorner: {
                break;
            }

            case TransformTool::BoundingRectItem::HotSpot::RotateTopLeftCorner:
            {
                break;
            }

            case TransformTool::BoundingRectItem::HotSpot::RotateTopRightCorner:
            {
                break;
            }
        }
    }

    _scalex  = 1;
    _scaley  = 1;
    _prevPos = _curPos;
    updateBounds();
} // Transform::move

/**
 * @brief Transform::drawBounds determines whether to draw the bounding rectangle
 * of the selection
 * @param draw
 */
void Transform::drawBounds(bool draw)
{
    if (draw) {
        drawBoundingRect();
    } else {
        _rect->setVisible(false);
    }

    _boundsDrawn = draw;
}

/**
 * @brief Transform::setTransformMode sets the transform mode whenever there is
 * a change in scale or rotate with the selection.
 * @param set
 */
void Transform::setTransformMode(bool set)
{
    _rect->transformMode(set);
}

/**
 * @brief Transform::updateBounds redraw the boundaries whenever there is a change
 * in the scene.
 */
void Transform::updateBounds()
{
    if (_boundsDrawn) {
        drawBoundingRect();
        _scene->update(_scene->sceneRect());
    }
}

/**
 * @brief Transform::drawBoundingRect calculated the bounding rect of the given
 * selection
 */
void Transform::drawBoundingRect()
{
    if (_scene == nullptr) {
        return;
    }

    QList<QGraphicsItem *> selected      = _scene->selectedItems();
    QList<QGraphicsItem *>::iterator itr = selected.begin();
    QPointF max(INT_MIN, INT_MIN), min(INT_MAX, INT_MAX);

    for (; itr != selected.end(); ++itr) {
        QGraphicsItem *temp    = *itr;
        QPointF itmTopLeft     = temp->boundingRect().topLeft();
        QPointF itmBottomRight = temp->boundingRect().bottomRight();
        itmTopLeft     = temp->mapToScene(itmTopLeft);
        itmBottomRight = temp->mapToScene(itmBottomRight);
        if (itmTopLeft.x() < min.x()) {
            min.setX(itmTopLeft.x());
        }

        if (itmTopLeft.y() < min.y()) {
            min.setY(itmTopLeft.y());
        }

        if (itmBottomRight.x() > max.x()) {
            max.setX(itmBottomRight.x());
        }

        if (itmBottomRight.y() > max.y()) {
            max.setY(itmBottomRight.y());
        }
    }

    if (max == QPointF(INT_MIN, INT_MIN) || min == QPointF(INT_MAX, INT_MAX)) {
        if (_scene->items().contains(_rect)) {
            _rect->setVisible(false);
        }
        return;
    }

    _rect->setPoints(min, max);
    width  = max.x() - min.x();
    height = max.y() - min.y();

    if (_scene->items().contains(_rect)) {
        _rect->setVisible(true);
    } else {
        _scene->addItem(_rect);
    }
} // Transform::drawBoundingRect

/**
 * @brief Transform::actionTaken decides whether to keep the current transforms
 * made after enter the transform mode or not
 * @param accept
 */
void Transform::actionTaken(bool accept)
{
    if (!accept) {
        for (int i = 0; i < _curItems.length(); i++) {
            _curItems[i]->setTransform(_prevState[i], false);
            _curItems[i]->moveBy(-1 * _totaldx, -1 * _totaldy);
        }
    }
    setTransformMode(false);
    _scene->update();
    drawBoundingRect();
    emit switchedToTransformMode(false);
    _totaldx = 0;
    _totaldy = 0;
}

/**
 * @brief Transform::getToolMenu returns the tool menu of the current tool
 * @return
 */
QWidget * Transform::getToolMenu()
{
    if (_menuExists) {
        return _menu;
    }
    _menuExists = true;

    TransformMenu *transformMenu = new TransformMenu();
    _menu = transformMenu;
    connectMenu(transformMenu);

    return _menu;
}

/**
 * @brief Transform::connectMenu connects the signals of the menu to the respective
 * slots
 * @param menu
 */
void Transform::connectMenu(TransformMenu *menu)
{
    connect(menu, SIGNAL(autoSelect(bool)), this, SLOT(setAutoSelect(bool)));
    connect(menu, SIGNAL(showTransform(bool)), this, SLOT(drawBounds(bool)));
    connect(this, SIGNAL(switchedToTransformMode(bool)), menu,
            SLOT(enterTransformMode(bool)));
    connect(menu, SIGNAL(changesAccepted(bool)), this, SLOT(actionTaken(bool)));
}

/**
 * @brief Transform::clone
 * @return
 */
Tool * Transform::clone() const
{
    return new Transform(*this);
}
