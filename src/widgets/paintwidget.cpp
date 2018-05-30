#include "paintwidget.h"

class PaintWidgetPrivate : public QGraphicsScene
{
public:
    PaintWidgetPrivate(PaintWidget *widget) :
        QGraphicsScene(widget)
    {
        _q = widget;
        _q->setScene(this);
    }

    ~PaintWidgetPrivate()
    {
    }

    void initialize(const QImage &image)
    {
        _image = image;
        _q->setSceneRect(image.rect());
        _canvas = addPixmap(QPixmap::fromImage(image));

        _q->setStyleSheet("background-color: rgb(70, 70, 70);");
    }

    void updateImageCanvas()
    {
        QImage surface = QImage(_image.size(), QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&surface);
        QBrush brush;
        brush.setTextureImage(QImage(":/brushes/checkers.png"));
        painter.setBrush(brush);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(surface.rect(), brush);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(0, 0, _image);
        painter.end();
        _canvas->setPixmap(QPixmap::fromImage(surface));
    }


    void setImage(const QImage &image)
    {
        _image = image;
        this->updateImageCanvas();
    }

    QString _imagePath;
    QLabel *_imageLabel;
    QImage _image;
    QGraphicsPixmapItem *_canvas;

    PaintWidget *_q;
};


PaintWidget::PaintWidget(const QString &imagePath,QWidget *parent):
    QGraphicsView(parent)
    , d(new PaintWidgetPrivate(this))
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

    if(exists){
        QImageReader reader(imagePath);
        QSize size = reader.size();
        int w = size.width() -1;
        int h = size.height() -1;
        QSize newSize = QSize(w,h);
        reader.setScaledSize(newSize);
        QImage raw = reader.read();
        d->initialize(raw);
    } else {
        d->initialize(QImage(imagePath));
    }
    d->updateImageCanvas();
    d->_imagePath = imagePath;
}

PaintWidget::PaintWidget(const QSize &imageSize, QWidget *parent)
    : QGraphicsView(parent)
    , d(new PaintWidgetPrivate(this))
{
    QImage image(imageSize, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::white);

    d->initialize(image);
}

void PaintWidget::setImagePath(QString path)
{
    d->_imagePath = path;
}

QString PaintWidget::imagePath() const
{
    return d->_imagePath;
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
