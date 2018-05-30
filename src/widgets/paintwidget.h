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

class PaintWidgetPrivate;

class PaintWidget : public QGraphicsView
{
    friend class PaintWidgetPrivate;
    Q_OBJECT
public:
    PaintWidget(const QString &imagePath, QWidget *parent=0);
    PaintWidget(const QSize &imageSize, QWidget *parent=0);

    void setImagePath(QString path);
    QString imagePath() const;

protected:
    void wheelEvent(QWheelEvent *event);

private:
    PaintWidgetPrivate *d;
};

#endif // PAINTWIDGET_H
