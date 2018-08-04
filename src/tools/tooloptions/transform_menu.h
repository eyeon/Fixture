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
    explicit TransformMenu(QWidget * parent = nullptr);
    ~TransformMenu();

public slots:
    void enterTransformMode(bool enter);

private slots:
    void on_showTransfromCheck_stateChanged(int arg1);
    void on_autoSelectCheck_stateChanged(int arg1);
    void on_acceptBtn_clicked();
    void on_rejectBtn_clicked();

signals:
    void autoSelect(bool check);
    void showTransform(bool show);
    void changesAccepted(bool accept);

private:
    Ui::TransformOptions * ui;
};

#endif // TRANSFORMOPTIONS_H
