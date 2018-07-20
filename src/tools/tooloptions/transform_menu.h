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

    void on_acceptBtn_clicked();

    void on_rejectBtn_clicked();

signals:
    void autoSelect(bool check);
    void showTransform(bool show);
    void accept();
    void reject();

private:
    Ui::TransformOptions *ui;

    void enterTransformMode(bool enter);
};

#endif // TRANSFORMOPTIONS_H
