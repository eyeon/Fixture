#include "PaintWidget.h"

Fixture::PaintWidget::PaintWidget(QWidget *parent):
    QAbstractScrollArea(parent)
{
    _canvas = new Fixture::Canvas(parent,QSize(200,200));
    setViewport(_canvas);
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
}

void
Fixture::PaintWidget::paintEvent(QPaintEvent *event)
{
    _canvas->paintEvent(event);
}
