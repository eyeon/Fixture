#include "paintwidget.h"

/**
 * @brief PaintWidget::PaintWidget Constructs a new PaintWidget for a new document
 * Creates a new canvas based on image path
 * @param imagePath
 * @param parent
 */
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

    bool isRaw = std::find(std::begin(rawExtensions), std::end(rawExtensions),
                            fileNameNoExt.toUpper()) != std::end(rawExtensions);

    _imagePath = imagePath;
    QImage image;

    if(isRaw){
        QImageReader reader(imagePath);
        QSize size = reader.size();

        int w = size.width() -1;
        int h = size.height() -1;

        QSize newSize = QSize(w,h);
        reader.setScaledSize(newSize);
        image = reader.read();
    } else {
        image = QImage(imagePath);
    }
    addStyleSheet();
    setSceneRect(image.rect());
    d = new Drawing(this,image);
    setScene(d);

    Layer l("Background",image,0,0,image.width(),image.height());
    _items.push_back(l);
    d->updateImageCanvas(_items);
}
/**
 * @brief PaintWidget::PaintWidget Constructs a new PaintWidget for a new document
 * Creates a new canvas based on Document
 * @param document
 * @param parent
 */
PaintWidget::PaintWidget(const Canvas *document, QWidget *parent)
    : QGraphicsView(parent)
{
    setImagePath(document->getName());
    QSize imageSize(document->getWidth(), document->getHeight());

    QImage image(imageSize, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::white);

    addStyleSheet();
    setSceneRect(image.rect());
    d = new Drawing(this,image);
    setScene(d);
}

void PaintWidget::addStyleSheet()
{
    QFile styleFile( ":/styles/paintwidget.qss" );
    styleFile.open( QFile::ReadOnly );

    QString style( styleFile.readAll() );
    setStyleSheet(style);
}

/**
 * @brief PaintWidget::wheelEvent Overrides the wheelEvent of QGraphicsView
 * Implements zooming in and out according to the position of the cursor
 * @param document
 * @param parent
 */
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
