#include "FixtureCanvas.h"

#include <QPainter>
#include <QBrush>

Fixture::Canvas::Canvas(QWidget *widget, QSize canvasSize):
    QOpenGLWidget(widget)
{
    setAutoFillBackground(false);
    setFixedSize(canvasSize);
}

void
Fixture::Canvas::paintEvent(QPaintEvent *event)
{
    QPainter *gc = new QPainter(this);
    gc->fillRect(event->rect(),QBrush(QColor(255,255,255)));
    event->accept();
    gc->end();
}
