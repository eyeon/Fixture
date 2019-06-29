#include "PaintWidget.h"

Fixture::PaintWidget::PaintWidget(QWidget *parent) :
    QAbstractScrollArea(parent)
{
    _canvas = FixtureCanvasSP(new Fixture::Canvas(parent, QSize(200, 200)));
    setViewport(_canvas.get());
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
}

void
Fixture::PaintWidget::paintEvent(QPaintEvent * event)
{
    _canvas->paintEvent(event);
}
