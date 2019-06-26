#include "FixtureCanvas.h"

#include <QPainter>
#include <QBrush>

Fixture::Canvas::Canvas(QWidget *widget, QSize canvasSize):
    QOpenGLWidget(widget), _canvasSize(canvasSize)
{ }

void
Fixture::Canvas::paintEvent(QPaintEvent *event)
{
    QPainter gc(this);

    //set the background color
    gc.fillRect(event->rect(), QBrush(QColor(50, 50, 50)));

    //draw the canvas
    QRect drawArea(QPoint(0,0), _canvasSize);
    drawArea.moveCenter(event->rect().center());
    gc.fillRect(drawArea, QBrush(QColor(255, 255, 255)));

    //done
    event->accept();
    gc.end();
}
