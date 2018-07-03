#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QGraphicsItem>
#include <QImageReader>
#include <QWheelEvent>
#include <QScrollBar>
#include <QObject>

#include <cmath>

#include "../items/drawing.h"
#include "../model/canvas.h"

class PaintWidget : public QGraphicsView
{
    friend class Drawing;
    Q_OBJECT
public:
    PaintWidget(const QString &imagePath, QWidget *parent=0);
    PaintWidget(const Canvas *document, QWidget *parent=0);

    void setImagePath(QString path);
    QString getImagePath() const;

protected:
    void wheelEvent(QWheelEvent *event);

private:
    Drawing *d;
    QString _imagePath;
    void addStyleSheet();
};

#endif // PAINTWIDGET_H
