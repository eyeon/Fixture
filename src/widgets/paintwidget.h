#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QGraphicsItem>
#include <QImageReader>

class PaintWidgetPrivate;

class PaintWidget : public QGraphicsView
{
public:
    PaintWidget(const QString &imagePath, QWidget *parent=0);
    PaintWidget(const QSize &imageSize, QWidget *parent=0);

    void setImagePath(QString path);
    QString imagePath() const;

private:
    PaintWidgetPrivate *d;
};

#endif // PAINTWIDGET_H
