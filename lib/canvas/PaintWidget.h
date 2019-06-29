#pragma once

#include <QAbstractScrollArea>
#include <QSharedPointer>

#include "FixtureCanvas.h"

typedef QSharedPointer<Fixture::Canvas> FixtureCanvasSP;

namespace Fixture {
class PaintWidget : public QAbstractScrollArea {
    Q_OBJECT
public:
    PaintWidget(QWidget *parent);
protected:
    void paintEvent(QPaintEvent *event);

private:
    FixtureCanvasSP _canvas;
};
}
