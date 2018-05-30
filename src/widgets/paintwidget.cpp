#include "paintwidget.h"

class PaintWidgetPrivate : public QGraphicsScene
{
public:
    PaintWidgetPrivate(PaintWidget *widget) :
        QGraphicsScene(widget)
    {
        q = widget;
        q->setScene(this);
    }

    ~PaintWidgetPrivate()
    {
    }

    void initialize(const QImage &image)
    {
        this->image = image;
        q->setSceneRect(image.rect());
        canvas = addPixmap(QPixmap::fromImage(image));

        q->setStyleSheet("background-color: rgb(70, 70, 70);");
    }

    void updateImageCanvas()
    {
        canvas->setPixmap(QPixmap::fromImage(image));
    }


    void setImage(const QImage &image)
    {
        this->image = image;
        this->updateImageCanvas();
    }

    QString imagePath;
    QLabel *imageLabel;
    QImage image;
    QGraphicsPixmapItem *canvas;

    PaintWidget *q;
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

    bool exists = std::find(std::begin(rawExtensions), std::end(rawExtensions), fileNameNoExt.toUpper()) != std::end(rawExtensions);

    if(exists)
    {
        QImageReader reader(imagePath);
        QSize size = reader.size();
        int w = size.width() -1;
        int h = size.height() -1;
        QSize newSize = QSize(w,h);
        reader.setScaledSize(newSize);
        QImage raw = reader.read();
        d->initialize(raw);
    }
    else
    {
        d->initialize(QImage(imagePath));
    }
    d->imagePath = imagePath;
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
    d->imagePath = path;
}

QString PaintWidget::imagePath() const
{
    return d->imagePath;
}
