#include "paintwidget.h"

PaintWidget::PaintWidget(const QString &imagePath,QWidget *parent):
    QGraphicsView(parent)
{
    QStringList list = imagePath.split(".");
    QString fileNameNoExt = list[1];

     QString rawExtensions[] = {
         "ARW",
         "BAY",
         "CR2",
         "DCS",
         "MOS",
         "NEF",
         "RAW"
    };

    bool exists = std::find(std::begin(rawExtensions), std::end(rawExtensions),
                            fileNameNoExt.toUpper()) != std::end(rawExtensions);

    setStyleSheet("background-color: rgb(70, 70, 70);");

    if(exists){
        QImageReader reader(imagePath);
        QSize size = reader.size();
        int w = size.width() -1;
        int h = size.height() -1;
        QSize newSize = QSize(w,h);
        reader.setScaledSize(newSize);
        QImage raw = reader.read();
        setSceneRect(raw.rect());
        d = new Drawing(this,raw);
    } else {
        QImage image(imagePath);
        setSceneRect(image.rect());
        d = new Drawing(this,image);
    }
    setScene(d);
    d->updateImageCanvas();
}

PaintWidget::PaintWidget(const QSize &imageSize, QWidget *parent)
    : QGraphicsView(parent)
{
    QImage image(imageSize, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::white);
    setSceneRect(image.rect());
    setStyleSheet("background-color: rgb(70, 70, 70);");
    d = new Drawing(this,image);
    setScene(d);
}

void PaintWidget::wheelEvent(QWheelEvent *event)
{
    const QPointF p0scene = mapToScene(event->pos());

    qreal factor = std::pow(1.001, event->delta());
    scale(factor, factor);

    const QPointF p1mouse = mapFromScene(p0scene);
    const QPointF move = p1mouse - event->pos(); // The move
    horizontalScrollBar()->setValue(move.x() + horizontalScrollBar()->value());
    verticalScrollBar()->setValue(move.y() + verticalScrollBar()->value());
}
