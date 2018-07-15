#include "transform.h"

Transform::Transform(QWidget* parent):
    AbstractSelection(QIcon(":/tools/select.svg"),"Transform Tool (V)",
         QCursor(QIcon(":/tools/select.svg").pixmap(QSize(15,15)),0,0),
         Tool::SELECTION, Tool::TRANSFORM, parent)
{
    setShortcut(Qt::Key_V);
    _rect = new BoundingRectItem();
    _boundsDrawn = false;
}

Transform::~Transform()
{
}


void Transform::press(QMouseEvent *event)
{
}

void Transform::release(QMouseEvent *event)
{
}

void Transform::move(QMouseEvent *event)
{
    if(_boundsDrawn){
        drawBoundingRect();
        _scene->update(_scene->sceneRect());
    }
}

void Transform::drawBounds(bool draw)
{
    if(draw){
        drawBoundingRect();
    }else{
        _rect->setVisible(false);
    }

    _boundsDrawn = draw;
}

void Transform::setTransformMode(bool set)
{
    _rect->transformMode(set);
}

void Transform::drawBoundingRect()
{
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

    _rect->setPoints(min,max);

    if(_scene->items().contains(_rect)){
        _rect->setVisible(true);
    }else{
        _scene->addItem(_rect);
    }
}

void Transform::removeBoundingRect()
{
    delete _rect;
}

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

void Transform::connectMenu(TransformMenu *menu)
{
    connect(menu, SIGNAL(showTransform(bool)), this, SLOT(drawBounds(bool)));
}

