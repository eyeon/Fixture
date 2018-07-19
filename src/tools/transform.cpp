#include "transform.h"

/**
 * @brief Transform::Transform
 * @param parent
 */
Transform::Transform(QWidget* parent):
    AbstractSelection(QIcon(":/tools/select.svg"),"Transform Tool (V)",
         QCursor(QIcon(":/tools/select.svg").pixmap(QSize(15,15)),0,0),
         Tool::SELECTION, Tool::TRANSFORM, parent)
{
    setShortcut(Qt::Key_V);
    _rect = new TransformTool::BoundingRectItem();
    _boundsDrawn = false;
    _mouseButton = Qt::NoButton;
    _scalex = 1;
    _scaley = 1;
}

/**
 * @brief Transform::~Transform
 */
Transform::~Transform()
{
}

/**
 * @brief Transform::press
 * @param event
 */
void Transform::press(QGraphicsSceneMouseEvent *event)
{
    _prevPos = event->scenePos();
    QGraphicsItem* itm = _scene->itemAt(_prevPos,QTransform());
    _mouseButton = event->button();

    if(_boundsDrawn) {
        _handle = _rect->checkMouse(event);
    }

    if(_handle != TransformTool::BoundingRectItem::HotSpot::Move){
        setTransformMode(true);
        _curState = _scene->selectedItems().last()->transform();
        return;
    }

    if(_autoSelect){
        if(itm != 0 && itm->flags() & QGraphicsItem::ItemIsSelectable){
            if(event->modifiers() & Qt::ControlModifier){
                itm->setSelected(true);
            }else{
                if(_scene->selectedItems().length() < 2) _scene->clearSelection();
                itm->setSelected(true);
            }
        }else{
            _scene->clearSelection();
        }
        emit _scene->selectionChanged();
        drawBounds(_boundsDrawn);
        return;
    }

    if(!(_scene->selectedItems().contains(itm))){
        _mouseButton = Qt::NoButton;
    }
}

/**
 * @brief Transform::release
 * @param event
 */
void Transform::release(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    _mouseButton = Qt::NoButton;
    _scalex = 1;
    _scaley = 1;
}

/**
 * @brief Transform::move
 * @param event
 */
void Transform::move(QGraphicsSceneMouseEvent *event)
{
    _curPos = event->scenePos();
    qreal dx = _curPos.x() - _prevPos.x();
    qreal dy = _curPos.y() - _prevPos.y();

    switch (_mouseButton){
    case Qt::LeftButton : {
        switch(_handle){
        case TransformTool::BoundingRectItem::HotSpot::Move:{
            foreach(QGraphicsItem *itm,_scene->selectedItems()) {
                itm->moveBy(dx,dy);
            }
            break;
        }

        case TransformTool::BoundingRectItem::HotSpot::ScaleBottomRightCorner:{
            _scalex += dx*0.002;
            _scaley += dy*0.002;
            _curState.scale(_scalex,_scaley);
            foreach(QGraphicsItem *itm,_scene->selectedItems()) {
                itm->setTransform(_curState,false);
            }
            break;
        }

        case TransformTool::BoundingRectItem::HotSpot::ScaleTopLeftCorner:{
            _scalex -= dx*0.002;
            _scaley -= dy*0.002;
            _curState.scale(_scalex,_scaley);
            foreach(QGraphicsItem *itm,_scene->selectedItems()) {
                itm->setTransform(_curState,false);
                itm->moveBy(dx*0.002,dy*0.002);
            }
            break;
        }

        case TransformTool::BoundingRectItem::HotSpot::ScaleTopRightCorner:{
            _scalex += dx*0.002;
            _scaley -= dy*0.002;
            _curState.scale(_scalex,_scaley);
            foreach(QGraphicsItem *itm,_scene->selectedItems()) {
                itm->setTransform(_curState,false);
                itm->moveBy(dx,dy);
            }
            break;
        }

        case TransformTool::BoundingRectItem::HotSpot::ScaleBottomLeftCorner:{
            _scalex += dx*0.002;
            _scaley -= dy*0.002;
            _curState.scale(_scalex,_scaley);
            foreach(QGraphicsItem *itm,_scene->selectedItems()) {
                itm->setTransform(_curState,false);
                itm->moveBy(dx,dy);
            }
            break;
        }
        case TransformTool::BoundingRectItem::HotSpot::ScaleTopBoundary:{
            _scaley -= dy*0.002;
            _curState.scale(_scalex,_scaley);
            foreach(QGraphicsItem *itm,_scene->selectedItems()) {
                itm->setTransform(_curState,false);
                itm->moveBy(0,dy);
            }
            break;
        }

        case TransformTool::BoundingRectItem::HotSpot::ScaleBottomBoundary:{
            _scaley += dy*0.002;
            _curState.scale(_scalex,_scaley);
            foreach(QGraphicsItem *itm,_scene->selectedItems()) {
                itm->setTransform(_curState,false);
            }
            break;
        }

        case TransformTool::BoundingRectItem::HotSpot::ScaleLeftBoundary:{
            _scalex -= dx*0.002;
            _curState.scale(_scalex,_scaley);
            foreach(QGraphicsItem *itm,_scene->selectedItems()) {
                itm->setTransform(_curState,false);
                itm->moveBy(dx,0);
            }
            break;
        }

        case TransformTool::BoundingRectItem::HotSpot::ScaleRightBoundary:{
            _scalex += dx*0.002;
            _curState.scale(_scalex,_scaley);
            foreach(QGraphicsItem *itm,_scene->selectedItems()) {
                itm->setTransform(_curState,false);
            }
            break;
        }
        }
    }
    }
    _scalex = 1;
    _scaley = 1;
    _prevPos = _curPos;
    updateBounds();
}

