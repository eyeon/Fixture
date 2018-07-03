#include "drawing.h"

Drawing::Drawing(QWidget *widget,QImage &image) :
    QGraphicsScene(widget)
{
    _canvas = addPixmap(QPixmap::fromImage(image));
    _image = image;
    _width = image.width();
    _height = image.height();
}

Drawing::~Drawing()
{
}

void Drawing::updateImageCanvas(QList<Layer> items)
{
    QImage surface = QImage(_width,_height, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&surface);

    QBrush brush;
    brush.setTextureImage(QImage(":/brushes/checkers.png"));
    painter.setBrush(brush);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(surface.rect(), brush);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    QList<Layer>::iterator itr = items.begin();
    for(;itr != items.end();++itr){
        QImage img = itr->getImage();
        img.scaled(itr->getWidth(),itr->getHeight());
        painter.drawImage(itr->getX(), itr->getY(), img);
    }

    painter.end();
    _canvas->setPixmap(QPixmap::fromImage(surface));
}
