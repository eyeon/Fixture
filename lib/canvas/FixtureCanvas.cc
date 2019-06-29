#include "FixtureCanvas.h"

#include <QPainter>

Fixture::Canvas::Canvas(QWidget *widget, QSize canvasSize) :
    QWidget(widget, Qt::WindowFlags()), _canvasSize(canvasSize)
{ }

void
Fixture::Canvas::paintEvent(QPaintEvent * event)
{
    QPainter gc(this);

    // set the background color
    gc.fillRect(event->rect(),
                QBrush(QColor(50, 50, 50, 255), Qt::SolidPattern));

    // draw the canvas
    QRect drawArea(QPoint(0, 0), _canvasSize);
    drawArea.moveCenter(event->rect().center());
    gc.fillRect(drawArea, QBrush(QColor(255, 255, 255, 255), Qt::SolidPattern));

    // done
    event->accept();
    gc.end();
}