/**
 * @brief Transform::drawBounds
 * @param draw
 */
void Transform::drawBounds(bool draw)
{
    if(draw){
        drawBoundingRect();
    }else{
        _rect->setVisible(false);
    }

    _boundsDrawn = draw;
}

/**
 * @brief Transform::setTransformMode
 * @param set
 */
void Transform::setTransformMode(bool set)
{
    _rect->transformMode(set);
}

void Transform::updateBounds()
{
    if(_boundsDrawn){
        drawBoundingRect();
        _scene->update(_scene->sceneRect());
    }
}

/**
 * @brief Transform::drawBoundingRect
 */
void Transform::drawBoundingRect()
{
    if(_scene == NULL){
        return;
    }

    QList<QGraphicsItem*> selected = _scene->selectedItems();
    QList<QGraphicsItem*>::iterator itr = selected.begin();
    QPointF max(INT_MIN,INT_MIN),min(INT_MAX,INT_MAX);

    for(;itr != selected.end();++itr){
        QGraphicsItem* temp = *itr;
        QPointF itmTopLeft = temp->boundingRect().topLeft();
        QPointF itmBottomRight = temp->boundingRect().bottomRight();
        itmTopLeft = temp->mapToScene(itmTopLeft);
        itmBottomRight = temp->mapToScene(itmBottomRight);
        if(itmTopLeft.x() < min.x()){
            min.setX(itmTopLeft.x());
        }

        if(itmTopLeft.y() < min.y()){
            min.setY(itmTopLeft.y());
        }

        if(itmBottomRight.x() > max.x()){
            max.setX(itmBottomRight.x());
        }

        if(itmBottomRight.y() > max.y()){
            max.setY(itmBottomRight.y());
        }
    }

    if(max == QPointF(INT_MIN,INT_MIN) || min == QPointF(INT_MAX,INT_MAX)) {
        if(_scene->items().contains(_rect)){
            _rect->setVisible(false);
        }
        return;
    }

    _rect->setPoints(min,max);

    if(_scene->items().contains(_rect)){
        _rect->setVisible(true);
    }else{
        _scene->addItem(_rect);
    }

}

/**
 * @brief Transform::getToolMenu
 * @return
 */
QWidget* Transform::getToolMenu()
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
 * @brief Transform::connectMenu
 * @param menu
 */
void Transform::connectMenu(TransformMenu *menu)
{
    connect(menu, SIGNAL(showTransform(bool)), this, SLOT(drawBounds(bool)));
    connect(menu, SIGNAL(autoSelect(bool)),this,SLOT(setAutoSelect(bool)));
}

