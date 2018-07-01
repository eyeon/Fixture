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

class PaintWidget : public QGraphicsView
{
    Q_OBJECT
public:
    PaintWidget(const QString &imagePath, QWidget *parent=0);
    PaintWidget(const QSize &imageSize, QWidget *parent=0);

    inline void setImagePath(QString path) { _imagePath = path; }
    inline QString imagePath() const { return _imagePath; }

protected:
    void wheelEvent(QWheelEvent *event);

private:
    Drawing *d;
    QString _imagePath;
};

#endif // PAINTWIDGET_H
