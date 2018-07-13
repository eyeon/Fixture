#include "transform.h"

Transform::Transform(QWidget* parent):
    Tool(QIcon(":/tools/select.svg"),"Transform Tool (V)",
         QCursor(QIcon(":/tools/select.svg").pixmap(QSize(15,15)),0,0),
         Tool::SELECTION,parent)
{
    setShortcut(Qt::Key_V);
    _rect = new BoundingRectItem();
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
}

void Transform::drawBounds(bool draw)
{
    if(draw){
        drawBoundingRect();
    }else{
        _rect->setVisible(false);
    }
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
        qDebug() << "ping";
        QGraphicsItem* temp = *itr;
        QPointF itmTopLeft = temp->boundingRect().topLeft();
        QPointF itmBottomRight = temp->boundingRect().bottomRight();
        if(itmTopLeft.x() < min.x()){
            min.setX(itmTopLeft.x());
        }

        if(itmTopLeft.y() < min.y()){
            min.setY(itmTopLeft.y());
        }

        if(itmBottomRight.x() > max.x()){
            max.setY(itmBottomRight.x());
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
