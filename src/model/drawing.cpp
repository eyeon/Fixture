#include "drawing.h"

Drawing::Drawing(QWidget * widget, int width, int height) :
    _height(height), _width(width),
    QGraphicsScene(widget)

{
    QImage surface =
        QImage(_width, _height, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&surface);
    QBrush brush;
    brush.setTextureImage(QImage(":/brushes/checkers.png"));
    painter.setBrush(brush);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(surface.rect(), brush);
    painter.end();
    _parentItem = addPixmap(QPixmap::fromImage(surface));
    _parentItem->setFlag(QGraphicsItem::ItemClipsChildrenToShape);
    _parentItem->setHandlesChildEvents(false);
}

Drawing::~Drawing()
{ }

void Drawing::dragEnterEvent(QGraphicsSceneDragDropEvent * e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void Drawing::dragMoveEvent(QGraphicsSceneDragDropEvent * e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void Drawing::dropEvent(QGraphicsSceneDragDropEvent * e)
{
    foreach(const QUrl &url, e->mimeData()->urls()){
        QString fileName = url.toLocalFile();
        emit importAvailable(fileName);
    }
}

void Drawing::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    _tool->press(event);
}

void Drawing::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    _tool->move(event);
}

void Drawing::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    _tool->release(event);
}

void Drawing::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
    event->accept();
}
