#ifndef TRANSFORMOPTIONS_H
#define TRANSFORMOPTIONS_H

#include "toolmenu.h"

namespace Ui {
class TransformOptions;
}

class TransformMenu : public ToolMenu
{
    Q_OBJECT

public:
    explicit TransformMenu(QWidget *parent = 0);
    ~TransformMenu();

private slots:
    void on_showTransfromCheck_stateChanged(int arg1);
    void on_autoSelectCheck_stateChanged(int arg1);

signals:
    void autoSelect(bool check);
    void showTransform(bool show);

private:
    Ui::TransformOptions *ui;
};

#endif // TRANSFORMOPTIONS_H
