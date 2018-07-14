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

private slots:
    void on_pushButton_clicked();

private:
    Ui::TransformOptions *ui;
};

#endif // TRANSFORMOPTIONS_H
