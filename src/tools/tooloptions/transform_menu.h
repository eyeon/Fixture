#ifndef TRANSFORMOPTIONS_H
#define TRANSFORMOPTIONS_H

#include <QFrame>

namespace Ui {
class TransformOptions;
}

class TransformMenu : public QFrame
{
    Q_OBJECT

public:
    explicit TransformMenu(QWidget *parent = 0);
    ~TransformMenu();

private:
    Ui::TransformOptions *ui;
};

#endif // TRANSFORMOPTIONS_H
