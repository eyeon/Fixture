#include "drawing.h"

Drawing::Drawing(QWidget *widget,QImage &image) :
    QGraphicsScene(widget)
{
    _width = image.width();
    _height = image.height();

    QImage surface = QImage(_width,_height, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&surface);
    QBrush brush;
    brush.setTextureImage(QImage(":/brushes/checkers.png"));
    painter.setBrush(brush);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(surface.rect(), brush);
    painter.end();
    addPixmap(QPixmap::fromImage(surface));
}

Drawing::~Drawing()
{
}

void Drawing::dragEnterEvent(QGraphicsSceneDragDropEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void Drawing::dragMoveEvent(QGraphicsSceneDragDropEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void Drawing::dropEvent(QGraphicsSceneDragDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        emit importAvailable(fileName);
    }
}
