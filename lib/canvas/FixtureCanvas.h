#pragma once

#include <QWidget>
#include <QPaintEvent>

namespace Fixture {
class PaintWidget;

class Canvas : public QWidget {
    Q_OBJECT
public:
    Canvas(QWidget *widget, QSize canvasSize);
protected:
    void paintEvent(QPaintEvent *event);
private:
    friend class Fixture::PaintWidget;
    QSize _canvasSize;
};
}
